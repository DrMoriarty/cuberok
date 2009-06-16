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
#include "playlistsettings.h"
#include "myapplication.h"
#include "starrating.h"

#include <QtGui>
#include "console.h"

QString style_name;

#define FILELOG
//#define DEBUG

#ifdef WIN32
#include <windows.h>
void GlobalWinKeys(WId hwnd)
{
    RegisterHotKey(hwnd, 100, MOD_SHIFT | MOD_ALT, 'Z');
    RegisterHotKey(hwnd, 200, MOD_SHIFT | MOD_ALT, 'X');
    RegisterHotKey(hwnd, 300, MOD_SHIFT | MOD_ALT, 'C');
    RegisterHotKey(hwnd, 400, MOD_SHIFT | MOD_ALT, 'V');
    RegisterHotKey(hwnd, 500, MOD_SHIFT | MOD_ALT, 'B');
}

void UnregisterWinKeys(WId hwnd)
{
    UnregisterHotKey(hwnd, 100);
    UnregisterHotKey(hwnd, 200);
    UnregisterHotKey(hwnd, 300);
    UnregisterHotKey(hwnd, 400);
    UnregisterHotKey(hwnd, 500);
}

void myMessageOutput(QtMsgType type, const char *msg)
 {
#ifdef FILELOG
	 {
		 QFile file(QDir::homePath()+"/.cuberok/log.txt");
		 file.open(QIODevice::Append);
		 QDataStream out(&file);
		 out << QString(msg).toLocal8Bit() << "\n";
	 }
#endif
     switch (type) {
     case QtDebugMsg:
         //fprintf(stderr, "Debug: %s\n", msg);
         Console::Self().message(msg);
         break;
     case QtWarningMsg:
         //fprintf(stderr, "Warning: %s\n", msg);
         Console::Self().warning(msg);
         break;
     case QtCriticalMsg:
         //fprintf(stderr, "Critical: %s\n", msg);
         Console::Self().error(msg);
         break;
     case QtFatalMsg:
         //fprintf(stderr, "Fatal: %s\n", msg);
         Console::Self().fatal(msg);
         abort();
     }
 }
#endif

int main(int argc, char *argv[])
{
    srand(0);
#ifdef WIN32
    qInstallMsgHandler(myMessageOutput);
#endif
	qRegisterMetaType<StarRating>("StarRating");
	qRegisterMetaTypeStreamOperators<StarRating>("StarRating");
    QApplication::setDesktopSettingsAware(false);
    QCoreApplication::setOrganizationName("DrMoriarty");
    //QCoreApplication::setOrganizationDomain("");
    QCoreApplication::setApplicationName("Cuberok");
    MyApplication a(argc, argv);
	QSharedMemory shm("Cuberok shared memory");
	if(shm.attach(QSharedMemory::ReadOnly)) {
		qDebug("Cuberok already started\n exiting...");
		return 0;
	}
	QString splashstring = QString("Cuberok v %1.%2.%3").arg(QString::number(CUBEROK_VERSION_MAJ), QString::number(CUBEROK_VERSION_MIN), QString::number(CUBEROK_VERSION_BUI));
	if(!shm.create(30)) {
		qWarning("Can not create shared memory segment!");
	} else {
		shm.lock();
		memcpy(shm.data(), (const char*)splashstring.toLocal8Bit(), splashstring.toLocal8Bit().size());
		shm.unlock();
	}
    QPixmap pixmap(":/icons/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage(splashstring, Qt::AlignBottom/*Qt::AlignCenter*/, Qt::black);
    QString locale = QLocale::system().name().left(2);
    QTranslator translator;
    QString trpath = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
    QString trfile = QString("cuberok_") + QLocale::system().name().left(2);
    if (!translator.load(trfile, trpath)) {
		qDebug("%s %s", (const char*)(trpath + QDir::separator() + trfile).toLocal8Bit() , " not found");
        trpath = a.applicationDirPath() + QDir::separator() + "translations";
        translator.load(trfile, trpath);
    }
    a.installTranslator(&translator);
	/*    QString loc_path;
#ifndef WIN32
    loc_path = qApp->applicationDirPath() + "/../share/cuberok/locale/";
    //loc_path = "/usr/share/cuberok/locale/";
#endif
    loc_path += QString("cuberok_") + locale;
    translator.load(loc_path);
    qDebug("Loading l10n from %s", (const char*)loc_path.toLocal8Bit());
    a.installTranslator(&translator);
	*/
    a.processEvents();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
    //qApp->setWindowIcon(QIcon(":/icons/application.png"));
    Cuberok w;
	MyApplication::restoreState();
    w.show();
    splash.finish(&w);
#ifndef DEBUG
    if(!a.restoreState(&w)) {
		w.firstStart();
	}
#endif
    a.canStore(true);
#ifdef WIN32
    //GlobalWinKeys(w.winId());
#endif
    PLSet.lang = locale;
    int res = a.exec();
#ifdef WIN32
    //cUnregisterWinKeys(w.winId());
#endif
#ifndef DEBUG
    a.storeState(&w);
    a.storeState();
#endif
    return res;
}
