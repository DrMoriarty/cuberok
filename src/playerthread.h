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

#ifndef PLAYERTHREAD_H
#define PLAYERTHREAD_H

#include <QtCore>
#include <QtGui>
#include "main.h"

class PlayerThread : public QThread
{
    Q_OBJECT

public:
	PlayerThread(QString fname, QMutex &mp, QObject *parent = 0);
    ~PlayerThread();

protected:
    void run();
    void prepareTags();
    QString prepareTag(char *);
    QMutex *mutexPause;

public slots:
	void seek(double pos);
	void timerUpdate();

signals:
	void position(double pos1, double pos2);
	void tagready(QString);
	
private:
	QString file;
	static AudioDevicePtr device = OpenDevice();
	static int count = 0;
	OutputStreamPtr stream;
	QTimer *timer;
};

#endif // PLAYERTHREAD_H
