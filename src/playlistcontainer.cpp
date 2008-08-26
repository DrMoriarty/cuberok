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

#include "playlistcontainer.h"
#include "playlistsettings.h"
#include "playlistmodel.h"

/************************
 * 
 *    PlaylistContainer
 * 
 ************************/

PlaylistContainer::PlaylistContainer(QWidget *parent) 
 : QWidget(parent), curlist(0), actlist(0), counter(0),
 alv(true), arv(true), cov(true), trv(true), tiv(true), yev(true), gev(true), fiv(true), lev(true)
{
	vboxLayout = new QVBoxLayout(this);
	vboxLayout->setContentsMargins(0,0,0,0);
	vboxLayout->setSpacing(2);
	tabs = new QTabWidget(this);
	vboxLayout->addWidget(tabs);
	connect(tabs, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
	connect(this, SIGNAL(internalnext()), this, SLOT(next()), Qt::QueuedConnection);
	newButton = new QToolButton();
	closeButton = new QToolButton();
	newButton->setIcon(QIcon(":/icons/newtab.png"));
	closeButton->setIcon(QIcon(":/icons/deltab.png"));
	connect(newButton, SIGNAL(pressed()), this, SLOT(addList()));
	connect(closeButton, SIGNAL(pressed()), this, SLOT(delList()));
	tabs->setCornerWidget(newButton, Qt::TopLeftCorner);
	tabs->setCornerWidget(closeButton, Qt::TopRightCorner);
	setContextMenuPolicy(Qt::ActionsContextMenu);

	QDir dir(QDir::homePath() + "/.cuberok/");
	QStringList filters;
	filters << "*.m3u";
	filters << "*.xspf";
	dir.setNameFilters(filters);
	foreach(QString file, dir.entryList()) {
		//int st = file.lastIndexOf('\\')+1;
		//QString plname = file.mid(st, file.lastIndexOf('.')-st);
		newList(QFileInfo(file).baseName());
		counter ++;
		if(file.toLower().endsWith(".m3u")) QFile::remove(file);
	}
	if(!counter) addList();
	
	QSettings set;
	QString curlistname = set.value("curlist", "").toString();
	if(set.value("playing", false).toBool() && curlistname.size()) {
		foreach(PlaylistView *p, lists) if(p->getName() == curlistname) {
			actlist = p;
			actlist->play(set.value("curindex", 0).toInt(), set.value("curpos", 0.0).toDouble());
		}
	}
}

PlaylistContainer::~PlaylistContainer()
{
	QSettings set;
	if(actlist && actlist->isPlaying()) {
		set.setValue("playing", 1);
		set.setValue("curlist", actlist->getName());
		set.setValue("curindex", actlist->curIndex());
		set.setValue("curpos", actlist->curPosition());
	} else set.setValue("playing", 0);
	while(lists.count() > 0) {
		lists.last()->setAutosave(true);
		delete lists.last();
		lists.pop_back();
	}
	delete tabs;
	delete vboxLayout;
}

void PlaylistContainer::listStarted(PlaylistView* pl)
{
	foreach(PlaylistView *p, lists) {
		if(p == pl) {
			if(!actlist) {
				actlist = p;
			} else
				actlist = p;
		}
		//else p->stop();
	}
}

void PlaylistContainer::addList()
{
	newList();
}

void PlaylistContainer::newList(QString listname)
{
	if(!listname.size()) {
		QString str = tr("Playlist")+" ";
		int i = 0;
		bool found;
		do {
			found = false;
			listname = str+QString::number(++i);
			foreach(PlaylistView *p, lists) if(p->getName() == listname) {
				found = true;
				break;
			}
		} while(found);
	}
	PlaylistView *pl = new PlaylistView(listname, this); 
	lists.append(pl);
	tabs->addTab(lists.last(), listname);
	curlist = lists.last();
	tabs->setCurrentIndex(tabs->count()-1);
	curlist->setContextMenuPolicy(Qt::ActionsContextMenu);
	curlist->actions() << actions();
	curlist->setAcceptDrops(true);
	curlist->setDragEnabled(true);
	curlist->setDragDropMode(QAbstractItemView::DragDrop);
	curlist->setDropIndicatorShown(true);
	curlist->setSortingEnabled(true);
	curlist->setToolTip(tr("Drag'n'Drop files to the playlist"));
	connect(pl, SIGNAL(status(QString)), this, SIGNAL(status(QString)));
	connect(pl, SIGNAL(message(QString)), this, SIGNAL(message(QString)));
	connect(pl, SIGNAL(songPosition(int)), this, SIGNAL(songPosition(int)));
	connect(pl, SIGNAL(started(PlaylistView*)), this, SLOT(listStarted(PlaylistView*)));
	closeButton->setDisabled(false);
}

void PlaylistContainer::delList()
{
	if(curlist) {
		if(actlist == curlist) {
			actlist->stop();
			actlist = 0;
		}
		int i;
		for(i=0; i<lists.count(); i++)
			if(lists[i] == curlist) {
				curlist->disconnect();
				lists.removeAt(i);
				//tabs->removeTab(i);
				delete curlist;
				break;
			}
		if(i<tabs->count()) {
			tabs->setCurrentIndex(i);
			curlist = lists[i];
		} else if(tabs->count() > 0) {
			tabs->setCurrentIndex(tabs->count()-1);
			curlist = lists[tabs->count()-1];
		} else {
			curlist = 0;
		}
		if(!lists.size()) closeButton->setDisabled(true);
	}
}
void PlaylistContainer::renameList()
{
	// TODO
}
void PlaylistContainer::prev()
{ if(actlist) actlist->prev(); }
void PlaylistContainer::next()
{ if(actlist) actlist->next(); }
void PlaylistContainer::play()
{ 
	if(curlist) {
		actlist = curlist;
		actlist->play(); 
	}
}
void PlaylistContainer::pause(bool b)
{ 
    PlayerManager::Self().setPause(b);
}
void PlaylistContainer::stop()
{
	if(actlist) actlist->stop();
}
void PlaylistContainer::repeat(bool mode)
{ 
    PlayerManager::Self().repeat_mode = mode;
}
void PlaylistContainer::shuffle(bool mode)
{ 
    PlayerManager::Self().shuffle_mode = mode;
}
void PlaylistContainer::setVolume(int volume)
{
    PlayerManager::Self().setVolume(volume);
}
void PlaylistContainer::clear()
{ if(curlist) curlist->clear(); }
void PlaylistContainer::queueNext()
{ if(curlist) curlist->queueNext(); }
void PlaylistContainer::viewAlbum(bool b)
{ //foreach(PlaylistView *pl, lists) pl->viewAlbum(b); 
  //alv = b; 
	PLSet.setColumnVisible(PlaylistModel::Album, b);
}
void PlaylistContainer::viewArtist(bool b)
{ //foreach(PlaylistView *pl, lists) pl->viewArtist(b); 
  //arv = b; 
	PLSet.setColumnVisible(PlaylistModel::Artist, b);
}
void PlaylistContainer::viewComment(bool b)
{ //foreach(PlaylistView *pl, lists) pl->viewComment(b); 
  //cov = b; 
	PLSet.setColumnVisible(PlaylistModel::Comment, b);
}
void PlaylistContainer::viewTrack(bool b)
{ //foreach(PlaylistView *pl, lists) pl->viewTrack(b); 
  //trv = b; 
	PLSet.setColumnVisible(PlaylistModel::Track, b);
}
void PlaylistContainer::viewTitle(bool b)
{ //foreach(PlaylistView *pl, lists) pl->viewTitle(b); 
  //tiv = b; 
	PLSet.setColumnVisible(PlaylistModel::Title, b);
}
void PlaylistContainer::viewYear(bool b)
{ //foreach(PlaylistView *pl, lists) pl->viewYear(b); 
  //yev = b; 
	PLSet.setColumnVisible(PlaylistModel::Year, b);
}
void PlaylistContainer::viewGenre(bool b)
{ //foreach(PlaylistView *pl, lists) pl->viewGenre(b); 
  //gev = b; 
	PLSet.setColumnVisible(PlaylistModel::Genre, b);
}
void PlaylistContainer::viewFile(bool b)
{ //foreach(PlaylistView *pl, lists) pl->viewFile(b); 
  //fiv = b; 
	PLSet.setColumnVisible(PlaylistModel::File, b);
}
void PlaylistContainer::viewLength(bool b)
{ //foreach(PlaylistView *pl, lists) pl->viewLength(b); 
  //lev = b; 
	PLSet.setColumnVisible(PlaylistModel::Length, b);
}
void PlaylistContainer::viewRating(bool b)
{
	PLSet.setColumnVisible(PlaylistModel::Rating, b);
}
void PlaylistContainer::editTag()
{ if(curlist) curlist->editTag(); }

void PlaylistContainer::removeSong()
{ if(curlist) curlist->removeSong(); }

void PlaylistContainer::reloadTags()
{ if(curlist) curlist->reloadTags(); }

void PlaylistContainer::tabChanged(int i)
{
	if(i < lists.count()) {
		curlist = lists[i];
	}
}

void PlaylistContainer::loadList()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open playlist"), QDir::homePath(), "*.xspf *.m3u");
	if(filename.size()) {
		newList(QFileInfo(filename).baseName());
		if(filename.toLower().endsWith(".m3u"))
			curlist->loadListM3U(filename);
		else if(filename.toLower().endsWith(".xspf"))
			curlist->loadListXSPF(filename);
	}
}

void PlaylistContainer::saveList()
{
	QString filter;
	if(curlist) {
		QString filename = QFileDialog::getSaveFileName(this, tr("Save playlist"), QDir::homePath(), "*.xspf\n*.m3u", &filter);
		if(filename.size()) {
			if(filter == "*.m3u")
				curlist->storeListM3U(filename);
			else if(filter == "*.xspf")
				curlist->storeListXSPF(filename);
			QString listname = QFileInfo(filename).baseName();
			curlist->setName(listname);
			tabs->setTabText(tabs->currentIndex(), listname);
		}
	}
}
