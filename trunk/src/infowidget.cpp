/* Cuberok
 * Copyright (C) 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "infowidget.h"
#include "database.h"

/************
 *
 *   ItemWidget
 *
 ************/

ItemWidget::ItemWidget(const QPixmap &pm, QString n, QString a, const StarRating &r, int level, QWidget *parent) 
	: QWidget(parent)
{
	QHBoxLayout *layout = new QHBoxLayout(this);
	layout->setContentsMargins(level ? 16 : 4, 4, 4, 4);
	layout->setSpacing(4);
	int picsize = 0;
	switch(level) {
	case 0: picsize = 128; break;
	case 1: picsize = 64; break;
	case 2: picsize = 32; break;
	case 3: picsize = 16; break;
	}
	QPixmap pm2 = pm.size().height() > pm.size().width() ? pm.scaledToHeight(picsize, Qt::SmoothTransformation) : pm.scaledToWidth(picsize, Qt::SmoothTransformation);
	pic = new QLabel(this);
	pic->setPixmap(pm2);
	pic->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	layout->addWidget(pic);
	QFrame *frame = new QFrame(this);
	QVBoxLayout *layout2 = new QVBoxLayout(frame);
	frame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	layout2->setContentsMargins(4, 4, 4, 4);
	layout2->setSpacing(4);
	name = new QLabel(n, this);
	layout2->addWidget(name);
	if(level < 2) {
		appendix = new QLabel(a, this);
		layout2->addWidget(appendix);
	}
	if(!level) {
		QFont font = name->font();
		font.setBold(true);
		name->setFont(font);
		appendix->setFont(font);
	}
	//StarRating sr(r, 5, 2);
	rating = new StarEditor(this);
	rating->setStarRating(r);
	rating->noEdit();
	layout2->addWidget(rating);
	layout2->addStretch();
	layout2->setSizeConstraint(QLayout::SetFixedSize);
	layout->addWidget(frame);
	layout->addStretch();
	layout->setSizeConstraint(QLayout::SetFixedSize);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

/************
 *
 *   InfoWidget
 *
 ************/

InfoWidget::InfoWidget(QWidget *parent) : QTreeWidget(parent), ar(0), al(0)
{
	setColumnCount(2);
	setColumnHidden(0, true);
	setArtist("");
	setAlbum("");
	header()->hide();
}

void InfoWidget::setArtist(QString a)
{
	if(a == artist) return;
	if(ar) {
		delete ar;
		ar = 0;
	}
	if(!a.size() || a == " ") return;
	ar = new QTreeWidgetItem(this);
	artist = a;
	QString art(":/icons/def_artist.png"), text;
	int rating = 0;
	QList<struct Database::Attr> attrs;
	Database::Self().pushSubset();
	Database::Self().subsetArtist(a);
	attrs = Database::Self().Artists();
	if(attrs.size()) {
		if(attrs[0].art.size()) {
			art = attrs[0].art;
			rating = attrs[0].rating;
		}
	}
	while(ar->childCount()) delete ar->child(0);
	QList<struct Database::AttrAl> attral;
	attral = Database::Self().Albums();
	int alb_count = 0;
	foreach(struct Database::AttrAl attr, attral) {
		if(!attr.name.size() || attr.name == " ") continue;
		alb_count ++;
		QTreeWidgetItem *it = new QTreeWidgetItem(ar);
// 		it->setIcon(1, attr.art.size() ? QIcon(attr.art) : QIcon(":/icons/def_album.png"));
// 		it->setText(1, attr.name+"\n"+tr("%n song(s)", "", attr.refs));
// 		//it->setSizeHint(1, it->icon(1).actualSize(QSize(64, 64)));
		setItemWidget(it, 1, new ItemWidget(QPixmap(attr.art.size() ? attr.art : ":/icons/def_album.png"), attr.name, tr("%n song(s)", "", attr.refs), StarRating(attr.rating, 5, 2), 1, this));
		it->setSizeHint(1, itemWidget(it, 1)->sizeHint());
	}
	if(alb_count)
		text = tr("%n album(s)", "", alb_count);
// 	ar->setIcon(1, QIcon(art));
// 	ar->setText(1, text);
// 	//ar->setSizeHint(1, ar->icon(1).actualSize(QSize(128,128)));
// 	ar->setBackground(1, QApplication::palette().brush(QPalette::Inactive, QPalette::Highlight));
// 	QFont font = ar->font(1);
// 	font.setBold(true);
// 	ar->setFont(1, font);
	setItemWidget(ar, 1, new ItemWidget(QPixmap(art), artist, text, StarRating(rating, 5, 2), 0, this));
	ar->setSizeHint(1, itemWidget(ar, 1)->sizeHint());
	Database::Self().popSubset();
	collapseItem(ar);
}

void InfoWidget::setAlbum(QString a)
{
	if(a == album) return;
	if(al) {
		delete al;
		al = 0;
	}
	if(!a.size() || a == " ") return;
	al = new QTreeWidgetItem(this);
	album = a;
	QString art(":/icons/def_album.png"), text;
	int rating = 0;
	QList<struct Database::AttrAl> attrs;
	Database::Self().pushSubset();
	Database::Self().subsetArtist(artist);
	Database::Self().subsetAlbum(Database::Self().AddAlbum(a, Database::Self().AddArtist(artist)));
	attrs = Database::Self().Albums();
	if(attrs.size()) {
		if(attrs[0].art.size()) {
			art = attrs[0].art;
			rating = attrs[0].rating;
		}
		text = tr("%n song(s)", "", attrs[0].refs);
	}
// 	al->setIcon(1, QIcon(art));
// 	al->setText(1, text);
// 	//al->setSizeHint(1, al->icon(1).actualSize(QSize(128,128)));
// 	al->setBackground(1, QApplication::palette().brush(QPalette::Inactive, QPalette::Highlight));
// 	QFont font = al->font(1);
// 	font.setBold(true);
// 	al->setFont(1, font);
	setItemWidget(al, 1, new ItemWidget(QPixmap(art), album, text, StarRating(rating, 5, 2), 0, this));
	al->setSizeHint(1, itemWidget(al, 1)->sizeHint());
	while(al->childCount()) delete al->child(0);
	QList<QString> songs = Database::Self().Songs();
	foreach(QString song, songs) {
		QString title, artist, album, comment, genre, length;
		int track, year, rating;
		Database::Self().GetTags(song, title, artist, album, comment, genre, track, year, rating, length);
		QTreeWidgetItem *it = new QTreeWidgetItem(al);
// 		it->setText(1, title);
// 		it->setIcon(1, QIcon(":/icons/def_song.png"));
		setItemWidget(it, 1, new ItemWidget(QPixmap(":/icons/def_song.png"), title, "", StarRating(rating, 5, 1), 2, this));
		it->setSizeHint(1, itemWidget(it, 1)->sizeHint());
	}
	Database::Self().popSubset();
	collapseItem(al);
}
