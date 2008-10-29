 /****************************************************************************
 **
 ** Copyright (C) 2007-2007 Trolltech ASA. All rights reserved.
 **
 ** This file is part of the example classes of the Qt Toolkit.
 **
 ** This file may be used under the terms of the GNU General Public
 ** License version 2.0 as published by the Free Software Foundation
 ** and appearing in the file LICENSE.GPL included in the packaging of
 ** this file.  Please review the following information to ensure GNU
 ** General Public Licensing requirements will be met:
 ** http://trolltech.com/products/qt/licenses/licensing/opensource/
 **
 ** If you are unsure which license is appropriate for your use, please
 ** review the following information:
 ** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
 ** or contact the sales department at sales@trolltech.com.
 **
 ** In addition, as a special exception, Trolltech gives you certain
 ** additional rights. These rights are described in the Trolltech GPL
 ** Exception version 1.0, which can be found at
 ** http://www.trolltech.com/products/qt/gplexception/ and in the file
 ** GPL_EXCEPTION.txt in this package.
 **
 ** In addition, as a special exception, Trolltech, as the sole copyright
 ** holder for Qt Designer, grants users of the Qt/Eclipse Integration
 ** plug-in the right for the Qt/Eclipse Integration to link to
 ** functionality provided by Qt Designer and its related libraries.
 **
 ** Trolltech reserves all rights not expressly granted herein.
 **
 ** Trolltech ASA (c) 2007
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **
 ****************************************************************************/

 #include <QtGui>
 #include <math.h>

 #include "starrating.h"

 const int PaintingScaleFactor = 14;

int StarRating::starMeasure1(int rating)
{
	return rating/10;
}

int StarRating::starMeasure2(int rating)
{
	return (rating+9) / 10;
}

StarRating::StarRating(int starCount, int maxStarCount, int measure)
 {
	 _rating = starCount;
	 switch(measure) {
	 case 2:
		 myStarCount = starMeasure2(_rating);
		 break;
	 default:
		 myStarCount = starMeasure1(_rating);
	 }
     myMaxStarCount = maxStarCount;

     starPolygon << QPointF(1.0, 0.5);
     for (int i = 1; i < 5; ++i)
         starPolygon << QPointF(0.5 + 0.5 * cos(0.8 * i * 3.14),
                                0.5 + 0.5 * sin(0.8 * i * 3.14));

     diamondPolygon << QPointF(0.4, 0.5) << QPointF(0.5, 0.4)
                    << QPointF(0.6, 0.5) << QPointF(0.5, 0.6)
                    << QPointF(0.4, 0.5);
 }

 QSize StarRating::sizeHint() const
 {
     return PaintingScaleFactor * QSize(myMaxStarCount, 1);
 }

 void StarRating::paint(QPainter *painter, const QRect &rect,
                        const QPalette &palette, EditMode mode) const
 {
     painter->save();

     painter->setRenderHint(QPainter::Antialiasing, true);
     painter->setPen(Qt::NoPen);

	 QIcon icon(":/icons/star.png");
     if (mode == Editable) {
         painter->setBrush(palette.highlight());
     } else {
         painter->setBrush(palette.foreground());
	 }

     int yOffset = (rect.height() - PaintingScaleFactor) / 2;
	 float step = (float)(rect.width() - PaintingScaleFactor) / (myMaxStarCount-1);
     painter->translate(rect.x(), rect.y() + yOffset);
     //painter->scale(PaintingScaleFactor, PaintingScaleFactor);

	 QRect r(0,0,PaintingScaleFactor,PaintingScaleFactor);
     for (int i = 0; i < myMaxStarCount; ++i) {
         if (i < myStarCount) {
             //painter->drawPolygon(starPolygon, Qt::WindingFill);
			 icon.paint(painter, r);
         } else if (mode == Editable) {
             //painter->drawPolygon(diamondPolygon, Qt::WindingFill);
         }
         painter->translate(0.7*PaintingScaleFactor, 0.0);
     }

     painter->restore();
 } 
