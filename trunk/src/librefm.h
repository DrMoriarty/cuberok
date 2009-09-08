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

#ifndef LIBREFM_H
#define LIBREFM_H

#include "interfaces.h"

class LibreFM : public Extension
{
	Q_OBJECT

 public:
	LibreFM();
	virtual ~LibreFM();

	virtual bool prepare();
	virtual bool ready();
	virtual bool update();
	virtual QString getName();
	virtual QWidget* getWidget();
	virtual QWidget* getSetupWidget();
	virtual int getDisturbs();

 private:
	void handshake(QString user, QString password);
	void nowplaying(QString artist, QString title, QString album, int sec = 0, int track = 0, QString mb = "");
	void submission(QString artist, QString title, int time, QString album, int sec, QString src = "P", QString rating = "", int track = 0, QString mb = "");

	void doQueue();
	
	int httpGetId, httpPostId;
	QString session, nowPlayingUrl, submissionUrl;
	bool connected;
	QVector< QList<QVariant> > stack;
	bool needInfo, delayed;
	int try_count;

 private slots:
	void requestFinished(int, bool);
	void requestStarted(int);
	void timerConnect();

 signals:
	void xmlInfo(QString);
};

#endif // LIBREFM_H
