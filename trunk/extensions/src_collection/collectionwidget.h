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

#ifndef COLLECTIONWIDGET_H
#define COLLECTIONWIDGET_H

#include <QtGui>
#include "ui_collectionwidget.h"

class CollectionWidget: public QWidget
{
	Q_OBJECT
 public:
	CollectionWidget(QWidget* parent = 0);
	void storeState();
	
 private:
	Ui::CollectionWidget ui;
 private slots:
	void colmodeChanged(int);
};

#endif //LIBRARYWIDGET_H
