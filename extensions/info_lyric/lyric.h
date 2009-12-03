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

#ifndef LYRIC_H
#define LYRIC_H

#include <QtCore>
#include <QtNetwork>
#include "interfaces.h"

class Lyric : public Extension
{
	Q_OBJECT
	Q_INTERFACES(Extension) 

 public:
	Lyric();
	virtual ~Lyric();

	virtual bool prepare();
	virtual bool ready();
	virtual void update(int);
	virtual QString getName();
	virtual QWidget* getWidget();
	virtual QWidget* getSetupWidget();
	virtual int getDisturbs();
	
 private:
	QNetworkAccessManager *manager;
	QNetworkReply *reply;
	int searchType, trueSearchType;
	bool foundUrl;
	QString url;
	
	void getSong(QString artist, QString song);
	QString getLuckyLink(QString json);
	QString linkDigger(QString reply);
	void lyricDigger(QString reply);
	static int parseString(Lyric* that, const unsigned char * stringVal, unsigned int stringLen);
	static int parseMapKey(Lyric* that, const unsigned char * stringVal, unsigned int stringLen);

 private slots:
	void replyFinished(QNetworkReply*);
	void slotError(QNetworkReply::NetworkError);

};

#endif // LYRIC_H
