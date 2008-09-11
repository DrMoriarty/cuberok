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

#include "console.h"

/**************
 *
 * Console
 *
 **************/

Console::Console()
{
}

Console::~Console()
{
}

Console& Console::Self()
{
	static Console self;
	return self;
}

void Console::fatal(const QString& s)
{
	log(s, C_FAT);
}

void Console::error(const QString& s)
{
	log(s, C_ERR);
}

void Console::warning(const QString& s)
{
	log(s, C_WAR);
}

void Console::message(const QString& s)
{
	log(s, C_MES);
}

void Console::log(const QString& s, C_TYPE t)
{
	Log log;
	
	log.type = t;
	log.time = QDateTime::currentDateTime().toTime_t();
	log.text = s;
	
	logs << log;
}

QStringList Console::plainText(C_TYPE t)
{
	QStringList list;
	foreach(Log log, logs) if(log.type >= t) {
		QString s;
		switch(log.type) {
		case C_NONE: s = "  "; break;
		case C_MES:  s = "M "; break;
		case C_WAR:  s = "W "; break;
		case C_ERR:  s = "E "; break;
		case C_FAT:  s = "F "; break;
		}
		s += QDateTime::fromTime_t(log.time).toString();
		s += " ";
		s += log.text;
		list << s;
	}
	return list;
}

QString Console::htmlText(C_TYPE t)
{
	QString html;
	foreach(Log log, logs) if(log.type >= t) {
		QString s;
		switch(log.type) {
		case C_NONE: s = "<p style='color:gray; '>"; break;
		case C_MES:  s = "<p style='color:black; background-color:white;'>"; break;
		case C_WAR:  s = "<p style='color:black; background-color:yellow;'>"; break;
		case C_ERR:  s = "<p style='color:black; background-color:orange;font:bold;'>"; break;
		case C_FAT:  s = "<p style='color:black; background-color:red;font:bold;'>"; break;
		}
		s += QDateTime::fromTime_t(log.time).toString();
		s += " ";
		s += log.text;
		s += "</p>";
		html += s;
	}
	return html;
}

void Console::clear()
{
	logs.clear();
}


/**************
 *
 * ConsoleView
 *
 **************/

ConsoleView::ConsoleView(QWidget *parent) : QDialog(parent), type(Console::C_NONE)
{
	ui.setupUi(this);
	QActionGroup *viewGroup = new QActionGroup(this);
    viewGroup->addAction(ui.actionAll);
    viewGroup->addAction(ui.actionMessages);
    viewGroup->addAction(ui.actionWarnings);
    viewGroup->addAction(ui.actionErrors);
    viewGroup->addAction(ui.actionFatal_Errors);
    ui.actionAll->setChecked(true);
	refresh();
}

ConsoleView::~ConsoleView()
{
}

void ConsoleView::clear()
{
	Console::Self().clear();
	refresh();
}

void ConsoleView::refresh()
{
	ui.textEdit->document()->setHtml(Console::Self().htmlText(type));
}

void ConsoleView::autorefresh(bool b)
{
	// TODO
}

void ConsoleView::all(bool b)
{
	type = Console::C_NONE;
	refresh();
}

void ConsoleView::message(bool b)
{
	type = Console::C_MES;
	refresh();
}

void ConsoleView::warning(bool b)
{
	type = Console::C_WAR;
	refresh();
}

void ConsoleView::error(bool b)
{
	type = Console::C_ERR;
	refresh();
}

void ConsoleView::fatal(bool b)
{
	type = Console::C_FAT;
	refresh();
}
