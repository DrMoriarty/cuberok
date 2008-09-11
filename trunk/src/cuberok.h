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

#ifndef CUBEROK_H
#define CUBEROK_H

#include <QtGui>
//#include <QtGui/QMainWindow>
#include "ui_cuberok.h"
//#include "playlistmodel.h"

const char titlepref[] = "Cuberok - ";

class Cuberok : public QMainWindow
{
    Q_OBJECT

public:
    Cuberok(QWidget *parent = 0);
    ~Cuberok();
    
private:
    Ui::CuberokClass ui;
    QDirModel dirmodel;
    QSpinBox volumeBox;
    //PlaylistModel playlist;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

private slots:
	void on_AboutMenu();
	void on_AboutQtMenu();
	void trayevent(QSystemTrayIcon::ActivationReason);
	void progressEvent(double);
	void settings();
	void colmodeChanged(int);

public slots:
	void lookAndFeel();
	void message(QString/*, QString**/);
	void viewConsole();
};

#endif // CUBEROK_H
