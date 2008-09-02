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

#ifndef DATABASE_H_
#define DATABASE_H_

#include <QtSql>

static const QString nArtist = "Artist",
	nAlbum = "Album",
	nGenre = "Genre",
    nPlaylist = "Playlist";
//	nMark = "Mark";


class Database
{
public:
	struct Attr {
		QString name;
		int refs, rating;
		QString art;
	};

	static Database& Self();
	virtual ~Database();
	int AddFile(QString file);
	int AddArtist(QString artist);
	int AddAlbum(QString album);
	int AddGenre(QString genre);
	int AddPlaylist(QString list);
	//int AddMark(QString mark);
	void Increment(int ar, int al, int ge);
	void Decrement(int ar, int al, int ge);
	void RemoveFile(QString file);
	void RemoveArtist(QString artist);
	void RemoveAlbum(QString album);
	void RemoveGenre(QString genre);
	void RemovePlaylist(QString list);
	//void RemoveMark(QString mark);
	void RenameArtist(QString oldval, QString newval);
	void RenameAlbum(QString oldval, QString newval);
	void RenameGenre(QString oldval, QString newval);
	void RenamePlaylist(QString oldval, QString newval);
	//void RenameMark(QString oldval, QString newval);
	QList<struct Attr> Artists(QString *patt = 0);
	QList<struct Attr> Albums(QString *patt = 0);
	QList<struct Attr> Genres(QString *patt = 0);
	QList<struct Attr> Playlists(QString *patt = 0);
	//QList<struct Attr> Marks(QString *patt = 0);
	void ArtForArtist(QString val, QString art);
	void ArtForAlbum(QString val, QString art);
	void ArtForGenre(QString val, QString art);
	void ArtForPlaylist(QString val, QString art);
	QList<QString> Songs(QString *ar = 0, QString *al = 0, QString *ge = 0, QString *so = 0);
	QString GetArtist(int);
	QString GetAlbum(int);
	QString GetGenre(int);
	//QString GetMark(int);
	bool GetTags(QString file, QString &title, QString &artist, QString &album, QString &comment, QString &genre, int &track, int &year, int &rating, QString &length);
	bool SetTags(QString file, QString title, QString artist, QString album, QString comment, QString genre, int track, int year, int rating);
	//bool SetMark(QString file, QString mark);
	
	void clearSubset();
	void subsetAlbum(QString);
	void subsetArtist(QString);
	void subsetGenre(QString);
	//void subsetMark(QString);
private:
	Database();
	QSqlDatabase db;
	bool open;
	bool subset;
	QString ssAlbum;
	QString ssArtist;
	QString ssGenre;
	//QString ssMark;
	QString ssFilter;
	void RefAttribute(const QString attr, int id, int v, int r);
	int AddAttribute(const QString attr, QString val);
	void RemoveAttribute(const QString attr, QString val);
	void RenameAttribute(const QString attr, QString oldval, QString newval);
	QList<struct Attr> Attributes(const QString attr, QString *patt = 0);
	void ArtForAttribute(const QString attr, QString val, QString art);
	bool updateDatabase(int fromver);
	QString subsetFilter();
	QMutex lock;
};

#endif /*DATABASE_H_*/
