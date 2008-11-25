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

#ifndef CONSOLE_H
#define CONSOLE_H

#include <QtCore>
#include <QtGui>
#include "ui_console.h"

class Console: public QObject
{
	Q_OBJECT
 public:
	enum C_TYPE {C_NONE=0, C_MES, C_WAR, C_ERR, C_FAT};

	typedef struct _Log {
		C_TYPE type;
		uint time;
		QString text;
	} Log;

	~Console();
	static Console& Self();
	void fatal(const QString&);
	void error(const QString&);
	void warning(const QString&);
	void message(const QString&);

	void log(const QString&, C_TYPE t = C_NONE);

	QStringList plainText(C_TYPE t = C_NONE);
	QString htmlText(C_TYPE t = C_NONE);

	void clear();

	C_TYPE getLevel();
 signals:
	void newMessage(QString, int);

 private:
	Console();

	QVector<Log> logs;
	C_TYPE level;
};

class ConsoleView: public QDialog
{
	Q_OBJECT
 public:
	ConsoleView(QWidget *parent=0);
	~ConsoleView();

 public slots:
	void clear();
	void refresh();
	void autorefresh(bool);
	void all(bool);
	void message(bool);
	void warning(bool);
	void error(bool);
	void fatal(bool);

 private:
	Ui::ConsoleWindow ui;
	Console::C_TYPE type;
	QTimer *timer;
};

#endif // CONSOLE_H
