#include "playlistcontainer.h"

/************************
 * 
 *    PlaylistContainer
 * 
 ************************/

PlaylistContainer::PlaylistContainer(QWidget *parent) 
 : QWidget(parent), svolume(99), curlist(0), actlist(0), counter(0),
 rf(false), sf(false), alv(true), arv(true), cov(true), trv(true), tiv(true), yev(true), gev(true), fiv(true), lev(true)
{
	vboxLayout = new QVBoxLayout(this);
	tabs = new QTabWidget(this);
	vboxLayout->addWidget(tabs);
	device = OpenDevice();
	device->registerCallback(this);
	addList();
	connect(tabs, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
	connect(this, SIGNAL(internalnext()), this, SLOT(next()), Qt::QueuedConnection);
}

PlaylistContainer::~PlaylistContainer()
{
	while(lists.count() > 0) {
		delete lists.last();
		lists.pop_back();
	}
	delete tabs;
	delete vboxLayout;
}

void PlaylistContainer::ref() {}

void PlaylistContainer::unref() {}

void PlaylistContainer::streamStopped(StopEvent* event)
{
	//if(actlist) actlist->next();
	emit internalnext();
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
		else p->stop();
	}
}

void PlaylistContainer::addList()
{
	PlaylistView *pl = new PlaylistView(&device, this); 
	lists.append(pl);
	tabs->addTab(lists.last(), "Playlist "+QString::number(++counter));
	curlist = lists.last();
	tabs->setCurrentIndex(tabs->count()-1);
	//curlist->setContextMenuPolicy(Qt::ActionsContextMenu);
	curlist->setAcceptDrops(true);
	curlist->setDragEnabled(true);
	curlist->setDragDropMode(QAbstractItemView::DragDrop);
	curlist->setDropIndicatorShown(true);
	curlist->setSortingEnabled(false);
	curlist->setVolume(svolume);
	curlist->repeat(rf);
	curlist->shuffle(sf);
	curlist->viewAlbum(alv);
	curlist->viewArtist(arv);
	curlist->viewComment(cov);
	curlist->viewTrack(trv);
	curlist->viewTitle(tiv);
	curlist->viewYear(yev);
	curlist->viewGenre(gev);
	curlist->viewFile(fiv);
	curlist->viewLength(lev);
	connect(pl, SIGNAL(status(QString)), this, SIGNAL(status(QString)));
	connect(pl, SIGNAL(songPosition(int)), this, SIGNAL(songPosition(int)));
	connect(pl, SIGNAL(started(PlaylistView*)), this, SLOT(listStarted(PlaylistView*)));
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
	}
}
void PlaylistContainer::renameList()
{
	// TODO
}
void PlaylistContainer::fillCancel()
{ if(curlist) curlist->fillCancel(); }
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
{ if(actlist) actlist->pause(b); }
void PlaylistContainer::repeat(bool mode)
{ foreach(PlaylistView *pl, lists) pl->repeat(mode); 
  rf = mode; }
void PlaylistContainer::shuffle(bool mode)
{ foreach(PlaylistView *pl, lists) pl->shuffle(mode); 
  sf = mode; }
void PlaylistContainer::setVolume(int volume)
{ foreach(PlaylistView *pl, lists) pl->setVolume(volume);
  svolume = volume; }
void PlaylistContainer::eq1(int) {}
void PlaylistContainer::eq2(int) {}
void PlaylistContainer::eq3(int) {}
void PlaylistContainer::eq4(int) {}
void PlaylistContainer::eq5(int) {}
void PlaylistContainer::eq6(int) {}
void PlaylistContainer::eq7(int) {}
void PlaylistContainer::eq8(int) {}
void PlaylistContainer::eq9(int) {}
void PlaylistContainer::eq10(int) {}
void PlaylistContainer::eq11(int) {}
void PlaylistContainer::eq12(int) {}
void PlaylistContainer::eq13(int) {}
void PlaylistContainer::eq14(int) {}
void PlaylistContainer::eq15(int) {}
void PlaylistContainer::eq16(int) {}
void PlaylistContainer::eqalizer(bool b)
{ foreach(PlaylistView *pl, lists) pl->eqalizer(b); }
void PlaylistContainer::clear()
{ if(curlist) curlist->clear(); }
void PlaylistContainer::queueNext()
{ if(curlist) curlist->queueNext(); }
void PlaylistContainer::viewAlbum(bool b)
{ foreach(PlaylistView *pl, lists) pl->viewAlbum(b); 
  alv = b; }
void PlaylistContainer::viewArtist(bool b)
{ foreach(PlaylistView *pl, lists) pl->viewArtist(b); 
  arv = b; }
void PlaylistContainer::viewComment(bool b)
{ foreach(PlaylistView *pl, lists) pl->viewComment(b); 
  cov = b; }
void PlaylistContainer::viewTrack(bool b)
{ foreach(PlaylistView *pl, lists) pl->viewTrack(b); 
  trv = b; }
void PlaylistContainer::viewTitle(bool b)
{ foreach(PlaylistView *pl, lists) pl->viewTitle(b); 
  tiv = b; }
void PlaylistContainer::viewYear(bool b)
{ foreach(PlaylistView *pl, lists) pl->viewYear(b); 
  yev = b; }
void PlaylistContainer::viewGenre(bool b)
{ foreach(PlaylistView *pl, lists) pl->viewGenre(b); 
  gev = b; }
void PlaylistContainer::viewFile(bool b)
{ foreach(PlaylistView *pl, lists) pl->viewFile(b); 
  fiv = b; }
void PlaylistContainer::viewLength(bool b)
{ foreach(PlaylistView *pl, lists) pl->viewLength(b); 
  lev = b; }
void PlaylistContainer::editTag()
{ if(curlist) curlist->editTag(); }

void PlaylistContainer::removeSong()
{ if(curlist) curlist->removeSong(); }

void PlaylistContainer::tabChanged(int i)
{
	if(i < lists.count()) {
		curlist = lists[i];
	}
}
