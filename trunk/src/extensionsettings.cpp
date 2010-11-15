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
#include "console.h"

DummyExtensionSetupWidget::DummyExtensionSetupWidget(QWidget *parent) : ExtensionSetupWidget(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
	QVBoxLayout *layout = new QVBoxLayout(this);
	QLabel* label = new QLabel(tr("This extension doesn't have any settings"), this);
	label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	layout->addWidget(label);
}

void DummyExtensionSetupWidget::storeState()
{}

ExtensionSettings::ExtensionSettings(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	foreach(Extension *ex, ExtensionProxy::Self().extensionList()) {
		if(ex) {
			QListWidgetItem *it;
			QWidget *setup = ex->getSetupWidget();
			if(setup) {
				if(setup->windowIcon().isNull())
					it = new QListWidgetItem(QIcon(":/icons/star.png"), ex->getName(), ui.listWidget);
				else 
					it = new QListWidgetItem(setup->windowIcon(), ex->getName(), ui.listWidget);
				ui.stackedWidget->addWidget(setup);
			} else {
				it = new QListWidgetItem(QIcon(":/icons/star.png"), ex->getName(), ui.listWidget);
				ui.stackedWidget->addWidget(new DummyExtensionSetupWidget(this));
			}
			it->setData(Qt::UserRole, ui.stackedWidget->count()-1);
			it->setData(Qt::UserRole+1, ex->getName());
			it->setData(Qt::UserRole+2, ex->getAuthor());
			it->setData(Qt::UserRole+3, ex->getDescription());
			it->setData(Qt::UserRole+4, ExtensionProxy::Self().isExtensionEnabled(ex->getName()));
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
	QString name = it->data(Qt::UserRole+1).toString();
	ui.label_Name->setText(name);
	ui.label_Author->setText(it->data(Qt::UserRole+2).toString());
	ui.label_Description->setText(it->data(Qt::UserRole+3).toString());
	//ui.checkBox_Enabled->setCheckState(ExtensionProxy::Self().isExtensionEnabled(name) ? Qt::Checked : Qt::Unchecked);
	ui.checkBox_Enabled->setCheckState(it->data(Qt::UserRole+4).toBool() ? Qt::Checked : Qt::Unchecked);
}

void ExtensionSettings::storeState()
{
	Console::Self().log("store extension settings");
	for(int i=0; i<ui.stackedWidget->count(); i++) {
		((ExtensionSetupWidget*)ui.stackedWidget->widget(i))->storeState();
	}
	for(int i=0; i< ui.listWidget->count(); i++) {
		QListWidgetItem* it = ui.listWidget->item(i);
		QString name = it->data(Qt::UserRole+1).toString();
		ExtensionProxy::Self().enableExtension(name, it->data(Qt::UserRole+4).toBool());
	}
}

void ExtensionSettings::enableExtension(int st)
{
	QListWidgetItem *it = ui.listWidget->currentItem();
	//QString name = it->data(Qt::UserRole+1).toString();
	if(st == Qt::Checked) {
		it->setData(Qt::UserRole+4, true);
		//ExtensionProxy::Self().enableExtension(name, true);
	} else {
		it->setData(Qt::UserRole+4, false);
		//ExtensionProxy::Self().enableExtension(name, false);
	}
}
