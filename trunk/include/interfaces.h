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
#include <QtGui>

enum Disturbs {
	DoNotDisturb = 0,
	DisturbOnControl = 0x01,
	DisturbOnStatus = 0x02,
	DisturbOnTags = 0x04,
	DisturbOnUrl = 0x08,
	DisturbOnInfo = 0x10,
	DisturbOnRequest = 0x20,
	DisturbOnPlControl = 0x40,
	DisturbOnChangeSettings = 0x80,
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

class SPlControl {
	public:
	enum Command {
		Nothing = 0,
		Append, New, Close, Next, Previous
	};
	int command;
	QString value;

	SPlControl() : command(0) {};
	SPlControl(int c, QString val = QString()): command(c), value(val) {};
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

QDataStream& operator<<(QDataStream& s, const STags& v);
QDataStream& operator>>(QDataStream& s, STags& v);

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
	SInfo info;
	STags tags;
	long id;
 
	SRequest() {
		time.start();
	};
	
	SRequest(int t) {
		time.start();
		info.type = t;
	};
	SRequest(int t, const STags& tag) {
		time.start();
		info.type = t;
		tags = tag;
	}
	int elapsed() {
		return time.elapsed();
	}
 protected:
	QTime time;
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
	
	virtual void setControl(const SControl& control) = 0;
	virtual void setStatus(const SStatus& status) = 0;
	virtual void setTags(const STags& tags) = 0;
	virtual void setUrl(const QUrl& url) = 0;
	virtual void setInfo(const SInfo& info) = 0;
	virtual long setRequest(const SRequest& request) = 0;
	virtual void setResponse(long requestId, const SInfo& info) = 0;
	virtual void delRequest(long requestId) = 0;
	virtual void setPlControl(const SPlControl& plcontrol) = 0;

	virtual SControl getControl() = 0;
	virtual SStatus  getStatus() = 0;
	virtual SStatus  getPrevStatus() = 0;
	virtual STags    getTags() = 0;
	virtual QUrl     getUrl() = 0;
	virtual SInfo    getInfo(int type) = 0;
	virtual SRequest getRequest() = 0;
	virtual bool     infoExist(int type) = 0;
	virtual SPlControl getPlControl() = 0;

	virtual bool hasVariable(QString varname) = 0;
	virtual QString getVariable(QString varname) = 0;
	virtual void setVariable(QString varname, QString value) = 0;
	virtual void delVariable(QString varname) = 0;

	virtual void log(QString) = 0;
	virtual void message(QString) = 0;
	virtual void warning(QString) = 0;
	virtual void error(QString) = 0;
};

class ExtensionSetupWidget : public QWidget
{
	Q_OBJECT
 public:
	ExtensionSetupWidget(QWidget *parent = 0) : QWidget(parent) {};
	virtual ~ExtensionSetupWidget() {};
	virtual void storeState() = 0;
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
	virtual QString getAuthor() = 0;
	virtual QString getDescription() = 0;
	virtual QWidget* getWidget() = 0;
	virtual ExtensionSetupWidget* getSetupWidget() = 0;
	virtual int getDisturbs() = 0;
	virtual void storeState() {};

 signals:

 protected:
	Proxy* proxy;
};

Q_DECLARE_INTERFACE(Extension, "Cuberok.Extension/1.0")

#endif // INTERFACES_H
