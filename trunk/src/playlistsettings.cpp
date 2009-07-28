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

#include "playlistsettings.h"
#include <QtGui>

PlaylistSettings::PlaylistSettings() : QObject(0), autoRating(false), proxyEnabled(false), proxyPort(0), hideEmptyInCollection(false)
{
	QSettings set;
	for(int i=0; i<PlaylistModel::ColumnCount; i++) {
		_data[i].v = (bool)set.value("colvisible"+QString::number(i), 1).toInt(0);
		_data[i].w = set.value("colwidth"+QString::number(i), 30).toInt(0);
		_data[i].p = set.value("colposition"+QString::number(i), i).toInt(0);
	}
	autoRating = set.value("autoRating", false).toBool();
	cue_codepage = set.value("cue_codepage", "System").toString();

	proxyEnabled = set.value("proxyEnabled", false).toBool();
	proxyHost = set.value("proxyHost", "").toString();
	proxyPort = set.value("proxyPort", 0).toInt();
	proxyUser = set.value("proxyUser", "").toString();
	proxyPassword = set.value("proxyPassword", "").toString();

	lastfmScrobbler = set.value("lastfmScrobbler", false).toBool();
	lastfmUser = set.value("lastfmUser", "").toString();
	lastfmPassword = set.value("lastfmPassword", "").toString();
	librefmScrobbler = set.value("librefmScrobbler", false).toBool();
	librefmUser = set.value("librefmUser", "").toString();
	librefmPassword = set.value("librefmPassword", "").toString();

	hideEmptyInCollection = set.value("hideEmptyInCollection", false).toBool();

	cacheInfo = set.value("cacheInfo", true).toBool();

	hack1251 = set.value("hack1251", false).toBool();

	textToolbuttons = set.value("textToolbuttons", false).toBool();
	sizeToolbuttons = set.value("sizeToolbuttons", 1).toInt();

	collectionPath = set.value("collectionPath", "").toString();
	controlCuePath = set.value("controlCuePath", true).toBool();
	trayMessage = set.value("trayMessage", true).toBool();
	popupMessage = set.value("popupMessage", true).toBool();
	QByteArray mimeArr = qvariant_cast<QByteArray>(set.value("mimeMap"));
	if(mimeArr.size()) {
		QDataStream s(mimeArr);
		s >> mimeMap;
	}
	defaultPlayer = set.value("defaultPlayer", "").toString();
}

PlaylistSettings::~PlaylistSettings()
{
	//save();
}

void PlaylistSettings::save()
{
	QSettings set;
	for(int i=0; i<PlaylistModel::ColumnCount; i++) {
		set.setValue("colvisible"+QString::number(i), (int)_data[i].v);
		set.setValue("colwidth"+QString::number(i), _data[i].w);
		set.setValue("colposition"+QString::number(i), _data[i].p);
	}
	set.setValue("autoRating", autoRating);
	set.setValue("cue_codepage", cue_codepage);
	set.setValue("proxyEnabled", proxyEnabled);
	set.setValue("proxyHost", proxyHost);
	set.setValue("proxyPort", proxyPort);
	set.setValue("proxyUser", proxyUser);
	set.setValue("proxyPassword", proxyPassword);

	set.setValue("lastfmScrobbler", lastfmScrobbler);
	set.setValue("lastfmUser", lastfmUser);
	set.setValue("lastfmPassword", lastfmPassword);
	set.setValue("librefmScrobbler", librefmScrobbler);
	set.setValue("librefmUser", librefmUser);
	set.setValue("librefmPassword", librefmPassword);

	set.setValue("hideEmptyInCollection", hideEmptyInCollection);

	set.setValue("cacheInfo", cacheInfo);

	set.setValue("hack1251", hack1251);

	set.setValue("textToolbuttons", textToolbuttons);
	set.setValue("sizeToolbuttons", sizeToolbuttons);

	set.setValue("collectionPath", collectionPath);
	set.setValue("controlCuePath", controlCuePath);
	set.setValue("trayMessage", trayMessage);
	set.setValue("popupMessage", popupMessage);

	QByteArray mimeArr;
	QDataStream s(&mimeArr, QIODevice::WriteOnly);
	s << mimeMap;
	set.setValue("mimeMap", mimeArr);
	set.setValue("defaultPlayer", defaultPlayer);
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

int  PlaylistSettings::columnPosition(int col)
{
	return col < PlaylistModel::ColumnCount ? _data[col].p : 0;
}

int PlaylistSettings::setColumnPosition(int col, int pos)
{
	if(col >= PlaylistModel::ColumnCount) return 0;
	if(_data[col].p != pos) {
		int op = _data[col].p;
		_data[col].p = pos;
		emit positionChanged(col, pos);
		return op;
	} else return pos;
}
