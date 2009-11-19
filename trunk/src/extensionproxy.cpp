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
#include "console.h"

Q_IMPORT_PLUGIN(scrobbler_librefm)
Q_IMPORT_PLUGIN(scrobbler_lastfm)
Q_IMPORT_PLUGIN(infowidget)
Q_IMPORT_PLUGIN(src_filebrowser)
Q_IMPORT_PLUGIN(info_lastfm)
Q_IMPORT_PLUGIN(src_browser)
Q_IMPORT_PLUGIN(src_library)
Q_IMPORT_PLUGIN(info_lyric)

ExtensionProxy::ExtensionProxy() : Proxy(), transaction(false), transflag(0)
{
	// loading variables
	QSettings set;
	set.beginGroup("proxy_settings");
	QStringList vars = set.childKeys();
	foreach(QString var, vars)
		variables[var] = set.value(var).toString();
	set.endGroup();

	// loading extensions
	foreach (QObject *plugin, QPluginLoader::staticInstances()) {
		Extension *ex = qobject_cast<Extension *>(plugin);
		if (ex) {
			ex->setProxy(this);
			extensions.push_back(ex);
			bool res = ex->prepare();
			qDebug("Load static extension '%s'", (const char*)ex->getName().toLocal8Bit());
		}
	}

	QDir pluginsDir = QDir(qApp->applicationDirPath());
	pluginsDir.cd(CUBEROK_PLUGINS);
	qDebug((const char*)("Extension dir is "+pluginsDir.canonicalPath()).toLocal8Bit());
	foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
		if(!QLibrary::isLibrary(fileName)) continue;
	    qDebug((const char*)("Try to load extension " + fileName).toLocal8Bit());
		QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
		QObject *plugin = loader.instance();
		if (plugin) {
			Extension *ex = qobject_cast<Extension *>(plugin);
			if (ex) {
				ex->setProxy(this);
				extensions.push_back(ex);
				bool res = ex->prepare();
				qDebug("Load extension %s", (const char*)ex->getName().toLocal8Bit());
			}
		} else {
			qDebug((const char*)("Can't load extension " + fileName).toLocal8Bit());
			qDebug((const char*)loader.errorString().toLocal8Bit());
		}
	} 
}

ExtensionProxy::~ExtensionProxy()
{
	while(extensions.size()) {
		delete extensions.last();
		extensions.pop_back();
	}
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
	control = c;
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
	if(tags.tag0.title != t.tag0.title) info.remove(SInfo::Lyric);
	if(tags.tag0.artist != t.tag0.artist) {
		info.remove(SInfo::ArtistArt);
		info.remove(SInfo::ArtistText);
	}
	if(tags.tag0.album != t.tag0.album) {
		info.remove(SInfo::AlbumArt);
		info.remove(SInfo::AlbumText);
	}
	if(tags.tag0.genre != t.tag0.genre) {
		info.remove(SInfo::GenreArt);
		info.remove(SInfo::GenreText);
	}
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
	info[i.type] = i;
	if(transaction) {
		transflag |= DisturbOnInfo;
		log("Proxy: info in transaction");
	} else {
		log("Proxy: info");
		update(DisturbOnInfo);
	}
}

void ExtensionProxy::setRequest(SRequest r)
{
	request = r;
	if(transaction) {
		transflag |= DisturbOnRequest;
		log("Proxy: request in transaction");
	} else {
		log("Proxy: request");
		update(DisturbOnRequest);
	}
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

SInfo    ExtensionProxy::getInfo(int type)
{
	if(info.contains(type)) return info[type];
	else return SInfo();
}

bool ExtensionProxy::infoExist(int type)
{
	return info.contains(type);
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
	variables[varname] = value;
}

void ExtensionProxy::update(int flag)
{
	if(flag) {
		foreach(Extension* e, extensions) {
			if(!e->ready()) continue;
			if(e->getDisturbs() & flag) {
				e->update(flag);
			}
		}
	}
}

void ExtensionProxy::log(QString s)
{
	Console::Self().log(s);
}

void ExtensionProxy::message(QString s)
{
	Console::Self().message(s);
}

void ExtensionProxy::warning(QString s)
{
	Console::Self().warning(s);
}

void ExtensionProxy::error(QString s)
{
	Console::Self().error(s);
}

const QVector<Extension*>& ExtensionProxy::extensionList()
{
	return extensions;
}

void ExtensionProxy::storeState()
{
	QSettings set;
	foreach(Extension* e, extensions) {
		if(e->ready()) e->storeState();
	}
	set.beginGroup("proxy_settings");
	foreach(QString var, variables.keys()) {
		set.setValue(var, variables[var]);
	}
	set.endGroup();
}
