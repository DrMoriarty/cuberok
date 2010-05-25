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

#include "interfaces.h"

QDataStream& operator<<(QDataStream& s, const STags& v) {
	//s.writeRawData((const char*)&v, sizeof(v));
	s << v.tag0;
	return s;
}

QDataStream& operator>>(QDataStream& s, STags& v) {
	//s.readRawData((char*)&v, sizeof(v));
	s >> v.tag0;
	return s;
}

bool operator == (const TagEntry& t1, const TagEntry& t2)
{
	return t1.url == t2.url &&
		t1.start == t2.start &&
		t1.length == t2.length &&
		t1.artist == t2.artist &&
		t1.album == t2.album &&
		t1.title == t2.title &&
		t1.track == t2.track &&
		t1.slength == t2.slength &&
		t1.comment == t2.comment &&
		t1.genre == t2.genre &&
		t1.year == t2.year &&
		t1.dbindex == t2.dbindex &&
		t1.rating == t2.rating &&
		t1.filetype == t2.filetype;
}

bool operator != (const TagEntry& t1, const TagEntry& t2)
{
	return !(t1 == t2);
}
