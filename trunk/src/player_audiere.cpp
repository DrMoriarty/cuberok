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

#include "player_audiere.h"
#define TIME 200

PlayerAudiere::PlayerAudiere() : repeat_mode(0), shuffle_mode(0), svolume(100), file(""), sync(false), paused(false)
{
    stream = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
}

PlayerAudiere::~PlayerAudiere()
{
    delete timer;
}

bool PlayerAudiere::prepare()
{
    device = OpenDevice();
    if(device) device->registerCallback(this);
	return device;
}

bool PlayerAudiere::ready()
{
	return device;
}

void PlayerAudiere::ref() {}

void PlayerAudiere::unref() {}

void PlayerAudiere::streamStopped(StopEvent* event)
{
    if(sync) {
		sync = false;
		sem.release();
    } else emit finish();
}

bool PlayerAudiere::open(QUrl fname)
{
    file = fname.toLocalFile();
    stream = OpenSound(device, file.toLocal8Bit(), true);
    if(stream) stream->setVolume(float(svolume)/100);
    return stream;
}

bool PlayerAudiere::play()
{
    if(stream) {
		stream->play();
		timer->start(TIME);
		return true;
    }
    return false;
}

bool PlayerAudiere::stop()
{
    if(stream && stream->isPlaying()) {
		sync_stop();
		stream->reset();
		timer->stop();
		return true;
    }
    return false;
}

bool PlayerAudiere::setPause(bool p)
{
    if(p && stream && stream->isPlaying()) {
		timer->stop();
		sync_stop();
		paused = true;
		return true;
    }
    if(!p && stream && paused) {
		stream->play();
		timer->start(TIME);
		paused = false;
		return true;
    }
    return false;
}

bool PlayerAudiere::close()
{
    if(stream) {
		timer->stop();
		sync_stop();
		stream = 0;
		return true;
    }
    return false;
}

bool PlayerAudiere::setPosition(double pos)
{
    if(stream && stream->isSeekable()) {
		stream->setPosition(stream->getLength()*pos);
		return true;
    }
    return false;
}

double PlayerAudiere::getPosition()
{
    if(stream && stream->isPlaying()) {
		long p = stream->getPosition();
		long l = stream->getLength();
		if(l > 0) return (double)p/l;
    }
	return 0.0;
}

int  PlayerAudiere::volume()
{
    return svolume;
}

void PlayerAudiere::setVolume(int v)
{
    svolume = v;
    if(stream) stream->setVolume(float(svolume)/100);
}

bool PlayerAudiere::playing()
{
    return stream && stream->isPlaying();
}

int PlayerAudiere::weight()
{
	return 10;
}

QString PlayerAudiere::name()
{
	return "Audiere";
}

void PlayerAudiere::timerUpdate()
{
    if(stream && stream->isPlaying()) {
		long p = stream->getPosition();
		long l = stream->getLength();
		if(l > 0) emit position((double)p/l);
    } else {
		timer->stop();
    }
}

void PlayerAudiere::sync_stop()
{
    if(stream) {
		sync = true;
		stream->stop();
		sem.acquire();
    }
}
