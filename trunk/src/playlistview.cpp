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
#include <QtXml>

const QString XMLNS("http://code.google.com/p/cuberok");

/***********************
 * 
 *    PlaylistView
 * 
 ***********************/ 

PlaylistView::PlaylistView(QString &str, QWidget *parent)
    : QTreeView(parent), correct(false), playing(false), dragStarted(false), autosave(false), shuffle_count(0), delayedPlay(false), delayedIndex(-1), delayedPos(0.0), error_count(0)
{
	setItemDelegate(new StarDelegate);
	plistname = str;
    pmodel.setDynamicSortFilter(true);
	pmodel.setFilterCaseSensitivity(Qt::CaseInsensitive);
	pmodel.setFilterKeyColumn(-1);
    pmodel.setSourceModel(&model);
	setModel(&pmodel);
	setEditTriggers(QAbstractItemView::NoEditTriggers); 
	setSelectionMode(QAbstractItemView::ExtendedSelection);
	//setSortingEnabled(true);
	setAlternatingRowColors(true);
	connect(this, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onClick(const QModelIndex &)));
	connect(this, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(onDoubleClick(const QModelIndex &)));
	sortByColumn(PlaylistModel::Number, Qt::AscendingOrder);
	if(plistname.size()) {  // read stored playlist
		QString fname = QDir::homePath() + "/.cuberok/" + plistname + ".xspf";
		if(QFile::exists(fname)) loadList(fname);
		else {
			fname = QDir::homePath() + "/.cuberok/" + plistname + ".m3u";
			if(QFile::exists(fname)) loadList(fname);
		}
	}
	for(int i=0; i<PlaylistModel::ColumnCount; i++) {
		setColumnHidden(i, !PLSet.columnVisible(i));
		setColumnWidth(i, PLSet.columnWidth(i));
		header()->moveSection(header()->visualIndex(i), PLSet.columnPosition(i));
	}
	hideColumn(PlaylistModel::Empty);
	hideColumn(PlaylistModel::CueStart);
	hideColumn(PlaylistModel::CueLength);
	hideColumn(PlaylistModel::DBIndex);
	hideColumn(PlaylistModel::StartTime);
	header()->moveSection(PlaylistModel::Number, PlaylistModel::Stat);
	connect(&PLSet, SIGNAL(visibleChanged(int,bool)), this, SLOT(setColVisible(int,bool)));
	connect(&PLSet, SIGNAL(widthChanged(int,int)), this, SLOT(setColWidth(int,int)));
	connect(&PLSet, SIGNAL(positionChanged(int,int)), this, SLOT(setColPosition(int,int)));
	connect(&model, SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(updateStatus()));
	connect(&model, SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(updateStatus()));
	//connect(&header(), SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(updateStatus()));
}

PlaylistView::~PlaylistView()
{
	QString fname = QDir::homePath() + "/.cuberok/" + plistname + ".xspf";
	if(autosave) storeListXSPF(fname);
	else QFile::remove(fname);
}

void PlaylistView::dragEnterEvent(QDragEnterEvent *event)
{
	if(event->source() != this)
		event->acceptProposedAction();
}

void PlaylistView::storeListM3U(QString fname)
{
	if(!fname.size()) return;
	QFile file(fname);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream out(&file);
		out << "#EXTM3U" << endl;
		for(int i=0; i<model.rowCount(); i++) {
			out << model.data(model.index(i, PlaylistModel::File), Qt::UserRole).toUrl().toString() << endl;
		}
		file.close();
	}
}

