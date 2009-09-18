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

#include "filebrowser.h"

Q_EXPORT_PLUGIN2(src_filebrowser, FileBrowser) 

FileBrowser::FileBrowser() : Extension(), widget(0)
{
}

FileBrowser::~FileBrowser()
{
	//if(widget) delete widget;
}

bool FileBrowser::prepare()
{
	QSettings set;
	if(proxy) widget = new FileBrowserWidget();
	return widget;
}

bool FileBrowser::ready()
{
	return widget;
}

void FileBrowser::update(int)
{
}

QString FileBrowser::getName()
{
	return tr("File Browser");
}

QWidget* FileBrowser::getWidget()
{
	return widget;
}

QWidget* FileBrowser::getSetupWidget()
{
	return 0;
}

int FileBrowser::getDisturbs()
{
	return DoNotDisturb;
}

void FileBrowser::storeState()
{
	if(widget) widget->storeState();
}
