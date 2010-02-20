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

#include "psi_settings.h"


PsiTuneSettings::PsiTuneSettings(QWidget *parent) : ExtensionSetupWidget(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);

	QIcon icon4;
	icon4.addPixmap(QPixmap(QString::fromUtf8(":/icons/psi.png")), QIcon::Normal, QIcon::Off);
	setWindowIcon(icon4);

	QVBoxLayout *gridLayout3 = new QVBoxLayout(this);
	gridLayout3->setSpacing(4);
	gridLayout3->setMargin(4);
	gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
	
	checkBox_enable = new QGroupBox(this);
	checkBox_enable->setObjectName(QString::fromUtf8("checkBox_enable"));
	checkBox_enable->setFlat(true);
	checkBox_enable->setCheckable(true);
	checkBox_enable->setChecked(false);
	checkBox_enable->setTitle(QApplication::translate("Psi Tune", "Enable psi publish tune", 0, QApplication::UnicodeUTF8));

	QGridLayout *gridLayout5 = new QGridLayout(checkBox_enable);
	gridLayout5->setSpacing(4);
	gridLayout5->setMargin(0);
	gridLayout5->setObjectName(QString::fromUtf8("gridLayout5"));

	QLabel *label_12 = new QLabel(checkBox_enable);
	label_12->setObjectName(QString::fromUtf8("label_12"));
	label_12->setText(QApplication::translate("Psi Tune", "File to publish tune", 0, QApplication::UnicodeUTF8));

	gridLayout5->addWidget(label_12, 1, 0, 1, 1);

	lineEdit_psiTuneFile = new QLineEdit(checkBox_enable);
	lineEdit_psiTuneFile->setObjectName(QString::fromUtf8("lineEdit_psiTuneFile"));

	gridLayout5->addWidget(lineEdit_psiTuneFile, 1, 1, 1, 1);

	gridLayout3->addWidget(checkBox_enable);


	groupBox_enableKopete = new QGroupBox(this);
	groupBox_enableKopete->setObjectName(QString::fromUtf8("groupBox_enableKopete"));
	groupBox_enableKopete->setFlat(true);
	groupBox_enableKopete->setCheckable(true);
	groupBox_enableKopete->setChecked(false);
	groupBox_enableKopete->setTitle(QApplication::translate("Psi Tune", "Enable kopete publish tune", 0, QApplication::UnicodeUTF8));

	QGridLayout *gridLayout4 = new QGridLayout(groupBox_enableKopete);
	gridLayout4->setSpacing(4);
	gridLayout4->setMargin(0);
	gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));

	QLabel *label_1 = new QLabel(checkBox_enable);
	label_1->setObjectName(QString::fromUtf8("label_1"));
	label_1->setText(QApplication::translate("Psi Tune", "Status line", 0, QApplication::UnicodeUTF8));

	gridLayout4->addWidget(label_1, 1, 0, 1, 1);

	lineEdit_kopeteStatus = new QLineEdit(groupBox_enableKopete);
	lineEdit_kopeteStatus->setObjectName(QString::fromUtf8("lineEdit_kopeteStatus"));

	gridLayout4->addWidget(lineEdit_kopeteStatus, 1, 1, 1, 1);
	gridLayout3->addWidget(groupBox_enableKopete);

	checkBox_notifyEnable = new QCheckBox(this);
	checkBox_notifyEnable->setObjectName(QString::fromUtf8("checkBox_notifyEnable"));
	checkBox_notifyEnable->setText(QApplication::translate("Psi Tune", "Enable KDE4 notification", 0, QApplication::UnicodeUTF8));
	gridLayout3->addWidget(checkBox_notifyEnable);

	QSpacerItem *verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	gridLayout3->addItem(verticalSpacer_2);

	QSettings set;
	set.beginGroup("im_tune");
	checkBox_enable->setChecked(set.value("PsiTune", false).toBool());
	lineEdit_psiTuneFile->setText(set.value("PsiTuneFile", DEFAULT_PSI_TUNE).toString());
	groupBox_enableKopete->setChecked(set.value("KopeteTune", false).toBool());
	lineEdit_kopeteStatus->setText(set.value("KopeteStatus", DEFAULT_KOPETE_STATUS).toString());
	checkBox_notifyEnable->setChecked(set.value("KdeNotify", true).toBool());
	set.endGroup();
#ifndef Q_OS_LINUX
	groupBox_enableKopete->setEnabled(false);
	checkBox_notifyEnable->setEnabled(false);
#endif
}

PsiTuneSettings::~PsiTuneSettings()
{
}

void PsiTuneSettings::storeState()
{
	QSettings set;
	set.beginGroup("im_tune");
	set.setValue("PsiTune", checkBox_enable->isChecked());
	set.setValue("PsiTuneFile", lineEdit_psiTuneFile->text());
	set.setValue("KopeteTune", groupBox_enableKopete->isChecked());
	set.setValue("KopeteStatus", lineEdit_kopeteStatus->text());
	set.setValue("KdeNotify", checkBox_notifyEnable->isChecked());
	set.endGroup();
}
