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

#include "firststartwizard.h"
//#include "collectionfiller.h"
//#include "importcollection.h"
#include "extensionproxy.h"

FirstStartWizard::FirstStartWizard(QWidget *parent) :QWizard(parent)
{
	ui.setupUi(this);
	ui.lineEdit_import->setText(QDir::homePath() + "/.kde/share/apps/amarok/collection.db");
	ui.lineEdit_collect->setText(QDir::homePath());
	connect(this, SIGNAL(accepted()), this, SLOT(doSomething()));
}

FirstStartWizard::~FirstStartWizard()
{
}

void FirstStartWizard::selectFolderForScan()
{
	QString path = QFileDialog::getExistingDirectory(this, tr("Select your music folder"), QDir::homePath());
	if(path.size()) {
		ui.lineEdit_collect->setText(path);
	}
}

void FirstStartWizard::selectFileForImport()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Select Amarok music collection"), QDir::homePath());
	if(path.size()) {
		ui.lineEdit_import->setText(path);
	}
}

 int FirstStartWizard::nextId() const
 {
     switch (currentId()) {
     case 1:  // selection
         if (ui.radioButton->isChecked()) {
             return 2;
         } else if (ui.radioButton_2->isChecked()) {
             return 3;
         } else if (ui.radioButton_3->isChecked()) {
			 return 4;
		 }
     case 2: // listen
     case 3: // collect
     case 4: // import
     default:
         return -1;
     }
 }

void FirstStartWizard::doSomething()
{
     switch (currentId()) {
     case 3: // collect
		 {
			 /*QList<QUrl> urls;
			 urls << QUrl::fromLocalFile(ui.lineEdit_collect->text());
			 CollectionFiller * cf = new CollectionFiller(urls, M_SONG, "");
			 //connect(cf, SIGNAL(finished()), this, SLOT(update()));
			 cf->start();
			 EProxy.setVariable("collectionPath", ui.lineEdit_collect->text());*/
			 EProxy.setVariable("FirstStartWizard_collectionPath", ui.lineEdit_collect->text());
		 }
		 break;
     case 4: // import
		 //ImportCollection::importCollection(ui.lineEdit_import->text(), true);
		 EProxy.setVariable("FirstStartWizard_importPath", ui.lineEdit_import->text());
		 break;
     case 1:  // selection
     case 2: // listen
     default:
         break;
     }
}
