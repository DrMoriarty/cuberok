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

#include "playlistview.h"
#include "player_manager.h"
#include "tageditor.h"
#include "tagger.h"
#include "database.h"
#include "stardelegate.h"
#include "starrating.h"
#include "playlistsettings.h"
#include "lastfm.h"
#include "console.h"
#include "librefm.h"

Q_EXPORT_PLUGIN2(playlist_standard, PlaylistStandardFactory) 

/***********************
 * 
 *    MyTreeView
 * 
 ***********************/ 

MyTreeView::MyTreeView(QString &str, QWidget *parent)
  : QTreeView(parent), dragStarted(false)
{
	setItemDelegate(new StarDelegate);
    pmodel.setDynamicSortFilter(true);
	pmodel.setFilterCaseSensitivity(Qt::CaseInsensitive);
	pmodel.setFilterKeyColumn(-1);
    pmodel.setSourceModel(&model);
	setModel(&pmodel);
	setEditTriggers(QAbstractItemView::NoEditTriggers); 
	setSelectionMode(QAbstractItemView::ExtendedSelection);
	//setSortingEnabled(true);
	setAlternatingRowColors(true);
	sortByColumn(PlaylistModel::Number, Qt::AscendingOrder);
	hideColumn(PlaylistModel::Empty);
	hideColumn(PlaylistModel::CueStart);
	hideColumn(PlaylistModel::CueLength);
	hideColumn(PlaylistModel::DBIndex);
	hideColumn(PlaylistModel::StartTime);
	header()->moveSection(PlaylistModel::Number, PlaylistModel::Stat);
	for(int i=0; i<PlaylistModel::ColumnCount; i++) {
		setColumnHidden(i, !PLSet.columnVisible(i));
		setColumnWidth(i, PLSet.columnWidth(i));
		header()->moveSection(header()->visualIndex(i), PLSet.columnPosition(i));
	}
	connect(&PLSet, SIGNAL(visibleChanged(int,bool)), this, SLOT(setColVisible(int,bool)));
	connect(&PLSet, SIGNAL(widthChanged(int,int)), this, SLOT(setColWidth(int,int)));
	connect(&PLSet, SIGNAL(positionChanged(int,int)), this, SLOT(setColPosition(int,int)));
	connect(&model, SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(updateStatus()));
	connect(&model, SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(updateStatus()));
	//connect(&header(), SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(updateStatus()));
	
	setDragEnabled(true);
	setDragDropMode(QAbstractItemView::DragDrop);
	setDropIndicatorShown(true);
	setSortingEnabled(true);
}

// start drag&drop block
void MyTreeView::dragEnterEvent(QDragEnterEvent *event)
{
	if(event->source() != this)
		event->acceptProposedAction();
}

void MyTreeView::dropEvent(QDropEvent *event)
{
	if(dragStarted) {
	    QModelIndex index = indexAt(event->pos());
        if (model.dropMimeData(event->mimeData(),
            Qt::MoveAction, index.row(), index.column(), index)) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
	    stopAutoScroll();
	    setState(NoState);
	} else QTreeView::dropEvent(event);
}

void MyTreeView::startDrag(Qt::DropActions supportedActions)
{
	dragStarted = true;
	QTreeView::startDrag(supportedActions);
	dragStarted = false;
}


// end drag&drop block

void MyTreeView::setColVisible(int c, bool v)
{
	if(v) showColumn(c);
	else hideColumn(c);
}

void MyTreeView::setColWidth(int c, int w)
{
	setColumnWidth(c, w);
}

void MyTreeView::setColPosition(int c, int p)
{
	header()->moveSection(header()->visualIndex(c), p);
}

void MyTreeView::hideEvent ( QHideEvent * event )
{
	for(int i=0; i<PlaylistModel::ColumnCount; i++) {
		PLSet.setColumnWidth(i, columnWidth(i));
		PLSet.setColumnPosition(i, header()->visualIndex(i));
	}
	QTreeView::hideEvent(event);
}

