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

#ifndef LIBRARY_DB_H_
#define LIBRARY_DB_H_

#include <QtCore>
#include "interfaces.h"

class LibraryDB : public QObject
{
	Q_OBJECT
public:
    struct Attr {
        QString name;
        int refs, rating;
        QString art;
		QString mbid;
    };

	Proxy* proxy;

    static LibraryDB& Self(Proxy *pr = 0);
    ~LibraryDB();

    int AddPlaylist(QString list);
    void RemovePlaylist(QString list);
    void RenamePlaylist(QString oldval, QString newval);
    QList<struct Attr> Playlists(QString *patt = 0);
    void ArtForPlaylist(QString val, QString art);

 private:
    LibraryDB(Proxy *pr);
    bool open;

    bool updateDatabase(int fromver);
	void FillFromCollection();
    QMutex lock;
};

#endif /*LIBRARY_DB_H_*/
