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

#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QtCore>
#include <QtNetwork>
#include "interfaces.h"

class Downloader : public QObject
{
	Q_OBJECT
 public:
	Downloader(Proxy *p);
	~Downloader();

	bool download(QUrl, QString file = "");
	bool done();
 
 signals:
	void complete(QString);
	void progress(int, int);
	void cancel(QString);

 private slots:
     void cancelDownload();
     void httpRequestFinished(int requestId, bool error);
     void readResponseHeader(const QHttpResponseHeader &responseHeader);
     void slotAuthenticationRequired(const QString &, quint16, QAuthenticator *);

 private:
	 Proxy *proxy;
     QHttp *http;
     QFile *file;
     int httpGetId, taskID;
     bool httpRequestAborted, finished;
	 void clean();
};

class SyncDownloader : public QThread
{
    Q_OBJECT
 public:
	SyncDownloader ( QUrl, QString*, QObject * parent = 0 );
	~SyncDownloader();
    void run();

 protected:
	QUrl url;
	QString *file;
	QMutex mutex;

 private slots:
	void complete(QString);
	void cancel(QString);
};

class MultyDownloader: public QObject
{
	Q_OBJECT
 public:
	MultyDownloader(Proxy* p = 0);
	~MultyDownloader();
	void download(QUrl url, QString file = "");
	bool done();
	
 signals:
	void complete(QString);

 private:
	Downloader *dn;
	QStringList cache;
	void processCache();

 private slots:
	void dnComplete(QString);
	void dnCancel(QString);
	
};

#endif //DOWNLOADER_H
