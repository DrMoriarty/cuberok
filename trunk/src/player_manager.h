/* Cuberok
 * Copyright (C) 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

#include "player.h"

class PlayerManager : public Player
{
    Q_OBJECT
 public:
    ~PlayerManager();
    static PlayerManager& Self();

	virtual bool prepare();
	virtual bool ready();

	virtual bool canOpen(QString mime);
    virtual bool open(QUrl fname, long start = 0, long length = 0);
    virtual bool play();
    virtual bool stop();
    virtual bool setPause(bool p);
    virtual bool close();
    virtual bool setPosition(double pos);
    virtual double getPosition();
    virtual int  volume();
    virtual void setVolume(int v);
    virtual bool playing();
	virtual int  weight();	
	virtual QString name();
	virtual void processErrorMessage(QString);

	QStringList getPlayers();
	bool setPrefferedPlayer(QString);
	QString getInfo();
	QStringList& blackList(QString playerName);
	QStringList& whiteList(QString playerName);

 private:
    PlayerManager();
	QList<Player*> players;
	QMap<QString, QStringList> blackLists, whiteLists;
	QStringList dummy;
	Player *player;
	QString info;
	QUrl filename;
	long filestart, filelength;
	bool autoEngine;
};

#endif //PLAYER_MANAGER_H
