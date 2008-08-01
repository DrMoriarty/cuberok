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

#include "player.h"

#ifdef AUDIERE
#include "player_audiere.h"
#endif

#ifdef GSTREAMER
#include "player_gst.h"
#endif

#include "player_void.h"

#include <QtGui>

PlayerManager::PlayerManager() : player(0)
{
#ifdef AUDIERE
	players.push_back(new PlayerAudiere());
	connect(players.last(), SIGNAL(position(double)), this, SIGNAL(position(double)));
	connect(players.last(), SIGNAL(finish()), this, SIGNAL(finish()));
#endif
#ifdef GSTREAMER
	players.push_back(new PlayerGst());
	connect(players.last(), SIGNAL(position(double)), this, SIGNAL(position(double)));
	connect(players.last(), SIGNAL(finish()), this, SIGNAL(finish()));
#endif
	players.push_back(new PlayerVoid());
	connect(players.last(), SIGNAL(position(double)), this, SIGNAL(position(double)));
	connect(players.last(), SIGNAL(finish()), this, SIGNAL(finish()));
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
	//QMessageBox::information(0, "Selected engine", player->name());
	qDebug("Selected engine %s", (const char*)player->name().toLocal8Bit());
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

bool PlayerManager::open(QUrl fname)
{
    return player ? player->open(fname) : false;
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
	if(player) player->stop();
	foreach(Player *pl, players) 
		if(pl->name() == name && ( pl->ready() || pl->prepare() )) {
			player = pl;
			return true;
		}
	QMessageBox::warning(0, tr("Error"), tr("Can't start engine %1").arg(name));
	return false;
}
