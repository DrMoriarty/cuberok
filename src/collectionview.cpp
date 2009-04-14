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
#include "lastfm.h"
#include "console.h"
#include "main.h"
#include "playlistsettings.h"
#include <QtXml>

/************************
 *
 *   CollectionFiller
 *
 ************************/

CollectionFiller::CollectionFiller(QList<QUrl> _urls, ListMode _mode, QString _attrname, int _param, QObject * parent) 
	: QThread(parent), urls(_urls), mode(_mode), attrname(_attrname), param(_param)
{
	cancel = false;
	connect(&Indicator::Self(), SIGNAL(userStop()), this, SLOT(cancelEvent()), Qt::QueuedConnection);
	connect(this, SIGNAL(internalUpdate()), &Indicator::Self(), SLOT(update()), Qt::QueuedConnection);
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
		proceed(ToLocalFile(url));
	}
	Indicator::Self().delTask(taskID);
}

int CollectionFiller::proceed(QString path)
{
	if(cancel) return -1;
	emit internalUpdate();
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
		if(cover.size() && _album.size() && _album != " " && _artist.size() && _artist != " ") {
			Database::Self().ArtForAlbum(_album, cover, Database::Self().AddArtist(_artist));
			Console::Self().log("set album cover" + cover);
		} else if(cover.size() && _artist.size() && _artist != " ") {
			Database::Self().ArtForArtist(_artist, cover);
			Console::Self().log("set artist cover" + cover);
		}
	} else {
		QString p2 = path.toLower();
		// check playlists
		if(p2.endsWith(".m3u") || p2.endsWith(".xspf") || p2.endsWith(".asx") || p2.endsWith(".asp") || p2.endsWith(".cue")) {
			return Database::Self().AddPlaylist(path);
		}
		// drop into item
		if(attrname.length()) {
			// check images
			if(p2.endsWith(".jpg") || p2.endsWith(".png") || p2.endsWith(".gif") || p2.endsWith(".bmp")) {
				switch(mode) {
				case M_ALBUM:
					Database::Self().ArtForAlbum(attrname, path, param);
					break;
				case M_ARTIST:
					Database::Self().ArtForArtist(attrname, path);
					break;
				case M_GENRE:
					Database::Self().ArtForGenre(attrname, path);
					break;
				case M_SONG:
					break;
				case M_LIST:
					Database::Self().ArtForPlaylist(attrname, path);
					break;
				case M_SQLLIST:
					break;
				}
				return -1;
			}
			// check songs
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
				return -1;
			case M_LIST:
				// TODO
				return -1;
			case M_SQLLIST:
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
			files = Database::Self().Songs(0, Database::Self().AddAlbum(oldvalue, itemFromIndex(index)->data().toInt()));
			foreach(QString file, files) Tagger::updateAlbum(file, newvalue);
			Database::Self().RenameAlbum(oldvalue, newvalue, itemFromIndex(index)->data().toInt());
			break;
		case M_GENRE:
			files = Database::Self().Songs(0, 0, &oldvalue);
			foreach(QString file, files) Tagger::updateGenre(file, newvalue);
			Database::Self().RenameGenre(oldvalue, newvalue);
			break;
		case M_SONG: {
			break;
		}
		case M_LIST: {
			QString file1 = itemFromIndex(index)->data().toString();
			QString file2 = QFileInfo(file1).absolutePath() + QDir::separator() + newvalue + "." + QFileInfo(file1).completeSuffix();
			QFile::rename(file1, file2);
			Database::Self().RenamePlaylist(file1, file2);
			itemFromIndex(index)->setData(file2);
			break;
		}
		case M_SQLLIST:
			Database::Self().RenameSQLPlaylist(oldvalue, newvalue);
			//itemFromIndex(index)->setData();
			break;
	}
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
		res = Database::Self().Songs(0, Database::Self().AddAlbum(s, itemFromIndex(i)->data().toInt()), 0, 0);
		break;
	case M_GENRE:
		res = Database::Self().Songs(0, 0, &s, 0);
		break;
	case M_SONG:
	case M_LIST:
		res.clear();
		res << itemFromIndex(i)->data().toString();
		break;
	case M_SQLLIST:
		res = Database::Self().SongsBySQLPlaylist(s);
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
		int param = 0;
    	if(parent.isValid()) {
			if(mode == M_LIST)
				attrname = this->itemFromIndex(parent)->data().toString();
			else
				attrname = this->data(parent, Qt::DisplayRole).toString();
			if(mode == M_ALBUM) 
				param = this->itemFromIndex(parent)->data().toInt();
		}
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
	case M_ALBUM: {
		QList<struct Database::AttrAl> dataAl;
		if(searchPattern.length()) dataAl = Database::Self().Albums(&searchPattern);
		else dataAl = Database::Self().Albums();
		icon.load(":/icons/def_album.png");
		QString tt("");
		QStandardItem *i;
		int count = 0;
		foreach(struct Database::AttrAl attr, dataAl) {
			if(PLSet.hideEmptyInCollection && (attr.name == " " || attr.name == "" || !attr.refs))
				continue;
			count ++;
			QPixmap px2;
			if(!attr.art.size() || !px2.load(attr.art))
				px2 = icon;
			drawStars(px2, attr.rating, false);
			i = new QStandardItem(QIcon(px2), attr.name);
			tt = Database::Self().GetArtist(attr.artist) + " - " + attr.name+"\n"+tr("%n song(s)", "", attr.refs);
			i->setToolTip(tt); 
			i->setData(attr.artist);
			appendRow(i);
		}
		stat = tr("Collection - %n album(s)", "", count);
		emit status(stat);
		emit modeChanged(mode);
		return;
	}
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
				drawStars(px2, rating, true);
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
	case M_LIST: {
		data = Database::Self().Playlists();
		icon.load(":/icons/def_list.png");
		stat = tr("Collection - %n lists(s)", "", data.count());
		QString tt("");
		QStandardItem *i;
		foreach(struct Database::Attr attr, data) {
			QPixmap px2;
			if(!attr.art.size() || !px2.load(attr.art))
				px2 = icon;
			drawStars(px2, attr.rating, false);
			if(QFileInfo(attr.name).exists()) 
				i = new QStandardItem(QIcon(px2), QFileInfo(attr.name).baseName());
			else
				i = new QStandardItem(QIcon(px2), attr.name);
			i->setData(attr.name);
			tt = attr.name;//+"\n"+tr("%n song(s)", "", attr.refs);
			i->setToolTip(tt); 
			appendRow(i);
		}
		emit status(stat);
		emit modeChanged(mode);
		return;
	}
	case M_SQLLIST: {
		QList<struct Database::SAttr> data = Database::Self().SQLPlaylists();
		icon.load(":/icons/def_sqllist.png");
		stat = tr("Collection - %n lists(s)", "", data.count());
		QString tt("");
		QStandardItem *i;
		foreach(struct Database::SAttr attr, data) {
			QPixmap px2;
			if(!attr.art.size() || !px2.load(attr.art))
				px2 = icon;
			drawStars(px2, 0/*attr.rating*/, false);
			i = new QStandardItem(QIcon(px2), attr.name);
			i->setData(attr.data);
			tt = attr.name;//+"\n"+tr("%n song(s)", "", attr.refs);
			i->setToolTip(tt); 
			appendRow(i);
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
		drawStars(px2, attr.rating, false);
		i = new QStandardItem(QIcon(px2), attr.name);
		tt = attr.name+"\n"+tr("%n song(s)", "", attr.refs);
		//tt = QString::number(attr.refs).append(QString(" ")+tr("songs"));
		i->setToolTip(tt); 
		appendRow(i);
	}
	emit status(stat);
	emit modeChanged(mode);
}

void CollectionModel::drawStars(QPixmap &bg, int rating, bool song)
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

/***********************
 * 
 *  CollectionView 
 * 
 ***********************/

CollectionView::CollectionView(QWidget *parent)
    : QListView(parent), wait_response(false)
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
	connect(&model, SIGNAL(status(QString)), this, SIGNAL(status(QString)));
	if(!connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(applySubset(QModelIndex))))
		Console::Self().error("connection error (doubleClicked)");
	connect(&model, SIGNAL(modeChanged(int)), this, SIGNAL(modeChanged(int)));
	connect(&downloader, SIGNAL(complete(QString)), this, SLOT(dlComplete(QString)));
	connect(&downloader, SIGNAL(cancel(QString)), this, SLOT(dlCancel(QString)));
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
		Database::Self().AddAlbum(tr("New Album"), 0);
		break;
	case M_ARTIST:
		Database::Self().AddArtist(tr("New Artist"));
		break;
	case M_GENRE:
		Database::Self().AddGenre(tr("New Genre"));
		break;
	case M_SONG:
		return;
	}
	model.update();
}

