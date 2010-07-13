/* Cuberok
 * Copyright (C) 2009 Vasiliy Makarov <drmoriarty.0@gmail.com>
 *
n * This program is free software; you can redistribute it and/or
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

#define EProxy ExtensionProxy::Self()

class ExtensionProxy : public Proxy {
	Q_OBJECT
 public:
	virtual ~ExtensionProxy();
	static ExtensionProxy& Self();
	
	virtual void beginTransaction();
	virtual void endTransaction();
	
	virtual void setControl(const SControl& control);
	virtual void setStatus(const SStatus& status);
	virtual void setTags(const STags& tags);
	virtual void setUrl(const QUrl& url);
	virtual void setInfo(const SInfo& info);
	virtual long setRequest(const SRequest& request);
	virtual void setResponse(long requestId, const SInfo& info);
	virtual void delRequest(long requestId);
	virtual void setPlControl(const SPlControl& plcontrol);

	virtual SControl getControl();
	virtual SStatus  getStatus();
	virtual SStatus  getPrevStatus();
	virtual STags    getTags();
	virtual QUrl     getUrl();
	virtual SInfo    getInfo(int type);
	virtual SRequest getRequest();
	virtual bool     infoExist(int type);
	virtual SPlControl getPlControl();

	virtual bool hasVariable(QString varname);
	virtual QString getVariable(QString varname);
	virtual void setVariable(QString varname, QString value);

	virtual void log(QString);
	virtual void message(QString);
	virtual void warning(QString);
	virtual void error(QString);

	void storeState();

	const QVector<Extension*>& extensionList();
	bool isExtensionEnabled(QString name);
	void enableExtension(QString name, bool en);

 signals:
	void aboutToUpdate(int);

 protected:
	ExtensionProxy();
	void update(int);

	QVector<Extension*> extensions;
	QMap<QString, QString> variables;
	QMap<QString, bool> enabledFlags;
	SControl control;
	SStatus status, prevstatus;
	STags tags;
	QUrl url;
	QMap<int, SInfo> info;
	QVector<SRequest> requests;
	bool transaction;
	int transflag;
	long nextRequest;
	QTimer reqTimer;
	SPlControl plcontrol;

 private slots:
	void requestTimeout();
};

#endif //EXTENSIONPROXY_H
