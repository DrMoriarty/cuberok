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

#include "global.h"
#include "lastfm.h"
#include "lastfm_settings.h"
#include <QtGui>
#include <QtXml>
#include <QtNetwork>

const QString apiKey("e8a336ea701a463d6c83533dfe1310fa");
static QHttp http;

Q_EXPORT_PLUGIN2(scrobbler_lastfm, LastFM) 

LastFM::LastFM() : Extension(), httpGetId(0), httpPostId(0), connected(false), needInfo(false), delayed(false), enabled(false), try_count(0)
{
	connect(&http, SIGNAL(requestFinished(int, bool)), this, SLOT(requestFinished(int, bool)));
	connect(&http, SIGNAL(requestStarted(int)), this, SLOT(requestStarted(int)));
	QFile file(QDir::homePath()+"/.cuberok/queue.lastfm");
	if(!file.exists()) return;
	file.open(QIODevice::ReadOnly);
	QDataStream in(&file);
	in >> stack;
}

LastFM::~LastFM()
{
	QFile file(QDir::homePath()+"/.cuberok/queue.lastfm");
	file.open(QIODevice::WriteOnly);
	QDataStream out(&file);
	out << stack;
}

bool LastFM::prepare()
{
	QSettings set;
	enabled = set.value("lastfmScrobbler", false).toBool();
	lastfmUser = set.value("lastfmUser", "").toString();
	lastfmPassword = set.value("lastfmPassword", "").toString();
	if(enabled) handshake(lastfmUser, lastfmPassword);
	return true;
}

bool LastFM::ready()
{
	return enabled;
}

void LastFM::update(int)
{
	static int starttime = 0;
	static bool listening = false;
	if(listening && proxy->getStatus().playing == SStatus::Stopped) {
		// track finished
		listening = false;
		STags t = proxy->getTags();
		int len = t.tag0.length/75;
		submission(t.tag0.artist, t.tag0.title, starttime, t.tag0.album, len, "P", "", t.tag0.track);
	}
	if(proxy->getStatus().playing == SStatus::Playing && proxy->getStatus().pos == .0f) {
		// track started
		listening = true;
		starttime = QDateTime::currentDateTime().toTime_t();
		STags t = proxy->getTags();
		nowplaying(t.tag0.artist, t.tag0.title, t.tag0.album, t.tag0.length/75, t.tag0.track);
	}
}

QString LastFM::getName()
{
	return tr("Last.FM Scrobbler");
}

QString InfoWidget::getAuthor()
{
	return QString("DrMoriarty");
}

QString InfoWidget::getDescription()
{
	return tr("Last.FM Scrobbler");
}

QWidget* LastFM::getWidget()
{
	return 0;
}

QWidget* LastFM::getSetupWidget()
{
	LastFMSettings *set = new LastFMSettings();
	connect(set, SIGNAL(destroyed(QObject*)), this, SLOT(settingsUpdate(QObject*)));
	return set;
}

int LastFM::getDisturbs()
{
	return DisturbOnStatus;// | DisturbOnTags;
}

void LastFM::handshake(QString user, QString password)
{
	if(connected || delayed) return;
	if(httpPostId) {
		QList<QVariant> item;
		stack << item;
		return;
	}
	if(proxy->hasVariable("proxyEnabled") && proxy->getVariable("proxyEnabled") == "true") {
		http.setProxy(proxy->getVariable("proxyHost"), proxy->getVariable("proxyPort").toInt(), proxy->getVariable("proxyUser"), proxy->getVariable("proxyPassword"));
	}

	try_count ++;
	if(try_count > 3) {
		delayed = true;
		QTimer::singleShot(300000, this, SLOT(timerConnect()));  // 5 minutes before continue
		return;
	}

	uint time = QDateTime::currentDateTime().toTime_t();
	QCryptographicHash cr_p(QCryptographicHash::Md5);
	cr_p.addData(password.toLocal8Bit());
	QCryptographicHash cr(QCryptographicHash::Md5);
	cr.addData((QString(cr_p.result().toHex())+QString::number(time)).toLocal8Bit());
	QString token = QString(cr.result().toHex());

	QUrl url("http://post.audioscrobbler.com/?");
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
	proxy->log("Last.FM: Request started " + http.currentRequest().toString());
}

