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

#ifndef INFO_H
#define INFO_H

#include <QtGui>
#include "ui_info.h"
#include "infowindow.h"

class Info: public QWidget
{
	Q_OBJECT

public:
	Info(QWidget *parent = 0);
	~Info();

 private:
	Ui::Info ui;
	int id;
	QString ar, al, so, ar_mbid, al_mbid;
	bool ar_complete, al_complete;
	InfoWindow *w_ar, *w_al, *w_ly;

	void updateRating();

 signals:
	void ban();
	void rateDown();
	void rateUp();
	void loveIt();
	
 public slots:
	void slot_ban();
	void slot_rateDown();
	void slot_rateUp();
	void slot_loveIt();
	void tabChanged(int);
	void setCurrent(int id);
	void setCurrent(QString artist, QString album, QString song);
	void showArtist();
	void showAlbum();
	void showLyric();
	
 private slots:
	void artistInfo(QString);
	void albumInfo(QString);
	void lyricInfo(QString);
	void artistClosed(QObject*);
	void albumClosed(QObject*);
	void lyricClosed(QObject*);
};


#endif // INFO_H
