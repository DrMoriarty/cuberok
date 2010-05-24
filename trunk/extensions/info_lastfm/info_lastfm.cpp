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

#include "info_lastfm.h"
#include <QtGui>
#include <QtXml>
#include <QtNetwork>

const QString apiKey("e8a336ea701a463d6c83533dfe1310fa");
static QHttp http;

Q_EXPORT_PLUGIN2(info_lastfm, InfoLastFM) 

InfoLastFM::InfoLastFM() : Extension(), httpGetId(0), httpPostId(0), needInfo(false), requestId(-1)
{
	connect(&http, SIGNAL(requestFinished(int, bool)), this, SLOT(requestFinished(int, bool)));
	connect(&http, SIGNAL(requestStarted(int)), this, SLOT(requestStarted(int)));
}

InfoLastFM::~InfoLastFM()
{
}

bool InfoLastFM::prepare()
{
	return true;
}

bool InfoLastFM::ready()
{
	return proxy;
}

void InfoLastFM::update(int f)
{
	if(f & DisturbOnRequest) {
		SRequest r = proxy->getRequest();
		STags &t = r.tags;
		switch(r.info.type) {
		case SInfo::ArtistArt:
			if(r.info.url.size()) break;
			artistInfo(t.tag0.artist, r.id, r.info.type);
			break;
		case SInfo::ArtistText:
			if(r.info.text.size()) break;
			artistInfo(t.tag0.artist, r.id, r.info.type);
			break;
		case SInfo::AlbumArt:
			if(r.info.url.size()) break;
			albumInfo(t.tag0.artist, t.tag0.album, r.id, r.info.type);
			break;
		case SInfo::AlbumText:
			if(r.info.text.size()) break;
			albumInfo(t.tag0.artist, t.tag0.album, r.id, r.info.type);
			break;
		default:
			break;
		}
	}
}

QString InfoLastFM::getName()
{
	return tr("Last.FM Info");
}

QString InfoLastFM::getAuthor()
{
	return QString("DrMoriarty");
}

QString InfoLastFM::getDescription()
{
	return tr("This extension tries to load information about your music from Last.FM");
}

QWidget* InfoLastFM::getWidget()
{
	return 0;
}

ExtensionSetupWidget* InfoLastFM::getSetupWidget()
{
	return 0;
}

int InfoLastFM::getDisturbs()
{
	return DisturbOnRequest;
}

void InfoLastFM::requestStarted(int id)
{
	proxy->log("Last.FM info: Request started " + http.currentRequest().toString());
}

void InfoLastFM::requestFinished(int id, bool err)
{
	if(err) {
		proxy->error(QString("Last.FM info: Request failed: %1.").arg(http.errorString()));
		if(httpGetId == id) httpGetId = 0;
		if(httpPostId == id) httpPostId = 0;
	} else {
		if(httpGetId == id) {
			httpGetId = 0;
			if(needInfo) {
				QByteArray arr = http.readAll();
				QString text = QString::fromUtf8((const char*)arr);
				proxy->log("Last.FM info response:" + text);
				QString artist, album, mbid, imageUrl, info;
				parseInfo(text, artist, album, mbid, imageUrl, info);
				if(album.size()) { // album found
					if(imageUrl.size() && infoType == SInfo::AlbumArt)
						proxy->setResponse(requestId, SInfo(SInfo::AlbumArt, "", imageUrl));
					if(info.size() && infoType == SInfo::AlbumText)
						proxy->setResponse(requestId, SInfo(SInfo::AlbumText, info, ""));
				} else if(artist.size()) { // artist found
					if(imageUrl.size() && infoType == SInfo::ArtistArt)
						proxy->setResponse(requestId, SInfo(SInfo::ArtistArt, "", imageUrl));
					if(info.size() && infoType == SInfo::ArtistText)
						proxy->setResponse(requestId, SInfo(SInfo::ArtistText, info, ""));
				}
				//emit xmlInfo(QString::fromUtf8((const char*)arr));
				needInfo = false;
			} else {
			}
		} else if(httpPostId == id) {
			httpPostId = 0;
			QString request = http.readAll();
			if(request.startsWith("OK")) {
				// nothing to do
			} else {
				proxy->warning("Last.FM info: Unknown response:  " + request);
			}
		}
	}
	doQueue();
}

