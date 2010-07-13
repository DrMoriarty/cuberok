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

#ifndef EXTENSIONSETTINGS_H
#define EXTENSIONSETTINGS_H

#include <QtGui>
#include "extensionproxy.h"
#include "ui_extensionsettings.h"

class DummyExtensionSetupWidget: public ExtensionSetupWidget
{
	Q_OBJECT
 public:
	DummyExtensionSetupWidget(QWidget *parent = 0);
	virtual void storeState();
};

class ExtensionSettings: public QWidget
{
	Q_OBJECT
 public:
	ExtensionSettings(QWidget* parent = 0);
 public slots:
	void selectExtension(QListWidgetItem*);
	void storeState();
	void enableExtension(int);
	
 private:
	Ui::ExtensionSettings ui;
};

#endif //EXTENSIONSETTINGS_H
