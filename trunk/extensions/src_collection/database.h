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

#ifndef DATABASE_H_
#define DATABASE_H_

#include <QtCore>
#include "interfaces.h"

typedef enum {M_ARTIST=0, M_ALBUM, M_GENRE, M_SONG, M_SQLLIST} ListMode;

static const QString nArtist = "Artist",
    nAlbum = "Album",
    nGenre = "Genre",
    nPlaylist = "Playlist";

class Database : public QObject
{
	Q_OBJECT
public:
    struct Attr {
        QString name;
        int refs, rating;
        QString art;
		QString mbid;
    };

    struct AttrAl : Attr {
        int artist;
    };

	struct SAttr {
        QString name;
        QString art;
		QString data;
	};

    static Database& Self(Proxy* p = 0);
    ~Database();
	static Proxy *proxy;

    int AddFile(QString file);
    int AddArtist(QString artist);
    int AddAlbum(QString album, int artist);
    int AddGenre(QString genre);
    int AddSQLPlaylist(QString list);
    int GetArtist(QString artist);
    int GetAlbum(QString album, int artist);
    void RemoveFile(QString file);
    void RemoveArtist(QString artist);
    void RemoveAlbum(QString album, int artist);
    void RemoveGenre(QString genre);
    void RemoveSQLPlaylist(QString list);
    void RenameArtist(QString oldval, QString newval);
    void RenameAlbum(QString oldval, QString newval, int artist);
    void RenameGenre(QString oldval, QString newval);
    void RenameSQLPlaylist(QString oldval, QString newval);
    QList<struct Attr> Artists(QString *patt = 0);
    QList<struct AttrAl> Albums(QString *patt = 0);
    QList<struct Attr> Genres(QString *patt = 0);
    QList<struct SAttr> SQLPlaylists(QString *patt = 0);
    void ArtForAlbum(QString val, QString art, int artist);
    void ArtForArtist(QString val, QString art);
    void ArtForGenre(QString val, QString art);
    void ArtForSQLPlaylist(QString val, QString art);
    QList<QString> Songs(QString *ar = 0, int al = 0, QString *ge = 0, QString *so = 0);
	QList<QString> SongsBySQLPlaylist(QString sqlname);
    bool GetTags(QString file, QString &title, QString &artist, QString &album, QString &comment, QString &genre, int &track, int &year, int &rating, QString &length, QString &type);
    bool SetTags(QString file, QString title, QString artist, QString album, QString comment, QString genre, int track, int year, int rating);
	bool GetTags(QString file, STags& tags);
	bool SetTags(QString file, const STags& tags);
	void MbidForAlbum(QString val, QString mbid, int artist);
	void MbidForArtist(QString val, QString mbid);
    QString GetArtist(int);
    QString GetAlbum(int);
    QString GetGenre(int);
	QString GetFile(int);
	void RateSong(QString file, int rate);
	QString getInfo(QString mbid);
	void setInfo(QString mbid, QString text);
	QString GetSQLPlaylist(QString name);
	void SetSQLPlaylist(QString name, QString sql);
	void SetFileType(QString file, QString type);

    void clearSubset();
    void pushSubset();
    void popSubset();
    void subsetAlbum(int);
    void subsetArtist(QString);
    void subsetGenre(QString);

	static QString commonPath(QString path1, QString path2);
	void cleanUpAlbums();
	void cleanUpArtists();
	void cleanUpGenres();

 signals:
	void DataUpdate();

 public slots:
	void GenSignalUpdate();
	
 private:
    Database();
    bool open;
    bool subset;
    int ssAlbum;
    QString ssArtist;
    QString ssGenre;
    QVector < QList<QString> > sstack;
    QString ssFilter;

    QString _GetArtist(int);
    QString _GetAlbum(int);
    QString _GetGenre(int);
	QString _GetFile(int);
    void _ArtForAlbum(QString val, QString art, int artist);
    void _RemoveAlbum(QString album, int artist);
    void _RemoveFile(QString file);
    int _AddGenre(QString genre);
    int _AddAlbum(QString album, int artist);
    int _AddArtist(QString artist);
	void _MbidForAlbum(QString val, QString mbid, int artist);
	void _MbidForArtist(QString val, QString mbid);

    void RefAttribute(const QString attr, int id, int v, int r);
    int AddAttribute(const QString attr, QString val);
    void RemoveAttribute(const QString attr, QString val);
    void RenameAttribute(const QString attr, QString oldval, QString newval);
    QList<struct Attr> Attributes(const QString attr, QString *patt = 0);
    void ArtForAttribute(const QString attr, QString val, QString art);
    bool updateDatabase(int fromver);
    QString subsetFilter();
	void CreateDefaultSqlPlaylists();
    QMutex lock;
};

#endif /*DATABASE_H_*/
