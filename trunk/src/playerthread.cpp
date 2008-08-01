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

#include "playerthread.h"
#include "main.h"

using namespace audiere;

PlayerThread::PlayerThread(int *fd, QString fname, QMutex &mp, QObject *parent)
    : QThread(parent), fdescr(fd), tags(true)
{
	file = fname;
	mutexPause = &mp;
	count ++;
	stream = OpenSound(device, fname, true);
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
	
}

PlayerThread::~PlayerThread()
{
    stream->stop();
    timer->stop();
    count --;
    delete timer;
}

void PlayerThread::run()
{
    stream->setVolume(float(svolume)/100);
    stream->play();
    timer->start(500);
    
	//if(mpg) run_mpg123();
	//else run_audiere();
}

void PlayerThread::timerUpdate()
{
	if(stream && stream->isPlaying()) {
		long p = stream->getPosition();
		long l = stream->getLength();
		emit position(p,l);
	} else {
		timer->stop();
	}
}


void PlayerThread::seek(double pos)
{
	
}

void PlayerThread::prepareTags()
{
	emit tagready(
			prepareTag("FIXME"/*mpg::id3.title.p*/)/*,
			prepareTag(mpg::id3.artist.p),
			prepareTag(mpg::id3.album.p),
			prepareTag(mpg::id3.year.p),
			prepareTag(mpg::id3.genre.p),
			prepareTag(mpg::id3.comment.p)*/);
}

QString PlayerThread::prepareTag(char *tag)
{
	switch(tag[0]) {
	case 0: return QString(tag+1);
	case 1: return QString::fromUtf16((ushort *)(tag+1));
	case 2: return QString::fromUtf16((ushort *)(tag+1));
	case 3: return QString::fromUtf8(tag+1);
	}
	return QString();
}
