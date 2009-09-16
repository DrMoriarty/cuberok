/* Cuberok
 * Copyright (C) 2009 Vasiliy Makarov <drmoriarty.0@gmail.com>
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

#ifndef INTERFACES_H
#define INTERFACES_H

// Some interfaces and types for plugins and extensions

#include "global.h"
#include "tagentry.h"
#include <QtCore>

enum Disturbs {
	DoNotDisturb = 0,
	DisturbOnControl = 0x01,
	DisturbOnStatus = 0x02,
	DisturbOnTags = 0x04,
	DisturbOnUrl = 0x08,
	DisturbOnInfo = 0x10,
	DisturbOnRequest = 0x20,
	DisturbAlways = 0xffff
};

class SControl {
 public:
	enum Command {
		Nothing = 0,
		Stop, Play, Pause, Volume, Position
	};
	int command;
	float value;

	SControl() : command(0), value(.0f) {};
	SControl(int c, float v = .0f) :command(c), value(v) {};
};

class SStatus {
 public:
	enum PlayingStatus {
		Stopped = 0, Playing, Paused
	};
	int playing;
	float pos;
	float volume;

	SStatus() : playing(0), pos(.0f), volume(.0f) {};
	SStatus(int p, float po, float vo) : playing(p), pos(po), volume(vo) {};
};

class STags {
 public:
	TagEntry tag0;
};

class SInfo {
 public:
	enum InfoType {
		Nothing = 0,
		ArtistArt = 0x01,
		AlbumArt = 0x02,
		GenreArt = 0x04,
		ArtistText = 0x08,
		AlbumText = 0x10,
		GenreText = 0x20,
		Lyric = 0x40,
		AllTypes = 0xffff
	};
	int type;
	QString text;
	QString url;

	SInfo() : type(0) {};
	SInfo(int ty, QString te, QString ur) : type(ty), text(te), url(ur) {};
};

class SRequest {
 public:
	int type;

	SRequest() : type(0) {};
	SRequest(int t) : type(t) {};
};

// proxy object for sending messages between plugins
class Proxy : public QObject
{
	Q_OBJECT
 public:
	Proxy(): QObject(0) {};
	virtual ~Proxy() {};

	virtual void beginTransaction() = 0;
	virtual void endTransaction() = 0;
	
	virtual void setControl(SControl control) = 0;
	virtual void setStatus(SStatus status) = 0;
	virtual void setTags(STags tags) = 0;
	virtual void setUrl(QUrl url) = 0;
	virtual void setInfo(SInfo info) = 0;
	virtual void setRequest(SRequest request) = 0;

	virtual SControl getControl() = 0;
	virtual SStatus  getStatus() = 0;
	virtual SStatus  getPrevStatus() = 0;
	virtual STags    getTags() = 0;
	virtual QUrl     getUrl() = 0;
	virtual SInfo    getInfo(int type) = 0;
	virtual SRequest getRequest() = 0;
	virtual bool     infoExist(int type) = 0;

	virtual bool hasVariable(QString varname) = 0;
	virtual QString getVariable(QString varname) = 0;

	virtual void log(QString) = 0;
	virtual void message(QString) = 0;
	virtual void warning(QString) = 0;
	virtual void error(QString) = 0;
};

// 
class Extension : public QObject
{
    Q_OBJECT
 public:
    Extension(): QObject(0) {};
    virtual ~Extension() {};

	virtual void setProxy(Proxy* p) { proxy = p; };
	virtual bool prepare() = 0;
	virtual bool ready() = 0;
	virtual void update(int) = 0;
	virtual QString getName() = 0;
	virtual QWidget* getWidget() = 0;
	virtual QWidget* getSetupWidget() = 0;
	virtual int getDisturbs() = 0;

 signals:

 protected:
	Proxy* proxy;
};

Q_DECLARE_INTERFACE(Extension, "Cuberok.Extension/1.0")

#endif // INTERFACES_H