void CollectionView::removeItem()
{
    foreach(QModelIndex ind, this->selectedIndexes()) {
		switch(model.mode) {
		case M_ALBUM:
			Database::Self().RemoveAlbum(model.data(ind).toString(), model.itemFromIndex(ind)->data().toInt());
			break;
		case M_ARTIST:
			Database::Self().RemoveArtist(model.data(ind).toString());
			break;
		case M_GENRE:
			Database::Self().RemoveGenre(model.data(ind).toString());
			break;
		case M_SONG:
			Database::Self().RemoveFile(model.itemFromIndex(ind)->data().toString());
			break;
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
	subsetLabel += QDir::separator() + value;
	emit setSubsetLabel(subsetLabel);
	switch(model.mode) {
	case M_ALBUM:
		Database::Self().subsetAlbum(Database::Self().AddAlbum(value, model.itemFromIndex(ind)->data().toInt()));
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
	QString val = model.data(this->selectedIndexes()[0]).toString();
	QList<QString> data;
	switch(model.mode) {
	case M_ALBUM:
		data = Database::Self().Songs(0, Database::Self().AddAlbum(val, model.itemFromIndex(this->selectedIndexes()[0])->data().toInt()), 0);
		break;
	case M_ARTIST:
		data = Database::Self().Songs(&val, 0, 0);
		break;
	case M_GENRE:
		data = Database::Self().Songs(0, 0, &val);
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
				Database::Self().ArtForAlbum(model.data(ind).toString(), filename, model.itemFromIndex(ind)->data().toInt());
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

void CollectionView::loadImage()
{
	QList<int> list;
	foreach(QModelIndex ind, this->selectedIndexes()) {
		if(list.contains(ind.row())) continue;
		switch(model.mode) {
		case M_ALBUM:{
			QList<QString> item;
			item << Database::Self().GetArtist(model.itemFromIndex(ind)->data().toInt());
			item << model.data(ind).toString();
			request_stack << item;
			break;
		}
		case M_ARTIST: {
			QList<QString> item;
			item << model.data(ind).toString();
			request_stack << item;
			break;
		}
		case M_GENRE:
		case M_SONG:
		case M_LIST:
		case M_SQLLIST:
			return;
		}
		list << ind.row();
	}
	if(!wait_response) doRequest();
}

void CollectionView::doRequest()
{
	if(wait_response || !request_stack.size()) return;
	QList<QString> &item = *request_stack.begin();
	
	if(item.size() == 1) {  // artist
		if(!connect(&LastFM::Self(), SIGNAL(xmlInfo(QString)), this, SLOT(infoResponse(QString))))
			Console::Self().error("Unable connection to xmlInfo");
		wait_response = true;
		lfmArtist = item[0];
		lfmAlbum = "";
		LastFM::Self().artistInfo(item[0]);
	} else if(item.size() == 2) {  // album
		if(!connect(&LastFM::Self(), SIGNAL(xmlInfo(QString)), this, SLOT(infoResponse(QString))))
			Console::Self().error("Unable connection to xmlInfo");
		wait_response = true;
		lfmArtist = item[0];
		lfmAlbum = item[1];
		LastFM::Self().albumInfo(item[0], item[1]);
	}

	request_stack.pop_front();
}

void CollectionView::infoResponse(QString info)
{
	wait_response = false;
	disconnect(&LastFM::Self(), SLOT(xmlInfo(QString)), this, SIGNAL(infoResponse(QString)));

	QDomDocument doc;
	QDomElement el, el2;
	QDomNodeList list;
	if(doc.setContent(info)) {
		el = doc.documentElement();
		//el = el.firstChildElement("lfm");
		if(!el.isNull()) {
			QString s = el.attribute("status");
			if(s == "ok") {
				el2 = el.firstChildElement("artist");
				if(!el2.isNull()) {  // proceed artist info
					QString name, img1, img2, img3, img4;
					el = el2;
					el2 = el.firstChildElement("name");
					if(!el2.isNull()) name = el2.firstChild().nodeValue();
					QString mbid;
					el2 = el.firstChildElement("mbid");
					if(!el2.isNull()) mbid = el2.firstChild().nodeValue();
					Database::Self().MbidForArtist(lfmArtist, mbid);
					el2 = el.firstChildElement("image");
					while(!el2.isNull()) {
						if(el2.attribute("size") == "small") img1 = el2.firstChild().nodeValue();
						if(el2.attribute("size") == "medium") img2 = el2.firstChild().nodeValue();
						if(el2.attribute("size") == "large") img3 = el2.firstChild().nodeValue();
						if(el2.attribute("size") == "extralarge") img4 = el2.firstChild().nodeValue();
						el2 = el2.nextSiblingElement("image");
					}
					el2 = el.firstChildElement("bio");
					if(!el2.isNull() && mbid.size() && PLSet.cacheInfo) {
						el2 = el2.firstChildElement("content");
						if(!el2.isNull()) {
							QString info = el2.firstChild().nodeValue();
							if(PLSet.cacheInfo && info.size()) {
								info = "<html><body>" + info + "</html></body>";
								Database::Self().setInfo(mbid, info);
							}
						}
					}
					if(!img2.size()) img2 = img1;
					if(!img3.size()) img3 = img2;
					if(!img4.size()) img4 = img3;
					Console::Self().log("Image URL" + img4);
					if(downloader.done()) {
						if(lfmArtist != name) {
							Database::Self().RenameArtist(lfmArtist, name);
							Database::Self().pushSubset();
							QList<QString> list = Database::Self().Songs(&name);
							foreach(QString file, list) {
								Tagger::updateArtist(file, name);
							}
							Database::Self().popSubset();
						}
						lfmArtist = name;
						lfmAlbum = "";
						downloader.download(img4);
					} else { // download queue
					}
				} else {
					el2 = el.firstChildElement("album");
					if(!el2.isNull()) {  // proceed album info
						QString name, artist, img1, img2, img3, img4;
						el = el2;
						el2 = el.firstChildElement("name");
						if(!el2.isNull()) name = el2.firstChild().nodeValue();
						el2 = el.firstChildElement("artist");
						if(!el2.isNull()) artist = el2.firstChild().nodeValue();
						QString mbid;
						el2 = el.firstChildElement("mbid");
						if(!el2.isNull()) mbid = el2.firstChild().nodeValue();
						Database::Self().MbidForAlbum(lfmAlbum, mbid, Database::Self().AddArtist(artist));
						el2 = el.firstChildElement("image");
						while(!el2.isNull()) {
							if(el2.attribute("size") == "small") img1 = el2.firstChild().nodeValue();
							if(el2.attribute("size") == "medium") img2 = el2.firstChild().nodeValue();
							if(el2.attribute("size") == "large") img3 = el2.firstChild().nodeValue();
							if(el2.attribute("size") == "extralarge") img4 = el2.firstChild().nodeValue();
							el2 = el2.nextSiblingElement("image");
						}
						el2 = el.firstChildElement("wiki");
						if(!el2.isNull() && mbid.size()) {
							el2 = el2.firstChildElement("content");
							if(!el2.isNull()) {
								QString info = el2.firstChild().nodeValue();
								if(PLSet.cacheInfo && info.size()) {
									info = "<html><body>" + info + "</html></body>";
									Database::Self().setInfo(mbid, info);
								}
							}
						}
						if(!img2.size()) img2 = img1;
						if(!img3.size()) img3 = img2;
						if(!img4.size()) img4 = img3;
						Console::Self().log("Image URL" + img4);
						if(downloader.done()) {
							if(lfmArtist != artist) {
								Database::Self().RenameArtist(lfmArtist, artist);
								Database::Self().pushSubset();
								QList<QString> list = Database::Self().Songs(&name);
								foreach(QString file, list) {
									Tagger::updateArtist(file, name);
								}
								Database::Self().popSubset();
							}
							if(lfmAlbum != name) {
								Database::Self().RenameAlbum(lfmAlbum, name, Database::Self().AddArtist(artist));
								Database::Self().pushSubset();
								QList<QString> list = Database::Self().Songs(&artist, Database::Self().AddAlbum(name, Database::Self().AddArtist(artist)));
								foreach(QString file, list) {
									Tagger::updateAlbum(file, name);
								}
								Database::Self().popSubset();
							}
							lfmArtist = artist;
							lfmAlbum = name;
							downloader.download(img4);
						} else { // download queue
						}
					} else {
						// something else
					}
				}
			} else if(s == "failed") {
				// TODO error message
				Console::Self().error("Can't take info from Last.FM");
			} else {
				// unknown error
				Console::Self().error("Last.FM: Unknown error");
			}
		} else {
			Console::Self().error("Last.FM: Element lfm not found");
		}
	} else {
		Console::Self().error("Last.FM: XML error");
	}

	if(request_stack.size())
		doRequest();
}

void CollectionView::dlComplete(QString file)
{
	QList<QString> data;
	if(lfmAlbum.size())
		data = Database::Self().Songs(0, Database::Self().AddAlbum(lfmAlbum, Database::Self().AddArtist(lfmArtist)), 0);
	else
		data = Database::Self().Songs(&lfmArtist, 0, 0);
	QString path = "";
	if(data.size()) {
		path = QFileInfo(data[0]).canonicalPath();
		foreach(QString str, data) {
			path = commonPath(path, QFileInfo(str).canonicalPath());
		}
		path += QDir::separator();
	} 
	if(path == "" || path == "/") path = QDir::homePath() + "/.cuberok/artcache/";
	QDir dir;
	if(dir.mkpath(path)) {
		QString file2 = path + lfmArtist;
		if(lfmAlbum.size()) file2 += "-"+lfmAlbum;
		file2 += "."+QFileInfo(file).suffix();
		if(QFile::exists(file2)) QFile::remove(file2);
		if(QFile::copy(file, file2)) {
			QFile::remove(file);
			if(lfmAlbum.size()) {  // cover for album
				Database::Self().ArtForAlbum(lfmAlbum, file2, Database::Self().AddArtist(lfmArtist));
				if(model.mode == M_ALBUM)
					model.update();
			} else {  // image for artist
				Database::Self().ArtForArtist(lfmArtist, file2);
				if(model.mode == M_ARTIST)
					model.update();
			}
		}
	}

	lfmAlbum = "";
	lfmArtist = "";
}

void CollectionView::dlCancel(QString)
{
	lfmAlbum = "";
	lfmArtist = "";
}
