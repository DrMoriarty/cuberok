/* Cuberok
 * Copyright (C) 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef URL_APPEND_H
#define URL_APPEND_H

#include <QtGui>
#include "ui_url_open.h"
#include "downloader.h"

class UrlOpen : public QDialog
{
	Q_OBJECT

 public:
	UrlOpen(QWidget *parent = 0);
	~UrlOpen();

 public slots:
	virtual void accept();

 signals:
	void append(QUrl);

 private slots:
	void dlComplete(QString);
	void dlCancel(QString);
	void dlProgress(int, int);

 private:
    Ui::UrlOpen ui;
	Downloader *dl;
};

#endif // URL_APPEND_H
