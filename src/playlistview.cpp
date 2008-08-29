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
#include "tageditor.h"
#include "tagger.h"
#include "database.h"
#include "stardelegate.h"
#include "starrating.h"
#include "playlistsettings.h"
#include <QtXml>

const QString XMLNS("http://code.google.com/p/cuberok");

/***********************
 * 
 *    PlaylistView
 * 
 ***********************/ 

PlaylistView::PlaylistView(QString &str, QWidget *parent)
    : QTreeView(parent), correct(false), playing(false), dragStarted(false), autosave(false), shuffle_count(0), delayedPlay(false), delayedIndex(-1), delayedPos(0.0)
{
	setItemDelegate(new StarDelegate);
	plistname = str;
    pmodel.setDynamicSortFilter(true);
    pmodel.setSourceModel(&model);
	setModel(&pmodel);
	setEditTriggers(QAbstractItemView::NoEditTriggers); 
	setSelectionMode(QAbstractItemView::ExtendedSelection);
	//setSortingEnabled(true);
	connect(this, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onClick(const QModelIndex &)));
	connect(this, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(onDoubleClick(const QModelIndex &)));
	sortByColumn(PlaylistModel::Artist, Qt::AscendingOrder);
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
	}
	hideColumn(PlaylistModel::Empty);
	connect(&PLSet, SIGNAL(visibleChanged(int,bool)), this, SLOT(setColVisible(int,bool)));
	connect(&PLSet, SIGNAL(widthChanged(int,int)), this, SLOT(setColWidth(int,int)));
	connect(&model, SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(updateStatus()));
	connect(&model, SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(updateStatus()));
}

PlaylistView::~PlaylistView()
{
	QString fname = QDir::homePath() + "/.cuberok/" + plistname + ".xspf";
	if(autosave) storeListXSPF(fname);
	else QFile::remove(fname);
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
	QList<TagEntry> list = Tagger::readEntry(QUrl::fromLocalFile(fname));
	foreach(TagEntry tag, list) {
		int row = model.rowCount();
		model.insertRow(row);
		model.setData(model.index(row, PlaylistModel::File), tag.url, Qt::EditRole);
		model.setData(model.index(row, PlaylistModel::Title), tag.title, Qt::EditRole);
		model.setData(model.index(row, PlaylistModel::Artist), tag.artist, Qt::EditRole);
		model.setData(model.index(row, PlaylistModel::Comment), tag.comment, Qt::EditRole);
		model.setData(model.index(row, PlaylistModel::Album), tag.album, Qt::EditRole);
		model.setData(model.index(row, PlaylistModel::Track), tag.track, Qt::EditRole);
		model.setData(model.index(row, PlaylistModel::CueStart), (qlonglong)tag.start, Qt::EditRole);
		model.setData(model.index(row, PlaylistModel::CueLength), (qlonglong)tag.length, Qt::EditRole);
		model.setData(model.index(row, PlaylistModel::DBIndex), (qlonglong)tag.dbindex, Qt::EditRole);
		model.setData(model.index(row, PlaylistModel::Genre), tag.genre, Qt::EditRole);
		model.setData(model.index(row, PlaylistModel::Length), tag.slength, Qt::EditRole);
		model.setData(model.index(row, PlaylistModel::Year), tag.year, Qt::EditRole);
		model.setData(model.index(row, PlaylistModel::Rating), qVariantFromValue(StarRating(tag.rating)), Qt::EditRole);
	}
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
	//QMessageBox::information(0, tr(""), item);
	//item.insert(0, QString::number(item.at(0).unicode()));
	if(!ind) ind = &insindex;
	if(id == PlaylistModel::File)
		model.insertRows(ind->row()<0 ? model.rowCount() : ind->row(), 1);
	model.setData(ind->row()<0 ? model.index(model.rowCount()-1, id) : model.index(ind->row(), id), item, Qt::EditRole);
}

void PlaylistView::prev()
{
	clearSelection();
	QModelIndex prev = prevItem(); 
	setCurrentIndex(pmodel.mapFromSource(prev));
	curindex = prev;
	play();
}

