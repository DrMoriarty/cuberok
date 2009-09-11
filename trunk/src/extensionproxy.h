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

#ifndef EXTENSIONPROXY_H
#define EXTENSIONPROXY_H

#include "interfaces.h"
#include "global.h"

#include <QtGui>

class ExtensionProxy : Proxy {
	Q_OBJECT
 public:
	virtual ~ExtensionProxy();
	static ExtensionProxy& Self();
	
	virtual void beginTransaction();
	virtual void endTransaction();
	
	virtual void setControl(SControl control);
	virtual void setStatus(SStatus status);
	virtual void setTags(STags tags);
	virtual void setUrl(QUrl url);
	virtual void setInfo(SInfo info);
	virtual void setRequest(SRequest request);

	virtual SControl getControl();
	virtual SStatus  getStatus();
	virtual SStatus  getPrevStatus();
	virtual STags    getTags();
	virtual QUrl     getUrl();
	virtual SInfo    getInfo();
	virtual SRequest getRequest();

	virtual bool hasVariable(QString varname);
	virtual QString getVariable(QString varname);
	void setVariable(QString varname, QString value);

	virtual void log(QString);
	virtual void message(QString);
	virtual void warning(QString);
	virtual void error(QString);

	const QVector<Extension*>& extensionList();
 protected:
	ExtensionProxy();
	void update(int);

	QVector<Extension*> extensions;
	QMap<QString, QString> variables;
	SControl control;
	SStatus status, prevstatus;
	STags tags;
	QUrl url;
	SInfo info;
	SRequest request;
	bool transaction;
	int transflag;
};

#endif //EXTENSIONPROXY_H
