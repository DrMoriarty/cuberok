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

#include "database.h"
#include <QtGui>
#include "main.h"
#include "tagger.h"
#include "console.h"

#define DB_VERSION 2

Database::Database() : subset(false)
{
	QMutexLocker locker(&lock);
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(QDir::homePath()+"/.cuberok/collection.db");
	if(QFile::exists(db.databaseName())) {
		if(!db.open()) {
			qDebug("Can not open database");
			Console::Self().error("Can not open database");
			open = false;
		} else {
			open = true;
			QSqlQuery q1("select value from Version", db);
			int ver = 0;
			if(q1.next()) ver = q1.value(0).toString().toInt();
			if(ver < DB_VERSION) {
				open = updateDatabase(ver);
				if(!open) db.close();
			} else if(ver > DB_VERSION) {
				open = false;
				db.close();
				qDebug("Wrong database version (%d)", ver);
				Console::Self().error("Wrong database version -" + QString::number(ver));
			}
		}
	} else {
		if(!QDir().mkpath(QDir::homePath()+"/.cuberok") || !db.open()) {
			qDebug("Can not create database");
			Console::Self().error("Can not create database");
			open = false;
		} else {
			QSqlQuery q0("create table Artist (ID integer primary key autoincrement, value varchar(200), refs integer, rating integer, art varchar(250))", db);
			QSqlQuery q1("create table Album (ID integer primary key autoincrement, value varchar(200), refs integer, rating integer, art varchar(250))", db);
			QSqlQuery q2("create table Genre (ID integer primary key autoincrement, value varchar(200), refs integer, rating integer, art varchar(250))", db);
			//QSqlQuery q3("create table Mark (ID integer primary key autoincrement, value varchar(200), refs integer, rating integer)", db);
			QSqlQuery q4("create table Song (ID integer primary key autoincrement, File varchar(250), Track integer, Title varchar(200), Artist integer, Album integer, Genre integer, Year integer, Comment varchar(200), Length varchar(20), Rating integer)", db);
			QSqlQuery q5("create table Version (value integer)", db);
			QSqlQuery q6("insert into Version (value) values ("+QString::number(DB_VERSION)+")");
			QSqlQuery q7("create table Playlist (ID integer primary key autoincrement, value varchar(200), refs integer, rating integer, art varchar(250), list varchar(250))", db);
			open = true;
		}
	}
	if(open) Console::Self().message("Database ready");
}

Database::~Database()
{
	db.close();
}

bool Database::updateDatabase(int fromver)
{
	switch (fromver) {
	case 0: {
		QSqlQuery q0("create table Version (value integer)", db);
		//QSqlQuery q1("insert into Version (value) values ("+QString::number(DB_VERSION)+")");
		QSqlQuery q3("alter table Artist add column art varchar(250)", db);
		QSqlQuery q4("alter table Album add column art varchar(250)", db);
		QSqlQuery q5("alter table Genre add column art varchar(250)", db);
		QSqlQuery q6("alter table Song drop column Mark", db);
		QSqlQuery q2("drop table Mark", db);
		qDebug("Update database from version 0");
		Console::Self().message("Database update from version "+QString::number(fromver));
	}
	case 1: {
		QSqlQuery q0("create table Playlist (ID integer primary key autoincrement, value varchar(200), refs integer, rating integer, art varchar(250), list varchar(250))", db);
		qDebug("Update database from version 1");
		Console::Self().message("Database update from version "+QString::number(fromver));
	}
	}
	QSqlQuery q1("delete from Version");
	QSqlQuery q2("insert into Version (value) values ("+QString::number(DB_VERSION)+")");
	return true;
}

Database& Database::Self()
{
	static QMutex mutex;
	QMutexLocker locker(&mutex);
	//mutex.lock();
 	//static Database* instance = 0;
	static Database instance;
 	//if(!instance) instance = new Database();
	//mutex.unlock();
 	//return *instance;
	//Database &db = instance();
	return instance;
}

