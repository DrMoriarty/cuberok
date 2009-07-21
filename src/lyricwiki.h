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

#ifndef LYRICWIKI_H
#define LYRICWIKI_H

#include <QtCore>
#include <QtNetwork>

class LyricWiki : public QObject
{
	Q_OBJECT

 public:
	static LyricWiki& Self();
	~LyricWiki();

	void getSong(QString artist, QString song);

 private:
	LyricWiki();
	QHttp http;

 private slots:
	void requestFinished(int, bool);
	void requestStarted(int);

 signals:
	void xmlInfo(QString);
};

#endif // LYRICWIKI_H