void MyTreeView::showEvent ( QShowEvent * event )
{
	//updateStatus();
	emit needUpdate();
}

/***********************
 * 
 *    PlaylistStandard
 * 
 ***********************/ 

PlaylistStandard::PlaylistStandard(QString &str, QWidget *parent) : Playlist(str, parent), autosave(false), playing(false), shuffle_count(0), delayedPlay(false), delayedIndex(-1), delayedPos(0.0), error_count(0)
{
	tree = new MyTreeView(str, parent);
	connect(tree, SIGNAL(needUpdate()), this, SLOT(updateStatus()));
	//connect(tree, SIGNAL(status(QString)), this, SIGNAL(status(QString)));
	connect(tree, SIGNAL(message(QString, QString, QString, long)), this, SIGNAL(message(QString, QString, QString, long)));
	connect(tree, SIGNAL(started()), this, SLOT(startedSlot()));
	connect(tree, SIGNAL(songPosition(int)), this, SIGNAL(songPosition(int)));
	connect(tree, SIGNAL(playPauseIcon (bool)), this, SIGNAL(playPauseIcon (bool)));
	connect(tree, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onClick(const QModelIndex &)));
	connect(tree, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(onDoubleClick(const QModelIndex &)));
	if(plistname.size()) {  // read stored playlist
		QString fname = QDir::homePath() + "/.cuberok/" + plistname + ".xspf";
		if(QFile::exists(fname)) loadList(fname);
		else {
			fname = QDir::homePath() + "/.cuberok/" + plistname + ".m3u";
			if(QFile::exists(fname)) loadList(fname);
		}
	}
};

PlaylistStandard::~PlaylistStandard()
{
	QString fname = QDir::homePath() + "/.cuberok/" + plistname + ".xspf";
	if(autosave) storeListXSPF(fname);
	else QFile::remove(fname);
}

QString PlaylistStandard::getName()
{
	return plistname;
}

void PlaylistStandard::setName(QString str)
{
	plistname = str;
}

void PlaylistStandard::storeListM3U(QString fname)
{
	if(!fname.size()) return;
	QFile file(fname);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream out(&file);
		out << "#EXTM3U" << endl;
		for(int i=0; i<tree->model.rowCount(); i++) {
			out << tree->model.data(tree->model.index(i, PlaylistModel::File), Qt::UserRole).toUrl().toString() << endl;
		}
		file.close();
	}
}

