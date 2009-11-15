/* Cuberok
 * Copyright (C) 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>
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

#include "cuberok.h"
#include "aboutdialog.h"
#include "lookandfeel.h"
#include "tagger.h"
#include "playlistsettings.h"
#include "indicator.h"
#include "settings.h"
#include "player_manager.h"
#include "collectionsettings.h"
#include "importcollection.h"
#include "firststartwizard.h"
#include "messagewindow.h"
#include "main.h"
#include "extensionproxy.h"
//#include "extensionsettings.h"

#include <QDesktopServices>

QFreeDesktopMime __mime;

Cuberok::Cuberok(QWidget *parent)
    : QMainWindow(parent), cv(0), needToClose(false), useMessageWindow(false)
{
	QUrl url("file:///home/vasya/music/song\\123.mp3");
	//Console::Self().log(url.toString());
	//Console::Self().log(url.toLocalFile());
	//Console::Self().log(ToLocalFile(url));
	// FIX_QT_PLEASE
	//Console::Self().log(QUrl::fromLocalFile("/home/vasya/music/song\\123.mp3").toString());
#ifdef QTAGCONVERT
	qtag = 0;
#endif
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timeSlot()));
	timer->start(100);
	
	QSettings set;

	QString engine = set.value("engine", "").toString();
	if(engine.size()) PlayerManager::Self().setPrefferedPlayer(engine);

	ui.setupUi(this);
	ui.subsetLabel->setVisible(false);
	ui.subsetDisableButton->setVisible(false);
	setWindowIcon(QIcon(":/icons/cuberok_bw.png"));
	trayIconMenu = new QMenu(this);
	trayIconMenu->addAction(ui.actionPrev);
	trayIconMenu->addAction(ui.actionPlayPause);
	trayIconMenu->addAction(ui.actionStop);
	trayIconMenu->addAction(ui.actionNext);
	trayIconMenu->addSeparator();
	trayIconMenu->addAction(ui.actionExit);
	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setContextMenu(trayIconMenu);
	trayIcon->setIcon(this->windowIcon());
	trayIcon->show();
	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayevent(QSystemTrayIcon::ActivationReason)));
	connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(setFocus()));

	if(!connect(&Console::Self(), SIGNAL(newMessage(QString, int)), this, SLOT(newConsoleMessage(QString, int))))
	   Console::Self().error("Can't connect to the Console::newMessage");

	if(!connect(ui.listView, SIGNAL(message(QString,QString,QString,long)), this, SLOT(message(QString,QString,QString,long)), Qt::DirectConnection))
		Console::Self().error("Can't connect to the listView.message");
	// connect the ui.actionPlayPause triggered signal to our own slot for icon switching:
	connect(ui.listView, SIGNAL(updatePlayPauseButton (bool) ), this, SLOT(setPlayPauseIcon (bool) ));

	QMenu * cm = createPopupMenu();
	cm->setTitle(tr("Addons"));
	ui.menuView->addMenu(cm);
	
	//ui.line->restoreState(set.value("splitter").toByteArray());

	connect(ui.volumeSlider, SIGNAL(valueChanged(int)), ui.listView, SLOT(setVolume(int)));
	ui.volumeSlider->setValue(set.value("volume", 99).toInt(0));
	
	if(set.value("shuffle", false).toBool())
		ui.actionShuffle->trigger();
	if(set.value("repeat", false).toBool())
		ui.actionRepeat->trigger();
	/*
	if(set.value("correctTag", false).toBool())
		Tagger::setAutoCorrect(true);
	if(set.value("saveCorrected", false).toBool())
		Tagger::setSaveCorrected(true);
	*/	
	//ui.actionCorrectTag->trigger();
	
	if(!connect(ui.progressBar, SIGNAL(userevent(double)), this, SLOT(progressEvent(double))))
		Console::Self().error("connection error (progressEvent)");

	ui.listView->prepare();

	ui.statusbar->addPermanentWidget(ui.listStatus);
	ui.statusbar->addPermanentWidget(ui.collectionStatus);

    if(PLSet.columnVisible(PlaylistModel::Stat)) ui.actionViewQueue->trigger();
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
	if(PLSet.columnVisible(PlaylistModel::Number)) ui.actionViewNumber->trigger();

	Indicator::Self().setWidget(*((QAbstractButton*)ui.toolBar_2->widgetForAction(ui.actionBreak)));

	QActionGroup *colmodeGroup = new QActionGroup(this);
    colmodeGroup->addAction(ui.actionGenreMode);
    colmodeGroup->addAction(ui.actionArtistMode);
    colmodeGroup->addAction(ui.actionAlbumMode);
    colmodeGroup->addAction(ui.actionSongMode);
    ui.actionGenreMode->setChecked(true);
	connect(ui.colView, SIGNAL(modeChanged(int)), this, SLOT(colmodeChanged(int)));

	QActionGroup *libmodeGroup = new QActionGroup(this);
	libmodeGroup->addAction(ui.actionLibraryRegularPlaylist);
	libmodeGroup->addAction(ui.actionLibrarySQLPlaylist);
	ui.actionLibraryRegularPlaylist->setChecked(true);
	//connect(ui.libView, SIGNAL(modeChanged(int)), this, SLOT(libmodeChanged(int)));
	//ui.actionAddToLibrary->setDisabled(true);
	ui.actionSQLListEdit->setDisabled(true);

	ui.toolBar_2->addAction(QWhatsThis::createAction(this));
	ui.toolBar_3->addWidget(ui.progressBar);
	ui.toolBar_3->addAction(ui.actionMute);
	ui.toolBar_3->addWidget(ui.volumeSlider);
	connect(ui.toolBar_3, SIGNAL(orientationChanged(Qt::Orientation)), ui.progressBar, SLOT(setOrientation(Qt::Orientation)));
	connect(ui.toolBar_3, SIGNAL(orientationChanged(Qt::Orientation)), ui.volumeSlider, SLOT(setOrientation(Qt::Orientation)));
	if(set.value("iconview", false).toBool())
		ui.actionIconView->trigger();

	applySettings();
	connect(qApp, SIGNAL(commitDataRequest(QSessionManager&)), this, SLOT(storeState()), Qt::DirectConnection);
	connect(qApp, SIGNAL(saveStateRequest(QSessionManager&)), this, SLOT(storeState()), Qt::DirectConnection);
	useMessageWindow = true;

	foreach(Extension *ex, ExtensionProxy::Self().extensionList()) {
		if(ex) {
			QWidget *widget = ex->getWidget();
			if(widget) {
				QDockWidget *dock = new QDockWidget(this);
				dock->setObjectName(ex->getName());
				dock->setFeatures(QDockWidget::AllDockWidgetFeatures);
				dock->setWidget(widget);
				this->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dock);
				dock->setWindowTitle(ex->getName());
			}
		}
	}
}

