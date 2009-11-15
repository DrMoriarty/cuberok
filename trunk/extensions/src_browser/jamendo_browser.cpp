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

#include "jamendo_browser.h"

JamendoBrowser::JamendoBrowser(Proxy *pr, QObject *owner)
	:Browser(pr, owner), listType(LIST_NONE)
{
	connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

JamendoBrowser::~JamendoBrowser()
{
}

bool JamendoBrowser::tagsAvailable()
{
	return true;
}

STags JamendoBrowser::getTags(QStringList list)
{
	STags tags;
	tags = _tag;
	tags.tag0.title = list[0];
	tags.tag0.url = QUrl(list[3]);
	tags.tag0.filetype = tags.tag0.url.scheme();
	return tags;
}

void JamendoBrowser::GetList(QString comefrom, QString text)
{
	if(proxy->hasVariable("proxyEnabled") && proxy->getVariable("proxyEnabled") == "true") {
		manager.setProxy(QNetworkProxy(QNetworkProxy::HttpProxy,
									   proxy->getVariable("proxyHost"),
									   proxy->getVariable("proxyPort").toInt(),
									   proxy->getVariable("proxyUser"),
									   proxy->getVariable("proxyPassword")));
	}
	if(!comefrom.size()) comefrom = "http://api.jamendo.com/get2/id+name+rating+url+weight/tag/plain/?order=rating_desc";
	comefrom += "&n=50";
	reply = manager.get(QNetworkRequest(QUrl(comefrom)));
	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
	if (text.size()) switch(listType) {
	case LIST_GENRE:
		_tag.tag0.genre = text; break;
	case LIST_ARTIST:
		_tag.tag0.artist = text; break;
	case LIST_ALBUM:
		_tag.tag0.album = text; break;
	case LIST_NONE:
	default:
		;
	}
}

void JamendoBrowser::replyFinished(QNetworkReply* reply)
{
	reply->disconnect();
	QString str = QString::fromUtf8((const char*)reply->readAll());
	proxy->log("Jamendo response:" + str);
	QList< QStringList > data;
	QStringList strs = str.split('\n');
	foreach(QString s, strs) {
		QString title, title_en, comment, id, url;
		QStringList fields = s.split('\t');
		if(fields.size() < 2) {
			proxy->warning(tr("Jamendo: Wrong response '%1'").arg(s));
			continue;
		}
		title = fields[1];
		if(fields.size() >=4) {
			QStringList ttt = fields[3].split('/');
			title_en = ttt[ttt.size()-1];
		}
		comment = title;
		switch(fields.size()) {
		case 2: // song
			url = QUrl::fromPercentEncoding(fields[0].toLocal8Bit());
			listType = LIST_NONE;
			break;
		case 3: // album
			id = "http://www.jamendo.com/get2/stream+name/track/plain/track_album/?order=rating&album_id="+fields[0];
			listType = LIST_ALBUM;
			break;
		case 4: // artist
			id = "http://www.jamendo.com/get2/id+name+rating/album/plain/album_artist/?order=rating&artist_id="+fields[0];
			listType = LIST_ARTIST;
			break;
		case 5: // tag
			id = "http://www.jamendo.com/get2/id+name+rating+url/artist/plain/artist_tag/?order=weight&tag_idstr="+title_en;
			listType = LIST_GENRE;
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
	data[0] << tr("There is an error during download data from the jamendo.com");
	data[0] << "";
	data[0] << "";
	emit list(data);
}
