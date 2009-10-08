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

#ifndef BROWSER_VIEWER_H
#define BROWSER_VIEWER_H

#include <QtGui>
#include "browser.h"
#include "downloader.h"

class BrowserList: public QListWidget
{
	Q_OBJECT
 public:
	BrowserList(QWidget* parent = 0);
 protected:
	virtual QStringList mimeTypes () const;
	virtual QMimeData * mimeData ( const QList<QListWidgetItem *> items ) const;
};

#include "ui_browser_viewer.h"

class BrowserViewer: public QWidget
{
	Q_OBJECT
 public:
	BrowserViewer( QWidget * parent = 0, Qt::WindowFlags f = 0 );
	~BrowserViewer();
	void storeState();
 public slots:
	void browserChanged(int);
	void back();
	//void forward();
	void home();
	void reload();
 signals:
	//void openUrl(QUrl);
 private:
    Ui::BrowserViewer ui;
	Browser *browser;
	QStringList history;
	QString current;
	//Downloader *dl;
	QStringList pathItems;

	void goTo(QString s);
	void updatePath();
 private slots:
	void putList(QList< QStringList >);
	void itemActivated(QListWidgetItem*);
	//void dlComplete(QString);
	//void dlCancel(QString);
};

#endif // BROWSER_VIEWER_H
