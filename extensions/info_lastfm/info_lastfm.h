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

#ifndef LASTFM_H
#define LASTFM_H

#include "interfaces.h"

class InfoLastFM : public Extension
{
	Q_OBJECT
	Q_INTERFACES(Extension) 

 public:
	InfoLastFM();
	virtual ~InfoLastFM();

	virtual bool prepare();
	virtual bool ready();
	virtual void update(int);
	virtual QString getName();
	virtual QWidget* getWidget();
	virtual QWidget* getSetupWidget();
	virtual int getDisturbs();

 private:

	void artistInfo(QString artist);
	void albumInfo(QString artist, QString album);

	bool parseInfo(const QString& xml, QString& artist, QString& album, QString& mbid, QString& imageUrl, QString& info);

	void doQueue();
	
	int httpGetId, httpPostId;
	QVector< QList<QVariant> > stack;
	bool needInfo;

 private slots:
	void requestFinished(int, bool);
	void requestStarted(int);
	void timerConnect();
};

#endif // LASTFM_H
