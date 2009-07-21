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

#ifndef MAIN_H_
#define MAIN_H_

#define NDEBUG

#include <fileref.h>
#include <tag.h>
#include <mpegfile.h>
#include <id3v2tag.h>
#include <id3v1tag.h>

// convert QString to TagLib::String and vice verse
#define QS(s) QString::fromUtf8(s.toCString(true))
#define TS(s) TagLib::String(s.toUtf8().constData(), TagLib::String::UTF8)

//#define ToLocalFile(url) (url.scheme().toLower() == "file" ? url.toString().toLocal8Bit().mid(8) : "")
#ifndef WIN32
#define ToLocalFile(url) (url.scheme().toLower() == "file" ? url.toString().mid(7) : "")
#else
#define ToLocalFile(url) (url.scheme().toLower() == "file" ? url.toString().mid(8) : "")
#endif

#include <QtCore>

extern QSharedMemory shm;
#define SHMEM_SIZE 1024

static QString CUBEROK_VERSION = QString("%1.%2.%3").arg(QString::number(CUBEROK_VERSION_MAJ), QString::number(CUBEROK_VERSION_MIN), QString::number(CUBEROK_VERSION_BUI));

//#define TRAYICONARTIFACKTWORKAROUND

#include "../QFreeDesktopMime/src/freedesktopmime.h"

#endif /*MAIN_H_*/
