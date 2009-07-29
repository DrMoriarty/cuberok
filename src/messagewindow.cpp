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

#include "messagewindow.h"
#include "console.h"

MessageWindow::MessageWindow(QMainWindow *mw, QString mes, int type)
	:QWidget(0, Qt::ToolTip), closing(false), iterate(0), mainwindow(mw)
{
	if(mainwindow->isActiveWindow()) {
		setWindowFlags(Qt::Popup);
	}
	setSizePos();
	QBoxLayout *vl = new QBoxLayout(QBoxLayout::TopToBottom, this);
	QFrame *fr = new QFrame(this);
	fr->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
	QBoxLayout *hl = new QBoxLayout(QBoxLayout::LeftToRight, fr);
	hl->setContentsMargins(0, 0, 0, 0);
	vl->addWidget(fr);
	QLabel *label = new QLabel(mes, this);
	label->setWordWrap(true);
	vl->addWidget(label);
	//QPushButton *b = new QPushButton("X", this);
	QPushButton *b = new QPushButton(QIcon(":/icons/edit-add.png"), "", this);
	connect(b, SIGNAL(clicked(bool)), this, SLOT(close()));
	b->setMaximumSize(24, 24);
	hl->addWidget(b);
	QString title;
	QPalette pal(palette());
	switch(type) {
	case Console::C_MES:
		//pal.setColor(QPalette::Window, QColor("white"));
		title = tr("Cuberok");
		break;
	case Console::C_WAR:
		pal.setColor(QPalette::Window, QColor("yellow"));
		title = tr("Warning");
		break;
	case Console::C_ERR:
		pal.setColor(QPalette::Window, QColor("orange"));
		title = tr("Error");
		break;
	case Console::C_FAT:
		pal.setColor(QPalette::Window, QColor("red"));
		title = tr("Fatal error");
		break;
	}
	hl->addWidget(new QLabel(title, this));
	setPalette(pal);
	//setAttribute(Qt::WA_DeleteOnClose);
	QTimer::singleShot(10000, this, SLOT(close()));
	//timer = new QTimer(this);
	//connect(timer, SIGNAL(timeout()), this, SLOT(updateSize()));
	//timer->start(100);
}

void MessageWindow::updateSize()
{
// 	iterate ++;
// 	int h;
// 	if(closing) h = 150 - iterate * 15;
// 	else h = iterate * 15;
// 	QPoint p = mainwindow->pos() + QPoint(0, mainwindow->height() - h);
// 	move(p);
// 	resize(150, h);
// 	if(iterate >= 10) {
// 		timer->stop();
// 		if(closing) close();
// 	}
}

void MessageWindow::setSizePos(float s)
{
	QPoint p;
	if(mainwindow->isActiveWindow())
		p = mainwindow->pos() + QPoint(0, mainwindow->frameGeometry().height() - 150*s);
	else
		p = QPoint(0, QApplication::desktop()->screenGeometry().height() - 150*s);
	move(p);
	resize(150, 150 * s);
}

void MessageWindow::startClose()
{
// 	closing = true;
// 	timer->start(100);
// 	iterate = 0;
}
