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

#include "playlistmodel.h"
#include "main.h"
#include "database.h"
#include "tagger.h"
#include "starrating.h"
#include "indicator.h"
#include "console.h"

PlaylistModel::PlaylistModel(QObject *parent) : QAbstractListModel(parent),
_current(-1)
{
	setSupportedDragActions(Qt::CopyAction | Qt::MoveAction);
}

PlaylistModel::~PlaylistModel() 
{
	removeRows(0, _data.count());
}

QStringList PlaylistModel::mimeTypes() const
{
	QStringList list;
	list.append("text/uri-list");
	list.append("text/plain");
	return list;
}

QMimeData * PlaylistModel::mimeData( const QModelIndexList & indexes ) const
{
	QMimeData *mime = QAbstractListModel::mimeData(indexes);
    QList<QUrl> list;
    QList<int> rows;
    foreach(QModelIndex ind, indexes) {
    	bool none = true;
    	foreach(int r, rows) if(ind.row() == r) {
    		none = false;
    		break;
    	}
    	if(none) rows << ind.row();
    }
    foreach(int r, rows) {
		list.append(data(index(r, File), Qt::UserRole).toUrl());
    }
	mime->setUrls(list);
	return mime;
}

bool PlaylistModel::dropMimeData ( const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent )
{
    if (action == Qt::IgnoreAction)
        return true;
    
	int beginRow;
	QList<QUrl> list;
	if(data->hasUrls()) 
		list = data->urls();
	else if(data->hasText())
		list << QUrl(data->text());
	else return true;

	if (row != -1)
		beginRow = row; 
	//else if (parent.isValid())
	//    beginRow = parent.row()+1; 
	else
		beginRow = rowCount();
	PlaylistFiller *filler = new PlaylistFiller(list, beginRow);
	if(!connect(filler, SIGNAL(sendFile(QUrl, int, QList<QVariant>, long, long)), this, SLOT(addItem(QUrl, int, QList<QVariant>, long, long)), Qt::QueuedConnection))
		Console::Self().error("connection error (addItem)");
	filler->start(QThread::IdlePriority);
	return true;
}

QVariant PlaylistModel::removeReturns(const QVariant& v)
{
	QString str = v.toString();
	return QVariant(str.replace('\n', ' ').replace('\r', ""));
}

void PlaylistModel::addItem(QUrl path, int row, QList<QVariant> l, long start, long length)
{
	try {
		if(l.count() >= 9) {
	    	insertRows(row, 1);
	    	if(row >= rowCount()) row = rowCount() - 1;
	        *_data.at(row).values[File] = path;
	        *_data.at(row).values[Title] = removeReturns(l[0]);
			*_data.at(row).values[Artist] = removeReturns(l[1]);
			*_data.at(row).values[Album] = removeReturns(l[2]);
			*_data.at(row).values[Comment] = removeReturns(l[3]);
			*_data.at(row).values[Genre] = l[4];
			*_data.at(row).values[Length] = l[5];
			*_data.at(row).values[Track] = l[6];
			*_data.at(row).values[Year] = l[7];
			*_data.at(row).values[Rating] = l[8];
			*_data.at(row).values[CueStart] = QVariant((qlonglong)start);
			*_data.at(row).values[CueLength] = QVariant((qlonglong)length);
			*_data.at(row).values[DBIndex] = QVariant((qlonglong)0);
			*_data.at(row).values[Number] = QVariant(rowCount());

	        emit dataChanged(index(row, 0), index(row, ColumnCount-1));
		}
	} catch (char * mes) {
		Console::Self().error(QString(mes));
	}
}

Qt::DropActions PlaylistModel::supportedDropActions () const 
{
	return Qt::CopyAction | Qt::MoveAction;
}

int PlaylistModel::rowCount(const QModelIndex &parent) const
{
    return _data.count();
}

int PlaylistModel::columnCount(const QModelIndex & parent) const
{
	return ColumnCount;
}
/*
QVariant PlaylistModel::data(int role) const
{
	if(role == Qt::BackgroundRole) {
		return QVariant(QBrush(QColor::fromRgb(128, 200, 200)));
	}
	return QVariant();
}
*/
QVariant PlaylistModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= _data.size())
        return QVariant();

    if(index.column() == File) {
    	if(role == Qt::UserRole) 
			return *_data.at(index.row()).values[index.column()];
		else if(role == Qt::DisplayRole) 
			//return QFileInfo(_data.at(index.row()).values[index.column()]->toUrl().toLocalFile()).fileName(); 
			return _data.at(index.row()).values[File]->toUrl().toString();
		else if(role == Qt::ToolTipRole)
			return _data.at(index.row()).values[File]->toUrl().toString();
    }
    
    if(index.row() == _current) {
    	if(role == Qt::FontRole) return QVariant(QFont("arial", 10, 75, false));
    	else if(role == Qt::BackgroundRole) return QVariant(QBrush(QColor::fromRgb(128, 200, 200)));
    }
    
    switch(role) {
    case Qt::DisplayRole: return *_data.at(index.row()).values[index.column()];
    //case Qt::DecorationRole:
    //case Qt::StatusTipRole: return stringList.at(index.row());
    case Qt::ToolTipRole: return *_data.at(index.row()).values[index.column()];
    default: return QVariant();
    }
} 

