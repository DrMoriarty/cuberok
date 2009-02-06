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
#include "console.h"
#include "playlistsettings.h"

#include <QtXml>

Info::Info(QWidget *parent)
    : QWidget(parent),
	  id(-1),
	  ar_complete(false),
	  al_complete(false)
{
	ui.setupUi(this);
}

Info::~Info()
{
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
	QString art(":/icons/def_artist.png"), text;
	int rating = 0;
// 	QList<struct Database::Attr> attrs;
// 	Database::Self().pushSubset();
// 	Database::Self().subsetArtist(artist);
// 	attrs = Database::Self().Artists();
// 	if(attrs.size()) {
// 		if(attrs[0].art.size()) {
// 			art = attrs[0].art;
// 			rating = attrs[0].rating;
// 		}
// 	}
	int picsize = 128;
	QPixmap pm = QPixmap(art);
	QPixmap pm2 = pm.size().height() > pm.size().width() ? pm.scaledToHeight(picsize, Qt::SmoothTransformation) : pm.scaledToWidth(picsize, Qt::SmoothTransformation);
// 	ui.label_ar0->setPixmap(pm2);
// 	ui.label_ar0->setMinimumSize(pm2.size());
// 	ui.label_ar0->setMaximumSize(pm2.size());
// 	ui.label_ar1->setText(artist);
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
// 	Database::Self().popSubset();


	art = ":/icons/def_album.png";
	rating = 0;
	attral.clear();
	Database::Self().pushSubset();
	Database::Self().subsetArtist(artist);
	QList<struct Database::Attr> attrs;
	attrs = Database::Self().Artists();
	if(attrs.size()) {
		ar_mbid = attrs[0].mbid;
	} else ar_mbid = "";
	Database::Self().subsetAlbum(Database::Self().AddAlbum(album, Database::Self().AddArtist(artist)));
	attral = Database::Self().Albums();
	if(attral.size()) {
		if(attral[0].art.size()) {
			art = attral[0].art;
		}
		rating = attral[0].rating;
		al_mbid = attral[0].mbid;
		//text = tr("%n song(s)", "", attral[0].refs);
	} else al_mbid = "";
	pm = QPixmap(art);
	pm2 = pm.size().height() > pm.size().width() ? pm.scaledToHeight(picsize, Qt::SmoothTransformation) : pm.scaledToWidth(picsize, Qt::SmoothTransformation);
	ui.label_al0->setPixmap(pm2);
	ui.label_al0->setMinimumSize(pm2.size());
	ui.label_al0->setMaximumSize(pm2.size());
	ui.label_al1->setText(album);
	//ui.label_al2->setText(text)
	ui.albumRating->setStarRating(StarRating(rating));
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
	disconnect(&LastFM::Self(), SLOT(xmlInfo(QString)), this, SIGNAL(artistInfo(QString)));
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
	disconnect(&LastFM::Self(), SLOT(xmlInfo(QString)), this, SIGNAL(albumInfo(QString)));
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
					Database::Self().MbidForAlbum(al, mbid, Database::Self().AddArtist(ar));
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
								al_complete = true;
							}
						}
					}
				}
			}
		}
	}
}
