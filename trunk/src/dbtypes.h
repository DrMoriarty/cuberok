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

#ifndef DBTYPES_H
#define DBTYPES_H

#include <QtCore>
#include "tagger.h"

class DBAttribute {
 public:
	DBAttribute(QString name, int refs, int rating, QString art, QString table = "", int id = 0);
	DBAttribute(QString table, int id);
	virtual ~DBAttribute();

	virtual QString name();
	virtual bool rename(QString newname);
	virtual int refs();
	virtual int rating();
	virtual bool update(int refs, int rating);
	virtual QString art();
	virtual void setArt(QString art);
	virtual bool remove();

 protected:
	QString _value, _art, _table;
	int _refs, _rating, _id;
};

class DBGenre : public DBAttribute {
 public:
	DBGenre(int id);
};

class DBArtist : public DBAttribute {
 public:
	DBArtist(int id);

	virtual bool rename(QString newname);
};

class DBAlbum : public DBAttribute {
 public:
	DBAlbum(int id);
	virtual ~DBAlbum();
	virtual bool rename(QString newname);
	virtual int artist();

 protected:
	int _artist;
};

class DBSong {
 public:
	DBSong(int id);
	DBSong(const TagEntry &tags);
	const TagEntry &tags();
	bool setTags(const TagEntry &tags);

 protected:
	TagEntry _tags;
	int _id, _genre, _artist, _album;
};

#endif //DBTYPES_H
