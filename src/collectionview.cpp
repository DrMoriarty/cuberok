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

#include "collectionview.h"
#include "database.h"
#include "tagger.h"
#include "indicator.h"

/************************
 *
 *   CollectionFiller
 *
 ************************/

CollectionFiller::CollectionFiller(QList<QUrl> _urls, ListMode _mode, QString _attrname, QObject * parent) 
: QThread(parent), urls(_urls), mode(_mode), attrname(_attrname)
{
	cancel = false;
	connect(&Indicator::Self(), SIGNAL(userStop()), this, SLOT(cancelEvent()));
}

CollectionFiller::~CollectionFiller()
{
	disconnect(&Indicator::Self(), SIGNAL(userStop()), this, SLOT(cancel()));
}

void CollectionFiller::run()
{
	int taskID = Indicator::Self().addTask(tr("Collect music"));
	foreach(QUrl url, urls) {
		if(cancel) break;
		proceed(url.toLocalFile());
	}
	Indicator::Self().delTask(taskID);
}

int CollectionFiller::proceed(QString path)
{
	if(cancel) return -1;
	Indicator::Self().update();
	QDir dir;
	if(dir.cd(path)) {
		int count = 0;
		QString _album, _artist;
		QStringList covers;
		foreach(QString file, dir.entryList()) {
			if(file == "." || file == "..") continue;
			if(proceed(dir.filePath(file)) > 0) {
				count ++;
				QString title, artist, album, comment, genre, length;
				int track, year, rating;
				Database::Self().GetTags(dir.filePath(file), title, artist, album, comment, genre, track, year, rating, length);
				if(count > 1) {
					if(_album != album) _album = "";
					if(_artist != artist) _artist = "";
				} else {
					_album = album;
					_artist = artist;
				}
			} else {
				QString p2 = file.toLower();
				if(p2.endsWith(".jpg") || p2.endsWith(".png") || p2.endsWith(".gif") || p2.endsWith(".bmp")) {
					covers << dir.filePath(file);
				}
			}
		}
		QString cover;
		qint64 fsize = 0;
		foreach(QString cvr, covers) {
			qint64 s2 = QFileInfo(cvr).size();
			if(s2 > fsize) {
				fsize = s2;
				cover = cvr;
			}
		}
		if(cover.size() && _album.size() && _album != " ") {
			Database::Self().ArtForAlbum(_album, cover);
			//QMessageBox::information(0, "set album cover", cover);
		} else if(cover.size() && _artist.size() && _artist != " ") {
			Database::Self().ArtForArtist(_artist, cover);
			//QMessageBox::information(0, "set artist cover", cover);
		}
	} else {
		if(attrname.length()) {
			QString p2 = path.toLower();
			if(p2.endsWith(".jpg") || p2.endsWith(".png") || p2.endsWith(".gif") || p2.endsWith(".bmp")) {
				switch(mode) {
				case M_ALBUM:
					Database::Self().ArtForAlbum(attrname, path);
					break;
				case M_ARTIST:
					Database::Self().ArtForArtist(attrname, path);
					break;
				case M_GENRE:
					Database::Self().ArtForGenre(attrname, path);
					break;
				case M_SONG:
					break;
				}
				return -1;
			}
			QString title, artist, album, comment, genre, length;
			int track, year, rating;
			bool exist = Database::Self().GetTags(path, title, artist, album, comment, genre, track, year, rating, length);
			switch(mode) {
				case M_ALBUM:
					Tagger::updateAlbum(path, attrname);
					album = attrname;
					break;
				case M_ARTIST:
					Tagger::updateArtist(path, attrname);
					artist = attrname;
					break;
				case M_GENRE:
					Tagger::updateGenre(path, attrname);
					genre = attrname;
					break;
				case M_SONG:
					//Database::Self().SetMark(path, attrname);
					return -1;
			}
			if(exist) Database::Self().SetTags(path, title, artist, album, comment, genre, track, year, rating); 
			else return Database::Self().AddFile(path);
		} else return Database::Self().AddFile(path);
	}
	return -1;
}

void CollectionFiller::cancelEvent()
{
	cancel = true;
}

/************************
 * 
 *  CollectionModel
 * 
 ************************/