void PlaylistView::storeListXSPF(QString fname)
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
		xml.writeTextElement("title", QFileInfo(fname).baseName());
		xml.writeTextElement("creator", "Cuberok");
		xml.writeTextElement("date", QDateTime::currentDateTime().toUTC().toString("yyyy-MM-dd'T'hh:mm:ss"));
		xml.writeStartElement("trackList");
		for(int i=0; i<model.rowCount(); i++) {
			xml.writeStartElement("track");
			xml.writeTextElement("location", model.data(model.index(i, PlaylistModel::File), Qt::UserRole).toUrl().toString());
			xml.writeTextElement("title", model.data(model.index(i, PlaylistModel::Title), Qt::DisplayRole).toString());
			xml.writeTextElement("creator", model.data(model.index(i, PlaylistModel::Artist), Qt::DisplayRole).toString());
			xml.writeTextElement("annotation", model.data(model.index(i, PlaylistModel::Comment), Qt::DisplayRole).toString());
			xml.writeTextElement("album", model.data(model.index(i, PlaylistModel::Album), Qt::DisplayRole).toString());
			xml.writeTextElement("trackNum", QString::number(model.data(model.index(i, PlaylistModel::Track), Qt::DisplayRole).toInt()));
			xml.writeStartElement("extension");
			xml.writeAttribute("application", XMLNS);
			xml.writeTextElement(XMLNS, "cuestart", QString::number(model.data(model.index(i, PlaylistModel::CueStart), Qt::DisplayRole).toLongLong()));
			xml.writeTextElement(XMLNS, "cuelength", QString::number(model.data(model.index(i, PlaylistModel::CueLength), Qt::DisplayRole).toLongLong()));
			xml.writeTextElement(XMLNS, "dbindex", QString::number(model.data(model.index(i, PlaylistModel::DBIndex), Qt::DisplayRole).toLongLong()));
			xml.writeTextElement(XMLNS, "genre", model.data(model.index(i, PlaylistModel::Genre), Qt::DisplayRole).toString());
			xml.writeTextElement(XMLNS, "length", model.data(model.index(i, PlaylistModel::Length), Qt::DisplayRole).toString());
			xml.writeTextElement(XMLNS, "year", QString::number(model.data(model.index(i, PlaylistModel::Year), Qt::DisplayRole).toInt()));
			xml.writeTextElement(XMLNS, "rating", QString::number(qVariantValue<StarRating>(model.data(model.index(i, PlaylistModel::Rating), Qt::DisplayRole)).rating()));
			xml.writeEndElement(); //extension
			xml.writeEndElement(); //track
		}
		xml.writeEndElement(); // trackList
		xml.writeEndElement(); //playlist
		xml.writeEndDocument();
	}
}

void PlaylistView::loadList(QString fname)
{
	while(model.rowCount()) model.removeRow(0);
	addUrl(QUrl::fromLocalFile(fname));
}

void PlaylistView::addUrl(QUrl url)
{
// 	if(url.scheme().toLower() == "http") {
// 		QMimeData data;
// 		QList<QUrl> list;
// 		list << url;
// 		data.setUrls(list);
// 		model.dropMimeData(&data, Qt::CopyAction, model.rowCount(), 0, QModelIndex());
// 		return;
// 	}
	QList<TagEntry> list = Tagger::readEntry(url);
	Console::Self().log("Add URL: "+url.toString() + " " + QString::number(list.size()) + " record(s)");
	model.appendList(list);
// 	foreach(TagEntry tag, list) {
// 		int row = model.rowCount();
// 		model.insertRow(row);
// 		model.setData(model.index(row, PlaylistModel::File), tag.url, Qt::EditRole);
// 		model.setData(model.index(row, PlaylistModel::Title), tag.title, Qt::EditRole);
// 		model.setData(model.index(row, PlaylistModel::Artist), tag.artist, Qt::EditRole);
// 		model.setData(model.index(row, PlaylistModel::Comment), tag.comment, Qt::EditRole);
// 		model.setData(model.index(row, PlaylistModel::Album), tag.album, Qt::EditRole);
// 		model.setData(model.index(row, PlaylistModel::Track), tag.track, Qt::EditRole);
// 		model.setData(model.index(row, PlaylistModel::CueStart), (qlonglong)tag.start, Qt::EditRole);
// 		model.setData(model.index(row, PlaylistModel::CueLength), (qlonglong)tag.length, Qt::EditRole);
// 		model.setData(model.index(row, PlaylistModel::DBIndex), (qlonglong)tag.dbindex, Qt::EditRole);
// 		model.setData(model.index(row, PlaylistModel::Genre), tag.genre, Qt::EditRole);
// 		model.setData(model.index(row, PlaylistModel::Length), tag.slength, Qt::EditRole);
// 		model.setData(model.index(row, PlaylistModel::Year), tag.year, Qt::EditRole);
// 		model.setData(model.index(row, PlaylistModel::Rating), qVariantFromValue(StarRating(tag.rating)), Qt::EditRole);
// 	}
}

