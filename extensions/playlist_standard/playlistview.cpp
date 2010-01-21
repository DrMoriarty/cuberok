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
//#include "playlistview_wa.h"
#include "player_manager.h"
#include "tagger.h"
#include "database.h"
#include "stardelegate.h"
#include "starrating.h"
#include "playlistsettings.h"
//#include "lastfm.h"
//#include "console.h"
//#include "librefm.h"
#include "extensionproxy.h"

Q_EXPORT_PLUGIN2(playlist_standard, PlaylistStandardFactory) 

/***********************
 * 
 *    MyTreeView
 * 
 ***********************/ 

MyTreeView::MyTreeView(QString &str, PlaylistModel &model, QWidget *parent)
: QTreeView(parent), dragStarted(false)
{
	_model = &model;
	setItemDelegate(new StarDelegate);
    pmodel.setDynamicSortFilter(true);
	pmodel.setFilterCaseSensitivity(Qt::CaseInsensitive);
	pmodel.setFilterKeyColumn(-1);
    pmodel.setSourceModel(_model);
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
	//connect(&header(), SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(updateStatus()));
	
	setDragEnabled(true);
	setDragDropMode(QAbstractItemView::DragDrop);
	setDropIndicatorShown(true);
	setSortingEnabled(true);
}

QModelIndexList MyTreeView::getSelectedIndexes()
{
	return selectedIndexes();
}

QModelIndex MyTreeView::mapToSource(QModelIndex ind)
{
	return pmodel.mapToSource(ind);
}

QModelIndex MyTreeView::mapToSource(int row, int column)
{
	return mapToSource(pmodel.index(row, column));
}

QModelIndex MyTreeView::mapFromSource(QModelIndex ind)
{
	return pmodel.mapFromSource(ind);
}

QModelIndex MyTreeView::mapFromSource(int row, int column)
{
	return mapFromSource(pmodel.index(row, column));
}

