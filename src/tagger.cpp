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

#include "tagger.h"
#include "main.h"
#include "database.h"

Tagger::Tagger()
{
}

Tagger::~Tagger()
{
}

/*Tagger& Tagger::Self()
{
	static Tagger *instance = 0;
	if(!instance) instance = new Tagger();
	return *instance;
}*/

bool Tagger::readTags(QString file, QString &title, QString &artist, QString &album, QString &comment, QString &genre, int &track, int &year, QString &length)
{
	//if(Database::Self().GetTags(file, title, artist, album, comment, genre, track, year, length)) 
	//	return true;
	bool corrected = false;
#define corstr(s) autoCorrect() ? correct8bit(s, &corrected) : s
	TagLib::FileRef fr(file.toLocal8Bit().constData());
	TagLib::Tag *tag;
	if(!fr.isNull() && fr.audioProperties()) {
		tag = fr.tag();
		if(tag) {
			if(tag->title().isEmpty())
		        title = QFileInfo(file).fileName();
			else
		        title = corstr(QS(tag->title()));
			artist = corstr(QS(tag->artist()));
			album = corstr(QS(tag->album()));
			year = tag->year();
			comment = corstr(QS(tag->comment()));
			track = tag->track();
			genre = corstr(QS(tag->genre()));
			if(corrected && saveCorrected()) {
				TagLib::FileRef fr(file.toLocal8Bit().constData());
				if(file.endsWith(QString(".MP3"), Qt::CaseInsensitive)) {
					TagLib::ID3v2::FrameFactory::instance()->setDefaultTextEncoding(TagLib::String::UTF8);
					TagLib::MPEG::File &file = *((TagLib::MPEG::File*)fr.file());
					TagLib::ID3v2::Tag &tag2 = *file.ID3v2Tag(true);
					tag2.setAlbum(TS(album));
					tag2.setArtist(TS(artist));
					tag2.setComment(TS(comment));
					tag2.setGenre(TS(genre));
					tag2.setTitle(TS(title));
					file.save(TagLib::MPEG::File::ID3v2);
					//cor_count ++;
				} else {
					tag->setAlbum(TS(album));
					tag->setArtist(TS(artist));
					tag->setComment(TS(comment));
					tag->setGenre(TS(genre));
					tag->setTitle(TS(title));
					fr.save();
				}
			}
		}
		length = QString("%1:%2")
			.arg(QString::number(int(fr.audioProperties()->length()/60)), fr.audioProperties()->length()%60 < 10 ? QString("0%1").arg(QString::number(fr.audioProperties()->length()%60)) : QString::number(fr.audioProperties()->length()%60) );
			//.arg(fr.audioProperties()->length()%60, 2, 10, '0');
		return true;
	}
	return false;
#undef corstr
}

bool Tagger::writeTags(QString file, QString title, QString artist, QString album, QString comment, QString genre, int track, int year)
{
	TagLib::FileRef fr(file.toLocal8Bit().constData());
	if(file.endsWith(QString(".MP3"), Qt::CaseInsensitive)) {
		TagLib::ID3v2::FrameFactory::instance()->setDefaultTextEncoding(TagLib::String::UTF8);
		TagLib::MPEG::File &file = *((TagLib::MPEG::File*)fr.file());
		TagLib::ID3v2::Tag &tag2 = *file.ID3v2Tag(true);
		tag2.setAlbum(TS(album));
		tag2.setArtist(TS(artist));
		tag2.setComment(TS(comment));
		tag2.setGenre(TS(genre));
		tag2.setTitle(TS(title));
		tag2.setYear(year);
		tag2.setTrack(track);
		file.save(TagLib::MPEG::File::ID3v2);
	} else {
		fr.tag()->setAlbum(TS(album));
		fr.tag()->setArtist(TS(artist));
		fr.tag()->setComment(TS(comment));
		fr.tag()->setGenre(TS(genre));
		fr.tag()->setTitle(TS(title));
		fr.tag()->setYear(year);
		fr.tag()->setTrack(track);
		fr.save();
	}
	return true;
}

bool Tagger::updateArtist(QString file, QString artist)
{
	TagLib::FileRef fr(file.toLocal8Bit().constData());
	if(file.endsWith(QString(".MP3"), Qt::CaseInsensitive)) {
		TagLib::ID3v2::FrameFactory::instance()->setDefaultTextEncoding(TagLib::String::UTF8);
		TagLib::MPEG::File &file = *((TagLib::MPEG::File*)fr.file());
		TagLib::ID3v2::Tag &tag2 = *file.ID3v2Tag(true);
		tag2.setArtist(TS(artist));
		file.save(TagLib::MPEG::File::ID3v2);
	} else {
		fr.tag()->setArtist(TS(artist));
		fr.save();
	}
	return true;
}

bool Tagger::updateAlbum(QString file, QString album)
{
	TagLib::FileRef fr(file.toLocal8Bit().constData());
	if(file.endsWith(QString(".MP3"), Qt::CaseInsensitive)) {
		TagLib::ID3v2::FrameFactory::instance()->setDefaultTextEncoding(TagLib::String::UTF8);
		TagLib::MPEG::File &file = *((TagLib::MPEG::File*)fr.file());
		TagLib::ID3v2::Tag &tag2 = *file.ID3v2Tag(true);
		tag2.setAlbum(TS(album));
		file.save(TagLib::MPEG::File::ID3v2);
	} else {
		fr.tag()->setAlbum(TS(album));
		fr.save();
	}
	return true;
}

bool Tagger::updateGenre(QString file, QString genre)
{
	TagLib::FileRef fr(file.toLocal8Bit().constData());
	if(file.endsWith(QString(".MP3"), Qt::CaseInsensitive)) {
		TagLib::ID3v2::FrameFactory::instance()->setDefaultTextEncoding(TagLib::String::UTF8);
		TagLib::MPEG::File &file = *((TagLib::MPEG::File*)fr.file());
		TagLib::ID3v2::Tag &tag2 = *file.ID3v2Tag(true);
		tag2.setGenre(TS(genre));
		file.save(TagLib::MPEG::File::ID3v2);
	} else {
		fr.tag()->setGenre(TS(genre));
		fr.save();
	}
	return true;
}

QString Tagger::correct8bit(QString str, bool *corrected)
{
	foreach(QChar ch, str) {
		ushort cc = ch.unicode(); 
		if(cc > 127 && cc < 256) {
			QString s;
			foreach(QChar c, str) {
				char buf = (char)c.unicode();
				s.append(QString::fromLocal8Bit(&buf, 1));
			}
			if(corrected) *corrected = true;
			return s;
		}
	}
	return str;
}

QString Tagger::correctBrokenUnicode(QString str, bool *corrected)
{
	bool latin = false;
	bool local8bit = false;
	foreach(QChar ch, str) {
		ushort cc = ch.unicode(); 
		if(cc < 0x20) local8bit = true;
		if(cc >= 0x50) latin = true;
	}
	if(local8bit || !latin) {
		QString s;
		foreach(QChar c, str) {
			char buf;
			if((char)c.unicode() != 0x20) buf = (char)c.unicode() + 0xb0;
			else buf = 0x20;
			s.append(QString::fromLocal8Bit(&buf, 1));
		}
		if(corrected) *corrected = true;
		return s;
	}
	return str;
}

bool Tagger::autoCorrect()
{
	return _autoCorrect;
}

void Tagger::setAutoCorrect(bool b)
{
	_autoCorrect = b;
}

bool Tagger::saveCorrected()
{
	return _saveCorrected;
}

void Tagger::setSaveCorrected(bool b)
{
	_saveCorrected = b;
}