CollectionModel::CollectionModel(QObject *parent): QStandardItemModel(parent)
{
	setSupportedDragActions(Qt::CopyAction | Qt::MoveAction);
	searchPattern = "";
}

CollectionModel::~CollectionModel()
{
	
}

bool CollectionModel::setData ( const QModelIndex & index, const QVariant & value, int role )
{
	QString oldvalue = data(index, role).toString(),
		newvalue = value.toString();
	QList<QString> files;
	if(oldvalue != newvalue) switch(mode) {
	case M_ARTIST:
		files = Database::Self().Songs(&oldvalue);
		foreach(QString file, files) Tagger::updateArtist(file, newvalue);
		Database::Self().RenameArtist(oldvalue, newvalue);
		break;
	case M_ALBUM:
		files = Database::Self().Songs(0, &oldvalue);
		foreach(QString file, files) Tagger::updateAlbum(file, newvalue);
		Database::Self().RenameAlbum(oldvalue, newvalue);
		break;
	case M_GENRE:
		files = Database::Self().Songs(0, 0, &oldvalue);
		foreach(QString file, files) Tagger::updateGenre(file, newvalue);
		Database::Self().RenameGenre(oldvalue, newvalue);
		break;
	case M_SONG: {
// 		QString title, artist, album, comment, genre, length;
// 		int track, year, rating;
// 		if(Database::Self().GetTags(path, title, artist, album, comment, genre, track, year, rating, length))
// 			Database::Self().SetTags(path, newvalue, artist, album, comment, genre, track, year, rating); 
		//Database::Self().RenameMark(oldvalue, newvalue);
		break;
	}
	}
	//QMessageBox::information(0, "", value.toString());
	return QStandardItemModel::setData(index, value, role);
}

QStringList CollectionModel::mimeTypes() const
{
	QStringList list;
	list << "text/uri-list";
	return list;
}

