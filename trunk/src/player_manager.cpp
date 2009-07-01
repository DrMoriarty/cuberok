/* Cuberok
 * Copyright (C) 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this software; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "player_manager.h"
#include "console.h"

#include <QtGui>

Q_IMPORT_PLUGIN(player_void)

PlayerManager::PlayerManager() : player(0)
{
	foreach (QObject *plugin, QPluginLoader::staticInstances()) {
		Player *pl = qobject_cast<Player *>(plugin);
		if (pl) {
			pl->setManager(this);
			players.push_back(pl);
			connect(players.last(), SIGNAL(position(double)), this, SIGNAL(position(double)));
			connect(players.last(), SIGNAL(finish()), this, SIGNAL(finish()));
			info += pl->name() + "\n";
		}
	}
	QDir pluginsDir = QDir(qApp->applicationDirPath());
#ifndef WIN32
	//pluginsDir.cdUp(); 
	//pluginsDir.cd("./lib/cuberok"); 
	pluginsDir.cd(CUBEROK_PLUGINS);
#else
	pluginsDir.cd("plugins"); 
#endif
	qDebug((const char*)("Plugins dir is "+pluginsDir.canonicalPath()).toLocal8Bit());
	foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
	    qDebug((const char*)("Try to load " + fileName).toLocal8Bit());
		QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
		QObject *plugin = loader.instance();
		if (plugin) {
			Player *pl = qobject_cast<Player *>(plugin);
			if (pl) {
				pl->setManager(this);
				players.push_back(pl);
				connect(players.last(), SIGNAL(position(double)), this, SIGNAL(position(double)));
				connect(players.last(), SIGNAL(finish()), this, SIGNAL(finish()));
				info += pl->name() + "\n";
			}
		} else {
			qDebug((const char*)("Can't load " + fileName).toLocal8Bit());
		}
	} 
}

PlayerManager::~PlayerManager()
{
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
	Console::Self().message("Selected engine: " + player->name());
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

bool PlayerManager::open(QUrl fname, long start, long length)
{
	filename = fname;
	filestart = start;
	filelength = length;
    return player ? player->open(fname, start, length) : false;
}

bool PlayerManager::play()
{
    return player ? player->play() : false;
}

bool PlayerManager::stop()
{
    return player ? player->stop() : false;
}

bool PlayerManager::setPause(bool p)
{
    return player ? player->setPause(p) : false;
}

bool PlayerManager::close()
{
    return player ? player->close() : false;
}

bool PlayerManager::setPosition(double pos)
{
    return player ? player->setPosition(pos) : false;
}

double PlayerManager::getPosition()
{
    return player ? player->getPosition() : 0.0;
}

int  PlayerManager::volume()
{
    return player ? player->volume() : 0;
}

void PlayerManager::setVolume(int v)
{
	foreach(Player *pl, players)
		pl->setVolume(v);
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
	double pos = .0f;
	bool needToContinue = false;
	if(player && player->playing()) {
		needToContinue = true;
		pos = player->getPosition();
	}
	if(player) player->stop();
	foreach(Player *pl, players) 
		if(pl->name() == name && ( pl->ready() || pl->prepare() )) {
			player = pl;
			Console::Self().message("User select engine: " + player->name());
			if(needToContinue) {
				if(!player->open(filename, filestart, filelength) ||
				   !player->play() ||
				   !player->setPosition(pos))
					emit finish();
			}
			return true;
		}
	Console::Self().error(tr("Can't start engine %1").arg(name));
	emit finish();
	return false;
}

QString PlayerManager::getInfo()
{
	return info;
}
