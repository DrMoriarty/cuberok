/* Cuberok
 * Copyright (C) 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>
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

#include "player_manager.h"
#include "console.h"
#include "main.h"
#include "playlistsettings.h"
#include "extensionproxy.h"

#include <QtGui>

Q_IMPORT_PLUGIN(player_void)
#ifdef Q_OS_MAC
Q_IMPORT_PLUGIN(player_phonon)
#endif

PlayerManager::PlayerManager() : player(0), autoEngine(true), vol(.0f), pos(.0f)
{
	foreach (QObject *plugin, QPluginLoader::staticInstances()) {
		Player *pl = qobject_cast<Player *>(plugin);
		if (pl) {
			pl->setManager(this);
			players.push_back(pl);
			connect(players.last(), SIGNAL(position(double)), this, SLOT(positionSlot(double)));
			connect(players.last(), SIGNAL(finish()), this, SLOT(finishSlot()));
			info += pl->name() + "\n";
		}
	}
	QDir pluginsDir = QDir(qApp->applicationDirPath());
	pluginsDir.cd(CUBEROK_PLUGINS);
	qDebug((const char*)("Plugins dir is "+pluginsDir.canonicalPath()).toLocal8Bit());
	QSettings set;
	foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
		if(!QLibrary::isLibrary(fileName)) continue;
	    qDebug((const char*)("Try to load " + fileName).toLocal8Bit());
		QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
		QObject *plugin = loader.instance();
		if (plugin) {
			Player *pl = qobject_cast<Player *>(plugin);
			if (pl) {
				pl->setManager(this);
				players.push_back(pl);
				connect(players.last(), SIGNAL(position(double)), this, SLOT(positionSlot(double)));
				connect(players.last(), SIGNAL(finish()), this, SLOT(finishSlot()));
				info += pl->name() + "\n";
				/*if(set.contains(pl->name() + "/blackList")) {
					blackLists[pl->name()] = qVariantValue<QStringList>(set.value(pl->name() + "/blackList"));
				} else {
					blackLists[pl->name()] = pl->hardcodedBlacklist();
				}
				if(set.contains(pl->name() + "/whiteList")) {
					whiteLists[pl->name()] = qVariantValue<QStringList>(set.value(pl->name() + "/whiteList"));
				} else {
					whiteLists[pl->name()] = pl->hardcodedList();
				}
				*/
			}
		} else {
			qDebug((const char*)("Can't load " + fileName).toLocal8Bit());
			qDebug((const char*)loader.errorString().toLocal8Bit());
		}
	} 
}

PlayerManager::~PlayerManager()
{
	QSettings set;
	/*foreach(Player *pl, players) {
		set.setValue(pl->name() + "/blackList", blackLists[pl->name()]);
		set.setValue(pl->name() + "/whiteList", whiteLists[pl->name()]);
	}
	*/
	while(players.size()) {
		delete players.last();
		players.pop_back();
	}
}

bool PlayerManager::prepare()
{
	if(player) player->stop();
	int curweight = 0;
	foreach(Player *pl, players) if(pl->weight() > curweight) {
		if(pl->ready() ||  pl->prepare()) {
			curweight = pl->weight();
			player = pl;
		}
	}
	qDebug("Selected engine %s", (const char*)player->name().toLocal8Bit());
	Console::Self().log(tr("Selected engine: %1").arg(player->name()));
	autoEngine = true;
	return player;
}

bool PlayerManager::ready()
{
	return player;
}

PlayerManager &PlayerManager::Self()
{
    static PlayerManager* player = new PlayerManager();
	if(!player->ready()) player->prepare();
    return *player;
}

bool PlayerManager::canOpen(QString mime)
{
	return true;
}

bool PlayerManager::open(QUrl fname, long start, long length)
{
	if(autoEngine) {
		QString mimeString = Tagger::getFileType(fname);
		if(PLSet.mimeMap.contains(mimeString)) {
			QString engName = PLSet.mimeMap[mimeString];
			foreach(Player *pl, players) {
				if( pl->name() == engName && ( pl->ready() || pl->prepare() )) {
					player = pl;
					Console::Self().log(tr("Selected engine: %1").arg(player->name()));
					break;
				}
			}
		} else if(PLSet.defaultPlayer.size()) {
			foreach(Player *pl, players) {
				if( pl->name() == PLSet.defaultPlayer && (pl->ready() || pl->prepare()) ) {
					player = pl;
				}
			}
			Console::Self().log(tr("Selected engine: %1").arg(player->name()));
		} else if(!player->canOpen(mimeString)) {
			int weight = 0;
			foreach(Player *pl, players) {
				if( pl->ready() || pl->prepare() ) {
					if(pl->weight() >= weight && pl->canOpen(mimeString)) {
						player = pl;
						weight = pl->weight();
					}
				}
			}
			Console::Self().log(tr("Selected engine: %1").arg(player->name()));
		}
	}
	filename = fname;
	filestart = start;
	filelength = length;
    return player ? player->open(fname, start, length) : false;
}