QMimeData *CollectionModel::mimeData( const QModelIndexList & indexes ) const
{
    QMimeData *mimeData = QStandardItemModel::mimeData(indexes);
    QList<QUrl> list;
    foreach(QModelIndex ind, indexes) {
		list += SelectByItem(ind);
    }
    //QMessageBox::information(this, "", QString::number(list.count()));
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
QList<QUrl> CollectionModel::SelectByItem(QModelIndex i) const
{
	QString s = data(i).toString();
	QList<QString> res;
	switch(mode) {
	case M_ARTIST:
		res = Database::Self().Songs(&s, 0, 0, 0);
		break;
	case M_ALBUM:
		res = Database::Self().Songs(0, &s, 0, 0);
		break;
	case M_GENRE:
		res = Database::Self().Songs(0, 0, &s, 0);
		break;
	case M_SONG:
		res.clear();
		res << itemFromIndex(i)->data().toString();
		break;
	}
	QList<QUrl> urls;
	foreach(QString f, res) {
		urls << QUrl::fromLocalFile(f);
	}
	//QUrl::fromLocalFile(model.data(ind, Qt::UserRole).toString()));
	return urls;
}

bool CollectionModel::dropMimeData ( const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent )
{
    if (data->hasUrls()) {
    	QString attrname("");
    	if(parent.isValid()) attrname = this->data(parent, Qt::DisplayRole).toString();
    	QList<QUrl> urls = data->urls();
    	CollectionFiller * cf = new CollectionFiller(urls, mode, attrname);
    	connect(cf, SIGNAL(finished()), this, SLOT(update()));
    	cf->start();
    	//foreach(QUrl url, urls) {
    		//Database::Self().AddFile(url.toLocalFile());
    	//}
        //updateMode(mode);
        return true;
    }
    return false;
}

void CollectionModel::update()
{
	updateMode(mode);
}

Qt::DropActions CollectionModel::supportedDropActions() const
{
	return Qt::CopyAction | Qt::MoveAction;
}

void CollectionModel::updateMode(ListMode m)
{
	static QPixmap px_5(":/icons/stars5.png"), px_4(":/icons/stars4.png"), px_3(":/icons/stars3.png"), px_2(":/icons/stars2.png"), px_1(":/icons/stars1.png");
	mode = m;
	clear();
	QList<struct Database::Attr> data;
	QPixmap icon;
	QString stat;
	switch(m) {
	case M_ARTIST:
		if(searchPattern.length()) data = Database::Self().Artists(&searchPattern);
		else data = Database::Self().Artists();
		//icon = QApplication::style()->standardIcon(QStyle::SP_FileIcon);
		icon.load(":/icons/def_artist.png");
		stat = tr("Collection - %n artist(s)", "", data.count());
		break;
	case M_ALBUM:
		if(searchPattern.length()) data = Database::Self().Albums(&searchPattern);
		else data = Database::Self().Albums();
		//icon = QApplication::style()->standardIcon(QStyle::SP_DriveCDIcon);
		icon.load(":/icons/def_album.png");
		stat = tr("Collection - %n album(s)", "", data.count());
		break;
	case M_GENRE:
		if(searchPattern.length()) data = Database::Self().Genres(&searchPattern);
		else data = Database::Self().Genres();
		//icon = QApplication::style()->standardIcon(QStyle::SP_DirIcon);
		icon.load(":/icons/def_genre.png");
		stat = tr("Collection - %n genre(s)", "", data.count());
		break;
	case M_SONG: {
		// TODO if(searchPattern.length()) data = Database::Self().Songs(&searchPattern);
		/*else*/ 
		QList<QString> data;
		if(searchPattern.length()) data = Database::Self().Songs(0, 0, 0, &searchPattern);
		else data = Database::Self().Songs();
		icon.load(":/icons/def_song.png");
		stat = tr("Collection - %n song(s)", "", data.count());
		foreach(QString it, data) {
			QString title, artist, album, comment, genre, length;
			int track, year, rating;
			if(Database::Self().GetTags(it, title, artist, album, comment, genre, track, year, rating, length)) {
				QPixmap px2 = icon;
				if(rating >= 10) {
					QPainter painter(&px2);
					if(rating >= 50) painter.drawPixmap(QRect(0, 0, px2.width(), px2.height()), px_5, QRect(0, 0, px_5.width(), px_5.height()));
					else if(rating >= 40) painter.drawPixmap(QRect(0, 0, px2.width(), px2.height()), px_4, QRect(0, 0, px_4.width(), px_4.height()));
					else if(rating >= 30) painter.drawPixmap(QRect(0, 0, px2.width(), px2.height()), px_3, QRect(0, 0, px_3.width(), px_3.height()));
					else if(rating >= 20) painter.drawPixmap(QRect(0, 0, px2.width(), px2.height()), px_2, QRect(0, 0, px_2.width(), px_2.height()));
					else if(rating >= 10) painter.drawPixmap(QRect(0, 0, px2.width(), px2.height()), px_1, QRect(0, 0, px_1.width(), px_1.height()));
				}
				QStandardItem *row = new QStandardItem(QIcon(px2), title);
				row->setData(it);
				row->setToolTip(title+"\n"+tr("%1, album \"%2\"").arg(artist).arg(album));
				appendRow(row);
			}
		}
		emit status(stat);
		emit modeChanged(mode);
		return;
	}
	}
	QString tt("");
	QStandardItem *i;
	foreach(struct Database::Attr attr, data) {
		QPixmap px2;
		if(!attr.art.size() || !px2.load(attr.art))
			px2 = icon;
		if(attr.rating >= 1) {
			QPainter painter(&px2);
			if(attr.rating >= 40) painter.drawPixmap(QRect(0, 0, px2.width(), px2.height()), px_5, QRect(0, 0, px_5.width(), px_5.height()));
			else if(attr.rating >= 30) painter.drawPixmap(QRect(0, 0, px2.width(), px2.height()), px_4, QRect(0, 0, px_4.width(), px_4.height()));
			else if(attr.rating >= 20) painter.drawPixmap(QRect(0, 0, px2.width(), px2.height()), px_3, QRect(0, 0, px_3.width(), px_3.height()));
			else if(attr.rating >= 10) painter.drawPixmap(QRect(0, 0, px2.width(), px2.height()), px_2, QRect(0, 0, px_2.width(), px_2.height()));
			else if(attr.rating >= 1)  painter.drawPixmap(QRect(0, 0, px2.width(), px2.height()), px_1, QRect(0, 0, px_1.width(), px_1.height()));
		}
		i = new QStandardItem(QIcon(px2), attr.name);
		tt = attr.name+"\n"+tr("%n song(s)", "", attr.refs);
		//tt = QString::number(attr.refs).append(QString(" ")+tr("songs"));
		i->setToolTip(tt); 
		appendRow(i);
	}
	emit status(stat);
	emit modeChanged(mode);
}


/***********************
 * 
 *  CollectionView 
 * 
 ***********************/

CollectionView::CollectionView(QWidget *parent)
    : QListView(parent)
{
	ui.setupUi(this);
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
	connect(&model, SIGNAL(status(QString)), this, SIGNAL(status(QString)));
	if(!connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(applySubset(QModelIndex))))
		QMessageBox::information(0, "", "connection error");
	connect(&model, SIGNAL(modeChanged(int)), this, SIGNAL(modeChanged(int)));
	model.updateMode(M_GENRE);
}

