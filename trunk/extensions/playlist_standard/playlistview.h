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
#include "interfaces.h"
#include "playlist.h"
#include "playlistmodel.h"
#include "player.h"
#include "global.h"
#include "tageditor.h"

class MyTreeView : public QTreeView
{
    Q_OBJECT
public:
    MyTreeView(QString &str, PlaylistModel &model, QWidget *parent = 0);
    //~MyTreeView();
	QModelIndexList getSelectedIndexes();
	virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dropEvent(QDropEvent *event);
    virtual void startDrag(Qt::DropActions supportedActions);

	QModelIndex mapToSource(QModelIndex);
	QModelIndex mapToSource(int row, int column);
	QModelIndex mapFromSource(QModelIndex);
	QModelIndex mapFromSource(int row, int column);
	void setFilterRegExp(QString s);
    
protected:
	virtual void hideEvent ( QHideEvent * event );
	virtual void showEvent ( QShowEvent * event );

private:
    bool dragStarted;
    PlaylistModel *_model;
    QSortFilterProxyModel pmodel;
    
private slots:
	void setColVisible(int,bool);
	void setColWidth(int,int);
	void setColPosition(int,int);

public slots:
signals:
	void needUpdate();
};


class PlaylistAbstract : public Playlist
{
	Q_OBJECT
 public:
	PlaylistAbstract(QString &str, Proxy *pr, QWidget *parent = 0);
	virtual ~PlaylistAbstract();
	virtual QString getName();
	virtual void setName(QString newname);
	virtual void storeListM3U(QString fname);
	virtual void storeListXSPF(QString fname);
	virtual void loadList(QString fname);
    virtual bool isPlaying();
	virtual void play(int index, double pos);
	virtual void setAutosave(bool b);
	virtual int curIndex();
	virtual double curPosition();
	virtual void rateCurrent(int offset, int value = 0);
	virtual QString curFile();
	virtual void setCurrent(int index) = 0;

	void storeState(bool save = true);

 public slots:
	virtual void addUrl(QUrl url);
	virtual void prev();
	virtual void next();
	virtual void play() = 0;
	virtual void stop();
	virtual void findCurrent();

	void addItem(QVariant item, int id, QModelIndex* ind = 0);
	void playFinished();
	void updateTag(TagEditor*);
	void updateStatus();
 private slots:
	void timerSlot();

 protected:
	Proxy *proxy;
    PlaylistModel model;
	bool autosave;
    bool playing;
    QModelIndex insindex;
    QModelIndex curindex;
    QModelIndex plindex;
    QList<QModelIndex> queue;
    QList<QModelIndex> prev_queue;
    QList<QModelIndex> shuffle_queue;
	bool delayedPlay;
	int delayedIndex;
	double delayedPos;
	int error_count;
    QString info;
	QTimer timer;

    virtual QModelIndex nextItem() = 0;
    virtual QModelIndex prevItem() = 0;
    void resetTags(QModelIndex& ind);
	void rateSong(QModelIndex &ind, int r, int offset=0);
	void refillShuffleQueue(int except = -1, int notstartwith = -1);
};


class PlaylistStandard : public PlaylistAbstract
{
    Q_OBJECT
	Q_INTERFACES(Playlist) 
public:
	PlaylistStandard(QString &str, Proxy* pr, QWidget *parent = 0);
    virtual ~PlaylistStandard();
	virtual QWidget* getWidget();
	virtual void setCurrent(int index);
public slots:
	virtual void play();
	virtual void stop();
	virtual void clear();
	virtual void queueNext();
	virtual void editTag();
	virtual void removeSong();
	virtual void reloadTags();
	virtual void setFilter(QString s);
private slots:
	void onClick( const QModelIndex & index );
	void onDoubleClick( const QModelIndex & index );
	void position(double pos);
signals:
	void status(QString);
	void message(QString, QString, QString, long);
	void started(Playlist*);
	void songPosition(int);
	void playPauseIcon (bool); // true means show a "play" icon, false means show "pause"
 protected:
	void addHardcodedActions(QWidget* w);
	void prepareNextAlbum(int except = -1);
	void prepareAlbumList(const QString* except=0, const QString* notStartWith=0);
    virtual QModelIndex nextItem();
    virtual QModelIndex prevItem();

	MyTreeView *view;
	QList<QModelIndex> current_album;
	QStringList album_queue;
};

class PlaylistStandardFactory : public PlaylistFactory
{
	Q_OBJECT
	Q_INTERFACES(PlaylistFactory)
 public:
	PlaylistStandardFactory();
	virtual void setProxy(Proxy *pr);
	virtual QStringList getAvailableTypes();
	virtual Playlist* getNewPlaylist(QString type, QWidget* parent, QString name);
 protected:
	Proxy *proxy;
};


#endif // PLAYLISTVIEW_H
 