Cuberok::~Cuberok()
{
	storeState();
}

void Cuberok::storeState()
{
	QSettings set;
	//set.setValue("splitter", ui.line->saveState());
	set.setValue("volume", ui.volumeSlider->value());
	set.setValue("repeat", ui.actionRepeat->isChecked());
	set.setValue("shuffle", ui.actionShuffle->isChecked());
	set.setValue("iconview", ui.actionIconView->isChecked());
	ExtensionProxy::Self().storeState();
	qDebug("Cuberok, state was stored");
}

void Cuberok::firstStart()
{
	//tabifyDockWidget(ui.dockWidget, ui.dockWidget3);
	//tabifyDockWidget(ui.dockWidget3, ui.dockWidget1);
	//tabifyDockWidget(ui.dockWidget2, ui.dockWidget1);
	//tabifyDockWidget(ui.dockWidget1, ui.dockWidget4);
	PLSet.setColumnVisible(PlaylistModel::File, false);
	PLSet.setColumnVisible(PlaylistModel::Comment, false);
	PLSet.setColumnVisible(PlaylistModel::Genre, false);
	PLSet.setColumnVisible(PlaylistModel::Length, false);
	PLSet.setColumnVisible(PlaylistModel::Number, false);
	PLSet.setColumnVisible(PlaylistModel::Year, false);
        PLSet.setColumnVisible(PlaylistModel::CueStart, false);
        PLSet.setColumnVisible(PlaylistModel::CueLength, false);
        PLSet.setColumnVisible(PlaylistModel::DBIndex, false);
        PLSet.setColumnVisible(PlaylistModel::StartTime, false);
        PLSet.setColumnWidth(PlaylistModel::Title, 80);
	PLSet.setColumnWidth(PlaylistModel::Artist, 80);
	PLSet.setColumnWidth(PlaylistModel::Album, 80);
	ui.actionViewFile->setChecked(false);
	ui.actionViewComment->setChecked(false);
	ui.actionViewGenre->setChecked(false);
	ui.actionViewLength->setChecked(false);
	ui.actionViewNumber->setChecked(false);
	ui.actionViewYear->setChecked(false);

	FirstStartWizard fsw(this);
	fsw.exec();
}

void Cuberok::aboutMenu()
{
	AboutDialog ad(this);
	ad.exec();
}

void Cuberok::lookAndFeel()
{
	LookAndFeel lnf;
	lnf.exec();
}

