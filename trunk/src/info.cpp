/* Cuberok
 * Copyright (C) 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>
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

#include "info.h"
#include "database.h"
#include "lastfm.h"
#include "lyricwiki.h"
#include "console.h"
#include "playlistsettings.h"

#include <QtXml>

Info::Info(QWidget *parent)
    : QWidget(parent),
	  id(-1),
	  ar_complete(false),
	  al_complete(false),
	  ar_pic(false),
	  al_pic(false),
	  w_ar(0),
	  w_al(0),
	  w_ly(0)
{
	ui.setupUi(this);
	QSettings set;
	ui.actionShow_Song->setChecked(set.value("info_show_song", true).toBool());
	ui.actionShow_Album_Image->setChecked(set.value("info_show_album_image", true).toBool());
	ui.actionShow_Album_Title->setChecked(set.value("info_show_album_title", true).toBool());
	ui.actionShow_Artist_Image->setChecked(set.value("info_show_artist_image", false).toBool());
	ui.actionShow_Artist_Name->setChecked(set.value("info_show_artist_name", false).toBool());
	connect(qApp, SIGNAL(commitDataRequest(QSessionManager&)), this, SLOT(storeState()), Qt::DirectConnection);
	connect(qApp, SIGNAL(saveStateRequest(QSessionManager&)), this, SLOT(storeState()), Qt::DirectConnection);
	connect(&downloader, SIGNAL(complete(QString)), this, SLOT(dlComplete(QString)));
	connect(&downloader, SIGNAL(cancel(QString)), this, SLOT(dlCancel(QString)));
}

Info::~Info()
{
	storeState();
}

void Info::storeState()
{
	QSettings set;
	set.setValue("info_show_song", ui.actionShow_Song->isChecked());
	set.setValue("info_show_album_image", ui.actionShow_Album_Image->isChecked());
	set.setValue("info_show_album_title", ui.actionShow_Album_Title->isChecked());
	set.setValue("info_show_artist_image", ui.actionShow_Artist_Image->isChecked());
	set.setValue("info_show_artist_name", ui.actionShow_Artist_Name->isChecked());
}

void Info::tabChanged(int t)
{
	switch(t) {
	case 0:
		break;
	case 1: if(!ar_complete && ar.size()) {
		QString text;
		if(ar_mbid.size()) {
			text = Database::Self().getInfo(ar_mbid);
		}
		if(!text.size()) {
			if(!connect(&LastFM::Self(), SIGNAL(xmlInfo(QString)), this, SLOT(artistInfo(QString))))
				Console::Self().error("Unable connection to xmlInfo");
			LastFM::Self().artistInfo(ar);
		} else {
			ui.textEdit->setHtml(text);
			ui.textEdit->update();
			if(w_ar) {
				w_ar->setText(text);
			}
			ar_complete = true;
		}
	}
		break;
	case 2: if(!al_complete && al.size()) {
		QString text;
		if(al_mbid.size()) {
			text = Database::Self().getInfo(al_mbid);
		}
		if(!text.size()) {
			if(!connect(&LastFM::Self(), SIGNAL(xmlInfo(QString)), this, SLOT(albumInfo(QString))))
				Console::Self().error("Unable connection to xmlInfo");
			LastFM::Self().albumInfo(ar, al);
		} else {
			ui.textEdit_2->setHtml(text);
			ui.textEdit_2->update();
			if(w_al) {
				w_al->setText(text);
			}
			al_complete = true;
		}
	}
		break;
	}
}

void Info::setCurrent(int _id)
{
	id = _id;
}

void Info::setCurrent(QString artist, QString album, QString song)
{
	const int MAXLEN = 25;
	ar_pic = false;
	al_pic = false;
	if(ar != artist) {
		ar_complete = false;
		ui.textEdit->setText("");
	}	
	if(al != album) {
		al_complete = false;
		ui.textEdit_2->setText("");
	}
	ar = artist;
	al = album;
	so = song;
	if(Database::Self().GetArtist(artist) <= 0 || Database::Self().GetAlbum(album, Database::Self().GetArtist(artist)) <= 0) {
		ui.actionBan->setDisabled(true);
		ui.actionRateDown->setDisabled(true);
		ui.actionRateUp->setDisabled(true);
		ui.actionLoveIt->setDisabled(true);
		//return;
	} else {
		ui.actionBan->setDisabled(false);
		ui.actionRateDown->setDisabled(false);
		ui.actionRateUp->setDisabled(false);
		ui.actionLoveIt->setDisabled(false);
	}
	QString art(":/icons/def_artist.png"), text;
	int rating = 0;
 	QList<struct Database::Attr> attrs;
 	Database::Self().pushSubset();
 	Database::Self().subsetArtist(artist);
 	attrs = Database::Self().Artists();
 	if(attrs.size()) {
 		if(attrs[0].art.size()) {
 			art = attrs[0].art;
			ar_pic = true;
 		}
		rating = attrs[0].rating;
		ar_mbid = attrs[0].mbid;
 	} else	ar_mbid = "";
	int picsize = 128;
	QPixmap pm = QPixmap(art);
	QPixmap pm2 = pm.size().height() > pm.size().width() ? pm.scaledToHeight(picsize, Qt::SmoothTransformation) : pm.scaledToWidth(picsize, Qt::SmoothTransformation);
 	ui.label_ar0->setPixmap(pm2);
 	ui.label_ar0->setMinimumSize(pm2.size());
 	ui.label_ar0->setMaximumSize(pm2.size());
	if(artist.size() > MAXLEN) artist = artist.left(MAXLEN) + "...";
 	ui.label_ar1->setText(artist);
	ui.artistRating->setStarRating(StarRating(rating, 5, 2));
	ui.artistRating->noEdit();
 	QList<struct Database::AttrAl> attral;
// 	attral = Database::Self().Albums();
// 	int alb_count = 0;
// 	foreach(struct Database::AttrAl attr, attral) {
// 		if(!attr.name.size() || attr.name == " ") continue;
// 		alb_count ++;
// 	}
	//if(alb_count)
	//ui.label_ar2->setText(tr("%n album(s)", "", alb_count));
	//setItemWidget(ar, 1, new ItemWidget(QPixmap(art), artist, text, StarRating(rating, 5, 2), 0, this));
 	Database::Self().popSubset();


	QString art_al = ":/icons/def_album.png";
	rating = 0;
	attral.clear();
	Database::Self().pushSubset();
	Database::Self().subsetArtist(artist);
	//QList<struct Database::Attr> attrs;
	Database::Self().subsetAlbum(Database::Self().AddAlbum(album, Database::Self().AddArtist(artist)));
	attral = Database::Self().Albums();
	if(attral.size()) {
		if(attral[0].art.size()) {
			art_al = attral[0].art;
			al_pic = true;
		}
		rating = attral[0].rating;
		al_mbid = attral[0].mbid;
		//text = tr("%n song(s)", "", attral[0].refs);
	} else al_mbid = "";
	pm = QPixmap(art_al);
	pm2 = pm.size().height() > pm.size().width() ? pm.scaledToHeight(picsize, Qt::SmoothTransformation) : pm.scaledToWidth(picsize, Qt::SmoothTransformation);
	ui.label_al0->setPixmap(pm2);
	ui.label_al0->setMinimumSize(pm2.size());
	ui.label_al0->setMaximumSize(pm2.size());
	if(album.size() > MAXLEN) album = album.left(MAXLEN) + "...";
	ui.label_al1->setText(album);
	//ui.label_al2->setText(text)
	ui.albumRating->setStarRating(StarRating(rating, 5, 2));
	ui.albumRating->noEdit();

	QList<QString> songs = Database::Self().Songs(0, 0, 0, &song);
	rating = 0;
	if(songs.size() > 0) {
		foreach(QString s, songs) {
			QString title, artist, album, comment, genre, length;
			int track, year, r;
			Database::Self().GetTags(s, title, artist, album, comment, genre, track, year, r, length);
			if(song == title) {
				rating = r;
				break;
			} 
		}
	}
	if(song.size()>MAXLEN) song = song.left(MAXLEN) + "...";
	ui.label_so1->setText(song);
	ui.songRating->setStarRating(StarRating(rating));
	ui.songRating->noEdit();
	Database::Self().popSubset();

	tabChanged(ui.tabWidget->currentIndex());
}

void Info::slot_ban()
{
	emit ban();
	updateRating();
}

void Info::slot_loveIt()
{
	emit loveIt();
	updateRating();
}

void Info::slot_rateUp()
{
	emit rateUp();
	updateRating();
}

void Info::slot_rateDown()
{
	emit rateDown();
	updateRating();
}

void Info::updateRating()
{
	int rating = 0;
	Database::Self().pushSubset();
	Database::Self().subsetArtist(ar);
	Database::Self().subsetAlbum(Database::Self().AddAlbum(al, Database::Self().AddArtist(ar)));
 	QList<struct Database::AttrAl> attral;
	attral = Database::Self().Albums();
	if(attral.size()) {
		if(attral[0].art.size()) {
			rating = attral[0].rating;
		}
	}
	ui.albumRating->setStarRating(StarRating(rating));
	ui.albumRating->noEdit();
	ui.albumRating->update();
	QList<QString> songs = Database::Self().Songs(0, 0, 0, &so);
	rating = 0;
	if(songs.size() > 0) {
		foreach(QString s, songs) {
			QString title, artist, album, comment, genre, length;
			int track, year, r;
			Database::Self().GetTags(s, title, artist, album, comment, genre, track, year, r, length);
			if(so == title) {
				rating = r;
				break;
			} 
		}
	}
	ui.songRating->setStarRating(StarRating(rating));
	ui.songRating->noEdit();
	ui.songRating->update();
	Database::Self().popSubset();
}

void Info::artistInfo(QString response)
{
	disconnect(&LastFM::Self(), SIGNAL(xmlInfo(QString)), this, SLOT(artistInfo(QString)));
	QDomDocument doc;
	QDomElement el, el2;
	QDomNodeList list;
	if(doc.setContent(response)) {
		el = doc.documentElement();
		//el = el.firstChildElement("lfm");
		if(!el.isNull()) {
			QString s = el.attribute("status");
			if(s == "ok") {
				el2 = el.firstChildElement("artist");
				if(!el2.isNull()) {  // proceed artist info
					el = el2;
					el2 = el.firstChildElement("name");
					QString name;
					if(!el2.isNull()) name = el2.firstChild().nodeValue();
					QString mbid;
					el2 = el.firstChildElement("mbid");
					if(!el2.isNull()) mbid = el2.firstChild().nodeValue();
					Database::Self().MbidForArtist(ar, mbid);
					el2 = el.firstChildElement("bio");
					if(!el2.isNull()) {
						el2 = el2.firstChildElement("content");
						if(!el2.isNull()) {
							QString info = el2.firstChild().nodeValue();
							if(info.size()) {
								info = "<html><body>" + info + "</html></body>";
								if(PLSet.cacheInfo && mbid.size())
									Database::Self().setInfo(mbid, info);
								ui.textEdit->setHtml(info);
								ui.textEdit->update();
								if(w_ar) {
									w_ar->setText(info);
								}
								ar_complete = true;
							}
						}
					}
				}
			}
		}
	}
}

void Info::albumInfo(QString response)
{
	disconnect(&LastFM::Self(), SIGNAL(xmlInfo(QString)), this, SLOT(albumInfo(QString)));
	QDomDocument doc;
	QDomElement el, el2;
	QDomNodeList list;
	if(doc.setContent(response)) {
		el = doc.documentElement();
		//el = el.firstChildElement("lfm");
		if(!el.isNull()) {
			QString s = el.attribute("status");
			if(s == "ok") {
				el2 = el.firstChildElement("album");
				if(!el2.isNull()) {  // proceed album info
					el = el2;
					el2 = el.firstChildElement("name");
					QString name;
					if(!el2.isNull()) name = el2.firstChild().nodeValue();
					QString mbid;
					el2 = el.firstChildElement("mbid");
					if(!el2.isNull()) mbid = el2.firstChild().nodeValue();
					Database::Self().MbidForAlbum(al, mbid, Database::Self().GetArtist(ar));
					el2 = el.firstChildElement("wiki");
					if(!el2.isNull()) {
						el2 = el2.firstChildElement("content");
						if(!el2.isNull()) {
							QString info = el2.firstChild().nodeValue();
							if(info.size()) {
								info = "<html><body>" + info + "</html></body>";
								if(PLSet.cacheInfo && mbid.size())
									Database::Self().setInfo(mbid, info);
								ui.textEdit_2->setHtml(info);
								ui.textEdit_2->update();
								if(w_al) {
									w_al->setText(info);
								}
								al_complete = true;
							}
						}
					}
				}
			}
		}
	}
}

void Info::lyricInfo(QString response)
{
	disconnect(&LyricWiki::Self(), SIGNAL(xmlInfo(QString)), this, SLOT(lyricInfo(QString)));
	if(w_ly) {
		w_ly->setText(response);
	}
}

void Info::showArtist()
{
	if(w_ar) {
		w_ar->close();
		delete w_ar;
		w_ar = 0;
	} else {
		w_ar = new InfoWindow(this);
		w_ar->setWindowTitle(ar);
		connect(w_ar, SIGNAL( destroyed(QObject*)), this, SLOT(artistClosed(QObject*)));
		w_ar->show();
		if(ar_complete)
			w_ar->setText(ui.textEdit->toHtml());
		else 
			tabChanged(1);
	}
}

void Info::showAlbum()
{
	if(w_al) {
		w_al->close();
		delete w_al;
		w_al = 0;
	} else {
		w_al = new InfoWindow(this);
		w_al->setWindowTitle(al);
		connect(w_al, SIGNAL( destroyed(QObject*)), this, SLOT(albumClosed(QObject*)));
		w_al->show();
		if(al_complete)
			w_al->setText(ui.textEdit_2->toHtml());
		else 
			tabChanged(2);
	}
}

void Info::showLyric()
{
	if(w_ly) {
		w_ly->close();
		delete w_ly;
		w_ly = 0;
	} else {
		w_ly = new InfoWindow(this);
		w_ly->setWindowTitle(so);
		connect(w_ly, SIGNAL( destroyed(QObject*)), this, SLOT(lyricClosed(QObject*)));
		w_ly->show();
		connect(&LyricWiki::Self(), SIGNAL(xmlInfo(QString)), this, SLOT(lyricInfo(QString)));
		LyricWiki::Self().getSong(ar, so);
	}
}

void Info::artistClosed(QObject*)
{
	w_ar = 0;
}

void Info::albumClosed(QObject*)
{
	w_al = 0;
}

void Info::lyricClosed(QObject*)
{
	w_ly = 0;
}

void Info::getImages()
{
	connect(&LastFM::Self(), SIGNAL(xmlInfo(QString)), this, SLOT(infoResponse(QString)));
	if(!al_pic) {
		LastFM::Self().albumInfo(ar, al);
	} else if(!ar_pic) {
		LastFM::Self().artistInfo(ar);
	}
}

void Info::infoResponse(QString info)
{
	disconnect(&LastFM::Self(), SIGNAL(xmlInfo(QString)), this, SLOT(infoResponse(QString)));
	QString newArtist, newAlbum, mbid, imageUrl, information;
	if(LastFM::Self().parseInfo(info, newArtist, newAlbum, mbid, imageUrl, information)) {
		if(imageUrl.size() && downloader.done()) {
			downloader.download(imageUrl);
			return;
		}
	}
	if(!al_pic) {
		al_pic = true;
	} else {
		ar_pic = true;
	}
}

void Info::dlComplete(QString file)
{
	Database::Self().AddArtist(ar);
	QList<QString> data;
	if(!al_pic)
		data = Database::Self().Songs(&ar, Database::Self().AddAlbum(al, Database::Self().AddArtist(ar)), 0);
	else
		data = Database::Self().Songs(&ar, 0, 0);
	QString path = "";
	if(data.size()) {
		path = QFileInfo(data[0]).canonicalPath();
		foreach(QString str, data) {
			path = Database::commonPath(path, QFileInfo(str).canonicalPath());
		}
		path += QDir::separator();
	} 
	if(path == "" || path == "/") path = QDir::homePath() + "/.cuberok/artcache/";
	QDir dir;
	if(dir.mkpath(path)) {
		QString file2 = path + ar;
		if(!al_pic) file2 += "-"+al;
		file2 += "."+QFileInfo(file).suffix();
		if(QFile::exists(file2)) QFile::remove(file2);
		if(QFile::copy(file, file2)) {
			QFile::remove(file);
			if(!al_pic) {  // cover for album
				Database::Self().ArtForAlbum(al, file2, Database::Self().AddArtist(ar));
			} else {  // image for artist
				Database::Self().ArtForArtist(ar, file2);
			}
		}
	}
	setCurrent(ar, al, so);
}

void Info::dlCancel(QString)
{
	if(!al_pic) {
		al_pic = true;
	} else {
		ar_pic = true;
	}
}
