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

#include "libraryview.h"
#include "database.h"
#include "sqledit.h"

LibraryView::LibraryView(QWidget *parent): QListView(parent)
{
	setModel(&model);
	//setViewMode(QListView::IconMode);
	setSelectionMode(QAbstractItemView::ExtendedSelection);
	//setWrapping(true);
	setFlow(QListView::TopToBottom);
	//setFlow(QListView::LeftToRight);
	setLayoutMode(QListView::Batched);
	setResizeMode(QListView::Adjust);
	setAcceptDrops(true);
	setDragEnabled(true);
	setDragDropMode(QAbstractItemView::DragDrop);
	setDropIndicatorShown(true);
 	connect(&model, SIGNAL(status(QString)), this, SLOT(setStatus(QString)));
// 	connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(applySubset(QModelIndex)));
 	connect(&model, SIGNAL(modeChanged(int)), this, SIGNAL(modeChanged(int)));
	model.updateMode(M_LIST);
}

LibraryView::~LibraryView()
{
}

void LibraryView::setStatus(QString s)
{
	stat = s;
	emit status(stat);
}

void LibraryView::addItem()
{
	switch(model.mode) {
	case M_LIST:
		Database::Self().AddPlaylist(tr("New Playlist"));
		break;
	case M_SQLLIST:
		Database::Self().AddSQLPlaylist(tr("New Playlist"));
		break;
	default:
		return;
	}
	model.update();
}

void LibraryView::removeItem()
{
    foreach(QModelIndex ind, this->selectedIndexes()) {
		switch(model.mode) {
		case M_LIST:
			Database::Self().RemovePlaylist(model.itemFromIndex(ind)->data().toString());
			break;
		case M_SQLLIST:
			Database::Self().RemoveSQLPlaylist(model.data(ind).toString());
			break;
		default:
			return;
		}
    }
	//model.updateMode(model.mode);
    while(this->selectedIndexes().count()) model.removeRows(this->selectedIndexes().at(0).row(), 1);
    model.update();
}

void LibraryView::setImage()
{
	if(!this->selectedIndexes().size()) return;
	QString path = "";
	QString plist = model.itemFromIndex(this->selectedIndexes()[0])->data().toString();
	if(QFileInfo(plist).exists())
		path = QFileInfo(plist).absolutePath();
	else
		path = QDir::homePath();
	QString filename = QFileDialog::getOpenFileName(this, tr("Open image"), path, tr("Images (*.jpg *.gif *.png *.bmp)"));
	if(filename.size()) {
		foreach(QModelIndex ind, this->selectedIndexes()) {
			switch(model.mode) {
			case M_LIST:
				Database::Self().ArtForPlaylist(model.data(ind).toString(), filename);
				break;
			case M_SQLLIST:
				Database::Self().ArtForSQLPlaylist(model.data(ind).toString(), filename);
				break;
			default:
				break;
			}
		}
		model.update();
	}
}

void LibraryView::sqlPlaylist(bool)
{
	model.updateMode(M_SQLLIST);
}

void LibraryView::regularPlaylist(bool)
{
	model.updateMode(M_LIST);
}

void LibraryView::sqlListEdit()
{
	switch(model.mode) {
	case M_LIST:
		break;
	case M_SQLLIST:
		if(this->selectedIndexes().size()) {
			SQLEdit *se = new SQLEdit(model.data(selectedIndexes()[0]).toString());
			se->show();
		}
		break;
	}
}

void LibraryView::enterEvent ( QEvent * event )
{
	QListView::enterEvent(event);
	emit status(stat);
}

