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

#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#if !defined(_WIN32) && !defined(WIN32)
#include <unistd.h>
#else
#include <time.h>
#endif // WIN32
#include <QtGui>
#include "playlist.h"
#include "playlistmodel.h"
#include "player.h"
#include "global.h"

class MyTreeView : public QTreeView
{
    Q_OBJECT
public:
    MyTreeView(QString &str, QWidget *parent = 0);
    ~MyTreeView();
	virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual bool isPlaying();
    virtual void dropEvent(QDropEvent *event);
    virtual void startDrag(Qt::DropActions supportedActions);
	virtual void storeListM3U(QString fname);
	virtual void storeListXSPF(QString fname);
	virtual void loadList(QString fname);
	virtual void setAutosave(bool);
	virtual QString getName();
	virtual void setName(QString newname);
	virtual int curIndex();
	virtual double curPosition();
	virtual void play(int index, double pos);
	virtual void rateCurrent(int offset, int value = 0);
	virtual QString curFile();
	virtual void setCurrent(int index);
    
protected:
	virtual void hideEvent ( QHideEvent * event );
	virtual void showEvent ( QShowEvent * event );

private:
    QModelIndex nextItem();
    QModelIndex prevItem();
    void resetTags(QModelIndex& ind);
	void rateSong(QModelIndex &ind, int r, int offset=0);
    
	QString plistname;
    PlaylistModel model;
    QSortFilterProxyModel pmodel;
    QModelIndex insindex;
    QModelIndex curindex;
    QModelIndex plindex;
    QList<QModelIndex> queue;
    QList<QModelIndex> prev_queue;
    QString info;
    bool correct;
    bool playing;
    bool dragStarted;
	bool autosave;
	int  shuffle_count;
	bool delayedPlay;
	int delayedIndex;
	double delayedPos;
	int error_count;
    
private slots:
	void addItem(QVariant item, int id, QModelIndex* ind = 0);
	void playFinished();
	void onClick( const QModelIndex & index );
	void onDoubleClick( const QModelIndex & index );
	void position(double pos);
	void updateTag(int);
	void setColVisible(int,bool);
	void setColWidth(int,int);
	void setColPosition(int,int);
	void updateStatus();

public slots:
	virtual void prev();
	virtual void next();
	virtual void play();
	virtual void stop();
	virtual void clear();
	virtual void queueNext();
	virtual void editTag();
	virtual void removeSong();
	virtual void reloadTags();
	virtual void addUrl(QUrl);
	virtual void setFilter(QString);
	virtual void findCurrent();
signals:
	void status(QString);
	void message(QString, QString, QString, long);
	void started();
	void songPosition(int);
	void playPauseIcon (bool); // true means show a "play" icon, false means show "pause"
};

class PlaylistStandard : public Playlist
{
    Q_OBJECT
	Q_INTERFACES(Playlist) 
public:
	PlaylistStandard(QString &str, QWidget *parent = 0) : Playlist(str, parent) {
		tree = new MyTreeView(str, parent);
		connect(tree, SIGNAL(status(QString)), this, SIGNAL(status(QString)));
		connect(tree, SIGNAL(message(QString, QString, QString, long)), this, SIGNAL(message(QString, QString, QString, long)));
		connect(tree, SIGNAL(started()), this, SIGNAL(startedSlot()));
		connect(tree, SIGNAL(songPosition(int)), this, SIGNAL(songPosition(int)));
		connect(tree, SIGNAL(playPauseIcon (bool)), this, SIGNAL(playPauseIcon (bool)));
	};
    ~PlaylistStandard() {};
	virtual QWidget* getWidget() { return tree; };
    virtual bool isPlaying() { return tree->isPlaying(); };
	virtual void storeListM3U(QString fname) { tree->storeListM3U(fname); };
	virtual void storeListXSPF(QString fname) { tree->storeListXSPF(fname); };
	virtual void loadList(QString fname) { loadList(fname); };
	virtual void setAutosave(bool b) { setAutosave(b); };
	virtual QString getName() { return tree->getName(); };
	virtual void setName(QString newname) { tree->setName(newname); };
	virtual int curIndex() { return tree->curIndex(); };
	virtual double curPosition() { return tree->curPosition(); };
	virtual void play(int index, double pos) { tree->play(index, pos); };
	virtual void rateCurrent(int offset, int value = 0) { tree->rateCurrent(offset, value); };
	virtual QString curFile() { return tree->curFile(); };
	virtual void setCurrent(int index) { tree->setCurrent(index); };
public slots:
	virtual void prev() { tree->prev(); };
	virtual void next() { tree->next(); };
	virtual void play() { tree->play(); };
	virtual void stop() { tree->stop(); };
	virtual void clear() { tree->clear(); };
	virtual void queueNext() { tree->queueNext(); };
	virtual void editTag() { tree->editTag(); };
	virtual void removeSong() { tree->removeSong(); };
	virtual void reloadTags() { tree->reloadTags(); };
	virtual void addUrl(QUrl url) { tree->addUrl(url); };
	virtual void setFilter(QString s) { tree->setFilter(s); };
	virtual void findCurrent() { tree->findCurrent(); };
	void startedSlot() { emit started(this); };
signals:
	void status(QString);
	void message(QString, QString, QString, long);
	void started(Playlist*);
	void songPosition(int);
	void playPauseIcon (bool); // true means show a "play" icon, false means show "pause"
 private:
	MyTreeView *tree;
};


#endif // PLAYLISTVIEW_H
