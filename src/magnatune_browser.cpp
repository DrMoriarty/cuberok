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
#include <QtXml>
#include "console.h"

MagnatuneBrowser::MagnatuneBrowser(QObject *parent) : Browser(parent)
{
	connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

MagnatuneBrowser::~MagnatuneBrowser()
{
}

void MagnatuneBrowser::GetList(QString comefrom)
{
	if(PLSet.proxyEnabled) {
		manager.setProxy(QNetworkProxy(QNetworkProxy::HttpProxy, PLSet.proxyHost, PLSet.proxyPort, PLSet.proxyUser, PLSet.proxyPassword));
	}
	if(!comefrom.size() || comefrom[0] != '/') comefrom = "/microbrowse/" + comefrom;
	reply = manager.get(QNetworkRequest(QUrl("http://magnatune.com" + comefrom)));
	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
}

void MagnatuneBrowser::replyFinished(QNetworkReply* reply)
{
	reply->disconnect();
	QString str = QString::fromUtf8((const char*)reply->readAll());
	Console::Self().log("Magnatune response:" + str);
	if(str.indexOf("xspf") > 0) {
		QString url, title;
		int st = str.indexOf("playlist_url=");
		int end = str.indexOf("xspf", st);
		st += 13;
		end += 4;
		int len = end - st;
		if(len > 0 && end < str.size()) {
			url = str.mid(st, len);
		}
		st = str.indexOf("playlist_title=");
		end = str.indexOf("\"", st);
		st += 15;
		len = end - st;
		if(len > 0 && end < str.size()) {
			title = str.mid(st, len);
		}
		QList< QStringList > data;
		data << QStringList();
		url = "http://magnatune.com"+url;
		data[0] << title << url/*tr("Drag this link to the playlist")*/ << "" << url;
		emit list(data);
		return;
	}
	QDomDocument doc;
	QString errString;
	int errLine = 0, errColumn = 0;
	QTextDocument tdoc;
	tdoc.setHtml(str);
	if(!doc.setContent(tdoc.toHtml(), &errString, &errLine, &errColumn)) {
		Console::Self().error(tr("MagnaTune error: %1 at line %2 column %3").arg(errString).arg(QString::number(errLine)).arg(QString::number(errColumn)));
		return;
	}
	QDomNodeList l = doc.elementsByTagName("a");
	QList< QStringList > data;
	for(int i=0; i<l.size(); i++) {
		QDomElement el = l.at(i).toElement();
		QString title, comment, id, url;
		title = el.text();
		comment = el.attribute("title", title);
		id = el.attribute("href", "no href");
		data << QStringList();
		data[data.size()-1] << title << comment << id << url;
	}
	emit list(data);
}

void MagnatuneBrowser::slotError(QNetworkReply::NetworkError)
{
	reply->disconnect();
	QList< QStringList > data;
	data << QStringList();
	data[0] << tr("Network error!");
	data[0] << tr("There is error during download a page from the magnatune.com");
	data[0] << "";
	data[0] << "";
	emit list(data);
}
