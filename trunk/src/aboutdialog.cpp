/* Cuberok
 * Copyright (C) 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>
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

#include "aboutdialog.h"
#include "player_manager.h"

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
{
	ui.setupUi(this);
	QString ver = QString("v %1.%2.%3").arg(QString::number(CUBEROK_VERSION_MAJ), QString::number(CUBEROK_VERSION_MIN), QString::number(CUBEROK_VERSION_BUI));
	ui.label_version->setText(ver);
	QString text = "Cuberok " + ver + "\n";
	text += QString("build: ") + __TIME__ + " " + __DATE__ + "\n";
	text += QString("Qt: ") + QT_VERSION_STR + " ";
#ifdef Q_WS_X11
	text += "X11";
#endif
#ifdef Q_WS_MAC
	text += "Mac OS";
#endif
#ifdef Q_WS_WIN
	text += "MS Windows";
#endif
	text += "\nCurrent plugin: " + PlayerManager::Self().name() +
		"\nAvailable plugins are:\n" + PlayerManager::Self().getInfo();
	ui.textEdit->setText(text);
}

AboutDialog::~AboutDialog()
{

}