int Database::AddFile(QString file)
{
	if(!open) return 0;
	QMutexLocker locker(&lock);
	QSqlQuery q0("", db);
	q0.prepare("select ID from Song where File = :file");
	q0.bindValue(":file", file);
	q0.exec();
	if(q0.next()) return q0.value(0).toString().toInt();
	QString title, artist, album, comment, genre, length;
	int track, year;
	if(Tagger::readTags(file, title, artist, album, comment, genre, track, year, length)) {
	//	TagLib::FileRef fr(file.toLocal8Bit().constData());
		int art = AddArtist(artist);
		int alb = AddAlbum(album);
		int gen = AddGenre(genre);
		//QString com = QString("insert into Song (File, Track, Title, Artist, Album, Genre, Year, Comment) values ('%1', %2, '%3', %4, %5, %6, %7, '%8')")
		//.arg(file, QString::number(fr.tag()->track()), QS(fr.tag()->title()), QString::number(art), QString::number(alb), QString::number(gen), QString::number(fr.tag()->year()), QS(fr.tag()->comment()));
		QString com = QString("insert into Song (File, Track, Title, Artist, Album, Genre, Year, Comment, Length) values (:file, %1, :title, %2, %3, %4, %5, :comment, :length) ")
		.arg(QString::number(track), QString::number(art), QString::number(alb), QString::number(gen), QString::number(year));
		QSqlQuery q("", db);
		q.prepare(com);
		q.bindValue(":file", file);
		q.bindValue(":title", title);
		q.bindValue(":comment", comment);
		q.bindValue(":length", length);
		q.exec();
		QSqlQuery q1("", db);
		q1.prepare("select ID from Song where File = :file");
		q1.bindValue(":file", file);
		q1.exec();
		if (q1.next()) {
			RefAttribute(nArtist, art, 1, 0);
			RefAttribute(nAlbum, alb, 1, 0);
			RefAttribute(nGenre, gen, 1, 0);
			return q1.value(0).toString().toInt();
		}
	}
	return -1;
}

int Database::AddAttribute(QString attr, QString val)
{
	if(!open) return 0;
	if(!val.length()) val = " ";
	QSqlQuery q("", db);
	q.prepare("select ID from "+attr+" where value = :val");
	q.bindValue(":val", val);
	q.exec();
	if( !q.next() ) {
		q.prepare("insert into "+attr+" (value) values (:val)");
		q.bindValue(":val", val);
		q.exec();
		if(q.numRowsAffected() < 1) return -1;
		q.prepare("select ID from "+attr+" where value = :val");
		q.bindValue(":val", val);
		q.exec();
		q.next();
	}
	return q.value(0).toString().toInt();
}

int Database::AddArtist(QString artist)
{
	return AddAttribute(nArtist, artist);
}

int Database::AddAlbum(QString album)
{
	return AddAttribute(nAlbum, album);
}

int Database::AddGenre(QString genre)
{
	return AddAttribute(nGenre, genre);
}

// int Database::AddMark(QString mark)
// {
// 	return AddAttribute(nMark, mark);
// }

void Database::RefAttribute(const QString attr, int id, int v, int r)
{
	if(!open) return;
	QSqlQuery q("", db);
	q.prepare("select refs, rating from "+attr+" where ID = "+QString::number(id));
	q.exec();
	if( q.next() ) {
		int refs = q.value(0).toString().toInt() + v;
		int rating = q.value(1).toString().toInt() + r;
		if(refs > 0) {
			q.prepare("update "+attr+" set refs = "+QString::number(refs)+", rating = "+QString::number(rating)+" where ID = "+QString::number(id));
			q.exec();
		} else {
			q.prepare("delete from "+attr+" where ID = "+QString::number(id));
			q.exec();
		}
	}
}

void Database::RemoveFile(QString file)
{
	if(!open) return;
	QSqlQuery q("", db);
	q.prepare("select Artist, Album, Genre, Rating from Song where File = :file");
	q.bindValue(":file", file);
	q.exec();
	if( q.next() ) {
		int rating = q.value(3).toString().toInt();
		RefAttribute(nArtist, q.value(0).toString().toInt(), -1, -rating);
		RefAttribute(nAlbum, q.value(1).toString().toInt(), -1, -rating);
		RefAttribute(nGenre, q.value(2).toString().toInt(), -1, -rating);
		//RefAttribute(nMark, q.value(3).toString().toInt(), -1, -rating);
		q.prepare("delete from Song where File = :file");
		q.bindValue(":file", file);
		q.exec();
	}
}

void Database::RemoveAttribute(const QString attr, QString val)
{
	if(!open) return;
	int id = AddAttribute(attr, val);
	if(id > 0) {
		QSqlQuery q("", db);
		q.prepare("select File from Song where "+attr+" = "+QString::number(id));
		q.exec();
		while(q.next()) {
			RemoveFile(q.value(0).toString());
		}
		//QSqlQuery q0("delete from Song where "+attr+" = "+QString::number(id), db);
		QSqlQuery q1("delete from "+attr+" where ID = "+QString::number(id), db);
	}
}

void Database::RemoveArtist(QString artist)
{
	RemoveAttribute(nArtist, artist);
}

void Database::RemoveAlbum(QString album)
{
	RemoveAttribute(nAlbum, album);
}

