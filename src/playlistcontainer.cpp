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

#include "playlistcontainer.h"
#include "playlistsettings.h"
#include "playlistmodel.h"
#include "player_manager.h"
#include "url_open.h"
//#include "lastfm.h"
#include "console.h"
#include "extensionproxy.h"

Q_IMPORT_PLUGIN(playlist_standard)

/************************
 * 
 *    PlaylistContainer
 * 
 ************************/

PlaylistContainer::PlaylistContainer(QWidget *parent) 
 : QWidget(parent), curlist(0), actlist(0), counter(0),
   alv(true), arv(true), cov(true), trv(true), tiv(true), yev(true), gev(true), fiv(true), lev(true), _volume(0), _mute(false),
   isPaused(false)
{
	// playlist factories
	foreach (QObject *plugin, QPluginLoader::staticInstances()) {
		PlaylistFactory *pf = qobject_cast<PlaylistFactory *>(plugin);
		if (pf) {
			pf->setProxy(&ExtensionProxy::Self());
			factories.push_back(pf);
		}
	}
	
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
#if QT_VERSION >= 0x040500
	tabs->setMovable(true);
#endif
	setContextMenuPolicy(Qt::ActionsContextMenu);

	connect(qApp, SIGNAL(commitDataRequest(QSessionManager&)), this, SLOT(storeState()), Qt::DirectConnection);
	connect(qApp, SIGNAL(saveStateRequest(QSessionManager&)), this, SLOT(storeState()), Qt::DirectConnection);

}

PlaylistContainer::~PlaylistContainer()
{
	storeState();
	while(lists.count() > 0) {
		lists.last()->setAutosave(true);
		delete lists.last();
		lists.pop_back();
	}
	delete tabs;
	delete vboxLayout;
}

void PlaylistContainer::storeState()
{
	QSettings set;
	if(actlist) {
		set.setValue("curlist", actlist->getName());
		set.setValue("curindex", actlist->curIndex());
		if(actlist->isPlaying()) {
			set.setValue("playing", 1);
			set.setValue("curpos", actlist->curPosition());
		} else set.setValue("playing", 0);
	} else {
		set.remove("curlist");
		set.remove("curindex");
		set.remove("playing");
		set.remove("curpos");
	}
	qDebug("PlaylistContainer, state was stored");
}

void PlaylistContainer::prepare()
{
	QDir dir(QDir::homePath() + "/.cuberok/");
	QStringList filters;
	filters << "*.m3u";
	filters << "*.xspf";
	dir.setNameFilters(filters);
	foreach(QString file, dir.entryList()) {
		//int st = file.lastIndexOf('\\')+1;
		//QString plname = file.mid(st, file.lastIndexOf('.')-st);
		newList(QFileInfo(file).completeBaseName());
		counter ++;
		if(file.toLower().endsWith(".m3u")) QFile::remove(file);
	}
	if(!counter) addList();
	
	QSettings set;
	QString curlistname = set.value("curlist", "").toString();
	foreach(Playlist *p, lists) if(p->getName() == curlistname) {
		actlist = p;
 		connect(actlist, SIGNAL(playPauseIcon (bool) ), this, SLOT(detectPlayPauseIcon (bool) ));
		tabs->setCurrentIndex(tabs->indexOf(p->getWidget()));
		if(set.value("playing", false).toBool() && curlistname.size()) {
			actlist->play(set.value("curindex", 0).toInt(), set.value("curpos", 0.0).toDouble());
 		        emit updatePlayPauseButton (false); // we are playing, so set play/pause to "pause" mode
		} else {
			actlist->setCurrent(set.value("curindex", 0).toInt());
		}
		break;
	}
}

