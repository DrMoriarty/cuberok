/* Cuberok
 * Copyright (C) 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>
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

#include "console.h"

/**************
 *
 * Console
 *
 **************/

Console::Console() : level(C_NONE), enabled(true)
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
	if(!enabled) return;
	fprintf(stderr, "%s\n", (const char*)s.toLocal8Bit());
	Log log;
	
	log.type = t;
	log.time = QDateTime::currentDateTime().toTime_t();
	log.text = s;
	
	logs << log;

	if(t > level) level = t;
	if(logs.size() > MAXLOGSIZE) {
		Log l = logs.front();
		logs.pop_front();
		if(l.type == level) {
			C_TYPE _level = C_NONE;
			foreach(Log l, logs) {
				if(l.type > _level) _level = l.type;
			}
			level = _level;
		}
	}
	emit newMessage(s, t);
}

void Console::disableLog()
{
	enabled = false;
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
		list.push_front(s);
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
		html = s + html;
	}
	return html;
}

void Console::clear()
{
	logs.clear();
}

Console::C_TYPE Console::getLevel()
{
	return level;
}