bool PlaylistView::isPlaying()
{
	return playing;
}

// start drag&drop block
void PlaylistView::dropEvent(QDropEvent *event)
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

void PlaylistView::startDrag(Qt::DropActions supportedActions)
{
	dragStarted = true;
	QTreeView::startDrag(supportedActions);
	dragStarted = false;
}


// end drag&drop block

void PlaylistView::addItem(QVariant item, int id, QModelIndex* ind)
{
	if(!ind) ind = &insindex;
	if(id == PlaylistModel::File)
		model.insertRows(ind->row()<0 ? model.rowCount() : ind->row(), 1);
	model.setData(ind->row()<0 ? model.index(model.rowCount()-1, id) : model.index(ind->row(), id), item, Qt::EditRole);
}

void PlaylistView::prev()
{
	QModelIndex prev = prevItem();
	if(prev.row() >= 0) {
		clearSelection();
		setCurrentIndex(pmodel.mapFromSource(prev));
		curindex = prev;
		play();
	}
}

void PlaylistView::next()
{
	QModelIndex next;
	do {
		next = nextItem();
	} while(qVariantValue<StarRating>(model.data(model.index(next.row(), PlaylistModel::Rating), Qt::DisplayRole)).rating() <= -50);
	if(next.row() >= 0) {
		if(plindex.row() >= 0) {
			prev_queue.push_back(plindex);
			if(PlayerManager::Self().shuffle_mode) {
				model.setData(model.index(plindex.row(), PlaylistModel::Empty), "1", Qt::EditRole);
				shuffle_count ++;
			}
			if(PlayerManager::Self().playing()) rateSong(plindex, -1);
		}
		clearSelection();
		curindex = next;
		setCurrentIndex(pmodel.mapFromSource(curindex));
		play();
	}
	//else stop();
}

