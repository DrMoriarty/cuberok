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

#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QtGui>
#include "starrating.h"
#include "stareditor.h"

class ItemWidget : public QWidget
{
	Q_OBJECT
 public:
	ItemWidget(const QPixmap &pm, QString n, QString a, const StarRating &r, int level, QWidget *parent=0);

 public:
	QLabel *pic, *name, *appendix;
	StarEditor *rating;
};

class InfoWidget : public QTreeWidget
{
	Q_OBJECT
 public:
	InfoWidget(QWidget *parent = 0);

 public slots:
	void setArtist(QString ar);
	void setAlbum(QString al);

 private:
	QString artist, album;
	QTreeWidgetItem *ar, *al;
};

#endif //INFOWIDGET_H