void Database::RemoveGenre(QString genre)
{
	RemoveAttribute(nGenre, genre);
}

// void Database::RemoveMark(QString mark)
// {
// 	RemoveAttribute(nMark, mark);
// }

void Database::RenameAttribute(const QString attr, QString oldval, QString newval)
{
	if(!open) return;
	QSqlQuery q("", db);
	q.prepare("select ID from "+attr+" where value = :newval");
	q.bindValue(":newval", newval);
	q.exec();
	if(q.next()) {
		bool ok;
		int newID = q.value(0).toInt(&ok);
		if(ok) {
			int oldID = AddAttribute(attr, oldval);
			q.prepare("update Song set "+attr+" = "+QString::number(newID)+" where "+attr+" = "+QString::number(oldID));
			q.exec();
			q.prepare("select refs, rating from "+attr+" where ID = "+QString::number(oldID));
			q.exec();
			if(q.next()) {
				int oldref = q.value(0).toString().toInt();
				int oldrat = q.value(1).toString().toInt();
				RefAttribute(attr, newID, oldref, oldrat);
			}
			RemoveAttribute(attr, oldval);
		}
	} else {
		q.prepare("update "+attr+" set value = :newval where value = :oldval");
		q.bindValue(":oldval", oldval);
		q.bindValue(":newval", newval);
		q.exec();
	}
}

void Database::RenameArtist(QString oldval, QString newval)
{
	RenameAttribute(nArtist, oldval, newval);
}

void Database::RenameAlbum(QString oldval, QString newval)
{
	RenameAttribute(nAlbum, oldval, newval);
}

void Database::RenameGenre(QString oldval, QString newval)
{
	RenameAttribute(nGenre, oldval, newval);
}

// void Database::RenameMark(QString oldval, QString newval)
// {
// 	RenameAttribute(nMark, oldval, newval);
// }

QList<struct Database::Attr> Database::Attributes(const QString attr, QString *patt)
{
	if(!open) return QList<struct Database::Attr>();
	QMutexLocker locker(&lock);
	QList<struct Database::Attr> res;
	QSqlQuery q("", db);
	if(subset) {
		QString com = "select distinct A.value, A.refs, A.rating/A.refs as WR, A.art from Song left join "+attr+" as A on Song."+attr+"=A.ID where "+ssFilter;
		if(patt)  com += " and A.value like :pattern ";
		com += " order by WR DESC, A.value ASC";
		q.prepare(com);
		if(patt) q.bindValue(":pattern", QString("%")+*patt+QString("%"));
	} else {
		if(patt) {
			q.prepare("select value, refs, rating/refs as WR, art from "+attr+" where value like :pattern order by WR DESC, value ASC");
			q.bindValue(":pattern", QString("%")+*patt+QString("%"));
		} else q.prepare("select value, refs, rating/refs as WR, art from "+attr+" order by WR DESC, value ASC");
	}
	q.exec();
	while(q.next()) {
		struct Attr attr;
		attr.name = q.value(0).toString();
		attr.refs = q.value(1).toString().toInt();
		attr.rating = q.value(2).toString().toInt();
		attr.art = q.value(3).toString();
		res << attr;
	}
	return res;
}

QList<struct Database::Attr> Database::Artists(QString *patt)
{
	return Attributes(nArtist, patt);
}

QList<struct Database::Attr> Database::Albums(QString *patt)
{
	return Attributes(nAlbum, patt);
}

QList<struct Database::Attr> Database::Genres(QString *patt)
{
	return Attributes(nGenre, patt);
}

// QList<struct Database::Attr> Database::Marks(QString *patt)
// {
// 	return Attributes(nMark, patt);
// }

void Database::ArtForAttribute(const QString attr, QString val, QString art)
{
	if(!open) return;
	QSqlQuery q("", db);
	q.prepare("update "+attr+" set art = :art where value = :val");
	q.bindValue(":art", art);
	q.bindValue(":val", val);
	q.exec();
}

void Database::ArtForArtist(QString val, QString art)
{
	return ArtForAttribute(nArtist, val, art);
}

void Database::ArtForAlbum(QString val, QString art)
{
	return ArtForAttribute(nAlbum, val, art);
}

void Database::ArtForGenre(QString val, QString art)
{
	return ArtForAttribute(nGenre, val, art);
}

