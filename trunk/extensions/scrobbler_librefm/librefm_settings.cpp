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

#include "librefm_settings.h"

LibreFMSettings::LibreFMSettings(QWidget *parent) : QWidget(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);

	gridLayout3 = new QGridLayout(this);
	gridLayout3->setSpacing(4);
	gridLayout3->setMargin(4);
	gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
	
    checkBox_librefmScrobbling = new QGroupBox(this);
    checkBox_librefmScrobbling->setObjectName(QString::fromUtf8("checkBox_librefmScrobbling"));
    checkBox_librefmScrobbling->setFlat(true);
    checkBox_librefmScrobbling->setCheckable(true);
    checkBox_librefmScrobbling->setChecked(false);
    gridLayout5 = new QGridLayout(checkBox_librefmScrobbling);
    gridLayout5->setSpacing(4);
    gridLayout5->setMargin(0);
    gridLayout5->setObjectName(QString::fromUtf8("gridLayout5"));
    label_11 = new QLabel(checkBox_librefmScrobbling);
    label_11->setObjectName(QString::fromUtf8("label_11"));

    gridLayout5->addWidget(label_11, 0, 0, 1, 1);

    lineEdit_librefmUser = new QLineEdit(checkBox_librefmScrobbling);
    lineEdit_librefmUser->setObjectName(QString::fromUtf8("lineEdit_librefmUser"));

    gridLayout5->addWidget(lineEdit_librefmUser, 0, 1, 1, 1);

    label_12 = new QLabel(checkBox_librefmScrobbling);
    label_12->setObjectName(QString::fromUtf8("label_12"));

    gridLayout5->addWidget(label_12, 1, 0, 1, 1);

    lineEdit_librefmPassword = new QLineEdit(checkBox_librefmScrobbling);
    lineEdit_librefmPassword->setObjectName(QString::fromUtf8("lineEdit_librefmPassword"));
    lineEdit_librefmPassword->setEchoMode(QLineEdit::Password);

    gridLayout5->addWidget(lineEdit_librefmPassword, 1, 1, 1, 1);

    gridLayout3->addWidget(checkBox_librefmScrobbling, 1, 0, 2, 1);
    verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout3->addItem(verticalSpacer_2, 3, 0, 1, 1);

    QIcon icon4;
    icon4.addPixmap(QPixmap(QString::fromUtf8(":/icons/librefm.png")), QIcon::Normal, QIcon::Off);
	setWindowIcon(icon4);

	QSettings set;
	checkBox_librefmScrobbling->setChecked(set.value("librefmScrobbler", false).toBool());
	lineEdit_librefmUser->setText(set.value("librefmUser", "").toString());
	lineEdit_librefmPassword->setText(set.value("librefmPassword", "").toString());
}

LibreFMSettings::~LibreFMSettings()
{
	QSettings set;
	set.setValue("librefmScrobbler", checkBox_librefmScrobbling->isChecked());
	set.setValue("librefmUser", lineEdit_librefmUser->text());
	set.setValue("librefmPassword", lineEdit_librefmPassword->text());
}
