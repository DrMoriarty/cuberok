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

#include "global.h"

#include <QtCore>

extern QSharedMemory shm;
#define SHMEM_SIZE 1024

//#define TRAYICONARTIFACKTWORKAROUND

#include "../QFreeDesktopMime/src/freedesktopmime.h"

#endif /*MAIN_H_*/
