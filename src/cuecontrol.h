/* Cuberok
 * Copyright (C) 2009 Vasiliy Makarov <drmoriarty.0@gmail.com>
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

#ifndef CUECONTROL_H
#define CUECONTROL_H

#include <QtGui>
#include "ui_cuecontrol.h"

class CueControl: public QDialog
{
	Q_OBJECT
 public:
	CueControl(QString cuefile, QString wrongfile, QWidget* parent = 0);
	QString newfile;

 public slots:
	void browse();
	void maybeSave(QAbstractButton*);
	void maybeAccept();
	
 private:
	Ui::CueControl ui;
	QString dir, cue;
	bool errorDuringSave;
};

#endif //CUECONTROL_H
