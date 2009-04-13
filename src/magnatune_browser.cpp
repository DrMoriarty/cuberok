/* Cuberok
 * Copyright (C) 2008-2009 Vasiliy Makarov <drmoriarty.0@gmail.com>
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

#include "magnatune_browser.h"
#include "playlistsettings.h"

Magnatune_Browser::Magnatune_Browser(QObject *parent) : Browser(parent)
{
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

Magnatune_Browser::~Magnatune_Browser()
{
}

void Magnatune_Browser::GetList(QString comefrom)
{
	if(PLSet.proxyEnabled) {
		manager.setProxy(QNetworkProxy(QNetworkProxy::HttpProxy, PLSet.proxyHost, PLSet.proxyPort, PLSet.proxyUser, PLSet.proxyPassword));
	}
	reply = manager.get(QNetworkRequest(QUrl("http://magnatune.com/microbrowse/" + comefrom)));
	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
}

void Magnatune_Browser::replyFinished(QNetworkReply* reply)
{
	reply->disconnect();
	QString data = QString::fromUtf8((const char*)http.readAll());
	Console::Self().log("Magnatune response:" + data);
	
}

void Magnatune_Browser::slotError(QNetworkReply::NetworkError)
{
	reply->disconnect();
	QList< QList<QString> > data;
	data << QList<QString>();
	data[0] << "Network error!";
	data[0] << "There is error during download a page from the magnatune.com";
	data[0] << "";
	data[0] << "";
	emit list(data);
}
