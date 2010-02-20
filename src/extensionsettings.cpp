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

#include "extensionsettings.h"
#include "extensionproxy.h"

ExtensionSettings::ExtensionSettings(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	foreach(Extension *ex, ExtensionProxy::Self().extensionList()) {
		if(ex) {
			QWidget *setup = ex->getSetupWidget();
			if(setup) {
				QListWidgetItem *it = new QListWidgetItem(setup->windowIcon(), ex->getName(), ui.listWidget);
				it->setData(Qt::UserRole, ui.stackedWidget->count());
				it->setData(Qt::UserRole+1, ex->getName());
				it->setData(Qt::UserRole+2, ex->getAuthor());
				it->setData(Qt::UserRole+3, ex->getDescription());
				ui.stackedWidget->addWidget(setup);
			}
		}
	}
	if(ui.stackedWidget->count() > 0) {
		ui.stackedWidget->setCurrentIndex(0);
		ui.listWidget->setCurrentRow(0);
	}
}

void ExtensionSettings::selectExtension(QListWidgetItem* it)
{
	ui.stackedWidget->setCurrentIndex(it->data(Qt::UserRole).toInt());
	ui.label_Name->setText(it->data(Qt::UserRole+1).toString());
	ui.label_Author->setText(it->data(Qt::UserRole+2).toString());
	ui.label_Description->setText(it->data(Qt::UserRole+3).toString());
}

void ExtensionSettings::storeState()
{
	qDebug("store extension settings");
	for(int i=0; i<ui.stackedWidget->count(); i++) {
		((ExtensionSetupWidget*)ui.stackedWidget->widget(i))->storeState();
	}
}
