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

#include "progressbar.h"

ProgressBar::ProgressBar ( QWidget * parent ) : QProgressBar(parent) 
{
	connect(this, SIGNAL(valueChanged(int)), this, SLOT(updateFormat()));
}

void ProgressBar::mousePressEvent ( QMouseEvent * event ) 
{
	if(orientation() == Qt::Horizontal)
		emit userevent((double)event->x()/width());
	else 
		emit userevent((double)(height()-event->y())/height());
}

void ProgressBar::setDuration (long duration)
{
	_duration = duration;
}

void ProgressBar::setFormatText(QString s)
{
	_text = s;
}

void ProgressBar::updateFormat()
{
	QString format;
	QTime t1, t2;
	t1 = t1.addSecs((float)_duration * (value() - minimum()) / (maximum() - minimum()));
	t2 = t2.addSecs(_duration);
	format = _text + " " + t1.toString() + "/" + t2.toString();
	setFormat(format);
	setToolTip(format);
}
