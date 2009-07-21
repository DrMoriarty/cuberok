/* Cuberok
 * Copyright (C) 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>
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

#ifndef INDICATOR_H
#define INDICATOR_H

#include <QtCore>
#include <QtGui>

class Indicator: public QObject
{
 Q_OBJECT
 public:
	static Indicator& Self();
	~Indicator();
	void setWidget(QAbstractButton &w);
	int  addTask(QString message);
	void delTask(int ID);

 signals:
	void userStop();

 public slots:
	void stop();
	void update();

 private:
	Indicator();
	void updateWidget();

	struct Task {
		int id;
		QString message;
	};
	QList<struct Task> tasks;
	int counter;
	QAbstractButton *widget;
	//QIcon icon;
	//QPixmap pxN, pxD, pxR[36];
	//int rot;
	QTime time;
};

#endif //INDICATOR_H