void PlaylistStandard::storeListXSPF(QString fname)
{
	QFile file(fname);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QXmlStreamWriter xml(&file);
		//xml.setAutoFormatting(true);
		xml.writeStartDocument();
		xml.writeStartElement("playlist");
		xml.writeAttribute("version", "1");
		xml.writeDefaultNamespace("http://xspf.org/ns/0/");
		xml.writeNamespace(XMLNS, "cuberok");
		xml.writeTextElement("title", QFileInfo(fname).completeBaseName());
		xml.writeTextElement("creator", "Cuberok");
		xml.writeTextElement("date", QDateTime::currentDateTime().toUTC().toString("yyyy-MM-dd'T'hh:mm:ss"));
		xml.writeStartElement("trackList");
		for(int i=0; i<tree->model.rowCount(); i++) {
			xml.writeStartElement("track");
			xml.writeTextElement("location", tree->model.data(tree->model.index(i, PlaylistModel::File), Qt::UserRole).toUrl().toString());
			xml.writeTextElement("title", tree->model.data(tree->model.index(i, PlaylistModel::Title), Qt::DisplayRole).toString());
			xml.writeTextElement("creator", tree->model.data(tree->model.index(i, PlaylistModel::Artist), Qt::DisplayRole).toString());
			xml.writeTextElement("annotation", tree->model.data(tree->model.index(i, PlaylistModel::Comment), Qt::DisplayRole).toString());
			xml.writeTextElement("album", tree->model.data(tree->model.index(i, PlaylistModel::Album), Qt::DisplayRole).toString());
			xml.writeTextElement("trackNum", QString::number(tree->model.data(tree->model.index(i, PlaylistModel::Track), Qt::DisplayRole).toInt()));
			xml.writeStartElement("extension");
			xml.writeAttribute("application", XMLNS);
			xml.writeTextElement(XMLNS, "cuestart", QString::number(tree->model.data(tree->model.index(i, PlaylistModel::CueStart), Qt::DisplayRole).toLongLong()));
			xml.writeTextElement(XMLNS, "cuelength", QString::number(tree->model.data(tree->model.index(i, PlaylistModel::CueLength), Qt::DisplayRole).toLongLong()));
			xml.writeTextElement(XMLNS, "dbindex", QString::number(tree->model.data(tree->model.index(i, PlaylistModel::DBIndex), Qt::DisplayRole).toLongLong()));
			xml.writeTextElement(XMLNS, "genre", tree->model.data(tree->model.index(i, PlaylistModel::Genre), Qt::DisplayRole).toString());
			xml.writeTextElement(XMLNS, "length", tree->model.data(tree->model.index(i, PlaylistModel::Length), Qt::DisplayRole).toString());
			xml.writeTextElement(XMLNS, "year", QString::number(tree->model.data(tree->model.index(i, PlaylistModel::Year), Qt::DisplayRole).toInt()));
			xml.writeTextElement(XMLNS, "rating", QString::number(qVariantValue<StarRating>(tree->model.data(tree->model.index(i, PlaylistModel::Rating), Qt::DisplayRole)).rating()));
			xml.writeTextElement(XMLNS, "filetype", tree->model.data(tree->model.index(i, PlaylistModel::FileType), Qt::DisplayRole).toString());
			xml.writeEndElement(); //extension
			xml.writeEndElement(); //track
		}
		xml.writeEndElement(); // trackList
		xml.writeEndElement(); //playlist
		xml.writeEndDocument();
	}
}

void PlaylistStandard::loadList(QString fname)
{
	while(tree->model.rowCount()) tree->model.removeRow(0);
	addUrl(QUrl::fromLocalFile(fname));
}

void PlaylistStandard::addUrl(QUrl url)
{
	QList<TagEntry> list = Tagger::readEntry(url);
	Console::Self().log("Add URL: "+url.toString() + " " + QString::number(list.size()) + " record(s)");
	tree->model.appendList(list);
}

bool PlaylistStandard::isPlaying()
{
	return playing;
}

void PlaylistStandard::addItem(QVariant item, int id, QModelIndex* ind)
{
	if(!ind) ind = &insindex;
	if(id == PlaylistModel::File)
		tree->model.insertRows(ind->row()<0 ? tree->model.rowCount() : ind->row(), 1);
	tree->model.setData(ind->row()<0 ? tree->model.index(tree->model.rowCount()-1, id) : tree->model.index(ind->row(), id), item, Qt::EditRole);
}

void PlaylistStandard::prev()
{
	QModelIndex prev = prevItem();
	if(prev.row() >= 0) {
		setCurrent(prev.row());
		play();
	}
}

void PlaylistStandard::next()
{
	QModelIndex next;
	do {
		next = nextItem();
	} while(qVariantValue<StarRating>(tree->model.data(tree->model.index(next.row(), PlaylistModel::Rating), Qt::DisplayRole)).rating() <= -50);
	if(next.row() >= 0) {
		if(plindex.row() >= 0) {
			prev_queue.push_back(plindex);
			if(PlayerManager::Self().shuffle_mode) {
				tree->model.setData(tree->model.index(plindex.row(), PlaylistModel::Empty), "1", Qt::EditRole);
				shuffle_count ++;
			}
			if(PlayerManager::Self().playing()) rateSong(plindex, -1);
		}
		setCurrent(next.row());
		play();
	}
	//else stop();
}

