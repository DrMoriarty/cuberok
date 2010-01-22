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

#include "importcollection.h"
//#include "database.h"
//#include "collectionfiller.h"
#include <QtSql>

ImportCollection::ImportCollection(QWidget *parent) : QDialog(parent)
{
	ui.setupUi(this);
	ui.lineEdit->setText(QDir::homePath() + "/.kde/share/apps/amarok/collection.db");
}

ImportCollection::~ImportCollection()
{
}

void ImportCollection::selectFile()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Select Amarok music collection"), QDir::homePath());
	if(path.size()) {
		ui.lineEdit->setText(path);
	}
}

void ImportCollection::import()
{
	QString amarokdb = ui.lineEdit->text();
	if(importCollection(amarokdb, true)) {
		accept();
	} else {
		reject();
	}
}

bool ImportCollection::importCollection(QString amarokdb, bool messages)
{
	if(!QFile::exists(amarokdb)) {
		if(messages) QMessageBox::warning(0, tr("File not found"), tr("File %1 doesn't exist").arg(amarokdb));
		return false;
	}
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(amarokdb);
    if(!db.open()) {
		QString err = tr("Can not open Amarok database from %1").arg(amarokdb);
		qDebug((const char*)err.toLocal8Bit());
		if(messages) QMessageBox::warning(0, tr("Database error"), err);
		return false;
	}
	QStringList uniq_paths;
	QSqlQuery q0("", db);
	q0.prepare("select devices.lastmountpoint, dir from directories left join devices on devices.id = deviceid order by dir asc");
	q0.exec();
	while(q0.next()) {
		QString path = q0.value(0).toString() + "/" + q0.value(1).toString();
		bool un = true;
		foreach(QString p, uniq_paths) {
			if(path.startsWith(p)) {
				un = false;
				break;
			}
		}
		if(un) uniq_paths << path;
	}
	QList<QUrl> urls;
	foreach(QString path, uniq_paths) {
		if(QDir(path).exists()) {
			QUrl url = QUrl::fromLocalFile(path);
			if(url.isValid()) urls << url;
		}
	}
	if(!urls.size()) {
		if(messages) QMessageBox::warning(0, tr("Surprise"), tr("There aren't any local folders in Amarok's collection."));
		return false;
	}
	//CollectionFiller * cf = new CollectionFiller(urls, M_SONG, "");
	//connect(cf, SIGNAL(finished()), this, SLOT(update()));
	//cf->start();
	return true;
}
