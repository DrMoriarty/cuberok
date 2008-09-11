/* Cuberok
 * Copyright (C) 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>
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

#include "main.h"
#include "lastfm.h"
#include "playlistsettings.h"
#include <QtGui>

const QString apiKey("e8a336ea701a463d6c83533dfe1310fa");

LastFM::LastFM() : QObject(), httpGetId(0), httpPostId(0), connected(false), needInfo(false)
{
	connect(&http, SIGNAL(requestFinished(int, bool)), this, SLOT(requestFinished(int, bool)));
	connect(&http, SIGNAL(requestStarted(int)), this, SLOT(requestStarted(int)));
}

LastFM::~LastFM()
{
}

LastFM& LastFM::Self()
{
	static LastFM inst;
	return inst;
}

void LastFM::handshake(QString user, QString password)
{
	if(connected) return;
	if(httpPostId) {
		QList<QVariant> item;
		stack << item;
		return;
	}
	if(PLSet.proxyEnabled) {
		http.setProxy(PLSet.proxyHost, PLSet.proxyPort, PLSet.proxyUser, PLSet.proxyPassword);
	}

	uint time = QDateTime::currentDateTime().toTime_t();
	QCryptographicHash cr_p(QCryptographicHash::Md5);
	cr_p.addData(password.toLocal8Bit());
	QCryptographicHash cr(QCryptographicHash::Md5);
	cr.addData((QString(cr_p.result().toHex())+QString::number(time)).toLocal8Bit());
	QString token = QString(cr.result().toHex());

	QUrl url("/?");
	url.addQueryItem("hs", "true");
	url.addQueryItem("p", "1.2.1");
	url.addQueryItem("c", "cub");
	url.addQueryItem("v", CUBEROK_VERSION);
	url.addQueryItem("u", user);
	url.addQueryItem("t", QString::number(time));
	url.addQueryItem("a", token);

	http.setHost("post.audioscrobbler.com", QHttp::ConnectionModeHttp, 80);
	httpGetId = http.get(QString(url.toEncoded()));
}

void LastFM::requestStarted(int id)
{
	//QMessageBox::information(0, "", http.currentRequest().toString());
}

void LastFM::requestFinished(int id, bool err)
{
	if(err) {
		QMessageBox::warning(0, tr("Last.FM"), tr("Request failed: %1.").arg(http.errorString()));
		if(httpGetId == id) httpGetId = 0;
		if(httpPostId == id) httpPostId = 0;
	} else {
		if(httpGetId == id) {
			httpGetId = 0;
			if(needInfo) {
				//QMessageBox::information(0, "Last.FM response", QString(http.lastResponse().toString()/*http.readAll()*/));
				//QMessageBox::information(0, "Last.FM response", http.readAll());
				emit xmlInfo(QString::fromUtf8((const char*)http.readAll()));
				needInfo = false;
			} else {
				QString request = http.readAll();
				QString status = request.section('\n', 0, 0);
				if(status == "OK") {
					session = request.section('\n', 1, 1);
					nowPlayingUrl = request.section('\n', 2, 2);
					submissionUrl = request.section('\n', 3, 3);
					connected = true;
				} else if(status.startsWith("BANNED")) {
					QMessageBox::warning(0, tr("Last.FM"), "I am banned at Last.FM, I am don't need to live any more.");
					connected = false;
				} else if(status.startsWith("BADAUTH")) {
					QMessageBox::warning(0, tr("Last.FM"), "Incorrect user name or password.");
					connected = false;
				} else if(status.startsWith("BADTIME")) {
					QMessageBox::warning(0, tr("Last.FM"), "Incorrect time. The system clock must be corrected.");
					connected = false;
				} else if(status.startsWith("FAILED")) {
					QMessageBox::warning(0, tr("Last.FM"), status);
					connected = false;
				} else {
					connected = false;
				}
			}
		} else if(httpPostId == id) {
			httpPostId = 0;
			QString request = http.readAll();
			if(request.startsWith("OK")) {
				// nothing to do
			} else if(request.startsWith("BADSESSION")) {
				connected = false;
				QMessageBox::warning(0, tr("Last.FM"), "Bad session identifier. Need for reconnect to the server.");
			} else if(request.startsWith("FAILED")) {
				QMessageBox::warning(0, tr("Last.FM"), request);
			} else {
			}
		}
	}
	if(stack.size()) {
		QList<QVariant> &item = *stack.begin();
		if(item.size() == 0) {
			if(!httpGetId) {
				handshake(PLSet.lastfmUser, PLSet.lastfmPassword);
				stack.pop_front();
			}
		} else if(item.size() == 1) {
			if(!httpGetId) {
				artistInfo(item[0].toString());
				stack.pop_front();
			}
		} else if(item.size() == 2) {
			if(!httpGetId) {
				albumInfo(item[0].toString(), item[1].toString());
				stack.pop_front();
			}
		} else if(item.size() == 6) {
			if(!httpPostId) {
				nowplaying(item[0].toString(), item[1].toString(), item[2].toString(), item[3].toInt(), item[4].toInt(), item[5].toString());
				stack.pop_front();
			}
		} else if(item.size() == 9) {
			if(!httpPostId) {
				submission(item[0].toString(), item[1].toString(), item[2].toInt(), item[3].toString(), item[4].toInt(), item[5].toString(), item[6].toString(), item[7].toInt(), item[8].toString());
				stack.pop_front();
			}
		}
	}
}