void PlaylistStandard::play(int index, double pos)
{
	if(index >= 0 && index < tree->model.rowCount()) {
		setCurrent(index);
		play();
		if(pos >= 0 && pos <= 1)
			PlayerManager::Self().setPosition(pos);
			//position(pos);
	} else {
		delayedPlay = true;
		delayedIndex = index;
		delayedPos = pos;
	}
}

void PlaylistStandard::play()
{
	if(curindex.row() < 0) {
		curindex = tree->pmodel.mapToSource(tree->pmodel.index(0, 0));
	}
	plindex = tree->model.index(curindex.row(), tree->header()->logicalIndex(0));
	//plindex = model.index(curindex.row(), PlaylistModel::File);
	tree->model.setCurrent(plindex.row());
	tree->setCurrentIndex(tree->pmodel.mapFromSource(plindex));
	tree->scrollTo(tree->pmodel.mapFromSource(plindex));
	disconnect(&PlayerManager::Self(), SIGNAL(finish()), 0, 0);
	disconnect(&PlayerManager::Self(), SIGNAL(position(double)), 0, 0);
	if(PlayerManager::Self().playing()) PlayerManager::Self().close();
	if(!PlayerManager::Self().open(tree->model.data(tree->model.index(plindex.row(), PlaylistModel::File), Qt::UserRole).toUrl(), tree->model.data(tree->model.index(plindex.row(), PlaylistModel::CueStart), Qt::DisplayRole).toLongLong(), tree->model.data(tree->model.index(plindex.row(), PlaylistModel::CueLength), Qt::DisplayRole).toLongLong())) {
		Console::Self().error(tr("Can not open %1").arg(tree->model.data(tree->model.index(plindex.row(), PlaylistModel::File), Qt::UserRole).toUrl().toString()));
		//Console::Self().error(ToLocalFile(model.data(model.index(plindex.row(), PlaylistModel::File), Qt::UserRole).toUrl()));
		playing = false;
		error_count ++;
		if(error_count < 5) next();
		else {
			error_count = 0;
			return;
		}
	}
	error_count = 0;
	connect(&PlayerManager::Self(), SIGNAL(finish()), this, SLOT(playFinished()));
	connect(&PlayerManager::Self(), SIGNAL(position(double)), this, SLOT(position(double)));
	PlayerManager::Self().play();
	playing = true;
	emit started(this);
	emit playPauseIcon (false); // finished playing, show the "pause" icon
	tree->model.setData(tree->model.index(plindex.row(), PlaylistModel::StartTime), QDateTime::currentDateTime().toTime_t(), Qt::EditRole);
	info = tree->model.data(tree->model.index(plindex.row(), PlaylistModel::Title), Qt::DisplayRole).toString();
	QString ar = tree->model.data(tree->model.index(plindex.row(), PlaylistModel::Artist), Qt::DisplayRole).toString();
	QString alb = tree->model.data(tree->model.index(plindex.row(), PlaylistModel::Album), Qt::DisplayRole).toString();
	long len = tree->model.data(tree->model.index(plindex.row(), PlaylistModel::CueLength), Qt::DisplayRole).toLongLong() / 75;
	emit message(info, alb, ar, len);
	int n = tree->model.data(tree->model.index(plindex.row(), PlaylistModel::Track), Qt::DisplayRole).toInt();
	if(PLSet.lastfmScrobbler && ar.size()) {
		LastFM::Self().nowplaying(ar, info, alb, 0, n);
	}
	if(PLSet.librefmScrobbler && ar.size()) {
		LibreFM::Self().nowplaying(ar, info, alb, 0, n);
	}
}

void PlaylistStandard::stop()
{
	tree->model.setCurrent(-1);
	plindex = tree->model.index(-1, 0);
    PlayerManager::Self().stop();
    playing = false;
	emit message("", "", "", 0);
	emit songPosition(0);
}

