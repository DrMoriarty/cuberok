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

#ifndef CUBEROK_H
#define CUBEROK_H

#include <QtGui>
//#include <QtGui/QMainWindow>
#include "ui_cuberok.h"
//#include "playlistmodel.h"
#include "console.h"
#ifdef QTAGCONVERT
#include "../qtagconvert/src/KCmp3Tag.h"
#endif

const char titlepref[] = "Cuberok - ";

class Cuberok : public QMainWindow
{
    Q_OBJECT

public:
    Cuberok(QWidget *parent = 0);
    ~Cuberok();
	void firstStart();
    
private:
	void showhide(bool s);
    Ui::CuberokClass ui;
    QDirModel dirmodel;
    QSpinBox volumeBox;
    //PlaylistModel playlist;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
	ConsoleView *cv;
	bool needToClose;
#ifdef QTAGCONVERT
	mp3Dialog *qtag;
#endif
	QTimer *timer;

 protected:
	virtual void closeEvent(QCloseEvent *event);

private slots:
	void aboutMenu();
	void aboutQtMenu();
	void trayevent(QSystemTrayIcon::ActivationReason);
	void progressEvent(double);
	void settings();
	void colmodeChanged(int);
	void libmodeChanged(int);
	void consoleClosed(QObject*);
	void newConsoleMessage(QString, int);
#ifdef QTAGCONVERT
	void qtagClosed(QObject*);
#endif
	void storeState();
 	void setPlayPauseIcon  (bool);
	void timeSlot();

public slots:
	void lookAndFeel();
	void message(QString, QString, QString, long);
	void viewConsole();
	bool reallyClose();
	void qTagConvert();
	void refreshTree();
	void applySettings();
	void collectionSettings();
	void importCollection();
	void setBookmark();
	void removeBookmark();
	void selectBookmark(QListWidgetItem*);
	void selectBookmark(QString);
};

#endif // CUBEROK_H
