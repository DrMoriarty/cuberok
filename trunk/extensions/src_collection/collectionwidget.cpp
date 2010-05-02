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

#include "collectionwidget.h"
#include "database.h"

CollectionWidget::CollectionWidget(Proxy* proxy, QWidget *parent)
	:QWidget(parent), proxy(proxy)
{
	ui.setupUi(this);
	ui.colView->setProxy(proxy);
	ui.subsetLabel->setVisible(false);
	ui.subsetDisableButton->setVisible(false);

	QActionGroup *colmodeGroup = new QActionGroup(this);
    colmodeGroup->addAction(ui.actionGenreMode);
    colmodeGroup->addAction(ui.actionArtistMode);
    colmodeGroup->addAction(ui.actionAlbumMode);
    colmodeGroup->addAction(ui.actionSongMode);
	colmodeGroup->addAction(ui.actionSqlMode);
    ui.actionGenreMode->setChecked(true);
	connect(ui.colView, SIGNAL(modeChanged(int)), this, SLOT(colmodeChanged(int)));
	connect(ui.colView, SIGNAL(addUrl(QUrl)), this, SLOT(addUrl(QUrl)));

	QSettings set;
	if(set.value("iconview", false).toBool())
		ui.actionIconView->trigger();
}

void CollectionWidget::storeState()
{
	QSettings set;
	//ui.colView->storeState();
	set.setValue("iconview", ui.actionIconView->isChecked());
}

void CollectionWidget::colmodeChanged(int m)
{
	ui.actionAddToCollection->setDisabled(m == M_SONG);
	//ui.actionRemoveFromCollection->setDisabled(m == M_SONG);
	ui.actionSetImage->setDisabled(m == M_SONG);
	ui.actionGetImageFromLastFM->setDisabled(m != M_ARTIST && m != M_ALBUM);
	bool needtoclear = false;
	switch(m) {
	case M_ARTIST:
		if(!ui.actionArtistMode->isChecked()) {
			ui.actionArtistMode->setChecked(true);
			needtoclear = true;
		}
		break;
	case M_ALBUM:
		if(!ui.actionAlbumMode->isChecked()) {
			ui.actionAlbumMode->setChecked(true);
			needtoclear = true;
		}
		break;
	case M_GENRE:
		if(!ui.actionGenreMode->isChecked()) {
			ui.actionGenreMode->setChecked(true);
			needtoclear = true;
		}
		break;
	case M_SONG:
		if(!ui.actionSongMode->isChecked()) {
			ui.actionSongMode->setChecked(true);
			needtoclear = true;
		}
		break;
	case M_SQLLIST:
		break;
	}
	if(needtoclear) {
		ui.filterLineEdit->setText("");
	}
}

void CollectionWidget::updateInfo()
{
	ui.colView->infoResponse();
}

void CollectionWidget::addUrl(QUrl url)
{
	proxy->setPlControl(SPlControl(SPlControl::Append, url.toString()));
}
