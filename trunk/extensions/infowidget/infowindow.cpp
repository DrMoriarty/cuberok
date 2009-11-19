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

#include <QtXml>
#include "infowindow.h"

InfoWindow::InfoWindow(Proxy *pr, QWidget *parent) : QDialog(parent), proxy(pr)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
}

InfoWindow::~InfoWindow()
{
}

void InfoWindow::setText(QString text)
{
	/*
	// remove any <img> tags from html
	QDomDocument doc;
	QString errString;
	int errLine = 0, errColumn = 0;
	QTextDocument tdoc;
	tdoc.setHtml(text);
	if(!doc.setContent(tdoc.toHtml(), &errString, &errLine, &errColumn)) {
		proxy->error(tr("Info window error: %1 at line %2 column %3").arg(errString).arg(QString::number(errLine)).arg(QString::number(errColumn)));
		return;
	}
	QDomNodeList l = doc.elementsByTagName("img");
	for(int i=0; i<l.size(); i++) {
		QDomNode parent = l.at(i).parentNode();
		if(parent.isNull()) continue;
		parent = parent.removeChild(l.at(i));
		if(parent.isNull()) {
			proxy->warning("Info window: can't remove img tag");
			// error
		}
	}
	*/
	ui.textEdit->document()->setHtml(text);
}
