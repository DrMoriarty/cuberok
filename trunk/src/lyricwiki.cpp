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

#include "main.h"
#include "lyricwiki.h"
#include "playlistsettings.h"
#include <QtGui>
#include "console.h"

LyricWiki::LyricWiki() : QObject()
{
	connect(&http, SIGNAL(requestFinished(int, bool)), this, SLOT(requestFinished(int, bool)));
	connect(&http, SIGNAL(requestStarted(int)), this, SLOT(requestStarted(int)));
}

LyricWiki::~LyricWiki()
{
}

LyricWiki& LyricWiki::Self()
{
	static LyricWiki inst;
	return inst;
}

void LyricWiki::requestStarted(int id)
{
	Console::Self().log("LyricWiki: Request started " + http.currentRequest().toString());
}

void LyricWiki::requestFinished(int id, bool err)
{
	if(err) {
		Console::Self().error(QString("LyricWiki: Request failed: %1.").arg(http.errorString()));
	} else {
		QByteArray arr = http.readAll();
		Console::Self().log("LyricWiki response:" + arr);
		emit xmlInfo(QString::fromUtf8((const char*)arr));
	}
}

void LyricWiki::getSong(QString artist, QString song)
{
	if(PLSet.proxyEnabled) {
		http.setProxy(PLSet.proxyHost, PLSet.proxyPort, PLSet.proxyUser, PLSet.proxyPassword);
	}

	QUrl url("http://lyricwiki.org/api.php");
	url.addQueryItem("func", "getSong");
	url.addQueryItem("artist", artist);
	url.addQueryItem("song", song);
	url.addQueryItem("fmt", "html"); // xml

	http.setHost(url.host(), QHttp::ConnectionModeHttp, 80);
	http.get(QString(url.toEncoded()));
}
