/* Cuberok
 * Copyright (C) 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>
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

#include "libraryview.h"
#include "library_db.h"

/************************
 * 
 *  LibraryModel
 * 
 ************************/

LibraryModel::LibraryModel(QObject *parent): QStandardItemModel(parent)
{
	setSupportedDragActions(Qt::CopyAction | Qt::MoveAction);
	searchPattern = "";
}

LibraryModel::~LibraryModel()
{
	
}

bool LibraryModel::setData ( const QModelIndex & index, const QVariant & value, int role )
{
	QString oldvalue = data(index, role).toString(),
		newvalue = value.toString();
	QList<QString> files;
	if(oldvalue != newvalue) {
		QString file1 = itemFromIndex(index)->data().toString();
		QString file2 = QFileInfo(file1).absolutePath() + QDir::separator() + newvalue + "." + QFileInfo(file1).completeSuffix();
		QFile::rename(file1, file2);
		LibraryDB::Self().RenamePlaylist(file1, file2);
		itemFromIndex(index)->setData(file2);
	}
	return QStandardItemModel::setData(index, value, role);
}

QStringList LibraryModel::mimeTypes() const
{
	QStringList list;
	list << "text/uri-list";
	return list;
}

QMimeData *LibraryModel::mimeData( const QModelIndexList & indexes ) const
{
    QMimeData *mimeData = QStandardItemModel::mimeData(indexes);
    QList<QUrl> list;
    foreach(QModelIndex ind, indexes) {
		list += SelectByItem(ind);
    }
    mimeData->setUrls(list);
    /*QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << list.count();
    foreach(QModelIndex ind, this->selectedIndexes()) {
        dataStream << ind.column();
        dataStream << model.data(ind, Qt::DisplayRole).toString();
    }
    mimeData->setData("application/x-playlist", itemData);*/
    return mimeData;
}

// select files
QList<QUrl> LibraryModel::SelectByItem(QModelIndex i) const
{
	QString s = data(i).toString();
	QList<QString> res;
	res.clear();
	res << itemFromIndex(i)->data().toString();
	QList<QUrl> urls;
	foreach(QString f, res) {
		urls << QUrl::fromLocalFile(f);
	}
	//QUrl::fromLocalFile(model.data(ind, Qt::UserRole).toString()));
	return urls;
}

bool LibraryModel::dropMimeData ( const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent )
{
    if (data->hasUrls()) {
    	QString attrname("");
		int param = 0;
    	if(parent.isValid()) {
			attrname = this->itemFromIndex(parent)->data().toString();
		}
    	QList<QUrl> urls = data->urls();
    	CollectionFiller * cf = new CollectionFiller(urls, mode, attrname);
    	connect(cf, SIGNAL(finished()), this, SLOT(update()));
    	cf->start();
        return true;
    }
    return false;
}

void LibraryModel::update()
{
	clear();
	QList<struct LibraryDB::Attr> data;
	QPixmap icon;
	QString stat;
	data = LibraryDB::Self().Playlists();
	icon.load(":/icons/def_list.png");
	stat = tr("Collection - %n lists(s)", "", data.count());
	QString tt("");
	QStandardItem *i;
	foreach(struct LibraryDB::Attr attr, data) {
		QPixmap px2;
		if(!attr.art.size() || !px2.load(attr.art))
			px2 = icon;
		drawStars(px2, attr.rating, false);
		if(QFileInfo(attr.name).exists()) 
			i = new QStandardItem(QIcon(px2), QFileInfo(attr.name).completeBaseName());
		else
			i = new QStandardItem(QIcon(px2), attr.name);
		i->setData(attr.name);
		tt = attr.name;//+"\n"+tr("%n song(s)", "", attr.refs);
		i->setToolTip(tt); 
		appendRow(i);
	}
	emit status(stat);
}

Qt::DropActions LibraryModel::supportedDropActions() const
{
	return Qt::CopyAction | Qt::MoveAction;
}

void LibraryModel::drawStars(QPixmap &bg, int rating, bool song)
{
	static QPixmap px_5(":/icons/stars5.png"), px_4(":/icons/stars4.png"), px_3(":/icons/stars3.png"), px_2(":/icons/stars2.png"), px_1(":/icons/stars1.png");
	QPixmap px(px_1.width(), px_1.height());
	px.fill(QColor(0,0,0,0));
	QPainter painter(&px);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform /*| QPainter::HighQualityAntialiasing*/);
	int x=0, y=0, w, h;
	float s;
	w = bg.width();
	h = bg.height();
	s = h;
	if(w > h) {
		y = (w - h) / 2;
		s = w;
	} else if(h > w) {
		x = (h - w) / 2;
		s = h;
	}
	s = (float)px.width() / s;
	x = (int)(s * x);
	y = (int)(s * y);
	w = (int)(s * w);
	h = (int)(s * h);
	painter.drawPixmap(QRect(x, y, w, h), bg, QRect(0, 0, bg.width(), bg.height()));
	QPixmap *st = 0;
	if(song) {
		if(rating >= 50) st = &px_5;
		else if(rating >= 40) st = &px_4;
		else if(rating >= 30) st = &px_3;
		else if(rating >= 20) st = &px_2;
		else if(rating >= 10) st = &px_1;
	} else {
		if(rating >= 40) st = &px_5;
		else if(rating >= 30) st = &px_4;
		else if(rating >= 20) st = &px_3;
		else if(rating >= 10) st = &px_2;
		else if(rating >= 1)  st = &px_1;
	}
	if(st) painter.drawPixmap(0, 0, *st);
	bg = px;
}


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
 	connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(sendToPlaylist(QModelIndex)));
	model.update();
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
	LibraryDB::Self().AddPlaylist(tr("New Playlist"));
	model.update();
}

void LibraryView::removeItem()
{
    foreach(QModelIndex ind, this->selectedIndexes()) {
		LibraryDB::Self().RemovePlaylist(model.itemFromIndex(ind)->data().toString());
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
			LibraryDB::Self().ArtForPlaylist(model.data(ind).toString(), filename);
		}
		model.update();
	}
}

void LibraryView::enterEvent ( QEvent * event )
{
	QListView::enterEvent(event);
	emit status(stat);
}

void LibraryView::sendToPlaylist(QModelIndex ind)
{
	QList<QUrl> list = model.SelectByItem(ind);
	foreach(QUrl url, list) {
		emit addUrl(url);
	}
}

void LibraryView::storeState()
{
}
