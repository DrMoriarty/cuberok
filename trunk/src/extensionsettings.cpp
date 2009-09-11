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
	setAttribute(Qt::WA_DeleteOnClose);
	vboxLayout = new QVBoxLayout(this);
	vboxLayout->setContentsMargins(0,0,0,0);
	vboxLayout->setSpacing(2);
	tabs = new QTabWidget(this);
	vboxLayout->addWidget(tabs);
	/*newButton = new QToolButton();
	closeButton = new QToolButton();
	newButton->setIcon(QIcon(":/icons/newtab.png"));
	closeButton->setIcon(QIcon(":/icons/deltab.png"));
	connect(newButton, SIGNAL(pressed()), this, SLOT(addList()));
	connect(closeButton, SIGNAL(pressed()), this, SLOT(delList()));
	tabs->setCornerWidget(newButton, Qt::TopLeftCorner);
	tabs->setCornerWidget(closeButton, Qt::TopRightCorner);*/
#if QT_VERSION >= 0x040500
	tabs->setMovable(true);
#endif

	foreach(Extension *ex, ExtensionProxy::Self().extensionList()) {
		if(ex) {
			QWidget *setup = ex->getSetupWidget();
			//if(setup) tabs->addTab(setup, setup->windowIcon(), ex->getName());
		}
	}
	tabs->setCurrentIndex(0);
}