CollectionView::~CollectionView()
{

}

// start drag&drop block

/*void CollectionView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void CollectionView::dragLeaveEvent(QDragLeaveEvent *event)
{
}

void CollectionView::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void CollectionView::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasUrls()) {
    	QList<QUrl> urls = event->mimeData()->urls();
    	foreach(QUrl url, urls) {
    		Database::Self().AddFile(url.toLocalFile());
    	}
        event->acceptProposedAction();
        updateModel(mode);
    } else {
        event->ignore();
    }
} 

void CollectionView::mousePressEvent(QMouseEvent *event)
{
	QModelIndex i1 = indexAt(event->pos());
	bool selected = false;
	foreach(QModelIndex ind, this->selectedIndexes()) {
		if(ind == i1) {
			selected = true;
			break;
		}
	}
	if(!selected || event->button() != Qt::LeftButton) {
		QListView::mousePressEvent(event);
		return;
	}

    QMimeData *mimeData = new QMimeData;
    QList<QUrl> list;
    foreach(QModelIndex ind, this->selectedIndexes()) {
		list += SelectByItem(ind);
    }
    QMessageBox::information(this, "", QString::number(list.count()));
    mimeData->setUrls(list);
    /*QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << list.count();
    foreach(QModelIndex ind, this->selectedIndexes()) {
        dataStream << ind.column();
        dataStream << model.data(ind, Qt::DisplayRole).toString();
    }
    mimeData->setData("application/x-playlist", itemData);*/
/*
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(event->pos());
    //drag->setPixmap(pixmap);

    if (!(drag->exec(Qt::CopyAction) == Qt::CopyAction)) {
    	
    }
}
*/
// end drag&drop block

// select files
//QList<QUrl> CollectionView::SelectByItem(QModelIndex i)
//{
	//QList<QString> res;
	//switch(model.mode) {
	//case CollectionModel::M_ARTIST:
		//res = Database::Self().Songs(&model.data(i).toString(), 0, 0);
		//break;
	//case CollectionModel::M_ALBUM:
		//res = Database::Self().Songs(0, &model.data(i).toString(), 0);
		//break;
	//case CollectionModel::M_GENRE:
		//res = Database::Self().Songs(0, 0, &model.data(i).toString());
		//break;
	//}
	//QList<QUrl> urls;
	//foreach(QString s, res) {
		//urls.append(QUrl::fromLocalFile(s));
	//}
	////QUrl::fromLocalFile(model.data(ind, Qt::UserRole).toString()));
	//return urls;
//}

void CollectionView::artistMode()
{
	model.updateMode(M_ARTIST);
}

void CollectionView::albumMode()
{
	model.updateMode(M_ALBUM);
}

void CollectionView::genreMode()
{
	model.updateMode(M_GENRE);
}

void CollectionView::songMode()
{
	model.updateMode(M_SONG);
}

void CollectionView::addItem()
{
	switch(model.mode) {
	case M_ALBUM:
		Database::Self().AddAlbum(tr("New Album"));
		break;
	case M_ARTIST:
		Database::Self().AddArtist(tr("New Artist"));
		break;
	case M_GENRE:
		Database::Self().AddGenre(tr("New Genre"));
		break;
	case M_SONG:
		//Database::Self().AddMark(tr("New Mark"));
		return;
	}
	model.update();
}