void PlaylistView::next()
{
	if(plindex.row() >= 0) {
		prev_queue.push_back(plindex);
		if(PlayerManager::Self().shuffle_mode) {
			model.setData(model.index(plindex.row(), PlaylistModel::Empty), "1", Qt::EditRole);
			shuffle_count ++;
		}
		if(PlayerManager::Self().playing()) rateSong(plindex, -1);
	}
	QModelIndex next = nextItem();
	curindex = next;
	setCurrentIndex(pmodel.mapFromSource(curindex));
	if(curindex.row() >= 0) play();
	else stop();
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
	if(curindex.row() < 0) return;
	plindex = model.index(curindex.row(), PlaylistModel::File);
	//model.setCurrent(plindex.row());
	disconnect(&PlayerManager::Self(), SIGNAL(finish()), 0, 0);
	disconnect(&PlayerManager::Self(), SIGNAL(position(double)), 0, 0);
	if(PlayerManager::Self().playing()) PlayerManager::Self().close();
	if(!PlayerManager::Self().open(model.data(model.index(plindex.row(), PlaylistModel::File), Qt::UserRole).toUrl(), model.data(model.index(plindex.row(), PlaylistModel::CueStart), Qt::DisplayRole).toLongLong(), model.data(model.index(plindex.row(), PlaylistModel::CueLength), Qt::DisplayRole).toLongLong())) {
		QMessageBox::warning(0, tr("Error"), tr("Can not open %1").arg(model.data(model.index(plindex.row(), PlaylistModel::File), Qt::UserRole).toUrl().toString()));
		playing = false;
		return;
	}
	connect(&PlayerManager::Self(), SIGNAL(finish()), this, SLOT(playFinished()));
	connect(&PlayerManager::Self(), SIGNAL(position(double)), this, SLOT(position(double)));
	PlayerManager::Self().play();
	playing = true;
	emit started(this);
	//QMessageBox::information(this, tr(""), "message");
	info = model.data(model.index(plindex.row(), PlaylistModel::Title), Qt::DisplayRole).toString();
	QString m = model.data(model.index(plindex.row(), PlaylistModel::Artist), Qt::DisplayRole).toString() + " - " + model.data(model.index(plindex.row(), PlaylistModel::Album), Qt::DisplayRole).toString();
	emit message(info/*, &m*/);
}

void PlaylistView::stop()
{
	plindex = model.index(-1, 0);
    PlayerManager::Self().stop();
    playing = false;
	emit message("");
	emit songPosition(0);
}

void PlaylistView::playFinished()
{
	next();
}

QModelIndex PlaylistView::nextItem()
{
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
	if(curindex.row() >= 0) {
		prev = model.index(curindex.row()-1, 0); 
		if(prev.row() >= 0) return prev;
		return model.index(0,0);
	} else
		return model.index(-1,0);
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
		TagEditor *te = new TagEditor(model.data(model.index(curindex.row(), PlaylistModel::File), Qt::UserRole).toUrl().toLocalFile(), this);
		te->index = curindex.row();
		connect(te, SIGNAL(editComplete(int)), this, SLOT(updateTag(int)));
		//resetTags(curindex);
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
	QString path = model.data(model.index(ind.row(), PlaylistModel::File), Qt::UserRole).toUrl().toLocalFile();
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
	foreach(QModelIndex ind, /*pmodel.mapSelectionToSource(*/this->selectedIndexes()) {
		pmodel.removeRows(/*pmodel.mapToSource(*/ind.row(), 1);
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

void PlaylistView::setAutosave(bool b)
{
	autosave = b;
}

void PlaylistView::hideEvent ( QHideEvent * event )
{
	for(int i=0; i<PlaylistModel::ColumnCount; i++) {
		PLSet.setColumnWidth(i, columnWidth(i));
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
	emit status(tr("Playlist - %n song(s)", "", model.rowCount()));
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

void PlaylistView::rateSong(QModelIndex &ind, int r)
{
	if(!PLSet.autoRating || !r) return;
	QString path = model.data(model.index(ind.row(), PlaylistModel::File), Qt::UserRole).toUrl().toLocalFile();
	QString title, artist, album, comment, genre, length;
	int track, year, rating;
	if(Database::Self().GetTags(path, title, artist, album, comment, genre, track, year, rating, length)) {
		r = r * (5 - abs(rating/10));
		Database::Self().SetTags(path, title, artist, album, comment, genre, track, year, rating+r);
	}
	//QMessageBox::information(0, r>0?"rate up":"rate down", title);
}

int PlaylistView::curIndex()
{
	return plindex.row();
}

double PlaylistView::curPosition()
{
	return PlayerManager::Self().getPosition();
}