QVariant PlaylistModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
	/*if (role == Qt::BackgroundRole) {
		return QVariant(QBrush(QColor::fromRgb(128, 200, 200)));
		}*/
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
		switch(section) {
		case 2: return tr("File");
		case 3: return tr("Track");
		case 4: return tr("Title");
		case 5: return tr("Artist");
		case 6: return tr("Album");
		case 7: return tr("Comment");
		case 8: return tr("Genre");
		case 9: return tr("Year");
		case 10: return tr("Length");
		case 11: return tr("Rating");
		case 16: return tr("Number");
		default: return "";
		}
		//return tr(colnames[section]);
    else
        return QString("%1").arg(section);
} 

Qt::ItemFlags PlaylistModel::flags(const QModelIndex &index) const
 {
//     if (!index.isValid())
//         return Qt::ItemIsEnabled;

//     return QAbstractItemModel::flags(index) /*| Qt::ItemIsEditable*/;
     Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);

     if (index.isValid())
         return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
     else
         return Qt::ItemIsDropEnabled | defaultFlags;
 } 

bool PlaylistModel::setData(const QModelIndex &index,
                               const QVariant &value, int role)
{
    if (index.isValid() && (role == Qt::EditRole) && (*_data.at(index.row()).values[index.column()] != value)) {

        *_data.at(index.row()).values[index.column()] =  value;
        emit dataChanged(index, index);
        return true;
    }
    return false;
} 

bool PlaylistModel::insertRows(int position, int rows, const QModelIndex &parent)
{
	if(position > _data.count()) position = _data.count();
	if(position < 0) position = 0;
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
    	struct sData d;
    	for(int i=0; i<ColumnCount; i++) d.values[i] = new QVariant();
    	if(position >= _data.count())
    		_data.append(d); 
    	else
    		_data.insert(position, d);
    }

    endInsertRows();
    return true;
} 

bool PlaylistModel::removeRows(int position, int rows, const QModelIndex &parent)
{
	if(position > _data.count()) position = _data.count();
	if(position < 0) position = 0;
	if(rows <= 0) return false;
	if(_current >= position && _current <= (position + rows)) _current = -1;
	beginRemoveRows(QModelIndex(), position, position+rows-1);
	
	for (int row = 0; row < rows; ++row) {
		for(int i=0; i<ColumnCount; i++) delete _data.at(position).values[i];
		_data.removeAt(position);
	}
	
	endRemoveRows();
	return true;
} 

void PlaylistModel::appendList(QList<TagEntry> list)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount()+list.size()-1);
	foreach(TagEntry tag, list) {
    	struct sData d;
    	d.values[PlaylistModel::Empty] = new QVariant();
    	d.values[PlaylistModel::Stat] = new QVariant();
    	d.values[PlaylistModel::File] = new QVariant(tag.url);
    	d.values[PlaylistModel::Title] = new QVariant(tag.title);
    	d.values[PlaylistModel::Artist] = new QVariant(tag.artist);
    	d.values[PlaylistModel::Comment] = new QVariant(tag.comment);
    	d.values[PlaylistModel::Album] = new QVariant(tag.album);
    	d.values[PlaylistModel::Track] = new QVariant(tag.track);
    	d.values[PlaylistModel::CueStart] = new QVariant((qlonglong)tag.start);
    	d.values[PlaylistModel::CueLength] = new QVariant((qlonglong)tag.length);
    	d.values[PlaylistModel::DBIndex] = new QVariant((qlonglong)tag.dbindex);
    	d.values[PlaylistModel::Genre] = new QVariant(tag.genre);
    	d.values[PlaylistModel::Length] = new QVariant(tag.slength);
    	d.values[PlaylistModel::Year] = new QVariant(tag.year);
    	d.values[PlaylistModel::Rating] = new QVariant(qVariantFromValue(StarRating(tag.rating)));
    	d.values[PlaylistModel::StartTime] = new QVariant();
    	d.values[PlaylistModel::Number] = new QVariant(rowCount());
		_data.append(d); 
	}
    endInsertRows();
}

int PlaylistModel::current()
{
	return _current;
}

void PlaylistModel::setCurrent(int c)
{
	int oldcur = _current;
	_current = c;
	if(oldcur >= 0) 
		emit dataChanged(index(oldcur, 0), index(oldcur, ColumnCount));
	if(_current >= 0)
		emit dataChanged(index(_current, 0), index(_current, ColumnCount));
}

/************************
 * 
 * PlaylistFiller
 * 
 ************************/
PlaylistFiller::PlaylistFiller(QList<QUrl> dir, int ind, QObject *parent) 
: QThread(parent), paths(dir), index(ind)
{
	cancel = false;
}

