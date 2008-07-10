#include "playlistmodel.h"
#include "main.h"
#include "database.h"
#include "tagger.h"
#include "starrating.h"
#include "indicator.h"

PlaylistModel::PlaylistModel(QObject *parent) : QAbstractListModel(parent),
_current(1)
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
		list.append(QUrl::fromLocalFile(data(index(r, File), Qt::UserRole).toString()));
    }
	mime->setUrls(list);
	return mime;
}

bool PlaylistModel::dropMimeData ( const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent )
{
    if (action == Qt::IgnoreAction)
        return true;
    
    if(data->hasUrls()) {
        int beginRow;

		//QMessageBox::information(0, "dropped", QString::number(row));
        if (row != -1)
            beginRow = row; 
        //else if (parent.isValid())
		//    beginRow = parent.row()+1; 
        else
            beginRow = rowCount();
        QStringList list;
    	foreach(QUrl url, data->urls()) {
    		//addUrl(url.toLocalFile(), beginRow);
    		list << url.toLocalFile();
    	}
    	PlaylistFiller *filler = new PlaylistFiller(list, beginRow);
		if(!connect(filler, SIGNAL(sendFile(QString, int, QList<QVariant>)), this, SLOT(addItem(QString, int, QList<QVariant>)), Qt::QueuedConnection))
			QMessageBox::information(0, "", "connection error");
		//filler->setPriority();
		filler->start(QThread::IdlePriority);
    }
	return true;
}

void PlaylistModel::addItem(QString path, int row, QList<QVariant> l)
{
	//QMessageBox::information(0, "insert position", QString::number(row));
	try {
		if(l.count() >= 9) {
	    	insertRows(row, 1);
	    	if(row >= rowCount()) row = rowCount() - 1; 
	        *_data.at(row).values[File] = path;
	        *_data.at(row).values[Title] = l[0];
			*_data.at(row).values[Artist] = l[1];
			*_data.at(row).values[Album] = l[2];
			*_data.at(row).values[Comment] = l[3];
			*_data.at(row).values[Genre] = l[4];
			*_data.at(row).values[Length] = l[5];
			*_data.at(row).values[Track] = l[6];
			*_data.at(row).values[Year] = l[7];
			*_data.at(row).values[Rating] = l[8];
	        emit dataChanged(index(row, 0), index(row, ColumnCount-1));
		}
	} catch (char * mes) {
		QMessageBox::information(0, tr("Error"), QString(mes));
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

QVariant PlaylistModel::data(int role) const
{
	if(role == Qt::BackgroundRole) {
		return new QBrush(QColor::fromRgb(128, 200, 200));
	}
	return QVariant();
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= _data.size())
        return QVariant();

    if(index.column() == File) {
    	if(role == Qt::UserRole) return *_data.at(index.row()).values[index.column()];
    	else if(role == Qt::DisplayRole) return QFileInfo(_data.at(index.row()).values[index.column()]->toString()).fileName(); 
    }
    
    if(index.row() == _current) {
    	if(role == Qt::FontRole) return new QFont("arial", -1, -1, true);
    	else if(role == Qt::BackgroundRole) return new QBrush(QColor::fromRgb(128, 200, 200));
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
	if (role == Qt::BackgroundRole) {
		return new QBrush(QColor::fromRgb(128, 200, 200));
	}
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
    if (index.isValid() && role == Qt::EditRole) {

        *_data.at(index.row()).values[index.column()] =  value;
        emit dataChanged(index, index);
        return true;
    }
    return false;
} 

bool PlaylistModel::insertRows(int position, int rows, const QModelIndex &parent)
{
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
     beginRemoveRows(QModelIndex(), position, position+rows-1);

     for (int row = 0; row < rows; ++row) {
    	 for(int i=0; i<9; i++) delete _data.at(position).values[i];
         _data.removeAt(position);
     }

     endRemoveRows();
     return true;
 } 

/*int PlaylistModel::current()
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
		}*/

/************************
 * 
 * PlaylistFiller
 * 
 ************************/
PlaylistFiller::PlaylistFiller(QStringList dir, int ind, QObject *parent) 
: QThread(parent), paths(dir), index(ind)
{
	cancel = false;
	connect(&Indicator::Self(), SIGNAL(userStop()), this, SLOT(cancelEvent()));
}

PlaylistFiller::~PlaylistFiller()
{
	disconnect(&Indicator::Self(), SIGNAL(userStop()), this, SLOT(cancel()));
}

void PlaylistFiller::run()
{
	int taskID = Indicator::Self().addTask("Filling playlist");
	foreach(QString s, paths) {
		if(cancel) break;
		proceedDir(s);
	}
	Indicator::Self().delTask(taskID);
}

void PlaylistFiller::proceedDir(QString path)
{
	if(cancel) return;
	Indicator::Self().update();
	QDir dir;
	if(dir.cd(path)) {
		foreach(QString file, dir.entryList()) {
			if(file == "." || file == "..") continue;
			proceedDir(dir.filePath(file));
		}
	} else {
		QList<QVariant> l;
		QString title, artist, album, comment, genre, length;
		int track, year, rating;
		if(Database::Self().GetTags(path, title, artist, album, comment, genre, track, year, rating, length)) {
			l.append(QVariant(title));
			l.append(QVariant(artist));
			l.append(QVariant(album));
			l.append(QVariant(comment));
			l.append(QVariant(genre));
			l.append(QVariant(length));
			l.append(QVariant(track));
			l.append(QVariant(year));
			l.append(qVariantFromValue(StarRating(rating)));
		}
		else if(Tagger::readTags(path, title, artist, album, comment, genre, track, year, length)) {
			l.append(QVariant(title));
			l.append(QVariant(artist));
			l.append(QVariant(album));
			l.append(QVariant(comment));
			l.append(QVariant(genre));
			l.append(QVariant(length));
			l.append(QVariant(/*QString::number(*/track));
			l.append(QVariant(/*QString::number(*/year));
			l.append(qVariantFromValue(StarRating(0)));
		}
		setTerminationEnabled(false);
		emit sendFile(path, index, l);
		setTerminationEnabled(true);
		index++;
	}
}

void PlaylistFiller::cancelEvent()
{
	cancel = true;
}
