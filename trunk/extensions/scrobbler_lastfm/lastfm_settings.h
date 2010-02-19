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
 
#ifndef LASTFM_SETTINGS_H
#define LASTFM_SETTINGS_H

#include <QtGui>

class LastFMSettings : public ExtensionSetupWidget
{
	Q_OBJECT
 public:
	LastFMSettings(QWidget *parent = 0);
	~LastFMSettings();
	virtual void storeState();

 private:
    QSpacerItem *verticalSpacer_2;
    QGridLayout *gridLayout3;
    QGridLayout *gridLayout4;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *lineEdit_lastfmUser;
    QLineEdit *lineEdit_lastfmPassword;
    QGroupBox *checkBox_lastfmScrobbling;
    QGridLayout *gridLayout5;
    QLabel *label_11;
    QLabel *label_12;
};

#endif //LASTFM_SETTINGS_H