void Cuberok::message(QString title, QString album, QString artist, long len)
{
	//ui.infoWidget->setCurrent(artist, album, title);
	if(title.size() || album.size() || artist.size()) {
		//ui.progressBar->setFormat(title + " %p%");
		ui.progressBar->setFormatText(title);
		ui.progressBar->setDuration(len);
		QString trayMessage = QString("%1 - %2").arg(artist, album);
		if(PLSet.trayMessage) {
			trayIcon->showMessage(title, trayMessage, QSystemTrayIcon::Information/*NoIcon*/);
		}
		if(PLSet.popupMessage) {
			messageQueue.enqueue(QPair<QString, int>(title + "\n" + trayMessage, Console::C_MES));
		}
		setWindowTitle(QString(titlepref).append(title));
		trayIcon->setToolTip(QString("%1 - %2").arg(artist, title));
		setWindowIcon(QIcon(":/icons/cuberok.png"));
		trayIcon->setIcon(this->windowIcon());
#if !defined( WIN32 ) && defined( TRAYICONARTIFACKTWORKAROUND )
		// workaround for Qt bug of the tray icon
		trayIcon->hide();
        trayIcon->show();
#endif
	} else {
		//ui.progressBar->setFormat("%p%");
		ui.progressBar->setFormatText("");
		setWindowTitle("Cuberok");
		trayIcon->setToolTip("Cuberok");
		setWindowIcon(QIcon(":/icons/cuberok_bw.png"));
		trayIcon->setIcon(this->windowIcon());
	}
}

void Cuberok::trayevent(QSystemTrayIcon::ActivationReason r)
{
	if(r == QSystemTrayIcon::Trigger) {
		showhide(true);
        } else if ( r == QSystemTrayIcon::MiddleClick ) {
                ui.actionPlayPause->trigger();
	}
}

void Cuberok::showhide(bool s)
{
	bool act = !isVisible();
	setVisible(act);
        if (act) {
                activateWindow(); // for windows
                showNormal(); // for linux
        }

	/*bool vis = isVisible();
	if(vis && s) activateWindow();
	else if(vis != s) {
		vis = s;
		setVisible(vis);
		foreach (QWidget *widget, QApplication::allWidgets()) {
			QDialog *d = qobject_cast<QDialog*>(widget);
			if(d) d->setVisible(vis);	
		}
	}*/
}

void Cuberok::progressEvent(double pos)
{
    PlayerManager::Self().setPosition(pos);
}

void Cuberok::aboutQtMenu()
{
	QApplication::aboutQt();
}

void Cuberok::settings()
{
	Settings set(this);
	connect(&set, SIGNAL(accepted()), this, SLOT(applySettings()));
	set.exec();
	disconnect(&set);
}

void Cuberok::colmodeChanged(int m)
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

/*void Cuberok::libmodeChanged(int m)
{
	ui.actionAddToLibrary->setDisabled(m == M_LIST);
	ui.actionSQLListEdit->setDisabled(m == M_LIST);
	}*/

void Cuberok::viewConsole()
{
	if(cv) {
		cv->close();
		delete cv;
		cv = 0;
	} else {
		cv = new ConsoleView(this);
		connect(cv, SIGNAL( destroyed(QObject*)), this, SLOT(consoleClosed(QObject*)));
		cv->show();
	}
}

void Cuberok::consoleClosed(QObject*)
{
	//delete cv;
	cv = 0;
}

void Cuberok::newConsoleMessage(QString mes, int type)
{
	QIcon icon;
	QAbstractButton *but = (QAbstractButton*)ui.toolBar_2->widgetForAction(ui.actionConsole);
	switch(Console::Self().getLevel()) {
	case Console::C_NONE:
		icon.addFile(":/icons/console.png");
		break;
	case Console::C_MES:
		icon.addFile(":/icons/console_mes.png");
		break;
	case Console::C_WAR:
		icon.addFile(":/icons/console_war.png");
		break;
	case Console::C_ERR:
		icon.addFile(":/icons/console_err.png");
		break;
	case Console::C_FAT:
		icon.addFile(":/icons/console_fat.png");
		break;
	}
	but->setIcon(icon);
	if(useMessageWindow && PLSet.popupMessage && type != Console::C_NONE) {
		messageQueue.enqueue(QPair<QString, int>(mes, type));
	}
}

bool Cuberok::reallyClose()
{
	needToClose = true;
	return QMainWindow::close();
}

void Cuberok::closeEvent(QCloseEvent *event)
{
	if (needToClose) {
		event->accept();
	} else {
		showhide(false);
		event->ignore();
	}
} 

void Cuberok::qTagConvert()
{
#ifdef QTAGCONVERT
	if(qtag) {
		qtag->close();
		delete qtag;
		qtag = 0;
	} else {
		qtag = new mp3Dialog(this, ui.listView->getCurrentFile());
		connect(qtag, SIGNAL( destroyed(QObject*)), this, SLOT(qtagClosed(QObject*)));
		qtag->show();
	}
#else
	QStringList arg;
	arg << "path_to_current_song"; // TODO
	QProcess::execute("qtagconvert", arg);
#endif
}

