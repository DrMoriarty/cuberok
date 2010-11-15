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

#include "collectionsettings.h"
#include "extensionproxy.h"
#include "database.h"
#include "collectionfiller.h"
#include "importcollection.h"

CollectionSettings::CollectionSettings(QWidget *parent)
    : ExtensionSetupWidget(parent)
{
    ui.setupUi(this);
	ui.lineEdit_path->setText(EProxy.getVariable("collectionPath"));
	if(EProxy.hasVariable("slowFilter") && EProxy.getVariable("slowFilter") == "true") {
		ui.checkBox_fastFilter->setCheckState(Qt::Unchecked);
	} else {
		ui.checkBox_fastFilter->setCheckState(Qt::Checked);
	}
	if(EProxy.hasVariable("autoDownloadImages") && EProxy.getVariable("autoDownloadImages") == "true") {
		ui.checkBox_autoDownload->setCheckState(Qt::Checked);
	} else {
		ui.checkBox_autoDownload->setCheckState(Qt::Unchecked);
	}
}

CollectionSettings::~CollectionSettings()
{
	EProxy.setVariable("collectionPath", ui.lineEdit_path->text());
	EProxy.setVariable("slowFilter", ui.checkBox_fastFilter->checkState() == Qt::Checked ? "false" : "true");
	EProxy.setVariable("autoDownloadImages", ui.checkBox_autoDownload->checkState() != Qt::Checked ? "false" : "true");
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
}

void CollectionSettings::scan()
{
	QList<QUrl> urls;
	urls << QUrl::fromLocalFile(ui.lineEdit_path->text());
	CollectionFiller * cf = new CollectionFiller(urls, M_SONG, "");
	//connect(cf, SIGNAL(finished()), this, SLOT(update()));
	cf->start();
	EProxy.setVariable("collectionPath", ui.lineEdit_path->text());
	QMessageBox::information(this, tr("Operation was started in background"), tr("Scaning collection will take a couple minutes"));
}

void CollectionSettings::selectPath()
{
	QString path = QFileDialog::getExistingDirectory(this, tr("Select your music folder"), QDir::homePath());
	if(path.size()) {
		ui.lineEdit_path->setText(path);
	}
}

void CollectionSettings::importCollection()
{
	ImportCollection ic;
	ic.exec();
}

void CollectionSettings::storeState()
{
}
