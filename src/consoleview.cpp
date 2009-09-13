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

#include "consoleview.h"

/**************
 *
 * ConsoleView
 *
 **************/

ConsoleView::ConsoleView(QWidget *parent) : QDialog(parent), type(Console::C_MES)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	QActionGroup *viewGroup = new QActionGroup(this);
    viewGroup->addAction(ui.actionAll);
    viewGroup->addAction(ui.actionMessages);
    viewGroup->addAction(ui.actionWarnings);
    viewGroup->addAction(ui.actionErrors);
    viewGroup->addAction(ui.actionFatal_Errors);
    ui.actionMessages->setChecked(true);
	refresh();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));
}

ConsoleView::~ConsoleView()
{
	delete timer;
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
	if(b) timer->start(2000);
	else timer->stop();
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
