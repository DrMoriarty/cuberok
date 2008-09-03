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


#include <QtGui>

#include "downloader.h"
#include "ui_authenticationdialog.h"
#include "indicator.h"

Downloader::Downloader(): QObject(), httpGetId(0), taskID(0), httpRequestAborted(false), finished(false)
{
	http = new QHttp(this);
	
	connect(http, SIGNAL(requestFinished(int, bool)),
			this, SLOT(httpRequestFinished(int, bool)));
	connect(http, SIGNAL(dataReadProgress(int, int)), this, SIGNAL(process(int, int)));
	connect(http, SIGNAL(responseHeaderReceived(const QHttpResponseHeader &)),
			this, SLOT(readResponseHeader(const QHttpResponseHeader &)));
	connect(http, SIGNAL(authenticationRequired(const QString &, quint16, QAuthenticator *)),
			this, SLOT(slotAuthenticationRequired(const QString &, quint16, QAuthenticator *)));
	connect(&Indicator::Self(), SIGNAL(userStop()), this, SLOT(cancelDownload()));
	connect(http, SIGNAL(dataReadProgress(int, int)), &Indicator::Self(), SIGNAL(update()));
}

Downloader::~Downloader()
{
	delete http;
	disconnect(&Indicator::Self(), SIGNAL(userStop()), this, SLOT(cancelDownload()));
}

bool Downloader::download(QUrl url)
{
	QFileInfo fileInfo(url.path());
	QString fileName = fileInfo.fileName();
	if (fileName.isEmpty())
		fileName = "index.html";

	QString tmpath = QDir::homePath()+"/.cuberok/tmp/";
	QDir dir;
	dir.mkpath(tmpath);
	if (QFile::exists(tmpath+fileName)) {
		QFile::remove(tmpath+fileName);
	}
	
	file = new QFile(tmpath+fileName);
	if (!file->open(QIODevice::WriteOnly)) {
		QMessageBox::warning(0, tr("Error"),
                                  tr("Unable to save the file %1: %2.")
                                  .arg(tmpath+fileName).arg(file->errorString()));
		delete file;
		file = 0;
		return false;
	}
	
	QHttp::ConnectionMode mode = url.scheme().toLower() == "https" ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttp;
	http->setHost(url.host(), mode, url.port() == -1 ? 0 : url.port());
	
	if (!url.userName().isEmpty())
		http->setUser(url.userName(), url.password());
	
	httpRequestAborted = false;
	httpGetId = http->get(url.path(), file);
	
	taskID = Indicator::Self().addTask(tr("Download file %1").arg(url.toString()));

	return true;
	// sleep
// 	while(!finished && !httpRequestAborted) {
// 		QThread::currentThread()->wait(1000);
// 		Indicator::Self().update();
// 	}
// 	Indicator::Self().delTask(taskID);

// 	if(finished)
// 		return tmpath+fileName;
// 	else 
// 		return "";
}

bool Downloader::done()
{
	return finished || httpRequestAborted;
}

void Downloader::cancelDownload()
{
	httpRequestAborted = true;
	http->abort();
	emit cancel("Operation canceled by user");
}

void Downloader::httpRequestFinished(int requestId, bool error)
{
	if (requestId != httpGetId)
		return;
	if (httpRequestAborted) {
		if (file) {
			file->close();
			file->remove();
			delete file;
			file = 0;
		}
		return;
	}
	
	file->close();
	
	if (error) {
		file->remove();
		QMessageBox::warning(0, tr("Error"),
								 tr("Download failed: %1.")
								 .arg(http->errorString()));
		httpRequestAborted = true;
		emit cancel(tr("Download failed: %1.").arg(http->errorString()));
	} else {
		finished = true;
		emit complete(file->fileName());
	}
	Indicator::Self().delTask(taskID);
	
	delete file;
	file = 0;
}

void Downloader::readResponseHeader(const QHttpResponseHeader &responseHeader)
{
	if (responseHeader.statusCode() != 200) {
		QMessageBox::warning(0, tr("Error"),
							 tr("Download failed: %1.")
							 .arg(responseHeader.reasonPhrase()));
		httpRequestAborted = true;
		http->abort();
		emit cancel(tr("Download failed: %1.").arg(responseHeader.reasonPhrase()));
		return;
	}
}

void Downloader::slotAuthenticationRequired(const QString &hostName, quint16, QAuthenticator *authenticator)
{
	QDialog dlg;
	Ui::Dialog ui;
	ui.setupUi(&dlg);
	dlg.adjustSize();
	ui.siteDescription->setText(tr("%1 at %2").arg(authenticator->realm()).arg(hostName));
	
	if (dlg.exec() == QDialog::Accepted) {
		authenticator->setUser(ui.userEdit->text());
		authenticator->setPassword(ui.passwordEdit->text());
	}
} 

SyncDownloader::SyncDownloader ( QUrl u, QString* f, QObject * parent ) : QThread(parent)
{
	url = u;
	file = f;
}

SyncDownloader::~SyncDownloader()
{
}

void SyncDownloader::run()
{
	mutex.lock();
	Downloader dl;
	connect(&dl, SIGNAL(complete(QString)), this, SLOT(complete(QString)));
	connect(&dl, SIGNAL(cancel(QString)), this, SLOT(cancel(QString)));
	if(!dl.download(url)) {
		*file = "";
		return;
	}
	mutex.lock();
}

void SyncDownloader::complete(QString f)
{
	*file = f;
	mutex.unlock();
}

void SyncDownloader::cancel(QString err)
{
	*file = "";
	mutex.unlock();
}

