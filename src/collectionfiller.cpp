/* Cuberok
 * Copyright (C) 2009 Vasiliy Makarov <drmoriarty.0@gmail.com>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this software; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "collectionfiller.h"
#include "database.h"
#include "indicator.h"
#include "main.h"
#include "console.h"
#include "tagger.h"

/************************
 *
 *   CollectionFiller
 *
 ************************/

CollectionFiller::CollectionFiller(QList<QUrl> _urls, ListMode _mode, QString _attrname, int _param, QObject * parent) 
	: QThread(parent), urls(_urls), mode(_mode), attrname(_attrname), param(_param)
{
	cancel = false;
	connect(&Indicator::Self(), SIGNAL(userStop()), this, SLOT(cancelEvent()), Qt::QueuedConnection);
	connect(this, SIGNAL(internalUpdate()), &Indicator::Self(), SLOT(update()), Qt::QueuedConnection);
}

CollectionFiller::~CollectionFiller()
{
	disconnect(&Indicator::Self(), SIGNAL(userStop()), this, SLOT(cancel()));
}

void CollectionFiller::run()
{
	int taskID = Indicator::Self().addTask(tr("Collect music"));
	foreach(QUrl url, urls) {
		if(cancel) break;
		proceed(ToLocalFile(url));
	}
	Indicator::Self().delTask(taskID);
}

int CollectionFiller::proceed(QString path)
{
	if(cancel) return -1;
	emit internalUpdate();
	QDir dir;
	if(dir.cd(path)) {
		int count = 0;
		QString _album, _artist;
		QStringList covers;
		foreach(QString file, dir.entryList()) {
			if(file == "." || file == "..") continue;
			if(proceed(dir.filePath(file)) > 0) {
				count ++;
				QString title, artist, album, comment, genre, length;
				int track, year, rating;
				Database::Self().GetTags(dir.filePath(file), title, artist, album, comment, genre, track, year, rating, length);
				if(count > 1) {
					if(_album != album) _album = "";
					if(_artist != artist) _artist = "";
				} else {
					_album = album;
					_artist = artist;
				}
			} else {
				QString p2 = file.toLower();
				if(p2.endsWith(".jpg") || p2.endsWith(".png") || p2.endsWith(".gif") || p2.endsWith(".bmp")) {
					covers << dir.filePath(file);
				}
			}
		}
		QString cover;
		qint64 fsize = 0;
		foreach(QString cvr, covers) {
			qint64 s2 = QFileInfo(cvr).size();
			if(s2 > fsize) {
				fsize = s2;
				cover = cvr;
			}
		}
		if(cover.size() && _album.size() && _album != " " && _artist.size() && _artist != " ") {
			Database::Self().ArtForAlbum(_album, cover, Database::Self().AddArtist(_artist));
			Console::Self().log("set album cover" + cover);
		} else if(cover.size() && _artist.size() && _artist != " ") {
			Database::Self().ArtForArtist(_artist, cover);
			Console::Self().log("set artist cover" + cover);
		}
	} else {
		QString p2 = path.toLower();
		// check playlists
		if(p2.endsWith(".m3u") || p2.endsWith(".xspf") || p2.endsWith(".asx") || p2.endsWith(".asp") || p2.endsWith(".cue")) {
			return Database::Self().AddPlaylist(path);
		}
		// drop into item
		if(attrname.length()) {
			// check images
			if(p2.endsWith(".jpg") || p2.endsWith(".png") || p2.endsWith(".gif") || p2.endsWith(".bmp")) {
				switch(mode) {
				case M_ALBUM:
					Database::Self().ArtForAlbum(attrname, path, param);
					break;
				case M_ARTIST:
					Database::Self().ArtForArtist(attrname, path);
					break;
				case M_GENRE:
					Database::Self().ArtForGenre(attrname, path);
					break;
				case M_SONG:
					break;
				case M_LIST:
					Database::Self().ArtForPlaylist(attrname, path);
					break;
				case M_SQLLIST:
					break;
				}
				return -1;
			}
			// check songs
			QString title, artist, album, comment, genre, length;
			int track, year, rating;
			bool exist = Database::Self().GetTags(path, title, artist, album, comment, genre, track, year, rating, length);
			switch(mode) {
			case M_ALBUM:
				Tagger::updateAlbum(path, attrname);
				album = attrname;
				break;
			case M_ARTIST:
				Tagger::updateArtist(path, attrname);
				artist = attrname;
				break;
			case M_GENRE:
				Tagger::updateGenre(path, attrname);
				genre = attrname;
				break;
			case M_SONG:
				return -1;
			case M_LIST:
				// TODO
				return -1;
			case M_SQLLIST:
				return -1;
			}
			if(exist) Database::Self().SetTags(path, title, artist, album, comment, genre, track, year, rating); 
			else return Database::Self().AddFile(path);
		} else return Database::Self().AddFile(path);
	}
	return -1;
}

void CollectionFiller::cancelEvent()
{
	cancel = true;
}