void PlaylistStandard::playFinished()
{
	if(PLSet.lastfmScrobbler || PLSet.librefmScrobbler) {
		QString a = tree->model.data(tree->model.index(plindex.row(), PlaylistModel::Artist), Qt::DisplayRole).toString();
		QString t = tree->model.data(tree->model.index(plindex.row(), PlaylistModel::Title), Qt::DisplayRole).toString();
		QString b = tree->model.data(tree->model.index(plindex.row(), PlaylistModel::Album), Qt::DisplayRole).toString();
		int n = tree->model.data(tree->model.index(plindex.row(), PlaylistModel::Track), Qt::DisplayRole).toInt();
		long len = tree->model.data(tree->model.index(plindex.row(), PlaylistModel::CueLength), Qt::DisplayRole).toLongLong() / 75;
		uint start = tree->model.data(tree->model.index(plindex.row(), PlaylistModel::StartTime), Qt::DisplayRole).toLongLong();
		if(PLSet.lastfmScrobbler) LastFM::Self().submission(a, t, start, b, len, "P", "", n);
		if(PLSet.librefmScrobbler) LibreFM::Self().submission(a, t, start, b, len, "P", "", n);
	}	
	emit playPauseIcon (true); // finished playing, show the "play" icon
	next();
}

QModelIndex PlaylistStandard::nextItem()
{
	srand( time(NULL) );
	if(tree->model.rowCount() < 1) return tree->model.index(-1, 0);
	QModelIndex next;
	if(queue.count()) {
		next = queue.first();
		queue.pop_front();
		tree->model.setData(tree->model.index(next.row(), PlaylistModel::Stat), "", Qt::EditRole);
		for(int i=0; i<queue.count(); i++)
			tree->model.setData(tree->model.index(queue[i].row(), PlaylistModel::Stat), QVariant(i+1), Qt::EditRole);
	} else if(PlayerManager::Self().shuffle_mode) {
		if(shuffle_count >= tree->model.rowCount()) {
			if(PlayerManager::Self().repeat_mode) {
				shuffle_count = 0;
				next = tree->model.index(rand()%tree->model.rowCount(), 0);
				for(int i = 0; i < tree->model.rowCount(); i++)
					tree->model.setData(tree->model.index(i, PlaylistModel::Empty), "", Qt::EditRole);
			} else {
				next = tree->model.index(-1, 0);
			}
		} else if(shuffle_count == tree->model.rowCount()-1) {
			for(int i = 0; i < tree->model.rowCount(); i++)
				if(!tree->model.data(tree->model.index(i, PlaylistModel::Empty), Qt::DisplayRole).toString().size())
					next = tree->model.index(i, 0);
		} else {
			do {
				if(plindex.row() >= 0) next = tree->model.index((plindex.row()+rand())%tree->model.rowCount(), 0);
				else if(curindex.row() >= 0) next = tree->model.index((curindex.row()+rand())%tree->model.rowCount(), 0);
				else next = tree->model.index(rand()%tree->model.rowCount(), 0);
			} while(tree->model.data(tree->model.index(next.row(), PlaylistModel::Empty), Qt::DisplayRole).toString().size());
		}
	} else {
		if(tree->pmodel.mapFromSource(curindex).row() >= 0) 
			next = tree->pmodel.mapToSource(tree->pmodel.index(tree->pmodel.mapFromSource(curindex).row()+1, 0));
		if(next.row() < 0) {
			if(PlayerManager::Self().repeat_mode) next = tree->pmodel.mapToSource(tree->pmodel.index(0, 0));
			else next = tree->model.index(-1, 0);
		}
	}
	return next;
}

QModelIndex PlaylistStandard::prevItem()
{
	QModelIndex prev;
	if(prev_queue.count()) {
		prev = prev_queue.last();
		prev_queue.pop_back();
		return prev;
	}
	if(tree->pmodel.mapFromSource(curindex).row() >= 0) 
		prev = tree->pmodel.mapToSource(tree->pmodel.index(tree->pmodel.mapFromSource(curindex).row()-1, 0));
	if(prev.row() < 0) {
		if(PlayerManager::Self().repeat_mode) prev = tree->pmodel.mapToSource(tree->pmodel.index(tree->pmodel.rowCount()-1, 0));
		else prev = tree->model.index(-1, 0);
	}
	return prev;
}