QList<QString> Database::Songs(QString *ar, QString *al, QString *ge, QString *so)
{
	if(!open) return QList<QString>();
	QMutexLocker locker(&lock);
	QSqlQuery q("", db);
	QString com = "select File from Song ";
	if(ar || al || ge || so || subset) {
		com += " where ";
		bool andf = false;
		if(subset) com += ssFilter, andf = true;
		if(ar) { 
			if(andf) com += " and ";
			if(ar->length() > 0) com += " Artist = :ar ";
			else com += " Artist is null ";
			andf = true;
		}
		if(al) {
			if(andf) com += " and ";
			if(al->length() > 0) com += " Album = :al ";
			else com += " Album is null ";
			andf = true;
		}
		if(ge) {
			if(andf) com += " and ";
			if(ge->length() > 0) com += " Genre = :ge ";
			else com += " Genre is null ";
			andf = true;
		}
		if(so) {
			if(andf && so->length()) com += " and ";
			if(so->length()) com += " Title like :so ";
			andf = true;
		}
	}
	com += " order by Artist, Album, Track, Title";
	q.prepare(com);
	if(ar && ar->length() > 0) q.bindValue(":ar", AddArtist(*ar));
	if(al && al->length() > 0) q.bindValue(":al", AddAlbum(*al));
	if(ge && ge->length() > 0) q.bindValue(":ge", AddGenre(*ge));
	if(so && so->length() > 0) q.bindValue(":so", "%"+(*so)+"%");
	q.exec();
	
	QList<QString> res;
	while(q.next()) {
		res << q.value(0).toString();
	}
	return res;
}

QString Database::GetArtist(int id)
{
	if(!open) return "";
	QSqlQuery q("select value from Artist where ID = "+QString::number(id), db);
	if(q.next()) return q.value(0).toString();
	else return "";
}

QString Database::GetAlbum(int id)
{
	if(!open) return "";
	QSqlQuery q("select value from Album where ID = "+QString::number(id), db);
	if(q.next()) return q.value(0).toString();
	else return "";
}

QString Database::GetGenre(int id)
{
	if(!open) return "";
	QSqlQuery q("select value from Genre where ID = "+QString::number(id), db);
	if(q.next()) return q.value(0).toString();
	else return "";
}

// QString Database::GetMark(int id)
// {
// 	if(!open) return "";
// 	QSqlQuery q("select value from Mark where ID = "+QString::number(id), db);
// 	if(q.next()) return q.value(0).toString();
// 	else return "";
// }

bool Database::GetTags(QString file, QString &title, QString &artist, QString &album, QString &comment, QString &genre, int &track, int &year, int &rating, QString &length)
{
	if(!open) return false;
	QMutexLocker locker(&lock);
	QSqlQuery q("", db);
	QString com = "select Title, Artist, Album, Comment, Genre, Track, Year, Rating, Length from Song where File = :file";
	q.prepare(com);
	q.bindValue(":file", file);
	q.exec();
	if(q.next()) {
		int artistID, albumID, genreID;
		bool ok;
		title = q.value(0).toString();
		artistID = q.value(1).toInt(&ok);
		if(ok) artist = GetArtist(artistID);
		albumID = q.value(2).toInt(&ok);
		if(ok) album = GetAlbum(albumID);
		comment = q.value(3).toString();
		genreID = q.value(4).toInt(&ok);
		if(ok) genre = GetGenre(genreID);
		track = q.value(5).toInt(&ok);
		year = q.value(6).toInt(&ok);
		rating = q.value(7).toInt(&ok);
		length = q.value(8).toString();
		return true;
	}
	return false;
}

bool Database::SetTags(QString file, QString title, QString artist, QString album, QString comment, QString genre, int track, int year, int rating)
{
	if(!open) return false;
	QMutexLocker locker(&lock);
	QSqlQuery q("", db);
	q.prepare("select Artist, Album, Genre, Rating from Song where File = :file");
	q.bindValue(":file", file);
	q.exec();
	if(q.next()) {
		int _artistID, _albumID, _genreID, _rating;
		bool ok;
		_artistID = q.value(0).toInt(&ok);
		_albumID = q.value(1).toInt(&ok);
		_genreID = q.value(2).toInt(&ok);
		_rating  = q.value(3).toInt(&ok);
		int artistID, albumID, genreID;
		artistID = AddArtist(artist);
		albumID = AddAlbum(album);
		genreID = AddGenre(genre);
		if(_artistID != artistID) {
			RefAttribute(nArtist, _artistID, -1, -_rating);
			RefAttribute(nArtist, artistID, 1, rating);
		} else RefAttribute(nArtist, artistID, 0, rating - _rating);
		if(_albumID != albumID) {
			RefAttribute(nAlbum, _albumID, -1, -_rating);
			RefAttribute(nAlbum, albumID, 1, rating);
		} else RefAttribute(nAlbum, albumID, 0, rating - _rating);
		if(_genreID != genreID) {
			RefAttribute(nGenre, _genreID, -1, -_rating);
			RefAttribute(nGenre, genreID, 1, rating);
		} else RefAttribute(nGenre, genreID, 0, rating - _rating);
		q.prepare("update Song set Title = :title, Artist = "+QString::number(artistID)+", Album = "+QString::number(albumID)+", Comment = :comment, Genre = "+QString::number(genreID)+", Track = "+QString::number(track)+", Year = "+QString::number(year)+", Rating = "+QString::number(rating)+" where File = :file");
		q.bindValue(":title", title);
		q.bindValue(":comment", comment);
		q.bindValue(":file", file);
		q.exec();
		return q.numRowsAffected() > 0;
	}
	return false;
}

