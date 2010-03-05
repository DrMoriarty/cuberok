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


#include "collectionview.h"
#include "database.h"
#include "tagger.h"
#include "indicator.h"
//#include "lastfm.h"
#include "global.h"
#include "playlistsettings.h"
#include "collectionfiller.h"
#include <QtXml>

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
	list.append(CUBEROK_MIME_TYPE);
	return list;
}

QMimeData *CollectionModel::mimeData( const QModelIndexList & indexes ) const
{
	if(true) {
		QMimeData *mimeData = new QMimeData();
		QVector<STags> tags;
		foreach(QModelIndex ind, indexes) {
			tags += TagsByItem(ind);
		}
		QByteArray array;
		QDataStream stream(&array, QIODevice::WriteOnly);
		stream << tags;
		mimeData->setData(CUBEROK_MIME_TYPE, array);
		return mimeData;
	} else {
		QMimeData *mimeData = QStandardItemModel::mimeData(indexes);
		QList<QUrl> list;
		foreach(QModelIndex ind, indexes) {
			list += SelectByItem(ind);
		}
		mimeData->setUrls(list);
		return mimeData;
	}
    /*QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << list.count();
    foreach(QModelIndex ind, this->selectedIndexes()) {
        dataStream << ind.column();
        dataStream << model.data(ind, Qt::DisplayRole).toString();
    }
    mimeData->setData("application/x-playlist", itemData);
    return mimeData;*/
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

QVector<STags> CollectionModel::TagsByItem(QModelIndex i) const
{
	QString s = data(i).toString();
	QList<QString> files;
	switch(mode) {
	case M_ARTIST:
		files = Database::Self().Songs(&s, 0, 0, 0);
		break;
	case M_ALBUM:
		files = Database::Self().Songs(0, Database::Self().AddAlbum(s, itemFromIndex(i)->data().toInt()), 0, 0);
		break;
	case M_GENRE:
		files = Database::Self().Songs(0, 0, &s, 0);
		break;
	case M_SONG:
		files.clear();
		files << itemFromIndex(i)->data().toString();
		break;
	case M_SQLLIST:
		files = Database::Self().SongsBySQLPlaylist(s);
		break;
	}
	QVector<STags> res;
	foreach(QString file, files) {
		STags tag;
		if(Database::Self().GetTags(file, tag))
			res << tag;
		else {
			// error?
		}
	}
	return res;
}

bool CollectionModel::dropMimeData ( const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent )
{
    if (data->hasUrls()) {
    	QString attrname("");
		int param = 0;
    	if(parent.isValid()) {
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
			QString title, artist, album, comment, genre, length, type;
			int track, year, rating;
			if(Database::Self().GetTags(it, title, artist, album, comment, genre, track, year, rating, length, type)) {
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
	//downloader = new Downloader(proxy);
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
	connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(applySubset(QModelIndex)));
	connect(&model, SIGNAL(modeChanged(int)), this, SIGNAL(modeChanged(int)));
	//connect(downloader, SIGNAL(complete(QString)), this, SLOT(dlComplete(QString)));
	//connect(downloader, SIGNAL(cancel(QString)), this, SLOT(dlCancel(QString)));
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
	case M_SONG:  // add a song into the playlist
		emit addUrl(QUrl::fromLocalFile(model.itemFromIndex(ind)->data().toString()));
		return;
	}
	subsetLabel += QDir::separator() + value;
	emit setSubsetLabel(subsetLabel);
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
			path = Database::commonPath(path, QFileInfo(str).canonicalPath());
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
		lfmArtist = item[0];
		lfmAlbum = "";
		STags tags;
		tags.tag0.artist = lfmArtist;
		wait_response = proxy->setRequest(SRequest(SInfo::ArtistArt, tags));
	} else if(item.size() == 2) {  // album
		lfmArtist = item[0];
		lfmAlbum = item[1];
		STags tags;
		tags.tag0.artist = lfmArtist;
		tags.tag0.album = lfmAlbum;
		wait_response = proxy->setRequest(SRequest(SInfo::AlbumArt, tags));
	}

	request_stack.pop_front();
}

void CollectionView::infoResponse()
{
	SRequest req = proxy->getRequest();
	if(req.id == wait_response) {
		switch(req.info.type) {
		case SInfo::ArtistArt:
			break;
		case SInfo::AlbumArt:
			break;
		}
		if(request_stack.size()) doRequest();
	}
	/*
	wait_response = false;
	disconnect(&LastFM::Self(), SIGNAL(xmlInfo(QString)), this, SLOT(infoResponse(QString)));
	QString newArtist, newAlbum, mbid, imageUrl, information;
	if(LastFM::Self().parseInfo(info, newArtist, newAlbum, mbid, imageUrl, information)) {
		if(newAlbum.size()) { // album info
			if(mbid.size()) Database::Self().MbidForAlbum(lfmAlbum, mbid, Database::Self().AddArtist(lfmArtist));
			if(mbid.size() && PLSet.cacheInfo && info.size()) {
				Database::Self().setInfo(mbid, information);
			}
			if(lfmArtist != newArtist) {
				Database::Self().RenameArtist(lfmArtist, newArtist);
				Database::Self().pushSubset();
				QList<QString> list = Database::Self().Songs(&newArtist);
				foreach(QString file, list) {
					Tagger::updateArtist(file, newArtist);
				}
				Database::Self().popSubset();
			}
			if(lfmAlbum != newAlbum) {
				Database::Self().RenameAlbum(lfmAlbum, newAlbum, Database::Self().AddArtist(newArtist));
				Database::Self().pushSubset();
				QList<QString> list = Database::Self().Songs(&newArtist, Database::Self().AddAlbum(newAlbum, Database::Self().AddArtist(newArtist)));
				foreach(QString file, list) {
					Tagger::updateAlbum(file, newAlbum);
				}
				Database::Self().popSubset();
			}
			if(downloader.done()) {
				lfmArtist = newArtist;
				lfmAlbum = newAlbum;
				downloader.download(imageUrl);
			} else { // download queue
			}
		} else {  // artist info
			if(mbid.size()) Database::Self().MbidForArtist(lfmArtist, mbid);
			if(mbid.size() && PLSet.cacheInfo && information.size()) {
				Database::Self().setInfo(mbid, information);
			}
			if(lfmArtist != newArtist) {
				Database::Self().RenameArtist(lfmArtist, newArtist);
				Database::Self().pushSubset();
				QList<QString> list = Database::Self().Songs(&newArtist);
				foreach(QString file, list) {
					Tagger::updateArtist(file, newArtist);
				}
				Database::Self().popSubset();
			}
			if(downloader.done()) {
				lfmArtist = newArtist;
				lfmAlbum = "";
				downloader.download(imageUrl);
			} else { // download queue
			}
		}
	}

	if(request_stack.size())
		doRequest();
 */}

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
			path = Database::commonPath(path, QFileInfo(str).canonicalPath());
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

void CollectionView::storeState()
{
}
