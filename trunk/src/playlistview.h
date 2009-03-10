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

#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <unistd.h>
#include <QtGui>
#include "playlistmodel.h"
#include "player.h"
#include "main.h"

class PlaylistView : public QTreeView
{
    Q_OBJECT

public:
    PlaylistView(QString &str, QWidget *parent = 0);
    ~PlaylistView();
    bool isPlaying();
    void dropEvent(QDropEvent *event);
    void startDrag(Qt::DropActions supportedActions);
	void storeListM3U(QString fname);
	void storeListXSPF(QString fname);
	void loadList(QString fname);
	void setAutosave(bool);
	QString getName();
	void setName(QString newname);
	int curIndex();
	double curPosition();
	void play(int index, double pos);
	void rateCurrent(int offset, int value = 0);
	QString curFile();
    
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
	void updateStatus();

public slots:
	void prev();
	void next();
	void play();
	void stop();
	void clear();
	void queueNext();
	void editTag();
	void removeSong();
	void reloadTags();
	void addUrl(QUrl);
signals:
	void status(QString);
	void message(QString, QString, QString);
	void started(PlaylistView*);
	void songPosition(int);
};

#endif // PLAYLISTVIEW_H
