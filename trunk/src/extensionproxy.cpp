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

#include "extensionproxy.h"
ExtensionProxy::ExtensionProxy() : Proxy(), transaction(false), transflag(0)
{
	// TODO loading extensions
}

ExtensionProxy::~ExtensionProxy()
{
}

ExtensionProxy& ExtensionProxy::Self()
{
	static ExtensionProxy instance;
	return instance;
}

void ExtensionProxy::beginTransaction()
{
	if(transaction && transflag) {
		update(transflag);
	}
	transflag = 0;
	transaction = true;
}

void ExtensionProxy::endTransaction()
{
	transaction = false;
	update(transflag);
}

void ExtensionProxy::setControl(SControl c)
{
	control = s;
	if(transaction) transflag |= DisturbOnControl;
	else update(DisturbOnControl);
}

void ExtensionProxy::setStatus(SStatus s)
{
	prevstatus = status;
	status = s;
	if(transaction) transflag |= DisturbOnStatus;
	else update(DisturbOnStatus);
}

void ExtensionProxy::setTags(STags t)
{
	tags = t;
	if(transaction) transflag |= DisturbOnTags;
	else update(DisturbOnTags);
}

void ExtensionProxy::setUrl(QUrl u)
{
	url = u;
	if(transaction) transflag |= DisturbOnUrl;
	else update(DisturbOnUrl);
}

void ExtensionProxy::setInfo(SInfo i)
{
	info = i;
	if(transaction) transflag |= DisturbOnInfo;
	else update(DisturbOnInfo);
}

void ExtensionProxy::setRequest(SRequest r)
{
	request = r;
	if(transaction) transflag |= DisturbOnRequest;
	else update(DisturbOnRequest);
}

SControl ExtensionProxy::getControl()
{
	return control;
}

SStatus  ExtensionProxy::getStatus()
{
	return status;
}

SStatus  ExtensionProxy::getPrevStatus()
{
	return prevstatus;
}

STags    ExtensionProxy::getTags()
{
	return tags;
}

QUrl     ExtensionProxy::getUrl()
{
	return url;
}

SInfo    ExtensionProxy::getInfo()
{
	return info;
}

SRequest ExtensionProxy::getRequest()
{
	return request;
}

bool ExtensionProxy::hasVariable(QString varname)
{
	return variables.contains(varname);
}

QString ExtensionProxy::getVariable(QString varname)
{
	return variables[varname];
}

void ExtensionProxy::setVariable(QString varname, QString value)
{
	values[varname] = value;
}

void ExtensionProxy::update(int flag)
{
	if(flag) {
		foreach(Extension* e, extensions) {
			if(!e->ready()) continue;
			if(e->getDisturbs() & flag) {
				e->update();
			}
		}
	}
}
