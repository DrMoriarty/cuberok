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

#include "src_library.h"
#include "library_db.h"

Q_EXPORT_PLUGIN2(src_library, SrcLibrary) 

SrcLibrary::SrcLibrary() : Extension(), widget(0)
{
}

SrcLibrary::~SrcLibrary()
{
	//if(widget) delete widget;
}

bool SrcLibrary::prepare()
{
	QSettings set;
	if(proxy) {
		LibraryDB::Self(proxy).proxy = proxy;
		widget = new LibraryWidget(0, proxy);
	}
	return widget;
}

bool SrcLibrary::ready()
{
	return widget;
}

void SrcLibrary::update(int)
{
}

QString SrcLibrary::getName()
{
	return tr("Library");
}

QString SrcLibrary::getAuthor()
{
	return QString("DrMoriarty");
}

QString SrcLibrary::getDescription()
{
	return tr("This extension is a place for your playlists");
}

QWidget* SrcLibrary::getWidget()
{
	return widget;
}

ExtensionSetupWidget* SrcLibrary::getSetupWidget()
{
	return 0;
}

int SrcLibrary::getDisturbs()
{
	return DoNotDisturb;
}

void SrcLibrary::storeState()
{
	if(widget) widget->storeState();
}