void CollectionView::removeItem()
{
    foreach(QModelIndex ind, this->selectedIndexes()) {
		switch(model.mode) {
		case M_ALBUM:
			Database::Self().RemoveAlbum(model.data(ind).toString());
			break;
		case M_ARTIST:
			Database::Self().RemoveArtist(model.data(ind).toString());
			break;
		case M_GENRE:
			Database::Self().RemoveGenre(model.data(ind).toString());
			break;
		case M_SONG:
			//Database::Self().RemoveMark(model.data(ind).toString());
			return;
		}
    }
	//model.updateMode(model.mode);
    while(this->selectedIndexes().count()) model.removeRows(this->selectedIndexes().at(0).row(), 1);
    model.update();
}

void CollectionView::filter(QString patt)
{
	model.searchPattern = patt;
	model.update();
}

void CollectionView::applySubset(QModelIndex ind)
{
	emit setVisibleSubsetWidgets(true);
	QString value = model.data(ind).toString();
	subsetLabel += QString(subsetLabel.length()?" - ":"") + value;
	emit setSubsetLabel(subsetLabel);
	switch(model.mode) {
	case M_ALBUM:
		Database::Self().subsetAlbum(value);
		model.updateMode(M_SONG);
		break;
	case M_ARTIST:
		Database::Self().subsetArtist(value);
		model.updateMode(M_ALBUM);
		break;
	case M_GENRE:
		Database::Self().subsetGenre(value);
		model.updateMode(M_ARTIST);
		break;
	case M_SONG:
		//Database::Self().subsetMark(value);
		return;
	}
	//model.update();
}

void CollectionView::clearSubset()
{
	Database::Self().clearSubset();
	emit setVisibleSubsetWidgets(false);
	subsetLabel = "";
	emit setSubsetLabel(subsetLabel);
	model.update();
}

void CollectionView::setImage()
{
	if(model.mode == M_SONG || !this->selectedIndexes().size()) return;
	QList<QString> data;
	switch(model.mode) {
	case M_ALBUM:
		data = Database::Self().Songs(0, &model.data(this->selectedIndexes()[0]).toString(), 0);
		break;
	case M_ARTIST:
		data = Database::Self().Songs(&model.data(this->selectedIndexes()[0]).toString(), 0, 0);
		break;
	case M_GENRE:
		data = Database::Self().Songs(0, 0, &model.data(this->selectedIndexes()[0]).toString());
		break;
	case M_SONG:
		return;
	}
	QString path = "";
	if(data.size()) {
		path = QFileInfo(data[0]).canonicalPath();
		foreach(QString str, data) {
			path = commonPath(path, QFileInfo(str).canonicalPath());
		}
	} 
	if(path == "") path = QDir::homePath();
	QString filename = QFileDialog::getOpenFileName(this, tr("Open image"), path, tr("Images (*.jpg *.gif *.png *.bmp)"));
	if(filename.size()) {
		foreach(QModelIndex ind, this->selectedIndexes()) {
			switch(model.mode) {
			case M_ALBUM:
				Database::Self().ArtForAlbum(model.data(ind).toString(), filename);
				break;
			case M_ARTIST:
				Database::Self().ArtForArtist(model.data(ind).toString(), filename);
				break;
			case M_GENRE:
				Database::Self().ArtForGenre(model.data(ind).toString(), filename);
				break;
			case M_SONG:
				return;
			}
		}
		model.update();
	}
}

QString CollectionView::commonPath(QString path1, QString path2)
{
	if(!path1.size() || !path2.size()) return "";
	QDir dir1(path1), dir2(path2);
	if(dir1.isRoot() || dir2.isRoot()) return "";
	path1 = dir1.canonicalPath();
	while(!dir2.isRoot()) {
		if(path1.startsWith(dir2.canonicalPath())) return dir2.canonicalPath();
		dir2.cdUp();
	}
	return "";
}

void CollectionView::iconView(bool b)
{
	if(b) {
		setViewMode(QListView::IconMode);
		setFlow(QListView::LeftToRight);
		//setGridSize(QSize(64, 64));
		setGridSize(QSize(80, 80));
		setIconSize(QSize(64, 64));
	} else {
		setViewMode(QListView::ListMode);
		setFlow(QListView::TopToBottom);
		setGridSize(QSize(128, -1));
		setIconSize(QSize(-1, -1));
	}
	setAcceptDrops(true);
	setDragEnabled(true);
	setDragDropMode(QAbstractItemView::DragDrop);
	setDropIndicatorShown(true);
}
