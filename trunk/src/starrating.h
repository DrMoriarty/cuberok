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

 #ifndef STARRATING_H
 #define STARRATING_H

 #include <QMetaType>
 #include <QPointF>
 #include <QVector>

 class StarRating
 {
 public:
     enum EditMode { Editable, ReadOnly };

     StarRating(int starCount = 1, int maxStarCount = 5, int measure = 1);

     void paint(QPainter *painter, const QRect &rect,
                const QPalette &palette, EditMode mode) const;
     QSize sizeHint() const;
     int starCount() const { return myStarCount; }
     int maxStarCount() const { return myMaxStarCount; }
     void setStarCount(int starCount) { myStarCount = starCount; }
     void setMaxStarCount(int maxStarCount) { myMaxStarCount = maxStarCount; }
	 int rating() const { return _rating; }

	 static int starMeasure1(int rating);
	 static int starMeasure2(int rating);

 private:
     //QPolygonF starPolygon;
     //QPolygonF diamondPolygon;
     int myStarCount;
     int myMaxStarCount;
	 int _rating;
 };

 Q_DECLARE_METATYPE(StarRating)

 #endif 
