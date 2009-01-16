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

Info::Info(QWidget *parent)
    : QWidget(parent),
	  id(-1)
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
	case 1:
		break;
	case 2:
		break;
	}
}

void Info::setCurrent(int _id)
{
	id = _id;
}

void Info::setCurrent(QString artist, QString album, QString song)
{
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
	Database::Self().subsetAlbum(Database::Self().AddAlbum(album, Database::Self().AddArtist(artist)));
	attral = Database::Self().Albums();
	if(attral.size()) {
		if(attral[0].art.size()) {
			art = attral[0].art;
			rating = attral[0].rating;
		}
		//text = tr("%n song(s)", "", attral[0].refs);
	}
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
			if(s == title) {
				rating = r;
				break;
			}
		}
	}
	ui.label_so1->setText(song);
	ui.songRating->setStarRating(StarRating(rating));
	ui.songRating->noEdit();
	Database::Self().popSubset();
}

void Info::slot_ban()
{
	emit ban();
}

void Info::slot_loveIt()
{
	emit loveIt();
}

void Info::slot_rateUp()
{
	emit rateUp();
}

void Info::slot_rateDown()
{
	emit rateDown();
}
