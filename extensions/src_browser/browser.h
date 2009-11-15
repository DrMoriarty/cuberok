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

#ifndef BROWSER_H
#define BROWSER_H

#include <QtCore>
#include "global.h"
#include "interfaces.h"
// abstract class for internet services
class Browser: public QObject
{
	Q_OBJECT
 public:
	Browser(Proxy *pr, QObject *parent = 0):QObject(parent), proxy(pr) {};
	~Browser() {};
	virtual bool tagsAvailable() = 0;
	virtual STags getTags(QStringList) = 0;
	// request a list of vectors
	// first vector item is a title
	// second one is a comment
	// third one is an identifier (input parameter if user select it)
	// fourth one is an URL (if exist)
	virtual void GetList(QString = "", QString = "") = 0;
 signals:
	// send list of vectors to owner
	virtual void list(QList< QStringList >);
 protected:
	Proxy *proxy;
};

#endif // BROWSER_H
