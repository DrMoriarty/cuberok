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
		widget = new CollectionWidget(proxy);
		qDebug("done");
	}
	return widget;
}

bool SrcCollection::ready()
{
	return widget;
}

void SrcCollection::update(int d)
{
	if(d & DisturbOnRequest)
		widget->updateInfo();
	if(d & DisturbOnTags) {
		// read path to the image (if exist)
		proxy->beginTransaction();
		STags tags = proxy->getTags();
		Database::Self().pushSubset();
		Database::Self().subsetArtist(tags.tag0.artist);
		if(!proxy->infoExist(SInfo::ArtistArt)) {
			QList<struct Database::Attr> attr =  Database::Self().Artists();
			if(attr.size() && attr[0].name == tags.tag0.artist && attr[0].art.size()) {
				proxy->setInfo(SInfo(SInfo::ArtistArt, attr[0].art, ""));
			}
		}
		if(!proxy->infoExist(SInfo::AlbumArt)) {
			QList<struct Database::AttrAl> attrl = Database::Self().Albums(&tags.tag0.album);
			if(attrl.size() && attrl[0].art.size()) {
				proxy->setInfo(SInfo(SInfo::AlbumArt, attrl[0].art, ""));
			}
		}
		Database::Self().popSubset();
		proxy->endTransaction();
		// update tags in the DB
		QString file = ToLocalFile(tags.tag0.url);
		if(file.size()) {
			STags oldtags;
			if(Database::Self().GetTags(file, oldtags)) {
				if(tags.tag0 != oldtags.tag0) {
					Database::Self().SetTags(file, tags);
				}
			}
		}
	} else if(d & DisturbOnChangeSettings) {
		widget->updateSettings();
	}
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
	return DisturbOnRequest | DisturbOnTags | DisturbOnChangeSettings;
}

void SrcCollection::storeState()
{
	if(widget) widget->storeState();
}

void SrcCollection::settingsUpdate(QObject*)
{
}
