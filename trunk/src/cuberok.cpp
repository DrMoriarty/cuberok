/* Cuberok
 * Copyright (C) 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this software; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "cuberok.h"
#include "aboutdialog.h"
#include "lookandfeel.h"
#include "tagger.h"
#include "playlistsettings.h"
#include "indicator.h"
#include "settings.h"

Cuberok::Cuberok(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
	ui.subsetLabel->setVisible(false);
	ui.subsetDisableButton->setVisible(false);
	trayIconMenu = new QMenu(this);
	trayIconMenu->addAction(ui.actionPlay);
	trayIconMenu->addAction(ui.actionNext);
	trayIconMenu->addAction(ui.actionPrev);
	trayIconMenu->addAction(ui.actionPause);
	trayIconMenu->addSeparator();
	trayIconMenu->addAction(ui.actionExit);
	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setContextMenu(trayIconMenu);
	trayIcon->setIcon(this->windowIcon());
	trayIcon->show();
	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayevent(QSystemTrayIcon::ActivationReason)));
	connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(setFocus()));
	
	QSettings set;
	//ui.line->restoreState(set.value("splitter").toByteArray());
	dirmodel.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
	this->findChild<QTreeView*> ("treeView_2")->setModel(&dirmodel);
	ui.treeView_2->hideColumn(1);
	ui.treeView_2->hideColumn(2);
	ui.treeView_2->hideColumn(3);
	ui.treeView_2->setAllColumnsShowFocus(true);
	ui.treeView_2->sortByColumn(0, Qt::AscendingOrder);
	
	connect(ui.volumeSlider, SIGNAL(valueChanged(int)), ui.listView, SLOT(setVolume(int)));
	ui.volumeSlider->setValue(set.value("volume", 99).toInt(0));
	
	if(set.value("shuffle", false).toBool())
		ui.actionShuffle->trigger();
	if(set.value("repeat", false).toBool())
		ui.actionRepeat->trigger();
	if(set.value("correctTag", false).toBool())
		Tagger::setAutoCorrect(true);
	if(set.value("saveCorrected", false).toBool())
		Tagger::setSaveCorrected(true);
	//ui.actionCorrectTag->trigger();
	
	if(!connect(ui.progressBar, SIGNAL(userevent(double)), this, SLOT(progressEvent(double))))
	    QMessageBox::information(0, "error", "connection error");

	ui.statusbar->addPermanentWidget(ui.listStatus);
	ui.statusbar->addPermanentWidget(ui.collectionStatus);

    if(PLSet.columnVisible(PlaylistModel::Track)) ui.actionViewTrack->trigger();
    if(PLSet.columnVisible(PlaylistModel::Title)) ui.actionViewTitle->trigger();
    if(PLSet.columnVisible(PlaylistModel::Artist)) ui.actionViewArtist->trigger();
    if(PLSet.columnVisible(PlaylistModel::Album)) ui.actionViewAlbum->trigger();
    if(PLSet.columnVisible(PlaylistModel::Genre)) ui.actionViewGenre->trigger();
    if(PLSet.columnVisible(PlaylistModel::Year)) ui.actionViewYear->trigger();
    if(PLSet.columnVisible(PlaylistModel::Comment)) ui.actionViewComment->trigger();
	if(PLSet.columnVisible(PlaylistModel::File)) ui.actionViewFile->trigger();
	if(PLSet.columnVisible(PlaylistModel::Length)) ui.actionViewLength->trigger();
	if(PLSet.columnVisible(PlaylistModel::Rating)) ui.actionViewRating->trigger();

	Indicator::Self().setWidget(*((QAbstractButton*)ui.toolBar->widgetForAction(ui.actionBreak)));

	QString engine = set.value("engine", "").toString();
	if(engine.size()) PlayerManager::Self().setPrefferedPlayer(engine);

	QActionGroup *colmodeGroup = new QActionGroup(this);
    colmodeGroup->addAction(ui.actionGenreMode);
    colmodeGroup->addAction(ui.actionArtistMode);
    colmodeGroup->addAction(ui.actionAlbumMode);
    colmodeGroup->addAction(ui.actionSongMode);
    ui.actionGenreMode->setChecked(true);
	connect(ui.colView, SIGNAL(modeChanged(int)), this, SLOT(colmodeChanged(int)));

	ui.toolBar->addAction(QWhatsThis::createAction(this));
	if(set.value("iconview", false).toBool())
		ui.actionIconView->trigger();
	if(set.value("autoRating", false).toBool())
		PLSet.autoRating = true;
}

Cuberok::~Cuberok()
{
	QSettings set;
	//set.setValue("splitter", ui.line->saveState());
	set.setValue("volume", ui.volumeSlider->value());
	set.setValue("repeat", ui.actionRepeat->isChecked());
	set.setValue("shuffle", ui.actionShuffle->isChecked());
	set.setValue("iconview", ui.actionIconView->isChecked());
}

void Cuberok::on_AboutMenu()
{
	AboutDialog ad(this);
	ad.exec();
}

void Cuberok::lookAndFeel()
{
	LookAndFeel lnf;
	lnf.exec();
}

void Cuberok::message(QString title/*, QString* message*/)
{
	if(title.size()) {
		ui.progressBar->setFormat(title + " %p%");
		trayIcon->showMessage(title, /**message*/QString(""), QSystemTrayIcon::NoIcon, 10);
		setWindowTitle(QString(titlepref).append(title));
		trayIcon->setToolTip(title);
	} else {
		ui.progressBar->setFormat("%p%");
		setWindowTitle("Cuberok");
		trayIcon->setToolTip("Cuberok");
	}
}

void Cuberok::trayevent(QSystemTrayIcon::ActivationReason r)
{
	bool vis = !isVisible();
	if(r == QSystemTrayIcon::Trigger) {
		setVisible(vis);
		foreach (QWidget *widget, QApplication::allWidgets()) {
			QDialog *d = qobject_cast<QDialog*>(widget);
			if(d) d->setVisible(vis);	
		}
	}
	if(vis) activateWindow();
}

void Cuberok::progressEvent(double pos)
{
    PlayerManager::Self().setPosition(pos);
}

void Cuberok::on_AboutQtMenu()
{
	QApplication::aboutQt();
}

void Cuberok::settings()
{
	Settings set(this);
	set.exec();
}

void Cuberok::colmodeChanged(int m)
{
	ui.actionAddToCollection->setDisabled(m == M_SONG);
	ui.actionRemoveFromCollection->setDisabled(m == M_SONG);
	ui.actionSetImage->setDisabled(m == M_SONG);
	switch(m) {
	case M_ARTIST:
		ui.actionArtistMode->setChecked(true);
		break;
	case M_ALBUM:
		ui.actionAlbumMode->setChecked(true);
		break;
	case M_GENRE:
		ui.actionGenreMode->setChecked(true);
		break;
	case M_SONG:
		ui.actionSongMode->setChecked(true);
		break;
	}
}