void LastFM::nowplaying(QString artist, QString title, QString album, int sec, int track, QString mb)
{
	if(!connected || httpPostId) {
		handshake(PLSet.lastfmUser, PLSet.lastfmPassword);
		QList<QVariant> item;
		item << artist;
		item << title;
		item << album;
		item << sec;
		item << track;
		item << mb;
		stack << item;
		return;
	}
	if(PLSet.proxyEnabled) {
		http.setProxy(PLSet.proxyHost, PLSet.proxyPort, PLSet.proxyUser, PLSet.proxyPassword);
	}

	QUrl u(nowPlayingUrl);
	QUrl url("");
	url.addQueryItem("s", session);
	url.addQueryItem("a", artist);
	url.addQueryItem("t", title);
	url.addQueryItem("b", album);
	url.addQueryItem("l", QString::number(sec));
	url.addQueryItem("n", QString::number(track));
	url.addQueryItem("m", mb);
	//QMessageBox::information(0, "", QString(url.toEncoded().remove(0,1)));
	
	QHttp::ConnectionMode mode = u.scheme().toLower() == "https" ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttp;
	http.setHost(u.host(), mode, u.port(80));

	QHttpRequestHeader header(QLatin1String("POST"), QString(u.toEncoded()));
    header.setValue(QLatin1String("Connection"), QLatin1String("Keep-Alive"));
    header.setValue(QLatin1String("Host"), u.host().toLatin1());
	header.setContentLength(url.toString().toUtf8().remove(0,1).size());
	header.setContentType(QLatin1String("application/x-www-form-urlencoded"));

	httpPostId = http.request(header, url.toString().toUtf8().remove(0,1));
}

void LastFM::submission(QString artist, QString title, int time, QString album, int sec, QString src, QString rating, int track, QString mb)
{
	if(sec < 30 || (QDateTime::currentDateTime().toTime_t() - time) < (sec/2)) return;
	if(!connected || httpPostId) {
		handshake(PLSet.lastfmUser, PLSet.lastfmPassword);
		QList<QVariant> item;
		item << artist;
		item << title;
		item << time;
		item << album;
		item << sec;
		item << src;
		item << rating;
		item << track;
		item << mb;
		stack << item;
		return;
	}
	if(PLSet.proxyEnabled) {
		http.setProxy(PLSet.proxyHost, PLSet.proxyPort, PLSet.proxyUser, PLSet.proxyPassword);
	}

	QUrl u(submissionUrl);
	QUrl url("");
	url.addQueryItem("s", session);
	url.addQueryItem("a[0]", artist);
	url.addQueryItem("t[0]", title);
	url.addQueryItem("i[0]", QString::number(time));
	url.addQueryItem("o[0]", src);
	url.addQueryItem("r[0]", rating);
	url.addQueryItem("l[0]", QString::number(sec));
	url.addQueryItem("b[0]", album);
	url.addQueryItem("n[0]", QString::number(track));
	url.addQueryItem("m[0]", mb);
	//QMessageBox::information(0, "", QString(url.toString().toUtf8().remove(0,1)));
	
	QHttp::ConnectionMode mode = u.scheme().toLower() == "https" ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttp;
	http.setHost(u.host(), mode, u.port(80));

	QHttpRequestHeader header(QLatin1String("POST"), QString(u.toEncoded()));
    header.setValue(QLatin1String("Connection"), QLatin1String("Keep-Alive"));
    header.setValue(QLatin1String("Host"), u.host().toLatin1());
	header.setContentLength(url.toString().toUtf8().remove(0,1).size());
	header.setContentType(QLatin1String("application/x-www-form-urlencoded"));

	httpPostId = http.request(header, url.toString().toUtf8().remove(0,1));
}

void LastFM::artistInfo(QString artist)
{
	if(httpGetId) {
		QList<QVariant> item;
		item << artist;
		stack << item;
		return;
	}
	if(PLSet.proxyEnabled) {
		http.setProxy(PLSet.proxyHost, PLSet.proxyPort, PLSet.proxyUser, PLSet.proxyPassword);
	}

	QUrl url("http://ws.audioscrobbler.com/2.0/");
	url.addQueryItem("method", "artist.getinfo");
	url.addQueryItem("artist", artist);
	url.addQueryItem("api_key", apiKey);

	needInfo = true;
	http.setHost(url.host(), QHttp::ConnectionModeHttp, 80);
	httpGetId = http.get(QString(url.toEncoded()));
}

void LastFM::albumInfo(QString artist, QString album)
{
	if(httpGetId) {
		QList<QVariant> item;
		item << artist;
		item << album;
		stack << item;
		return;
	}
	if(PLSet.proxyEnabled) {
		http.setProxy(PLSet.proxyHost, PLSet.proxyPort, PLSet.proxyUser, PLSet.proxyPassword);
	}

	QUrl url("http://ws.audioscrobbler.com/2.0/");
	url.addQueryItem("method", "album.getinfo");
	url.addQueryItem("artist", artist);
	url.addQueryItem("album", album);
	url.addQueryItem("api_key", apiKey);

	needInfo = true;
	http.setHost(url.host(), QHttp::ConnectionModeHttp, 80);
	httpGetId = http.get(QString(url.toEncoded()));
}