void PlaylistContainer::listStarted(Playlist* pl)
{
	foreach(Playlist *p, lists) {
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
			foreach(Playlist *p, lists) if(p->getName() == listname) {
				found = true;
				break;
			}
		} while(found);
	}
	Playlist *pl = factories[0]->getNewPlaylist("Standard", this, listname); 
	lists.append(pl);
	tabs->addTab(lists.last()->getWidget(), listname);
	curlist = lists.last();
	tabs->setCurrentIndex(tabs->count()-1);
	//curlist->getWidget()->setContextMenuPolicy(Qt::ActionsContextMenu);
	//curlist->getWidget()->addActions(actions());
	curlist->getWidget()->setAcceptDrops(true);
	curlist->getWidget()->setToolTip(tr("Drag'n'Drop files to the playlist"));
	connect(pl, SIGNAL(status(QString)), this, SIGNAL(status(QString)));
	connect(pl, SIGNAL(message(QString, QString, QString, long)), this, SIGNAL(message(QString, QString, QString, long)));
	connect(pl, SIGNAL(songPosition(int)), this, SIGNAL(songPosition(int)));
	connect(pl, SIGNAL(started(Playlist*)), this, SLOT(listStarted(Playlist*)));
 	connect(pl, SIGNAL(playPauseIcon (bool) ), this, SLOT(detectPlayPauseIcon (bool) ));
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
				curlist->getWidget()->disconnect();
				curlist->disconnect();
				tabs->removeTab(tabs->currentIndex());
				lists.removeAt(i);
				//delete curlist;
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
		if(!lists.size()) {
			//closeButton->setDisabled(true);
			addList();
		}
	}
}
void PlaylistContainer::renameList()
{
	// TODO
}
void PlaylistContainer::prev() { 
  if(actlist) actlist->prev();
  isPaused = false;
  emit updatePlayPauseButton (false); // show "pause" on next
}

void PlaylistContainer::next() { 
  if(actlist) actlist->next(); 
  isPaused = false;
  emit updatePlayPauseButton (false); // show "pause" on prev
}

void PlaylistContainer::play_pause () { 
   // move all logic to the pause button: one button with different states
   if (isPaused &&
       (actlist &&
        actlist->isPlaying ())) {
      // we are paused, during play, resume playing:
      PlayerManager::Self().setPause(false);
      isPaused = false;
      emit updatePlayPauseButton (false); 

   } else if (actlist &&
              actlist->isPlaying ()) {
      // we are not paused and actively playing, enter pause:
      PlayerManager::Self().setPause(true);
      isPaused = true;
      emit updatePlayPauseButton (true); 
   } else {
      // we are not playing at all (stop pressed):
      if (curlist) {
        actlist = curlist;
        actlist->play();
        isPaused = false;
        emit updatePlayPauseButton (false); 
      }
   }
}
void PlaylistContainer::stop()
{
	if(actlist) actlist->stop();
        isPaused = false;
        emit updatePlayPauseButton (true); // show "play" on stop
}
void PlaylistContainer::repeat(bool mode)
{
	EProxy.setVariable("repeat_mode", mode ? "true" : "false");
    //PlayerManager::Self().repeat_mode = mode;
}
void PlaylistContainer::shuffle(bool mode)
{ 
	EProxy.setVariable("order_mode", mode ? "shuffle" : "continues");
    //PlayerManager::Self().shuffle_mode = mode;
}
void PlaylistContainer::setVolume(int volume)
{
	_volume = volume;
	if(!_mute)
		PlayerManager::Self().setVolume(volume);
}
void PlaylistContainer::mute(bool m)
{
	if(m) {
		_volume = PlayerManager::Self().volume();
		PlayerManager::Self().setVolume(0);
	} else PlayerManager::Self().setVolume(_volume);
}
void PlaylistContainer::clear()
{ if(curlist) curlist->clear(); }
void PlaylistContainer::queueNext()
{ if(curlist) curlist->queueNext(); }
void PlaylistContainer::viewAlbum(bool b)
{ 
	PLSet.setColumnVisible(PlaylistModel::Album, b);
}
void PlaylistContainer::viewArtist(bool b)
{
	PLSet.setColumnVisible(PlaylistModel::Artist, b);
}
void PlaylistContainer::viewComment(bool b)
{
	PLSet.setColumnVisible(PlaylistModel::Comment, b);
}
void PlaylistContainer::viewTrack(bool b)
{
	PLSet.setColumnVisible(PlaylistModel::Track, b);
}
void PlaylistContainer::viewTitle(bool b)
{
	PLSet.setColumnVisible(PlaylistModel::Title, b);
}
void PlaylistContainer::viewYear(bool b)
{
	PLSet.setColumnVisible(PlaylistModel::Year, b);
}
void PlaylistContainer::viewGenre(bool b)
{
	PLSet.setColumnVisible(PlaylistModel::Genre, b);
}
void PlaylistContainer::viewFile(bool b)
{
	PLSet.setColumnVisible(PlaylistModel::File, b);
}
void PlaylistContainer::viewLength(bool b)
{
	PLSet.setColumnVisible(PlaylistModel::Length, b);
}
void PlaylistContainer::viewRating(bool b)
{
	PLSet.setColumnVisible(PlaylistModel::Rating, b);
}
void PlaylistContainer::viewNumber(bool b)
{
	PLSet.setColumnVisible(PlaylistModel::Number, b);
}
void PlaylistContainer::viewQueue(bool b)
{
	PLSet.setColumnVisible(PlaylistModel::Stat, b);
}
void PlaylistContainer::viewType(bool b)
{
	PLSet.setColumnVisible(PlaylistModel::FileType, b);
}
void PlaylistContainer::editTag()
{ if(curlist) curlist->editTag(); }

