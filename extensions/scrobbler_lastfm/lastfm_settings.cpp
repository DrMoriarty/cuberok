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

#include "lastfm_settings.h"

LastFMSettings::LastFMSettings(QWidget *parent) : QWidget(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);

	gridLayout3 = new QGridLayout(this);
	gridLayout3->setSpacing(4);
	gridLayout3->setMargin(4);
	gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
	
    checkBox_lastfmScrobbling = new QGroupBox(this);
    checkBox_lastfmScrobbling->setObjectName(QString::fromUtf8("checkBox_lastfmScrobbling"));
    checkBox_lastfmScrobbling->setFlat(true);
    checkBox_lastfmScrobbling->setCheckable(true);
    checkBox_lastfmScrobbling->setChecked(false);
	checkBox_lastfmScrobbling->setTitle(QApplication::translate("LastFM", "Enable Last.FM scrobbling", 0, QApplication::UnicodeUTF8));
    gridLayout5 = new QGridLayout(checkBox_lastfmScrobbling);
    gridLayout5->setSpacing(4);
    gridLayout5->setMargin(0);
    gridLayout5->setObjectName(QString::fromUtf8("gridLayout5"));
    label_11 = new QLabel(checkBox_lastfmScrobbling);
    label_11->setObjectName(QString::fromUtf8("label_11"));
	label_11->setText(QApplication::translate("LastFM", "User name", 0, QApplication::UnicodeUTF8));

    gridLayout5->addWidget(label_11, 0, 0, 1, 1);

    lineEdit_lastfmUser = new QLineEdit(checkBox_lastfmScrobbling);
    lineEdit_lastfmUser->setObjectName(QString::fromUtf8("lineEdit_lastfmUser"));

    gridLayout5->addWidget(lineEdit_lastfmUser, 0, 1, 1, 1);

    label_12 = new QLabel(checkBox_lastfmScrobbling);
    label_12->setObjectName(QString::fromUtf8("label_12"));
	label_12->setText(QApplication::translate("LastFM", "Password", 0, QApplication::UnicodeUTF8));

    gridLayout5->addWidget(label_12, 1, 0, 1, 1);

    lineEdit_lastfmPassword = new QLineEdit(checkBox_lastfmScrobbling);
    lineEdit_lastfmPassword->setObjectName(QString::fromUtf8("lineEdit_lastfmPassword"));
    lineEdit_lastfmPassword->setEchoMode(QLineEdit::Password);

    gridLayout5->addWidget(lineEdit_lastfmPassword, 1, 1, 1, 1);

    gridLayout3->addWidget(checkBox_lastfmScrobbling, 1, 0, 2, 1);
    verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout3->addItem(verticalSpacer_2, 3, 0, 1, 1);

    QIcon icon4;
    icon4.addPixmap(QPixmap(QString::fromUtf8(":/icons/lastfm.png")), QIcon::Normal, QIcon::Off);
	setWindowIcon(icon4);

	QSettings set;
	checkBox_lastfmScrobbling->setChecked(set.value("lastfmScrobbler", false).toBool());
	lineEdit_lastfmUser->setText(set.value("lastfmUser", "").toString());
	lineEdit_lastfmPassword->setText(set.value("lastfmPassword", "").toString());

}

LastFMSettings::~LastFMSettings()
{
	QSettings set;
	set.setValue("lastfmScrobbler", checkBox_lastfmScrobbling->isChecked());
	set.setValue("lastfmUser", lineEdit_lastfmUser->text());
	set.setValue("lastfmPassword", lineEdit_lastfmPassword->text());
}
