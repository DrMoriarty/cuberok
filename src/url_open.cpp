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

#include "url_open.h"
#include "console.h"

UrlOpen::UrlOpen(QWidget *parent): QDialog(parent)
{
	ui.setupUi(this);
	dl = 0;
}

UrlOpen::~UrlOpen()
{
	if(dl) delete dl;
}

void UrlOpen::accept()
{
	if(dl) return;
	QUrl url(ui.lineEdit->text());
	if(url.scheme().toLower() == "file") {
		emit append(url);
		QDialog::accept();
	} else {
		dl = new Downloader();
		connect(dl, SIGNAL(complete(QString)), this, SLOT(dlComplete(QString)));
		connect(dl, SIGNAL(cancel(QString)), this, SLOT(dlCancel(QString)));
		connect(dl, SIGNAL(progress(int, int)), this, SLOT(dlProgress(int, int)));
		if(!dl->download(url)) {
			delete dl;
			QDialog::reject();
		}
	}
}

void UrlOpen::dlComplete(QString file)
{
	emit append(QUrl::fromLocalFile(file));
	QDialog::accept();
}

void UrlOpen::dlCancel(QString err)
{
	Console::Self().warning("Cancel: " + err);
	QDialog::reject();
}

void UrlOpen::dlProgress(int a, int b)
{
	ui.label->setText(tr("Downloading... %1/%2 bytes.").arg(QString::number(a), QString::number(b)));
}
