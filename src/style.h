/* Cuberok
 * Copyright (C) 2008-2009 Vasiliy Makarov <drmoriarty.0@gmail.com>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef STYLE_H
#define STYLE_H

#include <QtGui>
#include <QCleanlooksStyle>
#include <QPalette>

class CuberokStyle :public QCleanlooksStyle {
	Q_OBJECT
public:
	CuberokStyle();
	//virtual void drawComplexControl(ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p, const QWidget *widget) const;
	int pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const;
};

class StylePlugin: public QStylePlugin {
	Q_OBJECT
public:
	StylePlugin();
    virtual QStringList keys() const;
    virtual QStyle *create(const QString &key);
};

#endif //STYLE_H
