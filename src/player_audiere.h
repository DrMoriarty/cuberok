/* Cuberok
 * Copyright (C) 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef PLAYER_AUDIERE_H
#define PLAYER_AUDIERE_H

#include <QtCore>
#include "player.h"
//#include "main.h"
#include <audiere.h>

using namespace audiere;

class PlayerAudiere : public Player, StopCallback
{
    Q_OBJECT
	Q_INTERFACES(Player) 
 public:
    PlayerAudiere();
    ~PlayerAudiere();

    ADR_METHOD(void) streamStopped(StopEvent* event);
    ADR_METHOD(void) ref();
    ADR_METHOD(void) unref();

	virtual bool prepare();
	virtual bool ready();

	virtual bool canOpen(QString mime);
    virtual bool open(QUrl fname, long start = 0, long length = 0);
    virtual bool play();
    virtual bool stop();
    virtual bool setPause(bool p);
    virtual bool close();
    virtual bool setPosition(double pos);
    virtual double getPosition();
    virtual int  volume();
    virtual void setVolume(int v);
    virtual bool playing();

	virtual int  weight();
	virtual QString name();
	virtual QStringList hardcodedList();

    int  repeat_mode;
    int  shuffle_mode;

 private:
    void sync_stop();
    int svolume;
    QString file;
    AudioDevicePtr device;
    OutputStreamPtr stream;
    QTimer *timer;
    QSemaphore sem;
    bool sync;
	bool paused;

 private slots:
    void timerUpdate();

/* signals:
    void position(double);
    void finish();*/
};


#endif // PLAYER_AUDIERE_H
