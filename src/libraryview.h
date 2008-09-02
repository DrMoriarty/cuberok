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

#ifndef LIBRARYVIEW_H
#define LIBRARYVIEW_H

#include <QtGui>
#include "collectionview.h"

class LibraryView: public QListView
{
	Q_OBJECT

public:
	LibraryView(QWidget *parent = 0);
	~LibraryView();

public slots:
	void addItem();
	void removeItem();
	void setImage();

private:
	CollectionModel model;
};

#endif // LIBRARYVIEW_H
