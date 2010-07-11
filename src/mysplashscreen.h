/* Cuberok
 * Copyright (C) 2010 Vasiliy Makarov <drmoriarty.0@gmail.com>
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

#ifndef MYSPLASHSCREEN_H
#define MYSPLASHSCREEN_H

#include <QtGui>

class MySplashScreen : public QSplashScreen {
	Q_OBJECT
 public:
	MySplashScreen(const QPixmap & pixmap = QPixmap(), Qt::WindowFlags f = 0);
 protected:
	virtual void drawContents(QPainter * painter);
};


#endif //MYSPLASHSCREEN_H
