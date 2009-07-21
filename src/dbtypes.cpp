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

#include <QtSql.h>
#include "dbtypes.h"
#include "database.h"

#define db Database::Self().getDB()

DBDBAttribute::DBAttribute(QString name, int refs, int rating, QString art, QString table, int id):
	_value(name), _art(art), _table(table), _refs(refs), _rating(rating), _id(id)
{
}

DBAttribute::DBAttribute(QString table, int id):
	_value(""), _art(""), _table(table), _refs(0), _rating(0), _id(id)
{
	if(Database::Self().opened()) {
		QSqlQuery q("", db);
		q.prepare("select value, art, refs, rating from "+table+" where ID = "+QString::number(id));
		q.exec();
		if(q.next()) {
			_value = q.value(0).toString();
			_art = q.value(1).toString();
			_refs = q.value(2).toString().toInt();
			_rating = q.value(3).toString().toInt();
		}
	}
}

DBAttribute::~DBAttribute()
{
}

QString DBAttribute::name()
{
	return _value;
}

bool DBAttribute::rename(QString newval)
{
	if(!Database::Self().opened() || !_id || !_table.size()) return false;
	QSqlQuery q("", db);
	q.prepare("select ID, art from "+_table+" where value = :newval");
	q.bindValue(":newval", newval);
	q.exec();
	if(q.next()) {
		bool ok;
		int newID = q.value(0).toInt(&ok);
		QString newArt = q.value(1).toString();
		if(ok) {
			q.prepare("update Song set "+_table+" = "+QString::number(newID)+" where "+_table+" = "+QString::number(oldID));
			q.exec();
			Database::RefAttribute(_table, newID, refs, rating);
			if(!newArt.size() && art.size())
				Database::ArtForAttribute(_table, newID, oldArt);
			remove();
			_id = newID;
		}
	} else {
		q.prepare("update "+_table+" set value = :newval where ID = "+QString::number(_id));
		q.bindValue(":newval", newval);
		q.exec();
	}
	return true;
}

int DBAttribute::refs()
{
	return _refs;
}

int DBAttribute::rating()
{
	return _rating;
}

bool DBAttribute::update(int refs, int rating)
{
	if(!Database::Self().opened() || !_id || !_table.size()) return false;
	QSqlQuery q("", db);
	_refs += refs;
	rating += rating;
	if(_refs > 0) {
		q.prepare("update "+_table+" set refs = "+QString::number(_refs)+", rating = "+QString::number(_rating)+" where ID = "+QString::number(_id));
		q.exec();
	} else {
		q.prepare("delete from "+_table+" where ID = "+QString::number(_id));
		q.exec();
	}
	return true;
}

QString DBAttribute::art()
{
	return _art;
}

void DBAttribute::setArt()
{
	if(!Database::Self().opened() || !_id || !_table.size()) return false;
	QSqlQuery q("", db);
	q.prepare("update "+_table+" set art = :art where ID = "+QString::number(_id));
	q.bindValue(":art", art);
	q.exec();
	_art = art;
}

bool DBAttribute::remove()
{
	if(!Database::Self().opened() || !_id || !_table.size()) return false;
	QSqlQuery q("", db);
	q.prepare("delete from Song where "+_table+" = "+QString::number(_id));
	q.exec();
	QSqlQuery q1("delete from "+_table+" where ID = "+QString::number(_id), db);
	_id = 0;
	return true;
}

/*
 *  end attributes
 */

DBGDBGenre::DBGenre(int id) : DBAttribute("Genre", id)
{
}

DBArtist::DBArtist(int id) : DBAttribute("Artist", id)
{
}

bool DBArtist::rename(QString newval)
{
	int oldid = _id;
	bool r = DBAttribute::rename(newval);
	if(oldid != _id) {
		QSqlQuery q("update Album set artist = "+QString::number(_id)+" where artist = "+QString::number(oldid), db);
	}
	return r;
}

DBAlbum::DBAlbum(int id) : DBAttribute("Album", id)
{
	QSqlQuery q("select artist from Album where ID = "+QString::number(_id));
	if(q.next()) {
		_artist = q.value(0).toString();
	}
}

DBAlbum::~DBAlbum()
{
}

bool DBAlbum::rename(QString newval)
{
	if(!Database::Self().opened() || !_id || !_table.size()) return false;
	QSqlQuery q("", db);
	q.prepare("select ID, art from "+_table+" where value = :newval and artist = "+QString::number(_artist));
	q.bindValue(":newval", newval);
	q.exec();
	if(q.next()) {
		bool ok;
		int newID = q.value(0).toInt(&ok);
		QString newArt = q.value(1).toString();
		if(ok) {
			q.prepare("update Song set "+_table+" = "+QString::number(newID)+" where "+_table+" = "+QString::number(oldID));
			q.exec();
			Database::RefAttribute(_table, newID, refs, rating);
			if(!newArt.size() && art.size())
				Database::ArtForAttribute(_table, newID, oldArt);
			remove();
			_id = newID;
		}
	} else {
		q.prepare("update "+_table+" set value = :newval where ID = "+QString::number(_id));
		q.bindValue(":newval", newval);
		q.exec();
	}
	return true;
}

int DBAlbum::artist()
{
	return _artist;
}

DBSong::DBSong(int id): _id(id), _genre(0), _artist(0), _album(0)
{
	if(Database::Self().opened()) {
		QSqlQuery q("", db);
		QString com = "select File, Title, Artist, Album, Comment, Genre, Track, Year, Rating, Length from Song where ID = "+QString::number(_id);
		q.prepare(com);
		q.exec();
		if(q.next()) {
			bool ok;
			_tags.url = QUrl(q.value(0).toString());
			_tags.title = q.value(1).toString();
			_artist = q.value(2).toInt(&ok);
			if(ok) _tags.artist = Database::GetArtist(_artist);
			_album = q.value(3).toInt(&ok);
			if(ok) _tags.album = Database::GetAlbum(_album);
			_tags.comment = q.value(4).toString();
			_genre = q.value(5).toInt(&ok);
			if(ok) _tags.genre = Database::GetGenre(_genre);
			_tags.track = q.value(6).toInt(&ok);
			_tags.year = q.value(7).toInt(&ok);
			_tags.rating = q.value(8).toInt(&ok);
			_tags.slength = q.value(9).toString();
			_tags.dbindex = _id;
			return true;
		}
	}	
}

DBSong::DBSong(const TagEntry &tags) : _id(tags.dbindex), _genre(0), _artist(0), _album(0), _tags(tags)
{
}

const TagEntry &DBSong::tags()
{
	return _tags;
}

bool DBSong::setTags(const TagEntry &tags)
{
	if(_id != tags.dbindex) {
		_tags = tags;
		_id = tags.dbindex;
	} else {
		if(tags.genre != _tags.genre)
			Database::RefAttribute("Genre", _genre, -1, -_tags.rating);
		if(tags.artist != _tags.artist)
			Database::RefAttribute("Artist", _artist, -1, -_tags.rating);
		if(tags.album != _tags.album)
			Database::RefAttribute("Album", _album, -1, -_tags.rating);
	}
}