void InfoLastFM::doQueue()
{
	if(stack.size() && !httpGetId && !httpPostId) {
		QList<QVariant> &item = *stack.begin();
		if(item.size() == 0) {
			//handshake(PLSet.lastfmUser, PLSet.lastfmPassword);
			stack.pop_front();
		} else if(item.size() == 3) {
			artistInfo(item[0].toString(), item[1].toLongLong(), item[2].toInt());
			stack.pop_front();
		} else if(item.size() == 4) {
			albumInfo(item[0].toString(), item[1].toString(), item[2].toLongLong(), item[3].toInt());
			stack.pop_front();
		} else if(item.size() == 6) {
			//nowplaying(item[0].toString(), item[1].toString(), item[2].toString(), item[3].toInt(), item[4].toInt(), item[5].toString());
			stack.pop_front();
		} else if(item.size() == 9) {
			//submission(item[0].toString(), item[1].toString(), item[2].toInt(), item[3].toString(), item[4].toInt(), item[5].toString(), item[6].toString(), item[7].toInt(), item[8].toString());
			stack.pop_front();
		} else stack.pop_front();
	}
}

void InfoLastFM::artistInfo(QString artist, long reqId, int itype)
{
	if(httpGetId) {
		QList<QVariant> item;
		item << artist;
		item << (long long int)reqId;
		item << itype;
		stack << item;
		return;
	}
	requestId = reqId;
	infoType = itype;
	if(proxy->hasVariable("proxyEnabled") && proxy->getVariable("proxyEnabled") == "true") {
		http.setProxy(proxy->getVariable("proxyHost"),
					  proxy->getVariable("proxyPort").toInt(),
					  proxy->getVariable("proxyUser"),
					  proxy->getVariable("proxyPassword"));
	}

	QUrl url("http://ws.audioscrobbler.com/2.0/");
	url.addQueryItem("method", "artist.getinfo");
	url.addQueryItem("artist", artist);
	url.addQueryItem("api_key", apiKey);
	if(proxy->hasVariable("lang")) {
		url.addQueryItem("lang", proxy->getVariable("lang"));
	}

	needInfo = true;
	http.setHost(url.host(), QHttp::ConnectionModeHttp, 80);
	httpGetId = http.get(QString(url.toEncoded()));
}

void InfoLastFM::albumInfo(QString artist, QString album, long reqId, int itype)
{
	if(httpGetId) {
		QList<QVariant> item;
		item << artist;
		item << album;
		item << (long long int)reqId;
		item << itype;
		stack << item;
		return;
	}
	requestId = reqId;
	infoType = itype;
	if(proxy->hasVariable("proxyEnabled") && proxy->getVariable("proxyEnabled") == "true") {
		http.setProxy(proxy->getVariable("proxyHost"),
					  proxy->getVariable("proxyPort").toInt(),
					  proxy->getVariable("proxyUser"),
					  proxy->getVariable("proxyPassword"));
	}

	QUrl url("http://ws.audioscrobbler.com/2.0/");
	url.addQueryItem("method", "album.getinfo");
	url.addQueryItem("artist", artist);
	url.addQueryItem("album", album);
	url.addQueryItem("api_key", apiKey);
	if(proxy->hasVariable("lang")) {
		url.addQueryItem("lang", proxy->getVariable("lang"));
	}

	needInfo = true;
	http.setHost(url.host(), QHttp::ConnectionModeHttp, 80);
	httpGetId = http.get(QString(url.toEncoded()));
}

void InfoLastFM::timerConnect()
{
}

