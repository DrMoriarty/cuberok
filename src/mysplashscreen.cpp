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

#include "global.h"
#include "mysplashscreen.h"

MySplashScreen::MySplashScreen(const QPixmap & pixmap, Qt::WindowFlags f) : QSplashScreen(pixmap, f)
{
}

void MySplashScreen::drawContents(QPainter * painter)
{
	QPixmap pm = QSplashScreen::pixmap();
	QRect r(0, 0, pm.width(), pm.height());
// 	QString splashstring = QString("Cuberok v %1.%2.%3\n").arg(QString::number(CUBEROK_VERSION_MAJ), QString::number(CUBEROK_VERSION_MIN), QString::number(CUBEROK_VERSION_BUI));
// 	splashstring += QString("build: ") + __TIME__ + " " + __DATE__ + "\n";
// 	splashstring += QString("Qt: ") + QT_VERSION_STR + " ";
// #ifdef Q_WS_X11
// 	splashstring += "X11";
// #endif
// #ifdef Q_WS_MAC
// 	splashstring += "Mac OS";
// #endif
// #ifdef Q_WS_WIN
// 	splashstring += "MS Windows";
// #endif
	painter->setPen(Qt::yellow);
	painter->setFont(QFont("arial", 8));
	//painter->drawText(r, Qt::AlignLeft | Qt::AlignBottom, splashstring);
	painter->drawText(r, Qt::AlignRight | Qt::AlignBottom, tr("(c) DrMoriarty, 2008-2010"));

	QSplashScreen::drawContents(painter);
}
