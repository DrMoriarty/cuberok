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

#include <stdlib.h>
#include "cuberok.h"
#include "database.h"

#include <QtGui>
#include <QApplication>

QString style_name;

const int ver = 1;

void storeState(Cuberok *win)
{
	QSettings set;
	set.setValue("style", style_name);
#ifdef WIN32
	// FIXME qt bug?
	set.setValue("palette", (QVariant)QApplication::palette());
#endif
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

void restoreState(Cuberok *win)
{
	QSettings set;
	style_name = set.value("style").toString();
#ifdef WIN32
	// FIXME qt bug?
	QPalette p = set.value("palette").value<QPalette>();
#else
	QPalette p;
#endif
	win->restoreState(set.value("winstate").toByteArray(), ver);
	win->restoreGeometry(set.value("wingeometry").toByteArray());
	QApplication::setStyle(style_name);
	QApplication::setPalette(p);
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
}

int main(int argc, char *argv[])
{
	srand(0);
    QApplication a(argc, argv);
    QString locale = QLocale::system().name();
    QTranslator translator;
	QString loc_path;
#ifndef WIN32
	loc_path = "/usr/share/cuberok/locale/";
#endif
    translator.load(loc_path + QString("cuberok_") + locale);
    a.installTranslator(&translator); 

    QCoreApplication::setOrganizationName("DrMoriarty");
	//QCoreApplication::setOrganizationDomain("");
	QCoreApplication::setApplicationName("Cuberok");	
	//QDir::home().mkdir(".cuberock");
    Cuberok w;
#ifndef DEBUG
    restoreState(&w);
#endif
    w.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
    //Database::Self();
    int res = a.exec();
#ifndef DEBUG
    storeState(&w);
#endif
    return res;
}