// bool Database::SetMark(QString file, QString mark)
// {
// 	if(!open) return false;
// 	QSqlQuery q("", db);
// 	q.prepare("select Mark from Song where File = :file");
// 	q.bindValue(":file", file);
// 	q.exec();
// 	if(q.next()) {
// 		bool ok;
// 		int markID = q.value(0).toInt(&ok);
// 		if(ok) RefAttribute(nMark, markID, -1, 0);
// 		markID = AddMark(mark);
// 		q.prepare("update Song set Mark = "+QString::number(markID)+ " where File = :file");
// 		q.bindValue(":file", file);
// 		q.exec();
// 		RefAttribute(nMark, markID, 1, 0);
// 		return true;
// 	}
// 	return false;
// }

void Database::clearSubset()
{
	subset = false;
	ssAlbum = "";
	ssArtist = "";
	ssGenre = "";
// 	ssMark = "";
}

void Database::subsetAlbum(QString v)
{
	ssAlbum = v;
	if(ssAlbum.length()) subset = true;
	ssFilter = subsetFilter(); 
}

void Database::subsetArtist(QString v)
{
	ssArtist = v;
	if(ssArtist.length()) subset = true;
	ssFilter = subsetFilter(); 
}

void Database::subsetGenre(QString v)
{
	ssGenre = v;
	if(ssGenre.length()) subset = true;
	ssFilter = subsetFilter(); 
}

// void Database::subsetMark(QString v)
// {
// 	ssMark = v;
// 	if(ssMark.length()) subset = true;
// 	ssFilter = subsetFilter(); 
// }

QString Database::subsetFilter()
{
	QString filter;
	if(subset) {
		bool andf = false;
		if(ssAlbum.length()) filter += " Album = "+QString::number(AddAlbum(ssAlbum))+" ", andf = true;
		if(ssArtist.length()) filter += QString(andf?" and ":"")+" Artist = "+QString::number(AddArtist(ssArtist))+" ", andf = true;
		if(ssGenre.length()) filter += QString(andf?" and ":"")+" Genre = "+QString::number(AddGenre(ssGenre))+" ", andf = true;
// 		if(ssMark.length()) filter += QString(andf?" and ":"")+" Mark = "+QString::number(AddMark(ssMark))+" ", andf = true;
	}
	return filter;
}

int Database::AddPlaylist(QString list)
{
	//return AddAttribute(nPlaylist, artist);
	if(!open) return 0;
	QSqlQuery q("", db);
	QString val = list;
	q.prepare("select ID from Playlist where value = :val");
	q.bindValue(":val", val);
	q.exec();
	if( !q.next() ) {
		/*if(QFileInfo(list).exists()) {
			// real play list
			val = QFileInfo(list).baseName();
			q.prepare("insert into Playlist (value, list) values (:val, :list)");
			q.bindValue(":list", list);
			} else*/
			q.prepare("insert into Playlist (value) values (:val)");
		q.bindValue(":val", val);
		q.exec();
		if(q.numRowsAffected() < 1) return -1;
		q.prepare("select ID from Playlist where value = :val");
		q.bindValue(":val", val);
		q.exec();
		q.next();
	}
	return q.value(0).toString().toInt();
}

void Database::RemovePlaylist(QString list)
{
	if(!open) return;
	QSqlQuery q("", db);
	q.prepare("delete from Playlist where value = :val");
	q.bindValue(":val", list);
	q.exec();
}

void Database::RenamePlaylist(QString oldval, QString newval)
{
	if(!open) return;
	QSqlQuery q("", db);
	q.prepare("update Playlist set value = :newval where value = :oldval");
	q.bindValue(":oldval", oldval);
	q.bindValue(":newval", newval);
	q.exec();
}

QList<struct Database::Attr> Database::Playlists(QString *patt)
{
	return Attributes(nPlaylist, patt);
}

void Database::ArtForPlaylist(QString val, QString art)
{
	return ArtForAttribute(nArtist, val, art);
}

