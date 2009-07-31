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
#include "playlistsettings.h"

int WSIZE = 100;

MessageWindow::MessageWindow(QMainWindow *mw, QString mes, int type)
    :QWidget(0, Qt::SplashScreen), closing(false), iterate(0), mainwindow(mw)
{
	switch(PLSet.popupSize) {
	case 0:
		WSIZE = 100;
		break;
	case 1:
		WSIZE = 125;
		break;
	case 2:
	default:
		WSIZE = 150;
		break;
	}
    /*if(mainwindow->isActiveWindow()) {
		setWindowFlags(Qt::Popup);
    }*/
	//setSizePos();
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
	timer = new QTimer(this);
	if(!mainwindow->isActiveWindow()) {
		setSizePos(.0f);
		connect(timer, SIGNAL(timeout()), this, SLOT(updateSize()));
		timer->start(50);
	} else {
		setSizePos();
	}
}

void MessageWindow::updateSize()
{
	iterate ++;
	setSizePos(.05f * iterate);
	if(iterate >= 20) {
		timer->stop();
	}
}

void MessageWindow::setSizePos(float s)
{
	QPoint p;
	if(mainwindow->isActiveWindow())
		p = mainwindow->pos() + QPoint(0, mainwindow->frameGeometry().height() - WSIZE);
	else switch(PLSet.popupPosition) {
		case 0:
			p = QPoint((1.f-s)*(-WSIZE), 0);
			break;
		case 1:
			p = QPoint(QApplication::desktop()->screenGeometry().width() - (s*WSIZE), 0);
			break;
		case 2:
			p = QPoint((1.f-s)*(-WSIZE), QApplication::desktop()->screenGeometry().height() - WSIZE);
			break;
		case 3:
			p = QPoint(QApplication::desktop()->screenGeometry().width() - (s*WSIZE), QApplication::desktop()->screenGeometry().height() - WSIZE);
			break;
		}
	move(p);
	resize(WSIZE, WSIZE);
	update();
}

void MessageWindow::startClose()
{
// 	closing = true;
// 	timer->start(100);
// 	iterate = 0;
}
