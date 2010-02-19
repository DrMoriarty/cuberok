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
 
#ifndef PSI_SETTINGS_H
#define PSI_SETTINGS_H

#include <QtGui>

#ifdef WIN32
#define DEFAULT_PSI_TUNE (QDir::homePath()+"/PsiData/tune")
#else
#define DEFAULT_PSI_TUNE (QDir::homePath()+"/.psi/tune")
#endif

#define DEFAULT_KOPETE_STATUS (tr("[Cuberok] I am listening to '%song%' by %artist%"))

class PsiTuneSettings : public ExtensionSetupWidget
{
	Q_OBJECT
 public:
	PsiTuneSettings(QWidget *parent = 0);
	~PsiTuneSettings();
	virtual void storeState();

 private:
    QLineEdit *lineEdit_psiTuneFile, *lineEdit_kopeteStatus;
    QGroupBox *checkBox_enable, *groupBox_enableKopete;
	QCheckBox *checkBox_notifyEnable;
};

#endif //PSI_SETTINGS_H