void PlaylistStandard::onClick(const QModelIndex &index)
{
	//if(curindex.row() >= 0) prev_queue.push_back(curindex);
	curindex = tree->pmodel.mapToSource(index);
}

void PlaylistStandard::onDoubleClick(const QModelIndex &index)
{
	//if(curindex.row() >= 0) prev_queue.push_back(curindex);
	if(plindex.row() >= 0) prev_queue.push_back(plindex);
	curindex = tree->pmodel.mapToSource(index);
	rateSong(curindex, +1);
	play();
	emit playPauseIcon (false); // show a "pause" 
}

void PlaylistStandard::position(double pos)
{
	emit songPosition((int)(1000*pos));
}

void PlaylistStandard::clear()
{
	plindex = curindex = insindex = tree->model.index(-1, 0);
	queue.clear();
	prev_queue.clear();
	tree->setCurrentIndex(curindex);
	tree->model.removeRows(0, tree->model.rowCount());
}

void PlaylistStandard::queueNext()
{
	foreach(QModelIndex i1, tree->getSelectedIndexes()) {
		QModelIndex ind = tree->pmodel.mapToSource(i1);
		bool duplicate = false;
		foreach(QModelIndex ind2, queue) if(ind.row() == ind2.row()) {
			duplicate = true;
			break;
		}
		if(duplicate) continue;
		queue.append(ind);
		rateSong(ind, +1);
		tree->model.setData(tree->model.index(ind.row(), PlaylistModel::Stat), QVariant(queue.count()), Qt::EditRole);
	}
}

void PlaylistStandard::editTag()
{
	if(curindex.row() >= 0) {
		TagEditor *te = new TagEditor(ToLocalFile(tree->model.data(tree->model.index(curindex.row(), PlaylistModel::File), Qt::UserRole).toUrl()), 0);
		te->index = curindex.row();
		connect(te, SIGNAL(editComplete(int)), this, SLOT(updateTag(int)));
		//resetTags(curindex);
		te->setAttribute(Qt::WA_DeleteOnClose);
		te->show();
	}
}

void PlaylistStandard::updateTag(int i)
{
	QModelIndex ind = tree->model.index(i, 0); 
	resetTags(ind);
}

void PlaylistStandard::resetTags(QModelIndex& ind)
{
	QString path = ToLocalFile(tree->model.data(tree->model.index(ind.row(), PlaylistModel::File), Qt::UserRole).toUrl());
	QString title, artist, album, comment, genre, length, type;
	int track, year, rating=0;
	
	Tagger::readTags(path, title, artist, album, comment, genre, track, year, length);
	
	addItem(title, PlaylistModel::Title, &ind);
	addItem(artist, PlaylistModel::Artist, &ind);
	addItem(album, PlaylistModel::Album, &ind);
	addItem(QString::number(year), PlaylistModel::Year, &ind);
	addItem(comment, PlaylistModel::Comment, &ind);
	addItem(QString::number(track), PlaylistModel::Track, &ind);
	addItem(genre, PlaylistModel::Genre, &ind);

	if(Database::Self().GetTags(path, title, artist, album, comment, genre, track, year, rating, length, type)) {
		addItem(qVariantFromValue(StarRating(rating)), PlaylistModel::Rating, &ind);
	}
}

void PlaylistStandard::removeSong()
{
	QList<int> list;
	foreach(QModelIndex ind, /*pmodel.mapSelectionToSource(*/tree->getSelectedIndexes()) {
		if(!list.contains(ind.row())) 
			list << /*pmodel.mapToSource(*/ind.row();
	}
	qSort(list.begin(), list.end(), qGreater<int>());
	foreach(int ind, list) {
		if(curindex.row() == tree->pmodel.mapToSource(tree->pmodel.index(ind, 0)).row()) {
			curindex = tree->model.index(-1, 0);
			tree->setCurrentIndex(curindex);
		}
		tree->pmodel.removeRows(ind, 1);
	}
}

