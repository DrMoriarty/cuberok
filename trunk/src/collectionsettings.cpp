/* Cuberok
 * Copyright (C) 2009 Vasiliy Makarov <drmoriarty.0@gmail.com>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "collectionsettings.h"
#include "playlistsettings.h"
#include "database.h"
#include "collectionfiller.h"

CollectionSettings::CollectionSettings(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
	ui.lineEdit_path->setText(PLSet.collectionPath);
}

CollectionSettings::~CollectionSettings()
{
	PLSet.collectionPath = ui.lineEdit_path->text();
}

void CollectionSettings::cleanup()
{
	Database::Self().cleanUpGenres();
	Database::Self().cleanUpArtists();
	Database::Self().cleanUpAlbums();
	int count = 0;
	QList<QString> files = Database::Self().Songs();
	foreach(QString file, files) {
		if(!QFile::exists(file)) {
			Database::Self().RemoveFile(file);
			count ++;
		}
	}
	QMessageBox::information(this, tr("Operation complete"), tr("%1 link(s) has been removed from the collection.").arg(QString::number(count)));
	accept();
}

void CollectionSettings::scan()
{
	QList<QUrl> urls;
	urls << QUrl::fromLocalFile(ui.lineEdit_path->text());
	CollectionFiller * cf = new CollectionFiller(urls, M_SONG, "");
	//connect(cf, SIGNAL(finished()), this, SLOT(update()));
	cf->start();
	PLSet.collectionPath = ui.lineEdit_path->text();
	accept();
}

void CollectionSettings::selectPath()
{
	QString path = QFileDialog::getExistingDirectory(this, tr("Select your music folder"), QDir::homePath());
	if(path.size()) {
		ui.lineEdit_path->setText(path);
	}
}
