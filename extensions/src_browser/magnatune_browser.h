/* Cuberok
 * Copyright (C) 2008-2009 Vasiliy Makarov <drmoriarty.0@gmail.com>
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

#ifndef MAGNATUNE_BROWSER_H
#define MAGNATUNE_BROWSER_H

#include "browser.h"
#include <QtNetwork>

class MagnatuneBrowser: public Browser
{
	Q_OBJECT
public:
	MagnatuneBrowser(Proxy *pr, QObject *parent = 0);
	~MagnatuneBrowser();
	virtual void GetList(QString = "", QString = "");
	virtual bool tagsAvailable();
	virtual STags getTags(QStringList);
 signals:
	virtual void list(QList< QStringList >);
 private:
	QNetworkAccessManager manager;
	QNetworkReply *reply;
 private slots:
	void replyFinished(QNetworkReply*);
	void slotError(QNetworkReply::NetworkError);
};

#endif //MAGNATUNE_BROWSER_H
