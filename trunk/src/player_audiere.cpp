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

#include "player_audiere.h"
//#define ToLocalFile(url) url.toString().toLocal8Bit().mid(8)

#define TIME 200

//#include <QtGui>

Q_EXPORT_PLUGIN2(player_audiere, PlayerAudiere) 

QStringList whiteList;

PlayerAudiere::PlayerAudiere() : repeat_mode(0), shuffle_mode(0), svolume(100), file(""), sync(false), paused(false)
{
    stream = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
	whiteList << "application/ogg";
	whiteList << "audio/ogg";
	whiteList << "audio/x-vorbis+ogg";
	whiteList << "audio/x-flac+ogg";
	whiteList << "audio/mpeg";
	whiteList << "audio/x-flac";
	whiteList << "audio/x-wav";
	whiteList << "audio/x-aiff";
	whiteList << "audio/x-aiffc";
	whiteList << "audio/x-mod";
	whiteList << "audio/x-s3m";
	whiteList << "audio/x-xm";
	whiteList << "audio/x-it";
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

bool PlayerAudiere::canOpen(QString mime)
{
	return whiteList.contains(mime);
}

bool PlayerAudiere::open(QUrl fname, long start, long length)
{
    file = ToLocalFile(fname);
	SampleSource* source = OpenSampleSource(file.toLocal8Bit(), FF_AUTODETECT);
    stream = OpenSound(device, source, true);
    if(stream) {
		int ch, sr;
		SampleFormat sf;
		source->getFormat(ch, sr, sf);
		stream->setVolume(float(svolume)/100);
		_start = start * sr / 75;
		_length = length * sr / 75;
		if(!_length) _length = stream->getLength() - _start;
	} else {
		_start = _length = 0;
	}
    return stream;
}

bool PlayerAudiere::play()
{
    if(stream) {
		if(_start && stream->isSeekable()) 
			stream->setPosition(_start);
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
		stream->setPosition(_start + _length*pos);
		return true;
    }
    return false;
}

double PlayerAudiere::getPosition()
{
    if(stream && stream->isPlaying()) {
		long p = stream->getPosition();
		if(_length) return (double)(p - _start) / _length;
    }
	return 0.0;
}

int  PlayerAudiere::volume()
{
    return svolume;
}

void PlayerAudiere::setVolume(int v)
{
	if(v > 100) v = 100;
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
		if(_length) {
			if(p - _start >= _length) 
				stream->stop();
			else
				emit position((double)(p - _start) / _length);
		}
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

QStringList PlayerAudiere::hardcodedList()
{
	return whiteList;
}