void MyTreeView::setFilterRegExp(QString s)
{
	pmodel.setFilterRegExp(s);
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
        if (_model->dropMimeData(event->mimeData(),
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

int MyTreeView::rowCount()
{
	return pmodel.rowCount();
}

/***********************
 * 
 *    PlaylistAbstract
 * 
 ***********************/ 

PlaylistAbstract::PlaylistAbstract(QString &str, Proxy *pr, QWidget *parent) : Playlist(str, parent)
, proxy(pr), autosave(false), playing(false), delayedPlay(false), delayedIndex(-1), delayedPos(0.0), error_count(0)
{
	timer.setSingleShot(true);
	timer.setInterval(500);
	connect(&timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
	connect(&model, SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(updateStatus()));
	connect(&model, SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(updateStatus()));
}

PlaylistAbstract::~PlaylistAbstract()
{
	model.disconnect();
}

QString PlaylistAbstract::getName()
{
	return plistname;
}

void PlaylistAbstract::setName(QString str)
{
	plistname = str;
}

void PlaylistAbstract::storeListM3U(QString fname)
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

void PlaylistAbstract::storeListXSPF(QString fname)
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
			xml.writeTextElement(XMLNS, "filetype", model.data(model.index(i, PlaylistModel::FileType), Qt::DisplayRole).toString());
			xml.writeEndElement(); //extension
			xml.writeEndElement(); //track
		}
		xml.writeEndElement(); // trackList
		xml.writeEndElement(); //playlist
		xml.writeEndDocument();
	}
}

void PlaylistAbstract::storeState(bool save)
{
	QString fname = QDir::homePath() + "/.cuberok/" + plistname + ".xspf";
	if(save) storeListXSPF(fname);
	else QFile::remove(fname);
	qDebug("storeState");
}

void PlaylistAbstract::loadList(QString fname)
{
	while(model.rowCount()) model.removeRow(0);
	addUrl(QUrl::fromLocalFile(fname));
}

void PlaylistAbstract::addUrl(QUrl url)
{
	QList<TagEntry> list = Tagger::readEntry(url);
	proxy->log("Add URL: "+url.toString() + " " + QString::number(list.size()) + " record(s)");
	model.appendList(list);
}

bool PlaylistAbstract::isPlaying()
{
	return playing;
}

void PlaylistAbstract::addItem(QVariant item, int id, QModelIndex* ind)
{
	if(!ind) ind = &insindex;
	if(id == PlaylistModel::File)
		model.insertRows(ind->row()<0 ? model.rowCount() : ind->row(), 1);
	model.setData(ind->row()<0 ? model.index(model.rowCount()-1, id) : model.index(ind->row(), id), item, Qt::EditRole);
}

void PlaylistAbstract::prev()
{
	QModelIndex prev = prevItem();
	if(prev.row() >= 0) {
		setCurrent(prev.row());
		play();
	} else {
		play();
	}
}

void PlaylistAbstract::next()
{
	QModelIndex next;
	do {
		next = nextItem();
	} while(qVariantValue<StarRating>(model.data(model.index(next.row(), PlaylistModel::Rating), Qt::DisplayRole)).rating() <= -50);
	if(next.row() >= 0) {
		if(plindex.row() >= 0) {
			prev_queue.push_back(plindex);
			if(PlayerManager::Self().playing()) rateSong(plindex, -1);
		}
		setCurrent(next.row());
		play();
	}
	else stop();
}

void PlaylistAbstract::play(int index, double pos)
{
	if(index >= 0 && index < model.rowCount()) {
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

void PlaylistAbstract::stop()
{
	model.setCurrent(-1);
	plindex = model.index(-1, 0);
	shuffle_queue.clear();
    PlayerManager::Self().stop();
    playing = false;
	emit message("", "", "", 0);
	emit songPosition(0);
}

void PlaylistAbstract::playFinished()
{
	/*if(PLSet.lastfmScrobbler || PLSet.librefmScrobbler)*/ {
		// QString a = model.data(model.index(plindex.row(), PlaylistModel::Artist), Qt::DisplayRole).toString();
		// QString t = model.data(model.index(plindex.row(), PlaylistModel::Title), Qt::DisplayRole).toString();
		// QString b = model.data(model.index(plindex.row(), PlaylistModel::Album), Qt::DisplayRole).toString();
		// int n = model.data(model.index(plindex.row(), PlaylistModel::Track), Qt::DisplayRole).toInt();
		// long len = model.data(model.index(plindex.row(), PlaylistModel::CueLength), Qt::DisplayRole).toLongLong() / 75;
		// uint start = model.data(model.index(plindex.row(), PlaylistModel::StartTime), Qt::DisplayRole).toLongLong();
		//if(PLSet.lastfmScrobbler) LastFM::Self().submission(a, t, start, b, len, "P", "", n);
		//if(PLSet.librefmScrobbler) LibreFM::Self().submission(a, t, start, b, len, "P", "", n);
	}	
	emit playPauseIcon (true); // finished playing, show the "play" icon
	if(EProxy.getVariable("play_mode") == "song" && EProxy.getVariable("repeat_mode") == "true")
		play();
	else
		next();
}

void PlaylistAbstract::updateTag(TagEditor* ed)
{
	QModelIndex ind = model.index(ed->index, 0); 
	//resetTags(ind);
	addItem(ed->tag.tag0.title, PlaylistModel::Title, &ind);
	addItem(ed->tag.tag0.artist, PlaylistModel::Artist, &ind);
	addItem(ed->tag.tag0.album, PlaylistModel::Album, &ind);
	addItem(QString::number(ed->tag.tag0.year), PlaylistModel::Year, &ind);
	addItem(ed->tag.tag0.comment, PlaylistModel::Comment, &ind);
	addItem(QString::number(ed->tag.tag0.track), PlaylistModel::Track, &ind);
	addItem(ed->tag.tag0.genre, PlaylistModel::Genre, &ind);
	addItem(qVariantFromValue(StarRating(ed->tag.tag0.rating)), PlaylistModel::Rating, &ind);
}

void PlaylistAbstract::resetTags(QModelIndex& ind)
{
	QString path = ToLocalFile(model.data(model.index(ind.row(), PlaylistModel::File), Qt::UserRole).toUrl());
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

	/*if(Database::Self().GetTags(path, title, artist, album, comment, genre, track, year, rating, length, type)) {
		addItem(qVariantFromValue(StarRating(rating)), PlaylistModel::Rating, &ind);
		}*/
}

void PlaylistAbstract::setAutosave(bool b)
{
	autosave = b;
}

void PlaylistAbstract::updateStatus()
{
	if(delayedPlay && model.rowCount() > delayedIndex) {
		delayedPlay = false;
		setCurrent(delayedIndex);
		//play();
		//if(delayedPos >= 0 && delayedPos <= 1)
		//	position(delayedPos);
	}
	if(!delayedPlay && delayedIndex >= 0 && model.rowCount() > delayedIndex) {
		setCurrent(delayedIndex);
	}
	QDateTime time;
	for(int i=0; i<model.rowCount(); i++) {
		time = time.addSecs(model.data(model.index(i, PlaylistModel::CueLength), Qt::DisplayRole).toLongLong() / 75);
	}
	QString st = tr("Playlist - %n song(s)", "", model.rowCount());
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
	timer.start();
}

void PlaylistAbstract::timerSlot()
{
	storeState(true);
}

void PlaylistAbstract::rateSong(QModelIndex &ind, int r, int offset)
{
	if(!PLSet.autoRating || (!r && !offset)) return;
	// TODO
	/*QString path = ToLocalFile(model.data(model.index(ind.row(), PlaylistModel::File), Qt::UserRole).toUrl());
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
	proxy->log((r>0?"rate up ":"rate down ") + title);*/
}

int PlaylistAbstract::curIndex()
{
	return plindex.row() >= 0 ? plindex.row() : curindex.row();
}

double PlaylistAbstract::curPosition()
{
	return PlayerManager::Self().getPosition();
}

void PlaylistAbstract::rateCurrent(int offset, int value)
{
	if(playing) {
		bool ar = PLSet.autoRating;
		PLSet.autoRating = true;
		rateSong(plindex, 0, offset+value);
		PLSet.autoRating = ar;
		resetTags(plindex);
	}
}

QString PlaylistAbstract::curFile()
{
	if(curindex.row() >= 0) {
		return ToLocalFile(model.data(model.index(curindex.row(), PlaylistModel::File), Qt::UserRole).toUrl());
	}
	return "";
}

void PlaylistAbstract::findCurrent()
{
	if(plindex.row() >= 0) {
		setCurrent(plindex.row());
	}
}

/***********************
 * 
 *    PlaylistStandard
 * 
 ***********************/ 

PlaylistStandard::PlaylistStandard(QString &str, Proxy *pr, QWidget *parent) : PlaylistAbstract(str, pr, parent){
	view = new MyTreeView(str, model, parent);
	connect(view, SIGNAL(needUpdate()), this, SLOT(updateStatus()));
	connect(view, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onClick(const QModelIndex &)));
	connect(view, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(onDoubleClick(const QModelIndex &)));
	if(plistname.size()) {  // read stored playlist
		QString fname = QDir::homePath() + "/.cuberok/" + plistname + ".xspf";
		if(QFile::exists(fname)) loadList(fname);
		else {
			fname = QDir::homePath() + "/.cuberok/" + plistname + ".m3u";
			if(QFile::exists(fname)) loadList(fname);
		}
	}
	addHardcodedActions(view);
};

PlaylistStandard::~PlaylistStandard()
{
	storeState(autosave);
}

QWidget* PlaylistStandard::getWidget()
{
	return view;
}

void PlaylistStandard::addHardcodedActions(QWidget* w)
{
	w->setContextMenuPolicy(Qt::ActionsContextMenu);
	// queue next
	QAction *actionQueueNext = new QAction(this);
	actionQueueNext->setObjectName(QString::fromUtf8("actionQueueNext"));
	QIcon icon9;
	icon9.addFile(QString::fromUtf8(":/icons/next.png"), QSize(), QIcon::Normal, QIcon::Off);
	actionQueueNext->setIcon(icon9);
	w->addAction(actionQueueNext);
	QObject::connect(actionQueueNext, SIGNAL(triggered()), this, SLOT(queueNext()));
	actionQueueNext->setText(QApplication::translate("PlaylistStandard", "Queue as Next", 0, QApplication::UnicodeUTF8));
	actionQueueNext->setStatusTip(QApplication::translate("PlaylistStandard", "Enqueue selected song", 0, QApplication::UnicodeUTF8));
	actionQueueNext->setShortcut(QApplication::translate("PlaylistStandard", "Ctrl+D", 0, QApplication::UnicodeUTF8));
	// edit tags
	QAction* actionEditTag = new QAction(this);
	actionEditTag->setObjectName(QString::fromUtf8("actionEditTag"));
	QIcon icon10;
	icon10.addFile(QString::fromUtf8(":/icons/edittag.png"), QSize(), QIcon::Normal, QIcon::Off);
	actionEditTag->setIcon(icon10);
	w->addAction(actionEditTag);
	QObject::connect(actionEditTag, SIGNAL(triggered()), this, SLOT(editTag()));
	actionEditTag->setText(QApplication::translate("PlaylistStandard", "Edit Tag", 0, QApplication::UnicodeUTF8));
	actionEditTag->setIconText(QApplication::translate("PlaylistStandard", "Tag", 0, QApplication::UnicodeUTF8));
	actionEditTag->setToolTip(QApplication::translate("PlaylistStandard", "Edit Tag", 0, QApplication::UnicodeUTF8));
	actionEditTag->setStatusTip(QApplication::translate("PlaylistStandard", "Edit tags", 0, QApplication::UnicodeUTF8));
	// reload tags
	QAction *actionReloadTags = new QAction(this);
	actionReloadTags->setObjectName(QString::fromUtf8("actionReloadTags"));
	QIcon icon24;
	icon24.addFile(QString::fromUtf8(":/icons/reload.png"), QSize(), QIcon::Normal, QIcon::Off);
	actionReloadTags->setIcon(icon24);
	w->addAction(actionReloadTags);
	QObject::connect(actionReloadTags, SIGNAL(triggered()), this, SLOT(reloadTags()));
	actionReloadTags->setText(QApplication::translate("PlaylistStandard", "Reload tags", 0, QApplication::UnicodeUTF8));
	actionReloadTags->setStatusTip(QApplication::translate("PlaylistStandard", "Reload tags in selected song", 0, QApplication::UnicodeUTF8));
	// remove song
	QAction *actionRemoveSong = new QAction(this);
	actionRemoveSong->setObjectName(QString::fromUtf8("actionRemoveSong"));
	QIcon icon13;
	icon13.addFile(QString::fromUtf8(":/icons/col_rem.png"), QSize(), QIcon::Normal, QIcon::Off);
	actionRemoveSong->setIcon(icon13);
	actionRemoveSong->setShortcutContext(Qt::WidgetWithChildrenShortcut);
	w->addAction(actionRemoveSong);
	QObject::connect(actionRemoveSong, SIGNAL(triggered()), this, SLOT(removeSong()));
	actionRemoveSong->setText(QApplication::translate("PlaylistStandard", "Remove song", 0, QApplication::UnicodeUTF8));
	actionRemoveSong->setStatusTip(QApplication::translate("PlaylistStandard", "Remove song from the playlist", 0, QApplication::UnicodeUTF8));
	actionRemoveSong->setShortcut(QApplication::translate("PlaylistStandard", "Del", 0, QApplication::UnicodeUTF8));
	// clear
	QAction* actionClear_playlist = new QAction(this);
	actionClear_playlist->setObjectName(QString::fromUtf8("actionClear_playlist"));
	QIcon icon8;
	icon8.addFile(QString::fromUtf8(":/icons/clearlist.png"), QSize(), QIcon::Normal, QIcon::Off);
	actionClear_playlist->setIcon(icon8);
	w->addAction(actionClear_playlist);
	QObject::connect(actionClear_playlist, SIGNAL(triggered()), this, SLOT(clear()));
	actionClear_playlist->setText(QApplication::translate("PlaylistStandard", "Clear playlist", 0, QApplication::UnicodeUTF8));
	actionClear_playlist->setIconText(QApplication::translate("PlaylistStandard", "Clear", 0, QApplication::UnicodeUTF8));
	actionClear_playlist->setStatusTip(QApplication::translate("PlaylistStandard", "Clear playlist", 0, QApplication::UnicodeUTF8));
	actionClear_playlist->setShortcut(QApplication::translate("PlaylistStandard", "Ctrl+L", 0, QApplication::UnicodeUTF8));
}

void PlaylistStandard::play()
{
	if(curindex.row() < 0) {
		curindex = view->mapToSource(0, 0);
	}
	plindex = model.index(curindex.row(), view->header()->logicalIndex(0));
	//plindex = model.index(curindex.row(), PlaylistModel::File);
	model.setCurrent(plindex.row());
	view->setCurrentIndex(view->mapFromSource(plindex));
	view->scrollTo(view->mapFromSource(plindex));
	info = model.data(model.index(plindex.row(), PlaylistModel::Title), Qt::DisplayRole).toString();
	QString ar = model.data(model.index(plindex.row(), PlaylistModel::Artist), Qt::DisplayRole).toString();
	QString alb = model.data(model.index(plindex.row(), PlaylistModel::Album), Qt::DisplayRole).toString();
	long len = model.data(model.index(plindex.row(), PlaylistModel::CueLength), Qt::DisplayRole).toLongLong() / 75;
	// check play mode
	if(!shuffle_queue.size() && !PlayerManager::Self().playing() && EProxy.getVariable("order_mode") == "shuffle") {
		if(EProxy.getVariable("play_mode") == "list" || EProxy.getVariable("play_mode") == "song")
		   refillShuffleQueue(curindex.row());
		else if(EProxy.getVariable("play_mode") == "album")
			prepareNextAlbum(curindex.row());
	}
	if(EProxy.getVariable("play_mode") == "album" && current_album.size()) {
		QString ca = model.data(model.index(current_album[0].row(), PlaylistModel::Album), Qt::DisplayRole).toString();
		if(ca != alb) { // user selects another track
			current_album.clear();
			prepareNextAlbum(curindex.row());
		}
	}
	// play new track
	disconnect(&PlayerManager::Self(), SIGNAL(finish()), 0, 0);
	disconnect(&PlayerManager::Self(), SIGNAL(position(double)), 0, 0);
	if(PlayerManager::Self().playing()) PlayerManager::Self().close();
	if(!PlayerManager::Self().open(model.data(model.index(plindex.row(), PlaylistModel::File), Qt::UserRole).toUrl(), model.data(model.index(plindex.row(), PlaylistModel::CueStart), Qt::DisplayRole).toLongLong(), model.data(model.index(plindex.row(), PlaylistModel::CueLength), Qt::DisplayRole).toLongLong())) {
		proxy->error(tr("Can not open %1").arg(model.data(model.index(plindex.row(), PlaylistModel::File), Qt::UserRole).toUrl().toString()));
		playing = false;
		error_count ++;
		if(error_count < 5) next();
		else {
			error_count = 0;
			return;
		}
	}
	error_count = 0;
	model.setData(model.index(plindex.row(), PlaylistModel::StartTime), QDateTime::currentDateTime().toTime_t(), Qt::EditRole);
	emit message(info, alb, ar, len);
	int n = model.data(model.index(plindex.row(), PlaylistModel::Track), Qt::DisplayRole).toInt();
	/*if(PLSet.lastfmScrobbler && ar.size()) {
		LastFM::Self().nowplaying(ar, info, alb, 0, n);
	}
	if(PLSet.librefmScrobbler && ar.size()) {
		LibreFM::Self().nowplaying(ar, info, alb, 0, n);
	}*/
	STags t;
	t.tag0.title = info;
	t.tag0.artist = ar;
	t.tag0.album = alb;
	t.tag0.track = n;
	t.tag0.length = len * 75;
	proxy->setTags(t);

	connect(&PlayerManager::Self(), SIGNAL(finish()), this, SLOT(playFinished()));
	connect(&PlayerManager::Self(), SIGNAL(position(double)), this, SLOT(position(double)));
	PlayerManager::Self().play();
	playing = true;
	emit started(this);
	emit playPauseIcon (false); // finished playing, show the "pause" icon
}

void PlaylistStandard::stop()
{
	current_album.clear();
	album_queue.clear();
	PlaylistAbstract::stop();
}

QModelIndex PlaylistStandard::nextItem()
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
	} else if(EProxy.getVariable("play_mode") == "song") { // SONG
		if(EProxy.getVariable("order_mode") == "shuffle") { // SHUFFLE
			if(!shuffle_queue.size())
				refillShuffleQueue(-1, plindex.row());
			if(shuffle_queue.size()) {
				next = shuffle_queue.first();
				shuffle_queue.pop_front();
			} else next = model.index(-1, 0);
		} else if(EProxy.getVariable("order_mode") == "random") { // RANDOM
			int r = rand()%view->rowCount();
			if(view->rowCount() > 2) while(r == view->mapFromSource(plindex).row() || r == view->mapFromSource(curindex).row()) { r = rand()%view->rowCount(); }
			next = view->mapToSource(r, 0);
		} else {                                          // ORDERED
			if(view->mapFromSource(curindex).row() >= 0) 
				next = view->mapToSource(view->mapFromSource(curindex).row()+1, 0);
			if(next.row() < 0) {
				next = model.index(-1, 0);
			}
		}
	} else if(EProxy.getVariable("play_mode") == "album") {  // ALBUM
		if(!current_album.size()) prepareNextAlbum();
		if(!current_album.size())
			next = model.index(-1, 0);
		else {
			if(EProxy.getVariable("order_mode") == "shuffle") { // SHUFFLE
				if(!shuffle_queue.size())
					prepareNextAlbum();
				if(shuffle_queue.size()) {
					next = shuffle_queue.first();
					shuffle_queue.pop_front();
				} else next = model.index(-1, 0);
			} else if(EProxy.getVariable("order_mode") == "random") { // RANDOM
				int r = rand()%current_album.size();
				if(current_album.size() > 2) while(current_album[r].row() == plindex.row() || current_album[r].row() == curindex.row()) { r = rand()%current_album.size(); }
				next = current_album[r];
			} else {                                            // ORDERED
				int cur = 0;
				while(cur < current_album.size() && current_album[cur].row() != curindex.row()) cur ++;
				if(cur >= current_album.size()-1) {
					prepareNextAlbum();
					if(current_album.size()) next = current_album[0];
					else next = model.index(-1, 0);
				} else {
					next = current_album[cur+1];
				}
			}
		}
	} else if(EProxy.getVariable("play_mode") == "list") {     // LIST
		if(EProxy.getVariable("order_mode") == "shuffle") {    // SHUFFLE
			if(!shuffle_queue.size() && EProxy.getVariable("repeat_mode") == "true")
				refillShuffleQueue(-1, plindex.row());
			if(shuffle_queue.size()) {
				next = shuffle_queue.first();
				shuffle_queue.pop_front();
			} else next = model.index(-1, 0);
		} else if(EProxy.getVariable("order_mode") == "random") { // RANDOM
			int r = rand()%model.rowCount();
			if(model.rowCount() > 2) while(r == plindex.row() || r == curindex.row()) { r = rand()%model.rowCount(); }
			next = model.index(r, 0);
		} else {                                                  // ORDERED
			if(curindex.row() >= 0) 
				next = model.index(curindex.row()+1, 0);
			if(next.row() < 0) {
				if(EProxy.getVariable("repeat_mode") == "true") next = model.index(0, 0);
				else next = model.index(-1, 0);
			}
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
	if(view->mapFromSource(curindex).row() >= 0) 
		prev = view->mapToSource(view->mapFromSource(curindex).row()-1, 0);
	if(prev.row() < 0) {
		if(EProxy.getVariable("repeat_mode") == "playlist") prev = view->mapToSource(model.rowCount()-1, 0);
		else prev = model.index(-1, 0);
	}
	return prev;
}

void PlaylistStandard::refillShuffleQueue(int except, int notstartwith)
{
	shuffle_queue.clear();
	QList<QModelIndex> cache;
	if(EProxy.getVariable("play_mode") == "song") {
		for(int i = 0; i<view->rowCount(); i++) if(view->mapToSource(i,0).row() != except) cache << view->mapToSource(i, 0);
	} else if(EProxy.getVariable("play_mode") == "list") {
		for(int i = 0; i<model.rowCount(); i++) if(i != except) cache << model.index(i, 0);
	} else if(EProxy.getVariable("play_mode") == "album") {
		prepareNextAlbum(except);
	} else return;
	while(cache.size()) {
		int i;
		do {
			i = rand()%cache.size();
		} while(i == notstartwith);
		notstartwith = -1;
		shuffle_queue << cache[i];
		cache.erase(cache.begin() + i);
	}
}


void PlaylistStandard::onClick(const QModelIndex &index)
{
	//if(curindex.row() >= 0) prev_queue.push_back(curindex);
	curindex = view->mapToSource(index);
}

void PlaylistStandard::onDoubleClick(const QModelIndex &index)
{
	//if(curindex.row() >= 0) prev_queue.push_back(curindex);
	if(plindex.row() >= 0) prev_queue.push_back(plindex);
	curindex = view->mapToSource(index);
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
	plindex = curindex = insindex = model.index(-1, 0);
	queue.clear();
	prev_queue.clear();
	view->setCurrentIndex(curindex);
	model.removeRows(0, model.rowCount());
}

void PlaylistStandard::queueNext()
{
	foreach(QModelIndex i1, view->getSelectedIndexes()) {
		QModelIndex ind = view->mapToSource(i1);
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

void PlaylistStandard::editTag()
{
	if(curindex.row() >= 0) {
		STags t;
		t.tag0.url = model.data(model.index(curindex.row(), PlaylistModel::File), Qt::UserRole).toUrl();
		t.tag0.title = model.data(model.index(curindex.row(), PlaylistModel::Title), Qt::DisplayRole).toString();
		t.tag0.artist = model.data(model.index(curindex.row(), PlaylistModel::Artist), Qt::DisplayRole).toString();
		t.tag0.album = model.data(model.index(curindex.row(), PlaylistModel::Album), Qt::DisplayRole).toString();
		t.tag0.genre = model.data(model.index(curindex.row(), PlaylistModel::Genre), Qt::DisplayRole).toString();
		t.tag0.track = model.data(model.index(curindex.row(), PlaylistModel::Track), Qt::DisplayRole).toInt();
		t.tag0.year = model.data(model.index(curindex.row(), PlaylistModel::Year), Qt::DisplayRole).toInt();
		t.tag0.comment = model.data(model.index(curindex.row(), PlaylistModel::Comment), Qt::DisplayRole).toString();

		TagEditor *te = new TagEditor(t, 0);
		te->index = curindex.row();
		connect(te, SIGNAL(editComplete(TagEditor*)), this, SLOT(updateTag(TagEditor*)));
		//resetTags(curindex);
		te->setAttribute(Qt::WA_DeleteOnClose);
		te->show();
	}
}

void PlaylistStandard::removeSong()
{
	QList<int> list;
	foreach(QModelIndex ind, view->getSelectedIndexes()) {
		if(!list.contains(ind.row())) 
			list << ind.row();
	}
	qSort(list.begin(), list.end(), qGreater<int>());
	foreach(int ind, list) {
		if(curindex.row() == view->mapToSource(ind, 0).row()) {
			curindex = model.index(-1, 0);
			view->setCurrentIndex(curindex);
		}
		view->model()->removeRows(ind, 1);
	}
}

void PlaylistStandard::reloadTags()
{
	foreach(QModelIndex ind, view->getSelectedIndexes()) {
		QModelIndex i2 = view->mapToSource(ind);
		resetTags(i2);
	}
	//if(curindex.row() >= 0) resetTags(curindex);
}

void PlaylistStandard::setFilter(QString s)
{
	view->setFilterRegExp(s);
}

void PlaylistStandard::setCurrent(int index)
{
	if(index >= 0 && index < model.rowCount()) {
		curindex = model.index(index, 0);
		view->clearSelection();
		view->setCurrentIndex(view->mapFromSource(curindex));
		//model.setCurrent(index);
		view->scrollTo(view->mapFromSource(curindex));
	} else {
		delayedIndex = index;
		delayedPlay = false;
	}
}

void PlaylistStandard::prepareNextAlbum(int except)
{
	QString newAlbum;
	if(current_album.size()) {
		// find next album
		if(EProxy.getVariable("order_mode") == "random") {
			// the same album
			return;
		} else /*if(EProxy.getVariable("order_mode") == "shuffle")*/ {
			QString oldAlbum = model.data(model.index(current_album[0].row(), PlaylistModel::Album), Qt::DisplayRole).toString();
			if(!album_queue.size() && EProxy.getVariable("repeat_mode") == "true")
				prepareAlbumList(0, &oldAlbum);
			if(album_queue.size()) {
				newAlbum = album_queue.front();
				album_queue.pop_front();
			} else {
				current_album.clear();
				shuffle_queue.clear();
				return;
			}
			/*int max = 0;
			for(int i = 0; i< current_album.size(); i++) if(current_album[i].row() > max) max = current_album[i].row();
			max ++;
			if(max < model.rowCount())
				newAlbum = model.data(model.index(max, PlaylistModel::Album), Qt::DisplayRole).toString();
			else {
				if(EProxy.getVariable("repeat_mode") == "true")
					newAlbum = model.data(model.index(0, PlaylistModel::Album), Qt::DisplayRole).toString();
				else {
					current_album.clear();
					shuffle_queue.clear();
				}
			}
		} else { // ordered
			QString oldAlbum = model.data(model.index(current_album[0].row(), PlaylistModel::Album), Qt::DisplayRole).toString();
			if(current_album.size() < model.rowCount()) {
				do {
					newAlbum = model.data(model.index(rand()%model.rowCount(), PlaylistModel::Album), Qt::DisplayRole).toString();
				} while(newAlbum == oldAlbum);
			} else return;*/
		}
	} else if(curindex.row() >= 0) {
		// get album from current item
		newAlbum = model.data(model.index(curindex.row(), PlaylistModel::Album), Qt::DisplayRole).toString();
		prepareAlbumList(&newAlbum);
	} else {
		// get first album
		newAlbum = model.data(model.index(0, PlaylistModel::Album), Qt::DisplayRole).toString();
		prepareAlbumList(&newAlbum);
	}
	// lets fill new current album
	current_album.clear();
	for(int i = 0; i<model.rowCount(); i++) {
		if(newAlbum == model.data(model.index(i, PlaylistModel::Album), Qt::DisplayRole).toString())
			current_album << model.index(i, PlaylistModel::Album);
	}
	// prepare shuffle list
	if(EProxy.getVariable("order_mode") == "shuffle") {
		QList<QModelIndex> cache = current_album;
		shuffle_queue.clear();
		while(cache.size()) {
			int i = rand()%cache.size();
			if(cache[i].row() != except) shuffle_queue << cache[i];
			cache.erase(cache.begin() + i);
		}
	}
}

void PlaylistStandard::prepareAlbumList(const QString* except, const QString* notStartWith)
{
	album_queue.clear();
	for(int i=0; i<model.rowCount(); i++) {
		QString al = model.data(model.index(i, PlaylistModel::Album), Qt::DisplayRole).toString();
		if(except && al == *except) continue;
		bool coincidence = false;
		for(int j = album_queue.size()-1; j >= 0; j--)
			if(album_queue[j] == al) {
				coincidence = true;
				break;
			}
		if(!coincidence) album_queue << al;
	}
	if(EProxy.getVariable("order_mode") == "ordered") {
		QStringList cache = album_queue;
		album_queue.clear();
		while(cache.size()) {
			int i;
			do { i = rand()%cache.size(); } while(notStartWith && cache[i] == notStartWith);
			notStartWith = 0;
			album_queue << cache[i];
			cache.erase(cache.begin() + i);
		}
	}
}

/***********************
 * 
 *    PlaylistStandardFactory
 * 
 ***********************/ 

PlaylistStandardFactory::PlaylistStandardFactory() : proxy(0)
{}

void PlaylistStandardFactory::setProxy(Proxy *pr)
{
	proxy = pr;
}

QStringList PlaylistStandardFactory::getAvailableTypes()
{
	QStringList l;
	l << "Standard";
//	l << "WinAmp style";
	return l;
}

Playlist* PlaylistStandardFactory::getNewPlaylist(QString type, QWidget* parent, QString name) {
	if(type == "Standard") return new PlaylistStandard(name, proxy, parent);
//	if(type == "WinAmp style") return new PlaylistWinamp(name, parent);
	return 0;
};
