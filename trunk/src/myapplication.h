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

#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include <QtGui>
#include <QApplication>

extern QString style_name;

class MyApplication : public QApplication
{
	Q_OBJECT
 public:
	MyApplication ( int & argc, char ** argv );
	
	virtual void commitData(QSessionManager &manager);
	virtual void saveState ( QSessionManager & manager );

	// application
	static void storeState();
	// main window
	void storeState(QMainWindow *win);
	// application
	static bool restoreState();
	// main window
	bool restoreState(QMainWindow *win);
	void canStore(bool c);
 private:
	QMainWindow *mainwindow;
	bool canstore;
};

#endif //MYAPPLICATION_H