void PlaylistStandard::reloadTags()
{
	foreach(QModelIndex ind, tree->getSelectedIndexes()) {
		QModelIndex i2 = tree->pmodel.mapToSource(ind);
		resetTags(i2);
	}
	//if(curindex.row() >= 0) resetTags(curindex);
}

void PlaylistStandard::setAutosave(bool b)
{
	autosave = b;
}

void PlaylistStandard::updateStatus()
{
	if(delayedPlay && tree->model.rowCount() > delayedIndex) {
		delayedPlay = false;
		setCurrent(delayedIndex);
		//play();
		//if(delayedPos >= 0 && delayedPos <= 1)
		//	position(delayedPos);
	}
	if(!delayedPlay && delayedIndex >= 0 && tree->model.rowCount() > delayedIndex) {
		setCurrent(delayedIndex);
	}
	QDateTime time;
	for(int i=0; i<tree->model.rowCount(); i++) {
		time = time.addSecs(tree->model.data(tree->model.index(i, PlaylistModel::CueLength), Qt::DisplayRole).toLongLong() / 75);
	}
	QString st = tr("Playlist - %n song(s)", "", tree->model.rowCount());
	if(QDateTime().daysTo(time) > 1) {
		st += " (" +
			QString::number(QDateTime().daysTo(time)-1) +
			"d " +
			QString::number(time.time().hour()) +
			"h)";
	} else {
		st += " (" + time.time().toString()+")";
	}
	emit status(st);
}

void PlaylistStandard::rateSong(QModelIndex &ind, int r, int offset)
{
	if(!PLSet.autoRating || (!r && !offset)) return;
	QString path = ToLocalFile(tree->model.data(tree->model.index(ind.row(), PlaylistModel::File), Qt::UserRole).toUrl());
	QString title, artist, album, comment, genre, length, type;
	int track, year, rating;
	if(Database::Self().GetTags(path, title, artist, album, comment, genre, track, year, rating, length, type)) {
		if(r) {
			r = r * (5 - abs(rating/10));
		} else {
			r = offset;
		}
		Database::Self().SetTags(path, title, artist, album, comment, genre, track, year, rating+r);
	}
	Console::Self().log((r>0?"rate up ":"rate down ") + title);
}

int PlaylistStandard::curIndex()
{
	return plindex.row() >= 0 ? plindex.row() : curindex.row();
}

double PlaylistStandard::curPosition()
{
	return PlayerManager::Self().getPosition();
}

void PlaylistStandard::rateCurrent(int offset, int value)
{
	if(playing) {
		bool ar = PLSet.autoRating;
		PLSet.autoRating = true;
		rateSong(plindex, 0, offset+value);
		PLSet.autoRating = ar;
		resetTags(plindex);
	}
}

QString PlaylistStandard::curFile()
{
	if(curindex.row() >= 0) {
		return ToLocalFile(tree->model.data(tree->model.index(curindex.row(), PlaylistModel::File), Qt::UserRole).toUrl());
	}
	return "";
}

void PlaylistStandard::setFilter(QString s)
{
	tree->pmodel.setFilterRegExp(s);
}

void PlaylistStandard::findCurrent()
{
	if(plindex.row() >= 0) {
		tree->setCurrentIndex(tree->pmodel.mapFromSource(plindex));
		tree->scrollTo(tree->pmodel.mapFromSource(plindex));
	}
}

void PlaylistStandard::setCurrent(int index)
{
	if(index >= 0 && index < tree->model.rowCount()) {
		curindex = tree->model.index(index, 0);
		tree->clearSelection();
		tree->setCurrentIndex(tree->pmodel.mapFromSource(curindex));
		//tree->model.setCurrent(index);
		tree->scrollTo(tree->pmodel.mapFromSource(curindex));
	} else {
		delayedIndex = index;
		delayedPlay = false;
	}
}
