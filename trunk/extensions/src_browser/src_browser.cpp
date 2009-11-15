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

#include "src_browser.h"

Q_EXPORT_PLUGIN2(src_browser, Src_Browser) 

Src_Browser::Src_Browser() : Extension(), widget(0)
{
}

Src_Browser::~Src_Browser()
{
	//if(widget) delete widget;
}

bool Src_Browser::prepare()
{
	QSettings set;
	if(proxy) widget = new BrowserViewer(proxy);
	return widget;
}

bool Src_Browser::ready()
{
	return widget;
}

void Src_Browser::update(int)
{
}

QString Src_Browser::getName()
{
	return tr("Internet Services");
}

QWidget* Src_Browser::getWidget()
{
	return widget;
}

QWidget* Src_Browser::getSetupWidget()
{
	return 0;
}

int Src_Browser::getDisturbs()
{
	return DoNotDisturb;
}

void Src_Browser::storeState()
{
	if(widget) widget->storeState();
}