PlaylistFiller::~PlaylistFiller()
{
}

void PlaylistFiller::run()
{
	//connect(&Indicator::Self(), SIGNAL(userStop()), this, SLOT(cancelEvent()));
	//int taskID = Indicator::Self().addTask(tr("Filling playlist"));
	foreach(QUrl s, paths) {
		if(cancel) break;
// 		if(s.toLocalFile().size())
			proceedUrl(s);
// 		else {
// 			// add url
// 			QList<TagEntry> tags = Tagger::readEntry(s);
// 			foreach(TagEntry tag, tags) {
// 				QList<QVariant> l;
// 				l.append(QVariant(tag.title));
// 				l.append(QVariant(tag.artist));
// 				l.append(QVariant(tag.album));
// 				l.append(QVariant(tag.comment));
// 				l.append(QVariant(tag.genre));
// 				l.append(QVariant(tag.slength));
// 				l.append(QVariant(tag.track));
// 				l.append(QVariant(tag.year));
// 				l.append(qVariantFromValue(StarRating(tag.rating)));
// 				setTerminationEnabled(false);
// 				emit sendFile(tag.url, index, l, tag.start, tag.length);
// 				setTerminationEnabled(true);
// 				index++;
// 			}
// 		}
	}
	//Indicator::Self().delTask(taskID);
	//disconnect(&Indicator::Self(), SIGNAL(userStop()), this, SLOT(cancelEvent()));
}

void PlaylistFiller::proceedUrl(QUrl url)
{
	if(cancel) return;
	//Indicator::Self().update();
	QDir dir;
	QString path = ToLocalFile(url);
	if(!path.size() || !dir.cd(path)) {
			QList<TagEntry> tags = Tagger::readEntry(url);
			foreach(TagEntry tag, tags) {
				QList<QVariant> l;
				l.append(QVariant(tag.title));
				l.append(QVariant(tag.artist));
				l.append(QVariant(tag.album));
				l.append(QVariant(tag.comment));
				l.append(QVariant(tag.genre));
				l.append(QVariant(tag.slength));
				l.append(QVariant(tag.track));
				l.append(QVariant(tag.year));
				l.append(qVariantFromValue(StarRating(tag.rating)));
				setTerminationEnabled(false);
				emit sendFile(tag.url, index, l, tag.start, tag.length);
				setTerminationEnabled(true);
				index++;
			}
// 		QList<QVariant> l;
// 		QString title, artist, album, comment, genre, length;
// 		int track, year, rating;
// 		if(path.toLower().endsWith(".cue")) {
// 			QList<CueEntry> cuelist = Tagger::readCue(path);
// 			foreach(CueEntry item, cuelist) {
// 				l.clear();
// 				l.append(QVariant(item.title));
// 				l.append(QVariant(item.artist));
// 				l.append(QVariant(item.album));
// 				l.append(QVariant(""));
// 				l.append(QVariant(""));
// 				l.append(QVariant(item.slength));
// 				l.append(QVariant(item.track));
// 				l.append(QVariant(0));
// 				l.append(qVariantFromValue(StarRating(0)));
// 				setTerminationEnabled(false);
// 				emit sendFile(item.url, index, l, item.start, item.length);
// 				setTerminationEnabled(true);
// 				index++;
// 			}
// 			return;
// 		}
// 		else if(Database::Self().GetTags(path, title, artist, album, comment, genre, track, year, rating, length)) {
// 			l.append(QVariant(title));
// 			l.append(QVariant(artist));
// 			l.append(QVariant(album));
// 			l.append(QVariant(comment));
// 			l.append(QVariant(genre));
// 			l.append(QVariant(length));
// 			l.append(QVariant(track));
// 			l.append(QVariant(year));
// 			l.append(qVariantFromValue(StarRating(rating)));
// 		}
// 		else if(Tagger::readTags(path, title, artist, album, comment, genre, track, year, length)) {
// 			l.append(QVariant(title));
// 			l.append(QVariant(artist));
// 			l.append(QVariant(album));
// 			l.append(QVariant(comment));
// 			l.append(QVariant(genre));
// 			l.append(QVariant(length));
// 			l.append(QVariant(/*QString::number(*/track));
// 			l.append(QVariant(/*QString::number(*/year));
// 			l.append(qVariantFromValue(StarRating(0)));
// 		}
// 		setTerminationEnabled(false);
// 		emit sendFile(QUrl::fromLocalFile(path), index, l, 0, 0);
// 		setTerminationEnabled(true);
// 		index++;
	} else /*if(dir.cd(path))*/ {
		foreach(QString file, dir.entryList()) {
			if(file == "." || file == "..") continue;
			QString suf = QFileInfo(file).suffix().toLower();
			if(suf == "jpg" || suf == "png" || suf == "txt" || suf == "doc" || suf.startsWith("htm") || !suf.size())
				continue;
			proceedUrl(QUrl::fromLocalFile(dir.filePath(file)));
		}
	}
}

void PlaylistFiller::cancelEvent()
{
	cancel = true;
}
