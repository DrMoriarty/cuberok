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

#include "lyric.h"
#include "lyricwidget.h"

#ifdef HAVE_YAJL
#include <yajl/yajl_parse.h>
typedef int (*yajl_strcallback)(void*, const unsigned char*, unsigned int);
#endif

#if QT_VERSION >= 0x040600
#include <QtWebKit>
#endif

Q_EXPORT_PLUGIN2(info_lyric, Lyric) 

Lyric::Lyric() : Extension(), reply(0), searchType(-1)
{
	manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

Lyric::~Lyric()
{
	delete manager;
}

bool Lyric::prepare()
{
	return true;
}

bool Lyric::ready()
{
	return proxy;
}

void Lyric::update(int f)
{
	if(f & DisturbOnRequest) {
		STags t = proxy->getTags();
		SRequest r = proxy->getRequest();
		switch(r.type) {
		case SInfo::Lyric:
			getSong(t.tag0.artist, t.tag0.title);
			break;
		default:
			break;
		}
	}
}

QString Lyric::getName()
{
	return tr("Lyric");
}

QWidget* Lyric::getWidget()
{
	return 0;
}

QWidget* Lyric::getSetupWidget()
{
	return new LyricWidget(proxy);
}

int Lyric::getDisturbs()
{
	return DisturbOnRequest;
}

QString Lyric::linkDigger(QString reply)
{
	proxy->log("Lyric response:" + reply);
	switch(searchType) {
	case 1:
#if QT_VERSION >= 0x040600
		{
			QWebPage pg;
			pg.mainFrame()->setHtml(reply);
			QWebElement sr = pg.mainFrame()->documentElement().findFirst("ul.mw-search-results href");
			proxy->log(QString("search results ") + sr.toOuterXml());
			proxy->log(pg.mainFrame()->documentElement().findFirst("p.mw-search-pager-bottom").toOuterXml());
			QString link = sr.findFirst("a").attribute("href");
			searchType = -2;
			return link;
		}
		break;
#endif
	case 0:
	case 2:
	default:
		searchType = -1;
		return getLuckyLink(reply);
		break;
	}
}

void Lyric::lyricDigger(QString reply)
{
	searchType = trueSearchType;
	if(proxy->infoExist(SInfo::Lyric) || !reply.size()) return;
	proxy->log("Lyric response:" + reply);
#if QT_VERSION >= 0x040600
	switch(searchType) {
	case -2: // result page from LyricWikia
		{
			QWebPage pg;
			pg.mainFrame()->setHtml(reply);
			proxy->setInfo(SInfo(SInfo::Lyric, pg.mainFrame()->documentElement().findFirst("div.lyricbox").toOuterXml(), ""));
		}
		break;
	default:
		proxy->setInfo(SInfo(SInfo::Lyric, reply, ""));
		break;
	}
#else
		proxy->setInfo(SInfo(SInfo::Lyric, reply, ""));
#endif
}

void Lyric::replyFinished(QNetworkReply* reply)
{
	reply->disconnect();
	QString str = QString::fromUtf8((const char*)reply->readAll());
	if(searchType < 0) {
		lyricDigger(str);
	} else {
		QString link = linkDigger(str);
		if(link.size()) {
			reply = manager->get(QNetworkRequest(QUrl(link)));
			connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
			proxy->log("Lyric link is " + link);
		} else {
			proxy->log("Lyric: There isn't any link!");
		}
	}
}

void Lyric::getSong(QString artist, QString song)
{
	if(proxy->hasVariable("proxyEnabled") && proxy->getVariable("proxyEnabled") == "true") {
		manager->setProxy(QNetworkProxy(QNetworkProxy::HttpProxy,
									   proxy->getVariable("proxyHost"),
									   proxy->getVariable("proxyPort").toInt(),
									   proxy->getVariable("proxyUser"),
									   proxy->getVariable("proxyPassword")));
	}
	if(proxy->hasVariable("lyricSearchType")) trueSearchType = searchType = proxy->getVariable("lyricSearchType").toInt();
	else trueSearchType = searchType = 0;
	QString ar = artist, so = song;
	QUrl url;
	switch(searchType) {
	case 0:
	default:
		ar.replace(" ", "+");
		so.replace(" ", "+");
		url = QUrl("http://ajax.googleapis.com/ajax/services/search/web?v=1.0");
		url.addQueryItem("q", "lyric+\""+ar+"\"+\""+so+"\"");
		/*if(proxy->hasVariable("lang")) {
			url.addQueryItem("lang", proxy->getVariable("lang"));
			}*/
		break;
	case 1: // Lyrics.Wikia.Com
		ar.replace(" ", "+");
		so.replace(" ", "+");
#if QT_VERSION >= 0x040600
		url = QUrl("http://lyrics.wikia.com/index.php?");
		url.addQueryItem("search", "\""+ar+"\":\""+so+"\"");
#else
		url = QUrl("http://ajax.googleapis.com/ajax/services/search/web?v=1.0");
		url.addQueryItem("q", "\""+ar+"\":\""+so+"\"+site:lyrics.wikia.com");
#endif
		break;
	case 2: // NoMoreLyrics.Net
		ar.replace(" ", "+");
		so.replace(" ", "+");
		url = QUrl("http://ajax.googleapis.com/ajax/services/search/web?v=1.0");
		url.addQueryItem("q", "\""+ar+"\":\""+so+"\"+site:nomorelyrics.net");
		break;
	}
	proxy->log(tr("Lyric: search lyric at '%1'").arg(url.toString()));
	reply = manager->get(QNetworkRequest(url));
	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
}

void Lyric::slotError(QNetworkReply::NetworkError)
{
	if(searchType == -1) searchType = trueSearchType;
	reply->disconnect();
	proxy->error(tr("Lyric: Network error!"));
}

QString Lyric::getLuckyLink(QString json)
{
	foundUrl = false;
	url = "";
#ifdef HAVE_YAJL
	yajl_handle hand;
	yajl_status stat;
	yajl_parser_config cfg = { 1, 1 };
	yajl_callbacks callbacks = {  
		NULL, //null,  
		NULL, //boolean,  
		NULL,  
		NULL,  
		NULL, //number,  
		(yajl_strcallback)parseString, //string,  
		NULL, //start_map,  
		(yajl_strcallback)parseMapKey, //map_key,  
		NULL, //end_map,  
		NULL, //start_array,  
		NULL //end_array  
	};
	hand = yajl_alloc(&callbacks, &cfg,  NULL, (void *) this);
	QByteArray data = json.toUtf8();
	const unsigned char* dataptr = ((const unsigned char*)(const char*)data);
	stat = yajl_parse(hand, dataptr, data.size());
	if(stat == yajl_status_error && stat != yajl_status_client_canceled) {
		unsigned char * str = yajl_get_error(hand, 1, dataptr, data.size());  
		proxy->log(tr("Lucky Google: JSON parse error: %1").arg((const char *) str));  
		yajl_free_error(hand, str);
	}
	stat = yajl_parse_complete(hand);
	if(stat == yajl_status_error && stat != yajl_status_client_canceled) {
		unsigned char * str = yajl_get_error(hand, 1, dataptr, data.size());  
		proxy->log(tr("Lucky Google: JSON parse error: %1").arg((const char *) str));  
		yajl_free_error(hand, str);
	}
	yajl_free(hand);
#else
	proxy->warning("In order to use Lucky Google you have to install yajl before compiling Cuberok");
#endif
	if(foundUrl) {
		return url;
	} else {
		proxy->warning("Lucky Google: Url not found!");
		return "";
	}
}

int Lyric::parseString(Lyric* that, const unsigned char * stringVal, unsigned int stringLen)
{
	//that->proxy->log("parse string");
	if(that->foundUrl) {
		QString link = QString::fromUtf8((const char*)stringVal, stringLen);
		if(link.contains("lyric")) {
			that->url = link;
			return 0;
		} else that->foundUrl = false;
	}

	return 1;
}

int Lyric::parseMapKey(Lyric* that, const unsigned char * stringVal, unsigned int stringLen)
{
	QString key = QString::fromUtf8((const char*)stringVal, stringLen);
	if(key == "unescapedUrl") that->foundUrl = true;
	//that->proxy->log(QString("parse map key: %1").arg(key));
	return 1;
}
