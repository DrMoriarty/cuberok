/* Cuberok
 * Copyright (C) 2009 Vasiliy Makarov <drmoriarty.0@gmail.com>
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

#ifndef LIBRARYFILLER_H
#define LIBRARYFILLER_H

#include <QtCore>

class LibraryFiller : public QThread
{
	Q_OBJECT
public:
	LibraryFiller(QList<QUrl> _urls, QString _attrname=QString(""), int _param=0, QObject * parent = 0);
	~LibraryFiller();
	void run();
private:
	QList<QUrl> urls;
	QString attrname;
	int  proceed(QString);
	bool cancel;
	int param;
private slots:
	void cancelEvent();
signals:
	void internalUpdate();

};

#endif //LIBRARYFILLER_H
