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

#include "tagger.h"
#include "main.h"
#include "database.h"
#include "extensionproxy.h"
#include "downloader.h"
#include "console.h"

#include "QtGui"
#include <QtXml>

Tagger::Tagger()
{}

Tagger::~Tagger()
{}

Tagger& Tagger::Self()
{
	static Tagger instance;
	return instance;
}

bool Tagger::readTags(QString file, QString &title, QString &artist, QString &album, QString &comment, QString &genre, int &track, int &year, QString &length)
{
	//if(Database::Self().GetTags(file, title, artist, album, comment, genre, track, year, length)) 
	//	return true;
	bool corrected = false;
//#define corstr(s) autoCorrect() ? correct8bit(s, &corrected) : s
#define corstr(s) ((EProxy.hasVariable("hack1251") && EProxy.getVariable("hack1251")=="true") ? hack1251(s) : s)
#define local(s) s.toCString(false)
	TagLib::FileRef fr(file.toLocal8Bit().constData());
	TagLib::Tag *tag;
	if(!fr.isNull() && fr.audioProperties()) {
		tag = fr.tag();
		if(tag) {
			bool skiptag = false;
			if(file.endsWith(QString(".MP3"), Qt::CaseInsensitive)) {
				//TagLib::ID3v2::FrameFactory::instance()->setDefaultTextEncoding(TagLib::String::UTF8);
				TagLib::MPEG::File &mp3file = *((TagLib::MPEG::File*)fr.file());
				// if id3v1 exist and id3v2 not
				if(mp3file.ID3v1Tag()) {
					if(EProxy.hasVariable("hack1251") && EProxy.getVariable("hack1251") == "true") {
						QTextCodec::setCodecForCStrings (QTextCodec::codecForName("CP1251"));
					} else {
						QTextCodec::setCodecForCStrings (QTextCodec::codecForName("System"));
					}
					TagLib::ID3v1::Tag &tag1 = *mp3file.ID3v1Tag();
					if(tag1.title().isEmpty())
						title = QFileInfo(file).fileName();
					else
						title = local(tag1.title());
					artist = local(tag1.artist());
					album = local(tag1.album());
					year = tag1.year();
					comment = local(tag1.comment());
					track = tag1.track();
					genre = local(tag1.genre());
					QTextCodec::setCodecForCStrings (0);
				}
				if(mp3file.ID3v2Tag()) {
					TagLib::ID3v2::Tag &tag2 = *mp3file.ID3v2Tag();
					if(tag2.title().size()) title = corstr(QS(tag2.title()));
					if(tag2.artist().size()) artist = corstr(QS(tag2.artist()));
					if(tag2.album().size()) album = corstr(QS(tag2.album()));
					if(tag2.year()) year = tag2.year();
					if(tag2.comment().size()) comment = corstr(QS(tag2.comment()));
					if(tag2.track()) track = tag2.track();
					if(tag2.genre().size()) genre = corstr(QS(tag2.genre()));
				}
				skiptag = true;
			}
			if(!skiptag) {
				if(tag->title().isEmpty())
					title = QFileInfo(file).fileName();
				else
					title = QS(tag->title());
				artist = QS(tag->artist());
				album = QS(tag->album());
				year = tag->year();
				comment = QS(tag->comment());
				track = tag->track();
				genre = QS(tag->genre());
				/*if(corrected && saveCorrected()) {
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
				}*/
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

QString Tagger::hack1251(QString text)
{
	foreach(QChar ch, text) {
		ushort cc = ch.unicode(); 
		if(cc > 127 && cc < 256) {
			QTextCodec *codec = QTextCodec::codecForName("CP1251");
			return codec->toUnicode(text.toAscii());
		}
	}
	return text;
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

QList<CueEntry> Tagger::readCue(QString filename)
{
	return Self()._readCue(filename);
}

QList<CueEntry> Tagger::_readCue(QString filename)
{
	QList<CueEntry> list;
	CueEntry item;
	QString file, artist, artist2, album, title;
	long start=0;
	int track=0, ID = 0;
	bool entry = false, skip = false;
	QString path = QFileInfo(filename).path();
	
	QFile f(filename);
	if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream in(&f);
		if(EProxy.hasVariable("cue_codepage")) {
			in.setCodec(EProxy.getVariable("cue_codepage").toLocal8Bit());
		}
		while (!in.atEnd()) {
			QString line = in.readLine(), word;
			while(line.size()) {
				word = getWord(line);
				if(skip && word != "TRACK") break;
				if(word == "TITLE") {
					if(entry) title = getWord(line);
					else album = getWord(line);
				}
				else if(word == "PERFORMER") {
					if(entry) artist2 = getWord(line);
					else artist = getWord(line);
				}
				else if(word == "FILE") {
					file = getWord(line);
					if(QFileInfo(file).isRelative()) file = path + QDir::separator() + file;
					getWord(line); // type
					if(EProxy.hasVariable("controlCuePath") && EProxy.getVariable("controlCuePath") == "true") {
						if(!QFileInfo(file).exists()) {
							bool res;
							emit fixPlaylistItem(filename, &file, &res);
							if(!res) return list;
							if(QFileInfo(file).isRelative()) file = path + QDir::separator() + file;
						}
					}
				}
				else if(word == "TRACK") {
					skip = false;
					if(entry) {
						item.url = QUrl::fromLocalFile(file);
						item.start = start;
						item.length = 0;//length;
						item.artist = artist2.size() ? artist2 : artist;
						item.album = album;
						item.title = title.size() ? title : QString("Track ")+QString::number(++ID);
						item.track = track;
						list << item;
						item.start = 0;
						item.length = 0;
						item.artist = "";
						item.album = "";
						item.title = "";
						item.track = 0;
					}
					entry = true;
					track = getWord(line).toInt();
					if(getWord(line) != "AUDIO") 
						skip = true;
				}
				else if(word == "INDEX") {
					getWord(line); // index number
					QString ind = getWord(line);
					start = ind.section(':', 0, 0).toInt() * 4500 + ind.section(':', 1, 1).toInt() * 75 + ind.section(':', 2, 2).toInt();
				}
				else {
					// SYNTAX ERROR
				}
			}
		}
		if(entry && !skip) {
			item.url = QUrl::fromLocalFile(file);
			item.start = start;
			item.length = 0;//length;
			item.artist = artist2.size() ? artist2 : artist;
			item.album = album;
			item.title = title.size() ? title : QString("Track ")+QString::number(++ID);
			item.track = track;
			list << item;
		}
		for(int i = 0; i<list.size()-1; i++) {
			list[i].length = list[i+1].start - list[i].start;
			list[i].slength = QString::number((list[i].length%4500)/75);
			list[i].slength = QString("%1:%2").arg(QString::number(list[i].length/4500), list[i].slength.size()<2 ? "0"+list[i].slength : list[i].slength);
		}
		TagLib::FileRef fr(file.toLocal8Bit().constData());
		if(!fr.isNull() && fr.audioProperties()) {
			long len = fr.audioProperties()->length() * 75;
			list.last().length = len - list.last().start;
			list.last().slength = QString::number((list.last().length%4500)/75);
			list.last().slength = QString("%1:%2").arg(QString::number(list.last().length/4500), list.last().slength.size()<2 ? "0"+list.last().slength : list.last().slength);
		}
	}

	return list;
}
/*
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
*/
QString Tagger::getWord(QString &str)
{
	QString word;
	str = str.trimmed();
	if(str[0] == '\"') {
		int i = str.indexOf('"', 1);
		if(i >= 0) {
			word = str.mid(1, i-1);
			str = str.mid(i+1);
		} else { 
			word = str.mid(1);
			str = "";
		}
	} else {
		int i = str.indexOf(' ', 1);
		if(i >= 0) {
			word = str.mid(0, i);
			str = str.mid(i+1);
		} else { 
			word = str;
			str = "";
		}
	}
	return word;
}

TagEntry Tagger::readTags(QUrl &url)
{
	TagEntry tags;
	if(!url.isValid() || url.isEmpty()) return tags;
// 	tags.start = 0;
// 	tags.length = 0;
// 	tags.dbindex = 0;
// 	tags.rating = 0;
// 	tags.track = 0;
// 	tags.year = 0;
	tags.url = url;
	QString file = ToLocalFile(url);
	if(file.size()) {
		QString title, artist, album, comment, genre, length, type;
		int track, year, rating;
		TagLib::FileRef fr(file.toLocal8Bit().constData());
		if(!fr.isNull() && fr.audioProperties()) {
			tags.length = fr.audioProperties()->length() * 75;
		}
		if(Database::Self().GetTags(file, title, artist, album, comment, genre, track, year, rating, length, type)) {
			tags.title = title;
			tags.artist = artist;
			tags.album = album;
			tags.comment = comment;
			tags.genre = genre;
			tags.track = track;
			tags.year = year;
			tags.rating = rating;
			tags.slength = length;
			tags.filetype = type;
			if(!type.size()) {
				tags.filetype = getFileType(url);
				Database::Self().SetFileType(file, tags.filetype);
			}
		} else
		if(readTags(file, title, artist, album, comment, genre, track, year, length)) {
			tags.title = title;
			tags.artist = artist;
			tags.album = album;
			tags.comment = comment;
			tags.genre = genre;
			tags.track = track;
			tags.year = year;
			tags.slength = length;
		} else {
			tags.title = QFileInfo(file).completeBaseName();
		}
	} else { // can not read tags from remote source
		tags.title = url.toString();
	}
	if(!tags.filetype.size()) tags.filetype = getFileType(url);
	return tags;
}

QList<TagEntry> Tagger::readM3U(QString fname)
{
	QList<TagEntry> list;
	if(QFile::exists(fname)) {
		QFile file(fname);
		if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QTextStream in(&file);
			QMimeData data;
			QList<QUrl> urls;
			while (!in.atEnd()) {
				QString line = in.readLine();
				if(line[0] == '#' || !line.size()) continue;
				if(QFileInfo(line).exists()) {
					line = QUrl::fromLocalFile(line).toString();
				} else {
					QString line2 = QFileInfo(fname).absolutePath() + QDir::separator() + line;
					if(QFileInfo(line2).exists()) line = QUrl::fromLocalFile(line2).toString();
				}
				QUrl url(line);
				if(playlistDetected(url))
					list << readEntry(url);
				else
					list << readTags(url);
			} 
			file.close();
		}
	}
	return list;
}

QList<TagEntry> Tagger::readXSPF(QString fname)
{
	QList<TagEntry> list;
	TagEntry tags;
	//QString location, title, artist, comment, album, genre, length;
	//int track, dbindex, year, rating;
	//long cuestart, cuelength;
	if(QFile::exists(fname)) {
		QFile file(fname);
		if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QXmlStreamReader xml(&file);
			int step = 0;
			while (!xml.atEnd()) {
				QXmlStreamReader::TokenType tt = xml.readNext();
				if(tt == QXmlStreamReader::EndDocument || tt == QXmlStreamReader::Invalid)
					break;
				else if(tt == QXmlStreamReader::StartElement) {
					if(xml.name() == "playlist") {
						if(xml.namespaceUri() != "http://xspf.org/ns/0/") break;
						if(xml.attributes().value("version").toString() != "1") break;
						if(!step) step ++;
					} else if(xml.name() == "trackList" && step == 1) {
						step ++;
					} else if(xml.name() == "track" && step == 2) {
						step ++;
						tags.url = "";
						tags.title = tags.artist = tags.comment = tags.album = tags.genre = tags.slength = "";
						tags.track = tags.dbindex = tags.year = tags.rating = 0;
						tags.start = tags.length = 0;
					} else if(xml.name() == "location" && step == 3) {
						tags.url = xml.readElementText();
					} else if(xml.name() == "title" && step == 3) {
						tags.title = xml.readElementText();
					} else if(xml.name() == "creator" && step == 3) {
						tags.artist = xml.readElementText();
					} else if(xml.name() == "annotation" && step == 3) {
						tags.comment = xml.readElementText();
					} else if(xml.name() == "album" && step == 3) {
						tags.album = xml.readElementText();
					} else if(xml.name() == "trackNum" && step == 3) {
						tags.track = xml.readElementText().toInt();
					} else if(xml.name() == "extension") {
						if(xml.attributes().value(QString("application")).toString() == XMLNS) {
							while(tt=xml.readNext(), !xml.atEnd()) {
								if(tt == QXmlStreamReader::StartElement) {
									if(xml.name() == "cuestart") {
										tags.start = xml.readElementText().toLongLong();
									} else if(xml.name() == "cuelength") {
										tags.length = xml.readElementText().toLongLong();
									} else if(xml.name() == "dbindex") {
										tags.dbindex = xml.readElementText().toInt();
									} else if(xml.name() == "genre") {
										tags.genre = xml.readElementText();
									} else if(xml.name() == "length") {
										tags.slength = xml.readElementText();
									} else if(xml.name() == "year") {
										tags.year = xml.readElementText().toInt();
									} else if(xml.name() == "rating") {
										tags.rating = xml.readElementText().toInt();
									} else if(xml.name() == "filetype") {
										tags.filetype = xml.readElementText();
									}
								} else if(tt == QXmlStreamReader::EndElement && xml.name() == "extension") break;
							}
							}
					}
				} else if(tt == QXmlStreamReader::EndElement) {
					if(xml.name() == "playlist") {
						if(step == 1) step --;
					} else if(xml.name() == "trackList") {
						if(step == 2) step --;
					} else if(xml.name() == "track") {
						if(step == 3) step --;
						// insert
						if(!tags.title.size()) {
							if(tags.comment.size()) {
								tags.title = tags.comment;
							} else {
								tags.title = tags.url.toString();
							}
						}
						if(playlistDetected(tags.url))
							list << readEntry(tags.url);
						else
							list << tags;
					}
				}
			}
			if (xml.hasError()) {
				QString err = QString("There is error in XSPF playlist:\nLine number %1, column %2\n%3").arg(QString::number(xml.lineNumber()), QString::number(xml.columnNumber()), xml.errorString());
				Console::Self().error(err);
			} 
			file.close();
		}
	}
	return list;
}


QList<TagEntry> Tagger::readEntry(QUrl url)
{
	QList<TagEntry> list;
	if(!url.isValid() || url.isEmpty()) return list;
	QString file = ToLocalFile(url);
	if(!file.size()) { 
		if(playlistDetected(url)) {
			// download playlist
			SyncDownloader dl(url, &file);
			dl.start();
			dl.wait();
			//file = dl.download(url);
			if(!file.size()) { // error
				Console::Self().warning(QString("Can't download playlist ")+url.toString());
				return list;
			}
		} else {
			TagEntry tags;
			tags.url = url;
			tags.title = url.toString();
			list << tags;
			return list;
		}
	}
	if(file.toLower().endsWith(".m3u"))
		return readM3U(file);
	else if(file.toLower().endsWith(".xspf"))
		return readXSPF(file);
	else if(file.toLower().endsWith(".asx") || file.toLower().endsWith(".asp"))
		return readASX(file);
	else if(file.toLower().endsWith(".cue")) {
		QList<TagEntry> tlist;
		QList<CueEntry> clist = readCue(file);
		TagEntry t;
		if(clist.size()) t = readTags(clist[0].url);
		foreach(CueEntry cue, clist) {
			TagEntry tt = t;
			tt.url = cue.url;
			tt.start = cue.start;
			tt.length = cue.length;
			tt.artist = cue.artist;
			tt.album = cue.album;
			tt.title = cue.title;
			tt.track = cue.track;
			tt.slength = cue.slength;
			tlist << tt;
		}
		return tlist;
	}
	// this is not a playlist
	list << readTags(url);
	return list;
}

QList<TagEntry> Tagger::readASX(QString fname)
{
	QList<TagEntry> list;
	TagEntry tags;
	if(QFile::exists(fname)) {
		QFile file(fname);
		if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QXmlStreamReader xml(&file);
			int step = 0;
			while (!xml.atEnd()) {
				QXmlStreamReader::TokenType tt = xml.readNext();
				if(tt == QXmlStreamReader::EndDocument || tt == QXmlStreamReader::Invalid)
					break;
				else if(tt == QXmlStreamReader::StartElement) {
					if(xml.name().toString().toLower() == "asx") {
						if(xml.attributes().value("version").toString() != "3.0") break;
						if(!step) step ++;
					} else if(xml.name().toString().toLower() == "entry" && step == 1) {
						step ++;
					} else if(xml.name().toString().toLower() == "title" && step == 2) {
						tags.title = xml.readElementText();
					} else if(xml.name().toString().toLower() == "author" && step == 2) {
						tags.artist = xml.readElementText();
					} else if(xml.name().toString().toLower() == "copyright" && step == 2) {
						tags.comment = xml.readElementText();
					} else if(xml.name().toString().toLower() == "ref" && step == 2) {
						tags.url = xml.attributes().value("href").toString();
						if(tags.url.isEmpty())
							tags.url = xml.attributes().value("HREF").toString();
					}
				} else if(tt == QXmlStreamReader::EndElement) {
					if(xml.name().toString().toLower() == "asx" && step == 1) {
						step --;
					} else if(xml.name().toString().toLower() == "entry" && step == 2) {
						step --;
					} else if(xml.name().toString().toLower() == "ref" && step == 2) {
						if(playlistDetected(tags.url))
							list << readEntry(tags.url);
						else
							list << tags;
					}
				}
			}
			if (xml.hasError()) {
				QString err = QString("There is error in ASX playlist:\nLine number %1, column %2\n%3").arg(QString::number(xml.lineNumber()), QString::number(xml.columnNumber()), xml.errorString());
				Console::Self().error(err);
			} 
			file.close();
		}
	}
	return list;
}

bool Tagger::playlistDetected(QUrl url)
{
	QString file = url.path().toLower();
	if(!url.hasQuery()) {
		if(file.endsWith(".m3u"))
			return true;
		else if(file.endsWith(".xspf"))
			return true;
		else if(file.endsWith(".asx") || file.endsWith(".asp"))
			return true;
		else if(file.endsWith(".cue")) 
			return true;
	} else {
		if(file.contains(".m3u"))
			return true;
		else if(file.contains(".xspf"))
			return true;
		else if(file.contains(".asx") || file.contains(".asp"))
			return true;
		else if(file.contains(".cue")) 
			return true;
	}
	return false;
}

bool Tagger::garbageDetected(QUrl url)
{
	QFileInfo file(ToLocalFile(url));
	if(file.fileName() == "." || file.fileName() == "..") return true;
	QString suf = file.suffix().toLower();
	QString base = file.completeBaseName().toLower();
	if(file.isFile()) {
		if(suf == "jpg" ||
		   suf == "png" ||
		   suf == "txt" ||
		   suf == "doc" ||
		   suf == "log" ||
		   suf.startsWith("htm") ||
		   !suf.size() ||
		   !base.size())
			{
				return true;
			}
	}
	return false;
}

QString Tagger::getFileType(QUrl url)
{
	// set file type from url
	QString lf = ToLocalFile(url);
	if(lf.size()) {
		QFreeDesktopMime mime;
		return mime.fromFile(lf);
	} else {
		return url.scheme();
	}
}