bool PlayerManager::play()
{
    bool res = player ? player->play() : false;
	if(res) {
		ExtensionProxy::Self().setStatus(SStatus(SStatus::Playing, .0f, vol));
	}
	return res;
}

bool PlayerManager::stop()
{
    bool res = player ? player->stop() : false;
	if(res) ExtensionProxy::Self().setStatus(SStatus(SStatus::Stopped, .0f, vol));
	return res;
}

bool PlayerManager::setPause(bool p)
{
    bool res = player ? player->setPause(p) : false;
	if(res) ExtensionProxy::Self().setStatus(SStatus(p?SStatus::Paused:SStatus::Playing, pos, vol));
	return res;
}

bool PlayerManager::close()
{
    return player ? player->close() : false;
}

bool PlayerManager::setPosition(double _pos)
{
    bool res = player ? player->setPosition(_pos) : false;
	if(res) {
		pos = _pos;
		ExtensionProxy::Self().setStatus(SStatus(playing()?SStatus::Playing:SStatus::Paused, pos, vol));
	}
	return res;
}

double PlayerManager::getPosition()
{
    return pos = (player ? player->getPosition() : 0.0);
}

int  PlayerManager::volume()
{
    int v = player ? player->volume() : 0;
	vol = .01f * v;
	return v;
}

void PlayerManager::setVolume(int v)
{
	foreach(Player *pl, players)
		pl->setVolume(v);
	vol = .01f * v;
	ExtensionProxy::Self().setStatus(SStatus(playing()?SStatus::Playing:SStatus::Paused, pos, vol));
}

bool PlayerManager::playing()
{
    return player ? player->playing() : false;
}

int PlayerManager::weight()
{
	return 0;
}

QString PlayerManager::name()
{
	return player? player->name() : "no engine";
}

void PlayerManager::processErrorMessage(QString mes)
{
	Console::Self().error(mes);
}

QStringList PlayerManager::getPlayers()
{
	QStringList res;
	foreach(Player *pl, players)
		if(pl->ready() || pl->prepare())
			res << pl->name();
	return res;
}

bool PlayerManager::setPrefferedPlayer(QString name)
{
	if(player && name == player->name()) return true;
	if(!name.size() && autoEngine) return true;
	double pos = .0f;
	bool needToContinue = false;
	if(player && player->playing()) {
		needToContinue = true;
		pos = player->getPosition();
	}
	if(player) player->stop();
	bool res = false;
	if(!name.size()) {
		autoEngine = true;
		int curweight = 0;
		foreach(Player *pl, players) if(pl->weight() > curweight) {
			if(pl->ready() ||  pl->prepare()) {
				curweight = pl->weight();
				player = pl;
				res = true;
			}
		}
	} else {
		autoEngine = false;
		foreach(Player *pl, players) 
			if(pl->name() == name && ( pl->ready() || pl->prepare() )) {
				player = pl;
				res = true;
			}
	}
	if(res) {
		Console::Self().message(tr("%1 engine is selected by user").arg(player->name()));
		if(needToContinue) {
			if(!player->open(filename, filestart, filelength) ||
			   !player->play() ||
			   !player->setPosition(pos))
				finishSlot();
		}
		return true;
	}
	Console::Self().error(tr("Can't start engine %1").arg(name));
	finishSlot();
	return false;
}

QString PlayerManager::getInfo()
{
	return info;
}

void PlayerManager::positionSlot(double _pos)
{
	pos = _pos;
	ExtensionProxy::Self().setStatus(SStatus(SStatus::Playing, pos, vol));
	emit position(pos);
}

void PlayerManager::finishSlot()
{
	ExtensionProxy::Self().setStatus(SStatus(SStatus::Stopped, .0f, vol));
	emit finish();
}

/*QStringList& PlayerManager::blackList(QString playerName)
{
	if(blackLists.contains(playerName)) return blackLists[playerName];
	dummy.clear();
	return dummy;
}

QStringList& PlayerManager::whiteList(QString playerName)
{
	if(whiteLists.contains(playerName)) return whiteLists[playerName];
	dummy.clear();
	return dummy;
}
*/
