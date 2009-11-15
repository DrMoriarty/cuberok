/* Cuberok
 * Copyright (C) 2008-2009 Vasiliy Makarov <drmoriarty.0@gmail.com>
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

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QtGui>
#include "interfaces.h"

class Playlist: public QObject
{
    Q_OBJECT
public:
	Playlist(QString &str, QObject *parent = 0):QObject(parent) {
		plistname = str;
	};
	virtual ~Playlist() {};
	virtual QWidget* getWidget() = 0;
    virtual bool isPlaying() = 0;
	virtual void storeListM3U(QString fname) = 0;
	virtual void storeListXSPF(QString fname) = 0;
	virtual void loadList(QString fname) = 0;
	virtual void setAutosave(bool b) = 0;
	virtual QString getName() { return plistname; };
	virtual void setName(QString newname) { plistname = newname; };
	virtual int curIndex() = 0;
	virtual double curPosition() = 0;
	virtual void play(int index, double pos) = 0;
	virtual void rateCurrent(int offset, int value = 0) = 0;
	virtual QString curFile() = 0;
	virtual void setCurrent(int index)= 0;
public slots:
	virtual void prev() = 0;
	virtual void next() = 0;
	virtual void play() = 0;
	virtual void stop() = 0;
	virtual void clear() = 0;
	virtual void queueNext() = 0;
	virtual void editTag() = 0;
	virtual void removeSong() = 0;
	virtual void reloadTags() = 0;
	virtual void addUrl(QUrl url) = 0;
	virtual void setFilter(QString s) = 0;
	virtual void findCurrent() = 0;
signals:
	void status(QString);
	void message(QString, QString, QString, long);
	void started(Playlist*);
	void songPosition(int);
	void playPauseIcon (bool); // true means show a "play" icon, false means show "pause"
 protected:
	QString plistname;
};

class PlaylistFactory: public QObject
{
	Q_OBJECT
 public:
	virtual void setProxy(Proxy *pr) = 0;
	virtual QStringList getAvailableTypes() = 0;
	virtual Playlist* getNewPlaylist(QString type, QWidget* parent, QString name) = 0;
};

Q_DECLARE_INTERFACE(Playlist, "Cuberok.Playlist/1.0")
Q_DECLARE_INTERFACE(PlaylistFactory, "Cuberok.PlaylistFactory/1.0")

#endif // PLAYLIST_H
