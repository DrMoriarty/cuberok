/* Cuberok
 * Copyright (C) 2009 Vasiliy Makarov <drmoriarty.0@gmail.com>
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

#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtCore>
#ifndef WIN32
#define ToLocalFile(url) (url.scheme().toLower() == "file" ? url.toString().mid(7) : "")
#else
#define ToLocalFile(url) (url.scheme().toLower() == "file" ? url.toString().mid(8) : "")
#endif

#define SHMEM_SIZE 1024
const QString XMLNS("http://code.google.com/p/cuberok");

static QString CUBEROK_VERSION = QString("%1.%2.%3").arg(QString::number(CUBEROK_VERSION_MAJ), QString::number(CUBEROK_VERSION_MIN), QString::number(CUBEROK_VERSION_BUI));


#endif //GLOBAL_H
