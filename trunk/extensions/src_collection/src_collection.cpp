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

#include "src_collection.h"
#include "database.h"

Q_EXPORT_PLUGIN2(src_collection, SrcCollection) 

SrcCollection::SrcCollection() : Extension(), widget(0)
{
}

SrcCollection::~SrcCollection()
{
	//if(widget) delete widget;
}

bool SrcCollection::prepare()
{
	QSettings set;
	if(proxy) {
		qDebug("Collection database");
		Database::Self(proxy).proxy = proxy;
		qDebug("Collection widget");
		widget = new CollectionWidget();
		qDebug("done");
	}
	return widget;
}

bool SrcCollection::ready()
{
	return widget;
}

void SrcCollection::update(int)
{
}

QString SrcCollection::getName()
{
	return tr("Collection");
}

QString SrcCollection::getAuthor()
{
	return QString("DrMoriarty");
}

QString SrcCollection::getDescription()
{
	return tr("The collection of your music files");
}

QWidget* SrcCollection::getWidget()
{
	return widget;
}

ExtensionSetupWidget* SrcCollection::getSetupWidget()
{
	CollectionSettings *set = new CollectionSettings();
	connect(set, SIGNAL(destroyed(QObject*)), this, SLOT(settingsUpdate(QObject*)));
	return set;
}

int SrcCollection::getDisturbs()
{
	return DoNotDisturb;
}

void SrcCollection::storeState()
{
	if(widget) widget->storeState();
}

void SrcCollection::settingsUpdate(QObject*)
{
}
