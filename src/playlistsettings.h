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

#ifndef PLAYLISTSETTINGS_H
#define PLAYLISTSETTINGS_H

#include <QtCore>
#include "playlistmodel.h"

class PlaylistSettings: public QObject
{
Q_OBJECT
 public:
	~PlaylistSettings();
	static PlaylistSettings& Self();
	bool columnVisible(int col);
	bool setColumnVisible(int col, bool vis);
	int  columnWidth(int col);
	int  setColumnWidth(int col, int wid);
	int  columnPosition(int col);
	int  setColumnPosition(int col, int pos);

	void save();

	bool autoRating;
	QString cue_codepage;

	bool    proxyEnabled;
	QString proxyHost;
	int     proxyPort;
	QString proxyUser;
	QString proxyPassword;

	bool    lastfmScrobbler;
	QString lastfmUser;
	QString lastfmPassword;
	bool    librefmScrobbler;
	QString librefmUser;
	QString librefmPassword;

	bool hideEmptyInCollection;

	bool cacheInfo;

	QString lang;

	bool hack1251;
	
	bool textToolbuttons;
	int sizeToolbuttons;

	QString collectionPath;
	bool controlCuePath;
	bool trayMessage;

 signals:
	void visibleChanged(int, bool);
	void widthChanged(int, int);
	void positionChanged(int, int);

 private:
	PlaylistSettings();
	
	struct _Data {
		bool v;
		int w;
		int p;
	};
	struct _Data _data[PlaylistModel::ColumnCount];
};

#define PLSet PlaylistSettings::Self() 

#endif // PLAYLISTSETTINGS_H
