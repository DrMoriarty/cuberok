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

#ifndef PLAYER_H
#define PLAYER_H

#ifndef WIN32
#define ToLocalFile(url) (url.scheme().toLower() == "file" ? url.toString().mid(7) : "")
#else
#define ToLocalFile(url) (url.scheme().toLower() == "file" ? url.toString().mid(8) : "")
#endif

#include <QtCore>

class Player : public QObject
{
    Q_OBJECT
 public:
    Player(): QObject(0), repeat_mode(false), shuffle_mode(false) {};
    ~Player() {};

	virtual bool prepare() = 0;
	virtual bool ready() = 0;

    virtual bool open(QUrl fname, long start = 0, long length = 0) = 0;
    virtual bool play() = 0;
    virtual bool stop() = 0;
    virtual bool setPause(bool p) = 0;
    virtual bool close() = 0;
    virtual bool setPosition(double pos) = 0;
    virtual double getPosition() = 0;
    virtual int  volume() = 0;
    virtual void setVolume(int v) = 0;
    virtual bool playing() = 0;

	virtual int  weight() = 0;
	virtual QString name() = 0;

    int  repeat_mode;
    int  shuffle_mode;

 signals:
    void position(double);
    void finish();

 protected:
	long _start;
	long _length;
};

Q_DECLARE_INTERFACE(Player, "Cuberok.Player/1.0")

#endif // PLAYER_H
