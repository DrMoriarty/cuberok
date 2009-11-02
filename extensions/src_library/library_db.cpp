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

#include "library_db.h"
#include <QtGui>
#include <QtSql>
#include "global.h"
#include "interfaces.h"

#define DB_VERSION 0

QSqlDatabase db;

LibraryDB::LibraryDB() :QObject(0)
{
    QMutexLocker locker(&lock);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath()+"/.cuberok/library.db");
    if(QFile::exists(db.databaseName())) {
        if(!db.open()) {
            qDebug("Can not open library database");
            proxy->error("Can not open library database");
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
                proxy->error("Wrong database version -" + QString::number(ver));
            }
        }
    } else {
        if(!QDir().mkpath(QDir::homePath()+"/.cuberok") || !db.open()) {
            qDebug("Can not create database");
            proxy->error("Can not create database");
            open = false;
        } else {
            QSqlQuery q0("create table Version (value integer)", db);
            QSqlQuery q1("insert into Version (value) values ("+QString::number(DB_VERSION)+")");
            QSqlQuery q2("create table Playlist (ID integer primary key autoincrement, value varchar(200), refs integer, rating integer, art varchar(250), list varchar(250))", db);
            open = true;
        }
    }
    if(open) proxy->message("LibraryDB ready");
}

LibraryDB::~LibraryDB()
{
    db.close();
}

bool LibraryDB::updateDatabase(int fromver)
{
    switch (fromver) {
    case 0: {
	}
    }
    proxy->message("LibraryDB update from version "+QString::number(fromver));
    QSqlQuery q1("delete from Version");
    QSqlQuery q2("insert into Version (value) values ("+QString::number(DB_VERSION)+")");
    return true;
}

LibraryDB& LibraryDB::Self()
{
    static QMutex mutex;
    QMutexLocker locker(&mutex);
    static LibraryDB* instance = new LibraryDB();
    return *instance;
}

int LibraryDB::AddPlaylist(QString list)
{
    if(!open) return 0;
    QMutexLocker locker(&lock);
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

void LibraryDB::RemovePlaylist(QString list)
{
    if(!open) return;
    QMutexLocker locker(&lock);
    QSqlQuery q("", db);
    q.prepare("delete from Playlist where value = :val");
    q.bindValue(":val", list);
    q.exec();
}

void LibraryDB::RenamePlaylist(QString oldval, QString newval)
{
    if(!open) return;
    QMutexLocker locker(&lock);
    QSqlQuery q("", db);
    q.prepare("update Playlist set value = :newval where value = :oldval");
    q.bindValue(":oldval", oldval);
    q.bindValue(":newval", newval);
    q.exec();
}

QList<struct LibraryDB::Attr> LibraryDB::Playlists(QString *patt)
{
    QMutexLocker locker(&lock);
    if(!open) return QList<struct LibraryDB::Attr>();
    QList<struct LibraryDB::Attr> res;
    QSqlQuery q("", db);
	if(patt) {
		q.prepare("select value, refs, art from Playlist where value like :pattern order by value ASC");
		q.bindValue(":pattern", QString("%")+*patt+QString("%"));
	} else q.prepare("select value, refs, art from Playlist order by value ASC");
    q.exec();
    while(q.next()) {
        struct Attr attr;
        attr.name = q.value(0).toString();
        attr.refs = q.value(1).toString().toInt();
        attr.rating = 0;//q.value(2).toString().toInt();
        attr.art = q.value(2).toString();
        res << attr;
    }
    return res;
}

void LibraryDB::ArtForPlaylist(QString val, QString art)
{
    QMutexLocker locker(&lock);
    if(!open) return;
    QSqlQuery q("", db);
    q.prepare("update Playlist set art = :art where value = :val");
    q.bindValue(":art", art);
    q.bindValue(":val", val);
    q.exec();
}
