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
Q_IMPORT_PLUGIN(src_collection)
Q_IMPORT_PLUGIN(scrobbler_psi)

ExtensionProxy::ExtensionProxy() : Proxy(), transaction(false), transflag(0)
, nextRequest(1)
{
	// loading variables
	QSettings set;
	set.beginGroup("proxy_settings");
	QStringList vars = set.childKeys();
	foreach(QString var, vars)
		variables[var] = set.value(var).toString();
	set.endGroup();

	set.beginGroup("extensions");
	// loading extensions
	foreach (QObject *plugin, QPluginLoader::staticInstances()) {
		Extension *ex = qobject_cast<Extension *>(plugin);
		if (ex) {
			qDebug("Loading static extension '%s'", (const char*)ex->getName().toLocal8Bit());
			ex->setProxy(this);
			bool res = ex->prepare();
			if(res) {
				qDebug("... successfully");
				extensions.push_back(ex);
				enabledFlags[ex->getName()] = set.value(ex->getName(), true).toBool();
			} else {
				qDebug("... error");
			}
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
				enabledFlags[ex->getName()] = set.value(ex->getName(), true).toBool();
			}
		} else {
			qDebug((const char*)("Can't load extension " + fileName).toLocal8Bit());
			qDebug((const char*)loader.errorString().toLocal8Bit());
		}
	}
	set.endGroup();
	connect(&reqTimer, SIGNAL(timeout()), this, SLOT(requestTimeout()));
	reqTimer.start(1000);
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

void ExtensionProxy::setControl(const SControl& c)
{
	control = c;
	if(transaction) transflag |= DisturbOnControl;
	else update(DisturbOnControl);
}

void ExtensionProxy::setStatus(const SStatus& s)
{
	prevstatus = status;
	status = s;
	if(transaction) transflag |= DisturbOnStatus;
	else update(DisturbOnStatus);
}

void ExtensionProxy::setTags(const STags& t)
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

void ExtensionProxy::setUrl(const QUrl& u)
{
	url = u;
	if(transaction) transflag |= DisturbOnUrl;
	else update(DisturbOnUrl);
}

void ExtensionProxy::setInfo(const SInfo& i)
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

long ExtensionProxy::setRequest(const SRequest& r)
{
	requests.push_front(r);
	requests.first().id = nextRequest++;
	if(transaction) {
		transflag |= DisturbOnRequest;
		log("Proxy: request in transaction");
	} else {
		log("Proxy: request");
		update(DisturbOnRequest);
	}
	return requests.first().id;
}

void ExtensionProxy::setResponse(long requestId, const SInfo& info)
{
	for(int i=0; i<requests.size(); i++) {
		if(requests[i].id == requestId) {
			SRequest r = requests[i];
			requests.remove(i);
			if(!r.info.text.size()) r.info.text = info.text;
			if(!r.info.url.size()) r.info.url = info.url;
			requests.push_front(r);
			if(transaction) {
				transflag |= DisturbOnRequest;
			} else {
				update(DisturbOnRequest);
			}
			return;
		}
	}
}

void ExtensionProxy::delRequest(long requestId)
{
	for(int i=0; i<requests.size(); i++) {
		if(requests[i].id == requestId) {
			requests.remove(i);
			qDebug("remove request %ld\n", requestId);
			return;
		}
	}
	qDebug("not found request %ld\n", requestId);
}

void ExtensionProxy::setPlControl(const SPlControl& plcontrol)
{
	this->plcontrol = plcontrol;
	if(transaction) transflag |= DisturbOnPlControl;
	else update(DisturbOnPlControl);
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

SPlControl ExtensionProxy::getPlControl()
{
	return plcontrol;
}


SRequest ExtensionProxy::getRequest()
{
	if(requests.size())
		return requests.first();
	else return SRequest();
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
	update(DisturbOnChangeSettings);
}

void ExtensionProxy::delVariable(QString varname)
{
	if(variables.find(varname) != variables.end())
		variables.erase(variables.find(varname));
}

void ExtensionProxy::update(int flag)
{
	emit aboutToUpdate(flag);
	if(flag) {
		foreach(Extension* e, extensions) {
			if(!e->ready() || !isExtensionEnabled(e->getName())) continue;
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
	set.beginGroup("extensions");
	foreach(QString key, enabledFlags.keys()) {
		set.setValue(key, enabledFlags[key]);
	}
	set.endGroup();
}

void ExtensionProxy::requestTimeout()
{
	for(QVector<SRequest>::iterator r = requests.begin(); r != requests.end(); r ++) {
		if(r->elapsed() > 10000) {
			SRequest r2 = *r;
			requests.erase(r);
			requests.push_front(r2);
			// say 'good bye'
			update(DisturbOnRequest);
			if(requests.size() && r2.id == requests.front(). id)
				requests.pop_front();
			// drop one request per second
			qDebug("drop request");
			return;
		}
	}
}

bool ExtensionProxy::isExtensionEnabled(QString name)
{
	return enabledFlags.contains(name) && enabledFlags[name];
}

void ExtensionProxy::enableExtension(QString name, bool en)
{
	enabledFlags[name] = en;
}
