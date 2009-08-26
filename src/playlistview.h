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

class AbstractView : public QObject
{
	Q_OBJECT
 public:
	virtual QModelIndexList getSelectedIndexes() = 0;
	virtual QModelIndex mapToSource(QModelIndex) = 0;
	virtual QModelIndex mapToSource(int row, int column) = 0;
	virtual QModelIndex mapFromSource(QModelIndex) = 0;
	virtual QModelIndex mapFromSource(int row, int column) = 0;
	virtual void setFilterRegExp(QString s) = 0;
	virtual void scrollTo ( const QModelIndex & index, QAbstractItemView::ScrollHint hint = QAbstractItemView::EnsureVisible ) = 0;
 public slots:
	void clearSelection() = 0;
	void setCurrentIndex(const QModelIndex & index) = 0;
};

class MyTreeView : public QTreeView, public AbstractView
{
    Q_OBJECT
public:
    MyTreeView(QString &str, PlaylistModel &model, QWidget *parent = 0);
    //~MyTreeView();
	virtual QModelIndexList getSelectedIndexes();
	virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dropEvent(QDropEvent *event);
    virtual void startDrag(Qt::DropActions supportedActions);

	virtual QModelIndex mapToSource(QModelIndex);
	virtual QModelIndex mapToSource(int row, int column);
	virtual QModelIndex mapFromSource(QModelIndex);
	virtual QModelIndex mapFromSource(int row, int column);
	virtual void setFilterRegExp(QString s);
    
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

class PlaylistStandard : public Playlist
{
    Q_OBJECT
	Q_INTERFACES(Playlist) 
public:
	PlaylistStandard(QString &str, QWidget *parent = 0);
    virtual ~PlaylistStandard();
	virtual QWidget* getWidget();
    virtual bool isPlaying();
	virtual void storeListM3U(QString fname);
	virtual void storeListXSPF(QString fname);
	virtual void loadList(QString fname);
	virtual void setAutosave(bool b);
	virtual QString getName();
	virtual void setName(QString newname);
	virtual int curIndex();
	virtual double curPosition();
	virtual void play(int index, double pos);
	virtual void rateCurrent(int offset, int value = 0);
	virtual QString curFile();
	virtual void setCurrent(int index);
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
	virtual void addUrl(QUrl url);
	virtual void setFilter(QString s);
	virtual void findCurrent();
private slots:
	void onClick( const QModelIndex & index );
	void onDoubleClick( const QModelIndex & index );
	void addItem(QVariant item, int id, QModelIndex* ind = 0);
	void playFinished();
	void updateTag(int);
	void position(double pos);
	void updateStatus();
signals:
	void status(QString);
	void message(QString, QString, QString, long);
	void started(Playlist*);
	void songPosition(int);
	void playPauseIcon (bool); // true means show a "play" icon, false means show "pause"
 private:
    QModelIndex nextItem();
    QModelIndex prevItem();
	void rateSong(QModelIndex &ind, int r, int offset=0);
    void resetTags(QModelIndex& ind);

    PlaylistModel model;
	AbstractView *view;
	//QAbstractItemView *view;
	//MyTreeView *view;
	bool autosave;
    bool playing;
    QModelIndex insindex;
    QModelIndex curindex;
    QModelIndex plindex;
    QList<QModelIndex> queue;
    QList<QModelIndex> prev_queue;
	int  shuffle_count;
	bool delayedPlay;
	int delayedIndex;
	double delayedPos;
	int error_count;
    QString info;
};

class PlaylistStandardFactory : public PlaylistFactory
{
	Q_OBJECT
	Q_INTERFACES(PlaylistFactory)
 public:
	PlaylistStandardFactory();
	virtual QStringList getAvailableTypes();
	virtual Playlist* getNewPlaylist(QString type, QWidget* parent, QString name);
};


#endif // PLAYLISTVIEW_H
 
