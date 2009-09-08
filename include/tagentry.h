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

#ifndef TAGENTRY_H
#define TAGENTRY_H

typedef struct _CueEntry {
    QUrl url;
    long start;
    long length;
    QString artist;
    QString album;
    QString title;
    int track;
    QString slength;
    _CueEntry() {
        start = length = 0L;
        track = 0;
    }
} CueEntry;

typedef struct _TagEntry: _CueEntry {
    QString comment;
    QString genre;
    int year;
    long dbindex;
    int rating;
	QString filetype;
    _TagEntry() {
        year = rating = 0;
        dbindex = 0L;
    }
} TagEntry;

#endif // TAGENTRY_H
