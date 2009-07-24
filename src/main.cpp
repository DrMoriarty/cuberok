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

#include <stdlib.h>
#include "cuberok.h"
#include "database.h"
#include "playlistsettings.h"
#include "myapplication.h"
#include "starrating.h"

#include <QtGui>
#include "console.h"

QString style_name;
QSharedMemory shm("Cuberok shared memory");

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

void usage()
{
	printf("Usage:\n\
cuberok [OPTIONS] [FILES]\n\
\tOptions are:\n\
--new\t-n\tCreate a new playlist\n\
--url URL\t-u URL\tOpen given URL\n\
--volume NN\t-v NN\tSet volume to NN percent\n\
--next\t-x\tNext track\n\
--prev\t-r\tPrevious track\n\
--stop\t-s\tStop\n\
--play\t-p\tPlay or pause current track\n\
--help\t-h\tPrint this screen\n\
--version\t-V\tPrint Cuberok version\n\
\n\
\tFILES: local files or playlists to open\n");
}

void putCommands(int argc, char *argv[])
{
	QStringList list;
	bool url = false, volume = false;
	for(int i = 1; i < argc; i++) {
		if(!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
			usage();
			return;
		} else
		if(!strcmp(argv[i], "-n") || !strcmp(argv[i], "--new")) {
			//if(list.size() && list.back().size()) 
			list << QString("");
			continue;
		} else
		if(!strcmp(argv[i], "-u") || !strcmp(argv[i], "--url")) {
			url = true;
			continue;
		} else
		if(!strcmp(argv[i], "-v") || !strcmp(argv[i], "--volume")) {
			volume = true;
			continue;
		} else
		if(!strcmp(argv[i], "-x") || !strcmp(argv[i], "--next")) {
			list << "#next";
			continue;
		} else
		if(!strcmp(argv[i], "-r") || !strcmp(argv[i], "--prev")) {
			list << "#prev";
			continue;
		} else
		if(!strcmp(argv[i], "-s") || !strcmp(argv[i], "--stop")) {
			list << "#stop";
			continue;
		} else
		if(!strcmp(argv[i], "-p") || !strcmp(argv[i], "--play")) {
			list << "#play";
			continue;
		} else
		if(!strcmp(argv[i], "-V") || !strcmp(argv[i], "--version")) {
			printf("%s\n", (const char*)QString("%1.%2.%3").arg(QString::number(CUBEROK_VERSION_MAJ), QString::number(CUBEROK_VERSION_MIN), QString::number(CUBEROK_VERSION_BUI)).toLocal8Bit());
			continue;
		} else
		if(argv[i][0] == '-') {
			fprintf(stderr, "Unknown option %s\n", argv[i]);
			usage();
			return;
		}
		if(url) {
			list << argv[i];
			url = false;
		} else if(volume) {
			list << QString("#volume %1").arg(argv[i]);
			volume = false;
		} else {
			QString file = argv[i];
			if(QFileInfo(file).isRelative()) {
				file = QDir::currentPath() + QDir::separator() + file;
			}
			list << QUrl::fromLocalFile(file).toString();
		}
	}
	QByteArray bytes;
	QDataStream stream(&bytes, QIODevice::WriteOnly);
	stream << list;
	if(bytes.size() >= SHMEM_SIZE) {
		fprintf(stderr, "Arguments too long! These size is greater than %d bytes\n", SHMEM_SIZE);
	}
	bool success = false;
	long long time = 0;
	while(!success) {
		shm.lock();
		char *data = (char*)shm.data();
		if(!data[0]) {
			memcpy(data+1, bytes.data(), bytes.size());
			data[0] = list.size() > 255 ? 255 : list.size();
			shm.unlock();
			success = true;
		} else {
			shm.unlock();
			//msleep(100);
			time += 1;
		}
		if(!success && time > 10000) {
			fprintf(stderr, "Timeout!");
			return;
		}
	}
}

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
	if(shm.attach(QSharedMemory::ReadWrite)) {
		if(argc == 1) {
			qDebug("Cuberok already started\n exiting...");
			usage();
			return 1;
		} else {
			putCommands(argc, argv);
			return 0;
		}
	}
	if(!shm.create(SHMEM_SIZE)) {
		qFatal("Can not create shared memory segment!");
	} else {
		shm.lock();
		*(char*)shm.data() = 0;
		shm.unlock();
	}
	QString splashstring = QString("Cuberok v %1.%2.%3").arg(QString::number(CUBEROK_VERSION_MAJ), QString::number(CUBEROK_VERSION_MIN), QString::number(CUBEROK_VERSION_BUI));
    QPixmap pixmap(":/icons/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage(splashstring, Qt::AlignBottom/*Qt::AlignCenter*/, Qt::black);
    QString locale = QLocale::system().name().left(2);
    QTranslator translator;
    QString trpath;
	//trpath = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
#ifndef WIN32
    trpath = qApp->applicationDirPath() + "/../share/cuberok/locale/";
#endif
    QString trfile = QString("cuberok_") + QLocale::system().name().left(2);
    if (!translator.load(trfile, trpath)) {
		qDebug("%s %s", (const char*)(trpath + QDir::separator() + trfile).toLocal8Bit() , " not found");
        trpath = a.applicationDirPath() + QDir::separator() + "translations";
        translator.load(trfile, trpath);
    }
    a.installTranslator(&translator);
    a.processEvents();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
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
	shm.detach();
#ifndef DEBUG
    a.storeState(&w);
    a.storeState();
#endif
    return res;
}
