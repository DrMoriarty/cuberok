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

#include "tagentry.h"

QDataStream& operator<<(QDataStream& s, const TagEntry& t) {
    s << t.url;
    s << (qint32)t.start;
    s << (qint32)t.length;
    s << t.artist;
	s << t.album;
    s << t.title;
    s << t.track;
	s << t.slength;
    s << t.comment;
    s << t.genre;
    s << t.year;
    s << (qint32)t.dbindex;
    s << t.rating;
	s << t.filetype;
	return s;
}

QDataStream& operator>>(QDataStream& s, TagEntry& t) {
	qint32 qi;
    s >> t.url;
    s >> qi; t.start = qi;
    s >> qi; t.length = qi;
    s >> t.artist;
	s >> t.album;
    s >> t.title;
    s >> t.track;
	s >> t.slength;
    s >> t.comment;
    s >> t.genre;
    s >> t.year;
    s >> qi; t.dbindex = qi;
    s >> t.rating;
	s >> t.filetype;
	return s;
}