void PlaylistContainer::removeSong()
{ if(curlist) curlist->removeSong(); }

void PlaylistContainer::reloadTags()
{ if(curlist) curlist->reloadTags(); }

void PlaylistContainer::tabChanged(int i)
{
	if(i < lists.count() && i >= 0) {
		curlist = lists[i];
	}
}

void PlaylistContainer::loadList()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open playlist"), QDir::homePath(), "*.xspf *.m3u");
	if(filename.size()) {
		newList(QFileInfo(filename).completeBaseName());
		if(filename.toLower().endsWith(".m3u"))
			curlist->loadList(filename);
		else if(filename.toLower().endsWith(".xspf"))
			curlist->loadList(filename);
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
			QString listname = QFileInfo(filename).completeBaseName();
			curlist->setName(listname);
			tabs->setTabText(tabs->currentIndex(), listname);
		}
	}
}

void PlaylistContainer::openUrl()
{
	if(curlist) {
		UrlOpen *u = new UrlOpen(this);
		if(!connect(u, SIGNAL(append(QUrl)), curlist, SLOT(addUrl(QUrl)), Qt::QueuedConnection))
			Console::Self().error("Can not connect UrlOpen");
		u->show();
	}
}

void PlaylistContainer::addUrl(QUrl url)
{
	if(curlist) {
		curlist->addUrl(url);
	}
}

void PlaylistContainer::rateLove()
{
	if(actlist) {
		actlist->rateCurrent(0, 50);
	}
}

void PlaylistContainer::rateBan()
{
	if(actlist) {
		actlist->rateCurrent(0, -50);
	}
}

void PlaylistContainer::rateUp()
{
	if(actlist) {
		actlist->rateCurrent(10);
	}
}

void PlaylistContainer::rateDown()
{
	if(actlist) {
		actlist->rateCurrent(-10);
	}
}

QString PlaylistContainer::getCurrentFile()
{
	if(curlist) {
		return curlist->curFile();
	}
	return "";
}

void PlaylistContainer::setFilter(QString s)
{
	foreach(Playlist *pl, lists) pl->setFilter(s); 
}

void PlaylistContainer::clearFilter()
{
	foreach(Playlist *pl, lists) pl->setFilter("");
}

void PlaylistContainer::findCurrent()
{
	if(actlist) {
		actlist->findCurrent();
	}
}

// pass through from PlaylistView to the GUI for handling end of playlist & doubleclick updates to play/pause icon
// a "true" argument means show a "play" icon, false means show "pause"
void PlaylistContainer::detectPlayPauseIcon (bool playPause) {
     emit updatePlayPauseButton (playPause);
}
