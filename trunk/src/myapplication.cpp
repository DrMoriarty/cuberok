/* Cuberok
 * Copyright (C) 2009 Vasiliy Makarov <drmoriarty.0@gmail.com>
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

#include "myapplication.h"
#include "playlistsettings.h"

const int ver = 1;

MyApplication::MyApplication( int & argc, char ** argv )
	:QApplication(argc, argv), mainwindow(0), canstore(false)
{
}

void MyApplication::commitData(QSessionManager& manager)
{
    if(canstore) {
	QApplication::commitData(manager);
	storeState();
	if(mainwindow) storeState(mainwindow);
	//QMessageBox::information(0, "commitData", "The data was committed");
	qDebug("The data was committed");
    }
}

void MyApplication::saveState(QSessionManager& manager)
{
    if(canstore) {
	QApplication::saveState(manager);
	storeState();
	if(mainwindow) storeState(mainwindow);
	//QMessageBox::information(0, "saveState", "The state was saved");
	qDebug("The state was saved");
    }
}

void MyApplication::storeState()
{
	PLSet.save();
    QSettings set;
    set.setValue("style", style_name);
	//#ifdef WIN32
    // FIXME qt bug?
    set.setValue("palette", (QVariant)QApplication::palette());
	//#endif
}

void MyApplication::storeState(QMainWindow *win)
{
    QSettings set;
    set.setValue("winstate", win->saveState(ver));
    set.setValue("wingeometry", win->saveGeometry());
    /*QFile file(QDir::homePath()+"/.cuberock/state.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);   // we will serialize the data into the file
    out << style_name;
    out << QApplication::palette();
    out << win->saveState(ver);
    out << win->saveGeometry();
    out << win->splitter();
    */
}

bool MyApplication::restoreState()
{
    QSettings set;
	if(!set.contains("style") && !set.contains("palette")) {
	    qDebug("Therea aren't settings 'style' and 'palette'");
		return false;
	}
	
    style_name = set.value("style", "Cuberok").toString();
    QApplication::setStyle(style_name);
	//#ifdef WIN32
    // FIXME qt bug?
    QPalette p = set.value("palette").value<QPalette>();
    QApplication::setPalette(p);
	//#else
    //QPalette p;
	//#endif
	return true;
}

bool MyApplication::restoreState(QMainWindow *win)
{
	mainwindow = win;
    QSettings set;
	if(!set.contains("winstate") && !set.contains("wingeometry")) {
		return false;
	}
	
    win->restoreState(set.value("winstate").toByteArray(), ver);
    win->restoreGeometry(set.value("wingeometry").toByteArray());
    /*QFile file(QDir::homePath()+"/.cuberock/state.dat");
    if(!file.exists()) return;
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);    // read the data serialized from the file
    QPalette p;
    QByteArray s, g;
    int splitter;
    in >> style_name >> p >> s >> g >> splitter;
    QApplication::setStyle(style_name);
    QApplication::setPalette(p);
    win->restoreState(s, ver);
    win->restoreGeometry(g);
    win->setSplitter(splitter);
    */
	return true;
}

void MyApplication::canStore(bool c)
{
    canstore = c;
}