bool InfoLastFM::parseInfo(const QString& xml, QString& artist, QString& album, QString& mbid, QString& imageUrl, QString& info)
{
	QDomDocument doc;
	QDomElement el, el2;
	QDomNodeList list;
	if(doc.setContent(xml)) {
		el = doc.documentElement();
		//el = el.firstChildElement("lfm");
		if(!el.isNull()) {
			QString s = el.attribute("status");
			if(s == "ok") {
				el2 = el.firstChildElement("artist");
				if(!el2.isNull()) {  // proceed artist info
					QString img1, img2, img3, img4;
					el = el2;
					el2 = el.firstChildElement("name");
					if(!el2.isNull()) artist = el2.firstChild().nodeValue();
					el2 = el.firstChildElement("mbid");
					if(!el2.isNull()) mbid = el2.firstChild().nodeValue();
					el2 = el.firstChildElement("image");
					while(!el2.isNull()) {
						if(el2.attribute("size") == "small") img1 = el2.firstChild().nodeValue();
						if(el2.attribute("size") == "medium") img2 = el2.firstChild().nodeValue();
						if(el2.attribute("size") == "large") img3 = el2.firstChild().nodeValue();
						if(el2.attribute("size") == "extralarge") img4 = el2.firstChild().nodeValue();
						el2 = el2.nextSiblingElement("image");
					}
					el2 = el.firstChildElement("bio");
					if(!el2.isNull()) {
						el2 = el2.firstChildElement("content");
						if(!el2.isNull()) {
							info = el2.firstChild().nodeValue();
							if(info.size()) {
								info = "<html><body>" + info + "</html></body>";
							}
						}
					}
					if(!img2.size()) img2 = img1;
					if(!img3.size()) img3 = img2;
					if(!img4.size()) img4 = img3;
					if(img4.size())
						proxy->log("Image URL" + img4);
					else
						proxy->log("There isn't any images");
					imageUrl = img4;
					return true;
				} else {
					el2 = el.firstChildElement("album");
					if(!el2.isNull()) {  // proceed album info
						QString img1, img2, img3, img4;
						el = el2;
						el2 = el.firstChildElement("name");
						if(!el2.isNull()) album = el2.firstChild().nodeValue();
						el2 = el.firstChildElement("artist");
						if(!el2.isNull()) artist = el2.firstChild().nodeValue();
						el2 = el.firstChildElement("mbid");
						if(!el2.isNull()) mbid = el2.firstChild().nodeValue();
						el2 = el.firstChildElement("image");
						while(!el2.isNull()) {
							if(el2.attribute("size") == "small") img1 = el2.firstChild().nodeValue();
							if(el2.attribute("size") == "medium") img2 = el2.firstChild().nodeValue();
							if(el2.attribute("size") == "large") img3 = el2.firstChild().nodeValue();
							if(el2.attribute("size") == "extralarge") img4 = el2.firstChild().nodeValue();
							el2 = el2.nextSiblingElement("image");
						}
						el2 = el.firstChildElement("wiki");
						if(!el2.isNull()) {
							el2 = el2.firstChildElement("content");
							if(!el2.isNull()) {
								QString info = el2.firstChild().nodeValue();
								if(info.size()) {
									info = "<html><body>" + info + "</html></body>";
								}
							}
						}
						if(!img2.size()) img2 = img1;
						if(!img3.size()) img3 = img2;
						if(!img4.size()) img4 = img3;
						if(img4.size())
							proxy->log("Image URL" + img4);
						else
							proxy->log("There isn't any images");
						imageUrl = img4;
						return true;
					} else {
						// something else
					}
				}
			} else if(s == "failed") {
				// TODO error message
				proxy->error("Can't take info from Last.FM");
			} else {
				// unknown error
				proxy->error("Last.FM info: Unknown error");
			}
		} else {
			proxy->error("Last.FM info: Element lfm not found");
		}
	} else {
		proxy->error("Last.FM info: XML error");
	}
	return false;
}
