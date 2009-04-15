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

#include "jamendo_browser.h"
#include "playlistsettings.h"
#include "console.h"

JamendoBrowser::JamendoBrowser(QObject *owner)
	:Browser(owner)
{
	connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

JamendoBrowser::~JamendoBrowser()
{
}

void JamendoBrowser::GetList(QString comefrom)
{
	if(PLSet.proxyEnabled) {
		manager.setProxy(QNetworkProxy(QNetworkProxy::HttpProxy, PLSet.proxyHost, PLSet.proxyPort, PLSet.proxyUser, PLSet.proxyPassword));
	}
	if(!comefrom.size()) comefrom = "http://api.jamendo.com/get2/id+name+rating+url+weight/tag/plain/?order=rating_desc";
	comefrom += "&n=20";
	reply = manager.get(QNetworkRequest(QUrl(comefrom)));
	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
}

void JamendoBrowser::replyFinished(QNetworkReply* reply)
{
	reply->disconnect();
	QString str = QString::fromUtf8((const char*)reply->readAll());
	Console::Self().log("Jamendo response:" + str);
	QList< QStringList > data;
	QStringList strs = str.split('\n');
	foreach(QString s, strs) {
		QString title, comment, id, url;
		QStringList fields = s.split('\t');
		title = fields[1];
		comment = title;
		switch(fields.size()) {
		case 2: // song
			url = QUrl::fromPercentEncoding(fields[0].toLocal8Bit());
			break;
		case 3: // album
			id = "http://www.jamendo.com/get2/stream+name/track/plain/track_album/?order=rating&album_id="+fields[0];
			break;
		case 4: // artist
			id = "http://www.jamendo.com/get2/id+name+rating/album/plain/album_artist/?order=rating&artist_id="+fields[0];
			break;
		case 5: // tag
			id = "http://www.jamendo.com/get2/id+name+rating+url/artist/plain/artist_tag/?order=weight&tag_idstr="+title;
			break;
		}
		data << QStringList();
		data[data.size()-1] << title << comment << id << url;
	}
	emit list(data);
}

void JamendoBrowser::slotError(QNetworkReply::NetworkError)
{
	reply->disconnect();
	QList< QStringList > data;
	data << QStringList();
	data[0] << tr("Network error!");
	data[0] << tr("There is error during download data from the jamendo.com");
	data[0] << "";
	data[0] << "";
	emit list(data);
}
