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

#include "player_void.h"

Q_EXPORT_PLUGIN2(player_void, PlayerVoid) 

PlayerVoid::PlayerVoid()
{
}

PlayerVoid::~PlayerVoid()
{
}

bool PlayerVoid::prepare()
{
	return true;
}

bool PlayerVoid::ready()
{
	return true;
}

bool PlayerVoid::canOpen(QString mime)
{
	return false;
}

bool PlayerVoid::open(QUrl fname, long start, long length)
{
    return false;
}

bool PlayerVoid::play()
{
    return false;
}

bool PlayerVoid::stop()
{
    return false;
}

bool PlayerVoid::setPause(bool p)
{
    return false;
}

bool PlayerVoid::close()
{
    return false;
}

bool PlayerVoid::setPosition(double pos)
{
    return false;
}

double PlayerVoid::getPosition()
{
	return 0.0;
}

int  PlayerVoid::volume()
{
	return 0;
}

void PlayerVoid::setVolume(int v)
{
}

bool PlayerVoid::playing()
{
    return false;
}

int PlayerVoid::weight()
{
	return 1;
}

QString PlayerVoid::name()
{
	return "Null engine";
}