void LastFM::requestFinished(int id, bool err)
{
	if(err) {
		proxy->error(QString("Last.FM: Request failed: %1.").arg(http.errorString()));
		if(httpGetId == id) httpGetId = 0;
		if(httpPostId == id) httpPostId = 0;
	} else {
		if(httpGetId == id) {
			httpGetId = 0;
			if(needInfo) {
				QByteArray arr = http.readAll();
				proxy->log("Last.FM response:" + QString::fromUtf8(arr));
				emit xmlInfo(QString::fromUtf8((const char*)arr));
				needInfo = false;
			} else {
				QString request = http.readAll();
				QString status = request.section('\n', 0, 0);
				if(status == "OK") {
					session = request.section('\n', 1, 1);
					nowPlayingUrl = request.section('\n', 2, 2);
					submissionUrl = request.section('\n', 3, 3);
					connected = true;

					proxy->log("Last.FM: handshake complete");
				} else if(status.startsWith("BANNED")) {
					proxy->error("Last.FM: I was banned at Last.FM, I don't need to live any more.");
					connected = false;
				} else if(status.startsWith("BADAUTH")) {
					proxy->error("Last.FM: Incorrect user name or password.");
					connected = false;
				} else if(status.startsWith("BADTIME")) {
					proxy->error("Last.FM: Incorrect time. The system clock must be corrected.");
					connected = false;
				} else if(status.startsWith("FAILED")) {
					proxy->error("Last.FM: " + status);
					connected = false;
				} else {
					connected = false;
					proxy->warning("Last.FM: Unknown response:  " + status);
				}
			}
		} else if(httpPostId == id) {
			httpPostId = 0;
			QString request = http.readAll();
			if(request.startsWith("OK")) {
				// nothing to do
			} else if(request.startsWith("BADSESSION")) {
				connected = false;
				proxy->error("Last.FM: Bad session identifier. Need for reconnect to the server.");
			} else if(request.startsWith("FAILED")) {
				proxy->error("Last.FM: " + request);
			} else {
				proxy->warning("Last.FM: Unknown response:  " + request);
			}
		}
	}
	doQueue();
}

void LastFM::doQueue()
{
	if(stack.size() && !httpGetId && !httpPostId) {
		QList<QVariant> &item = *stack.begin();
		if(item.size() == 0) {
			handshake(lastfmUser, lastfmPassword);
			stack.pop_front();
		} else if(item.size() == 1) {
			//artistInfo(item[0].toString());
			//stack.pop_front();
		} else if(item.size() == 2) {
			//albumInfo(item[0].toString(), item[1].toString());
			//stack.pop_front();
		} else if(item.size() == 6) {
			nowplaying(item[0].toString(), item[1].toString(), item[2].toString(), item[3].toInt(), item[4].toInt(), item[5].toString());
			stack.pop_front();
		} else if(item.size() == 9) {
			submission(item[0].toString(), item[1].toString(), item[2].toInt(), item[3].toString(), item[4].toInt(), item[5].toString(), item[6].toString(), item[7].toInt(), item[8].toString());
			stack.pop_front();
		}
	}
}

void LastFM::nowplaying(QString artist, QString title, QString album, int sec, int track, QString mb)
{
	if(!connected || httpPostId) {
		handshake(lastfmUser, lastfmPassword);
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
	if(proxy->hasVariable("proxyEnabled") && proxy->getVariable("proxyEnabled") == "true") {
		http.setProxy(proxy->getVariable("proxyHost"), proxy->getVariable("proxyPort").toInt(), proxy->getVariable("proxyUser"), proxy->getVariable("proxyPassword"));
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
		handshake(lastfmUser, lastfmPassword);
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
	if(proxy->hasVariable("proxyEnabled") && proxy->getVariable("proxyEnabled") == "true") {
		http.setProxy(proxy->getVariable("proxyHost"), proxy->getVariable("proxyPort").toInt(), proxy->getVariable("proxyUser"), proxy->getVariable("proxyPassword"));
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
	
	QHttp::ConnectionMode mode = u.scheme().toLower() == "https" ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttp;
	http.setHost(u.host(), mode, u.port(80));

	QHttpRequestHeader header(QLatin1String("POST"), QString(u.toEncoded()));
    header.setValue(QLatin1String("Connection"), QLatin1String("Keep-Alive"));
    header.setValue(QLatin1String("Host"), u.host().toLatin1());
	header.setContentLength(url.toString().toUtf8().remove(0,1).size());
	header.setContentType(QLatin1String("application/x-www-form-urlencoded"));

	httpPostId = http.request(header, url.toString().toUtf8().remove(0,1));
}

void LastFM::timerConnect()
{
	delayed = false;
	try_count = 0;
	handshake(lastfmUser, lastfmPassword);
}

void LastFM::settingsUpdate(QObject* o)
{
	o->disconnect();
	QSettings set;
	bool newEnabled = set.value("lastfmScrobbler", false).toBool();
	QString newLastfmUser = set.value("lastfmUser", "").toString();
	QString newLastfmPassword = set.value("lastfmPassword", "").toString();
	if(newEnabled != enabled || newLastfmPassword != lastfmPassword || newLastfmUser != lastfmUser) {
		enabled = newEnabled;
		lastfmUser = newLastfmUser;
		lastfmPassword = newLastfmPassword;
		if(enabled) handshake(lastfmUser, lastfmPassword);
		else connected = false;
	}
}
