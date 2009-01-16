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

#ifndef PLAYLISTCONTAINER_H_
#define PLAYLISTCONTAINER_H_

#include "playlistview.h"

class PlaylistContainer : public QWidget
{
    Q_OBJECT

public:
	PlaylistContainer(QWidget *parent = 0);
    ~PlaylistContainer();
	void prepare();
	void newList(QString listname = "");
    
private:
    
    QList<PlaylistView*> lists;
    QVBoxLayout *vboxLayout;
    QTabWidget *tabs;
	QToolButton *newButton;
	QToolButton *closeButton;
    PlaylistView *curlist, *actlist;
    int counter;
    bool alv, arv, cov, trv, tiv, yev, gev, fiv, lev;
    
private slots:
	void listStarted(PlaylistView*);
	void tabChanged(int);

public slots:
	void addList();
	void delList();
	void renameList();
	void loadList();
	void saveList();
	void prev();
	void next();
	void play();
	void pause(bool);
	void stop();
	void repeat(bool mode);
	void shuffle(bool mode);
	void setVolume(int volume); 
	void clear();
	void queueNext();
	void viewAlbum(bool);
	void viewArtist(bool);
	void viewComment(bool);
	void viewTrack(bool);
	void viewTitle(bool);
	void viewYear(bool);
	void viewGenre(bool);
	void viewFile(bool);
	void viewLength(bool);
	void viewRating(bool);
	void editTag();
	void removeSong();
	void reloadTags();
	void openUrl();
	void rateLove();
	void rateBan();
	void rateUp();
	void rateDown();
signals:
	void status(QString);
	void message(QString, QString, QString);
	void internalnext();
	void songPosition(int);
};

#endif /*PLAYLISTCONTAINER_H_*/
