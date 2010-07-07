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

#ifndef PLAYER_PHONON_H
#define PLAYER_PHONON_H

#include <QtCore>
#include "player.h"
//#include "main.h"

#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>

class PlayerPhonon : public Player
{
    Q_OBJECT
	Q_INTERFACES(Player) 
 public:
    PlayerPhonon();
    ~PlayerPhonon();

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

    int  repeat_mode;
    int  shuffle_mode;

 private:
	qint64 Pstart, Plength, _pos;
	bool needPos, needPlay;
	QMap<QString, QString> mimeTypes;
	
	Phonon::AudioOutput *audioOutput;
	Phonon::MediaObject *mediaObject;
	Phonon::MediaObject *metaInformationResolver;
	Phonon::MediaSource source;
	
 private slots:
	void stateChanged(Phonon::State newState, Phonon::State oldState);
	void tick(qint64 time);
	void sourceChanged(const Phonon::MediaSource &source);
	void metaStateChanged(Phonon::State newState, Phonon::State oldState);
	void aboutToFinish();
	void sourceFinished();
};


#endif // PLAYER_PHONON_H
