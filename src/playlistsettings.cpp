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

#include "playlistsettings.h"
#include <QtGui>

PlaylistSettings::PlaylistSettings() : QObject(0), autoRating(false)
{
	QSettings set;
	for(int i=0; i<PlaylistModel::ColumnCount; i++) {
		_data[i].v = (bool)set.value("colvisible"+QString::number(i), 1).toInt(0);
		_data[i].w = set.value("colwidth"+QString::number(i), 30).toInt(0);
	}
}

PlaylistSettings::~PlaylistSettings()
{
	QSettings set;
	for(int i=0; i<PlaylistModel::ColumnCount; i++) {
		set.setValue("colvisible"+QString::number(i), (int)_data[i].v);
		set.setValue("colwidth"+QString::number(i), _data[i].w);
	}
}

PlaylistSettings& PlaylistSettings::Self()
{
	static PlaylistSettings self;
	return self;
}

bool PlaylistSettings::columnVisible(int col)
{
	return (col < PlaylistModel::ColumnCount ? _data[col].v : false);
}

bool PlaylistSettings::setColumnVisible(int col, bool vis)
{
	if(col >= PlaylistModel::ColumnCount) return false;
	if(_data[col].v != vis) {
		_data[col].v = vis;
		emit visibleChanged(col, vis);
		if(vis && !_data[col].w) setColumnWidth(col, 30);
		return !vis;
	} else return vis;
}

int  PlaylistSettings::columnWidth(int col)
{
	return col < PlaylistModel::ColumnCount ? _data[col].w : 0;
}

int  PlaylistSettings::setColumnWidth(int col, int wid)
{
	if(col >= PlaylistModel::ColumnCount) return 0;
	if(_data[col].w != wid) {
		int ow = _data[col].w;
		_data[col].w = wid;
		emit widthChanged(col, wid);
		return ow;
	} else return wid;
}