#ifdef QTAGCONVERT
void Cuberok::qtagClosed(QObject*)
{
	//delete qtag;
	qtag = 0;
}
#endif

void Cuberok::applySettings()
{
	if(PLSet.textToolbuttons) {
		ui.toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
		ui.toolBar_2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
		ui.toolBar_3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	} else {
		ui.toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
		ui.toolBar_2->setToolButtonStyle(Qt::ToolButtonIconOnly);
		ui.toolBar_3->setToolButtonStyle(Qt::ToolButtonIconOnly);
	}
	switch(PLSet.sizeToolbuttons) {
	case 0:
		ui.toolBar->setIconSize(QSize(16, 16));
		ui.toolBar_2->setIconSize(QSize(16, 16));
		ui.toolBar_3->setIconSize(QSize(16, 16));
		break;
	case 1:
		ui.toolBar->setIconSize(QSize(24, 24));
		ui.toolBar_2->setIconSize(QSize(24, 24));
		ui.toolBar_3->setIconSize(QSize(24, 24));
		break;
	case 2:
		ui.toolBar->setIconSize(QSize(36, 36));
		ui.toolBar_2->setIconSize(QSize(36, 36));
		ui.toolBar_3->setIconSize(QSize(36, 36));
		break;
	}
}

void Cuberok::collectionSettings()
{
	CollectionSettings cs;
	cs.exec();
}

void Cuberok::importCollection()
{
	ImportCollection ic;
	ic.exec();
}
 
// a slot to handle setting the play/pause button to "pause" whenever play is activated:
// playPause of true means show "play" icon, false means show "pause"
void Cuberok::setPlayPauseIcon (bool playPause) {
  if (playPause) {
     ui.actionPlayPause->setIcon (QIcon (":/icons/butt_play.png"));
     ui.actionPlayPause->setToolTip ("Play"); 
     ui.actionPlayPause->setText ("Play"); 

  } else {
     ui.actionPlayPause->setIcon (QIcon (":/icons/butt_pause.png"));
     ui.actionPlayPause->setToolTip ("Pause"); 
     ui.actionPlayPause->setText ("Pause"); 
  }
}

void Cuberok::timeSlot()
{
	// messages
	if(useMessageWindow && messageQueue.size() && !isActiveWindow()) {
		QPair<QString, int> m = messageQueue.dequeue();
		MessageWindow *mw = new MessageWindow(this, m.first, m.second);
		mw->show();
	} else if(!useMessageWindow) {
		messageQueue.clear();
	}
	// remote control
	shm.lock();
	char *data = (char*)shm.data();
	QStringList list;
	if(data[0]) {
		QByteArray bytes(data+1, SHMEM_SIZE-1);
		QDataStream stream(bytes);
		stream >> list;
		data[0] = 0;
	}
	shm.unlock();
	foreach(QString str, list) {
		Console::Self().log(QString("Remote command: %1").arg(str));
		if(!str.size()) {
			ui.listView->addList();
			continue;
		}
		if(str[0] == '#') {
			// commands
			QStringList arg = str.split(' ', QString::SkipEmptyParts);
			if(arg[0] == "#volume") {
				if(arg.size() > 1) {
					int v = arg[1].toInt();
					ui.volumeSlider->setValue(v);
				}
			} else if(arg[0] == "#prev") {
				ui.actionPrev->trigger();
			} else if(arg[0] == "#next") {
				ui.actionNext->trigger();
			} else if(arg[0] == "#play") {
				ui.actionPlayPause->trigger();
			} else if(arg[0] == "#stop") {
				ui.actionStop->trigger();
			}
			continue;
		}
		QUrl url = QUrl(str);
 		if(url.isValid()) {
			ui.listView->addUrl(url);
		}
	}
}

void Cuberok::showHelp()
{
	QProcess *process = new QProcess;
	QStringList args;
	args << QLatin1String("-collectionFile")
		 << QLatin1String("E:/nw/workspace/Cuberok/help/cuberok-collection.qhc")
		 << QLatin1String("-enableRemoteControl");
	//args << QLatin1String("-showUrl") << QLatin1String("https://sites.google.com/site/cuberok");
	process->start(QLatin1String("assistant"), args);
	if (!process->waitForStarted())
		return;	
	QByteArray ba;
	ba.append("setSource qthelp://cuberok.0_1_0/doc/index.html");
	ba.append('\0');
	process->write(ba);
}

void Cuberok::goToSite()
{
	if(!QDesktopServices::openUrl(QUrl("https://sites.google.com/site/cuberok/"))) {
		QMessageBox::warning(this, tr("Something wrong"), tr("It seems your browser isn't configured properly"));
	}
}

/*void Cuberok::setupExtensions()
{
	ExtensionSettings *es = new ExtensionSettings();
	es->show();
	}*/
