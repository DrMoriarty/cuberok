/* Cuberok
 * Copyright (C) 2009 Vasiliy Makarov <drmoriarty.0@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "libraryfiller.h"
#include "library_db.h"
#include "tagger.h"

/************************
 *
 *   LibraryFiller
 *
 ************************/

LibraryFiller::LibraryFiller(QList<QUrl> _urls, QString _attrname, int _param, QObject * parent) 
	: QThread(parent), urls(_urls), attrname(_attrname), param(_param)
{
	cancel = false;
	//connect(&Indicator::Self(), SIGNAL(userStop()), this, SLOT(cancelEvent()), Qt::QueuedConnection);
	//connect(this, SIGNAL(internalUpdate()), &Indicator::Self(), SLOT(update()), Qt::QueuedConnection);
}

LibraryFiller::~LibraryFiller()
{
	//disconnect(&Indicator::Self(), SIGNAL(userStop()), this, SLOT(cancel()));
}

void LibraryFiller::run()
{
	//int taskID = Indicator::Self().addTask(tr("Collect music"));
	foreach(QUrl url, urls) {
		if(cancel) break;
		proceed(ToLocalFile(url));
	}
	//Indicator::Self().delTask(taskID);
}

int LibraryFiller::proceed(QString path)
{
	if(cancel) return -1;
	emit internalUpdate();
	QDir dir;
	if(dir.cd(path)) {
		foreach(QString file, dir.entryList()) {
			if(file == "." || file == "..") continue;
			if(proceed(dir.filePath(file)) > 0) {
			}
		}
	} else {
		QString p2 = path.toLower();
		// check playlists
		if(Tagger::playlistDetected(QUrl::fromLocalFile(path))) {
			return LibraryDB::Self().AddPlaylist(path);
		}
		// drop into item
		if(attrname.length()) {
			// check images
			if(p2.endsWith(".jpg") || p2.endsWith(".png") || p2.endsWith(".gif") || p2.endsWith(".bmp")) {
				LibraryDB::Self().ArtForPlaylist(attrname, path);
				return -1;
			}
			return -1;
		}
	}
	return -1;
}

void LibraryFiller::cancelEvent()
{
	cancel = true;
}


