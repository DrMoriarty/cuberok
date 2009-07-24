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

#ifndef TAGGER_H_
#define TAGGER_H_

#include <QtCore>

//volatile static bool _autoCorrect = false;
//volatile static bool _saveCorrected = false;

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

class Tagger :public QObject
{
	Q_OBJECT
public:
    virtual ~Tagger();

    static Tagger& Self();
    static bool readTags(QString file, QString &title, QString &artist, QString &album, QString &comment, QString &genre, int &track, int &year, QString &length);
    static bool writeTags(QString file, QString title, QString artist, QString album, QString comment, QString genre, int track, int year);
    static bool updateArtist(QString file, QString artist);
    static bool updateAlbum(QString file, QString album);
    static bool updateGenre(QString file, QString genre);
    static QString correct8bit(QString str, bool *corrected = 0);
    static QString correctBrokenUnicode(QString str, bool *corrected = 0);
	static QString getFileType(QUrl);

    static TagEntry readTags(QUrl &url);
    static QList<CueEntry> readCue(QString file);
    static QList<TagEntry> readM3U(QString file);
    static QList<TagEntry> readXSPF(QString file);
    static QList<TagEntry> readASX(QString file);
    static QList<TagEntry> readEntry(QUrl url);

    /*static bool autoCorrect();
    static void setAutoCorrect(bool);
    static bool saveCorrected();
    static void setSaveCorrected(bool);*/

    static bool playlistDetected(QUrl);
	static bool garbageDetected(QUrl);

signals:
	void fixPlaylistItem(QString list, QString* item, bool* result);

private:
    Tagger();

    static QString getWord(QString &str);
	static QString hack1251(QString text);

    //static bool corrected = false;

    QList<CueEntry> _readCue(QString file);
};

#endif /*TAGGER_H_*/