void PlaylistView::play(int index, double pos)
{
	if(index >= 0 && index < model.rowCount()) {
		curindex = model.index(index, 0);
		setCurrentIndex(pmodel.mapFromSource(curindex));
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

void PlaylistView::play()
{
	if(curindex.row() < 0) {
		curindex = pmodel.mapToSource(pmodel.index(0, 0));
	}
	plindex = model.index(curindex.row(), header()->logicalIndex(0));
	//plindex = model.index(curindex.row(), PlaylistModel::File);
	model.setCurrent(plindex.row());
	setCurrentIndex(pmodel.mapFromSource(plindex));
	disconnect(&PlayerManager::Self(), SIGNAL(finish()), 0, 0);
	disconnect(&PlayerManager::Self(), SIGNAL(position(double)), 0, 0);
	if(PlayerManager::Self().playing()) PlayerManager::Self().close();
	if(!PlayerManager::Self().open(model.data(model.index(plindex.row(), PlaylistModel::File), Qt::UserRole).toUrl(), model.data(model.index(plindex.row(), PlaylistModel::CueStart), Qt::DisplayRole).toLongLong(), model.data(model.index(plindex.row(), PlaylistModel::CueLength), Qt::DisplayRole).toLongLong())) {
		Console::Self().error(tr("Can not open %1").arg(model.data(model.index(plindex.row(), PlaylistModel::File), Qt::UserRole).toUrl().toString()));
		Console::Self().error(ToLocalFile(model.data(model.index(plindex.row(), PlaylistModel::File), Qt::UserRole).toUrl()));
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
	model.setData(model.index(plindex.row(), PlaylistModel::StartTime), QDateTime::currentDateTime().toTime_t(), Qt::EditRole);
	info = model.data(model.index(plindex.row(), PlaylistModel::Title), Qt::DisplayRole).toString();
	QString ar = model.data(model.index(plindex.row(), PlaylistModel::Artist), Qt::DisplayRole).toString();
	QString alb = model.data(model.index(plindex.row(), PlaylistModel::Album), Qt::DisplayRole).toString();
	long len = model.data(model.index(plindex.row(), PlaylistModel::CueLength), Qt::DisplayRole).toLongLong() / 75;
	emit message(info, alb, ar, len);
	int n = model.data(model.index(plindex.row(), PlaylistModel::Track), Qt::DisplayRole).toInt();
	if(PLSet.lastfmScrobbler && ar.size()) {
		LastFM::Self().nowplaying(ar, info, alb, 0, n);
	}
	if(PLSet.librefmScrobbler && ar.size()) {
		LibreFM::Self().nowplaying(ar, info, alb, 0, n);
	}
}

void PlaylistView::stop()
{
	model.setCurrent(-1);
	plindex = model.index(-1, 0);
    PlayerManager::Self().stop();
    playing = false;
	emit message("", "", "", 0);
	emit songPosition(0);
}

void PlaylistView::playFinished()
{
	if(PLSet.lastfmScrobbler || PLSet.librefmScrobbler) {
		QString a = model.data(model.index(plindex.row(), PlaylistModel::Artist), Qt::DisplayRole).toString();
		QString t = model.data(model.index(plindex.row(), PlaylistModel::Title), Qt::DisplayRole).toString();
		QString b = model.data(model.index(plindex.row(), PlaylistModel::Album), Qt::DisplayRole).toString();
		int n = model.data(model.index(plindex.row(), PlaylistModel::Track), Qt::DisplayRole).toInt();
		long len = model.data(model.index(plindex.row(), PlaylistModel::CueLength), Qt::DisplayRole).toLongLong() / 75;
		uint start = model.data(model.index(plindex.row(), PlaylistModel::StartTime), Qt::DisplayRole).toLongLong();
		if(PLSet.lastfmScrobbler) LastFM::Self().submission(a, t, start, b, len, "P", "", n);
		if(PLSet.librefmScrobbler) LibreFM::Self().submission(a, t, start, b, len, "P", "", n);
	}	
	next();
}

QModelIndex PlaylistView::nextItem()
{
	srand( time(NULL) );
	if(model.rowCount() < 1) return model.index(-1, 0);
	QModelIndex next;
	if(queue.count()) {
		next = queue.first();
		queue.pop_front();
		model.setData(model.index(next.row(), PlaylistModel::Stat), "", Qt::EditRole);
		for(int i=0; i<queue.count(); i++)
			model.setData(model.index(queue[i].row(), PlaylistModel::Stat), QVariant(i+1), Qt::EditRole);
	} else if(PlayerManager::Self().shuffle_mode) {
		if(shuffle_count >= model.rowCount()) {
			if(PlayerManager::Self().repeat_mode) {
				shuffle_count = 0;
				next = model.index(rand()%model.rowCount(), 0);
				for(int i = 0; i < model.rowCount(); i++)
					model.setData(model.index(i, PlaylistModel::Empty), "", Qt::EditRole);
			} else {
				next = model.index(-1, 0);
			}
		} else if(shuffle_count == model.rowCount()-1) {
			for(int i = 0; i < model.rowCount(); i++)
				if(!model.data(model.index(i, PlaylistModel::Empty), Qt::DisplayRole).toString().size())
					next = model.index(i, 0);
		} else {
			do {
				if(plindex.row() >= 0) next = model.index((plindex.row()+rand())%model.rowCount(), 0);
				else if(curindex.row() >= 0) next = model.index((curindex.row()+rand())%model.rowCount(), 0);
				else next = model.index(rand()%model.rowCount(), 0);
			} while(model.data(model.index(next.row(), PlaylistModel::Empty), Qt::DisplayRole).toString().size());
		}
	} else {
		if(pmodel.mapFromSource(curindex).row() >= 0) 
			next = pmodel.mapToSource(pmodel.index(pmodel.mapFromSource(curindex).row()+1, 0));
		if(next.row() < 0) {
			if(PlayerManager::Self().repeat_mode) next = pmodel.mapToSource(pmodel.index(0, 0));
			else next = model.index(-1, 0);
		}
	}
	return next;
}

QModelIndex PlaylistView::prevItem()
{
	QModelIndex prev;
	if(prev_queue.count()) {
		prev = prev_queue.last();
		prev_queue.pop_back();
		return prev;
	}
	if(pmodel.mapFromSource(curindex).row() >= 0) 
		prev = pmodel.mapToSource(pmodel.index(pmodel.mapFromSource(curindex).row()-1, 0));
	if(prev.row() < 0) {
		if(PlayerManager::Self().repeat_mode) prev = pmodel.mapToSource(pmodel.index(pmodel.rowCount()-1, 0));
		else prev = model.index(-1, 0);
	}
	return prev;
}

void PlaylistView::onClick(const QModelIndex &index)
{
	//if(curindex.row() >= 0) prev_queue.push_back(curindex);
	curindex = pmodel.mapToSource(index);
}

void PlaylistView::onDoubleClick(const QModelIndex &index)
{
	//if(curindex.row() >= 0) prev_queue.push_back(curindex);
	if(plindex.row() >= 0) prev_queue.push_back(plindex);
	curindex = pmodel.mapToSource(index);
	rateSong(curindex, +1);
	play();
}

void PlaylistView::position(double pos)
{
	emit songPosition((int)(1000*pos));
}

void PlaylistView::clear()
{
	plindex = curindex = insindex = model.index(-1, 0);
	queue.clear();
	prev_queue.clear();
	setCurrentIndex(curindex);
	model.removeRows(0, model.rowCount());
}

void PlaylistView::queueNext()
{
	foreach(QModelIndex i1, this->selectedIndexes()) {
		QModelIndex ind = pmodel.mapToSource(i1);
		bool duplicate = false;
		foreach(QModelIndex ind2, queue) if(ind.row() == ind2.row()) {
			duplicate = true;
			break;
		}
		if(duplicate) continue;
		queue.append(ind);
		rateSong(ind, +1);
		model.setData(model.index(ind.row(), PlaylistModel::Stat), QVariant(queue.count()), Qt::EditRole);
	}
}

void PlaylistView::editTag()
{
	if(curindex.row() >= 0) {
		TagEditor *te = new TagEditor(ToLocalFile(model.data(model.index(curindex.row(), PlaylistModel::File), Qt::UserRole).toUrl()), this);
		te->index = curindex.row();
		connect(te, SIGNAL(editComplete(int)), this, SLOT(updateTag(int)));
		//resetTags(curindex);
		te->setAttribute(Qt::WA_DeleteOnClose);
		te->show();
	}
}

void PlaylistView::updateTag(int i)
{
	QModelIndex ind = model.index(i, 0); 
	resetTags(ind);
}

void PlaylistView::resetTags(QModelIndex& ind)
{
	QString path = ToLocalFile(model.data(model.index(ind.row(), PlaylistModel::File), Qt::UserRole).toUrl());
	QString title, artist, album, comment, genre, length;
	int track, year, rating=0;
	
	Tagger::readTags(path, title, artist, album, comment, genre, track, year, length);
	
	addItem(title, PlaylistModel::Title, &ind);
	addItem(artist, PlaylistModel::Artist, &ind);
	addItem(album, PlaylistModel::Album, &ind);
	addItem(QString::number(year), PlaylistModel::Year, &ind);
	addItem(comment, PlaylistModel::Comment, &ind);
	addItem(QString::number(track), PlaylistModel::Track, &ind);
	addItem(genre, PlaylistModel::Genre, &ind);

	if(Database::Self().GetTags(path, title, artist, album, comment, genre, track, year, rating, length)) {
		addItem(qVariantFromValue(StarRating(rating)), PlaylistModel::Rating, &ind);
	}
}

void PlaylistView::removeSong()
{
	QList<int> list;
	foreach(QModelIndex ind, /*pmodel.mapSelectionToSource(*/this->selectedIndexes()) {
		if(!list.contains(ind.row())) 
			list << /*pmodel.mapToSource(*/ind.row();
	}
	qSort(list.begin(), list.end(), qGreater<int>());
	foreach(int ind, list) {
		if(curindex.row() == pmodel.mapToSource(pmodel.index(ind, 0)).row()) {
			curindex = model.index(-1, 0);
			setCurrentIndex(curindex);
		}
		pmodel.removeRows(ind, 1);
	}
}

void PlaylistView::reloadTags()
{
	foreach(QModelIndex ind, this->selectedIndexes()) {
		QModelIndex i2 = pmodel.mapToSource(ind);
		resetTags(i2);
	}
	//if(curindex.row() >= 0) resetTags(curindex);
}

void PlaylistView::setColVisible(int c, bool v)
{
	if(v) showColumn(c);
	else hideColumn(c);
}

void PlaylistView::setColWidth(int c, int w)
{
	setColumnWidth(c, w);
}

void PlaylistView::setColPosition(int c, int p)
{
	header()->moveSection(header()->visualIndex(c), p);
}

void PlaylistView::setAutosave(bool b)
{
	autosave = b;
}

void PlaylistView::hideEvent ( QHideEvent * event )
{
	for(int i=0; i<PlaylistModel::ColumnCount; i++) {
		PLSet.setColumnWidth(i, columnWidth(i));
		PLSet.setColumnPosition(i, header()->visualIndex(i));
	}
	QTreeView::hideEvent(event);
}

void PlaylistView::showEvent ( QShowEvent * event )
{
	updateStatus();
}

void PlaylistView::updateStatus()
{
	if(delayedPlay && model.rowCount() > delayedIndex) {
		delayedPlay = false;
		curindex = model.index(delayedIndex, 0);
		setCurrentIndex(pmodel.mapFromSource(curindex));
		//play();
		//if(delayedPos >= 0 && delayedPos <= 1)
		//	position(delayedPos);
	}
	if(!delayedPlay && delayedIndex >= 0 && model.rowCount() > delayedIndex) {
		curindex = model.index(delayedIndex, 0);
		setCurrentIndex(pmodel.mapFromSource(curindex));
	}
	long len = 0;
	for(int i=0; i<model.rowCount(); i++) {
		len += model.data(model.index(i, PlaylistModel::CueLength), Qt::DisplayRole).toLongLong() / 75;
	}
	emit status(tr("Playlist - %n song(s)", "", model.rowCount()) + " (" + QTime().addSecs(len).toString()+")");
}

QString PlaylistView::getName()
{
	return plistname;
}

void PlaylistView::setName(QString newname)
{
	if(plistname != newname) {
		QString fname = QDir::homePath() + "/.cuberok/" + plistname + ".m3u";
		QFile::remove(fname);
		plistname = newname;
	}
}

void PlaylistView::rateSong(QModelIndex &ind, int r, int offset)
{
	if(!PLSet.autoRating || (!r && !offset)) return;
	QString path = ToLocalFile(model.data(model.index(ind.row(), PlaylistModel::File), Qt::UserRole).toUrl());
	QString title, artist, album, comment, genre, length;
	int track, year, rating;
	if(Database::Self().GetTags(path, title, artist, album, comment, genre, track, year, rating, length)) {
		if(r) {
			r = r * (5 - abs(rating/10));
		} else {
			r = offset;
		}
		Database::Self().SetTags(path, title, artist, album, comment, genre, track, year, rating+r);
	}
	Console::Self().log((r>0?"rate up ":"rate down ") + title);
}

int PlaylistView::curIndex()
{
	return plindex.row() >= 0 ? plindex.row() : curindex.row();
}

double PlaylistView::curPosition()
{
	return PlayerManager::Self().getPosition();
}

void PlaylistView::rateCurrent(int offset, int value)
{
	if(playing) {
		bool ar = PLSet.autoRating;
		PLSet.autoRating = true;
		rateSong(plindex, 0, offset+value);
		PLSet.autoRating = ar;
		resetTags(plindex);
	}
}

QString PlaylistView::curFile()
{
	if(curindex.row() >= 0) {
		return ToLocalFile(model.data(model.index(curindex.row(), PlaylistModel::File), Qt::UserRole).toUrl());
	}
	return "";
}

void PlaylistView::setFilter(QString s)
{
	pmodel.setFilterRegExp(s);
}

void PlaylistView::findCurrent()
{
	if(plindex.row() >= 0) {
		setCurrentIndex(pmodel.mapFromSource(plindex));
	}
}

void PlaylistView::setCurrent(int index)
{
	if(index >= 0 && index < model.rowCount()) {
		curindex = model.index(index, 0);
		setCurrentIndex(pmodel.mapFromSource(curindex));
	} else {
		delayedIndex = index;
		delayedPlay = false;
	}
}
