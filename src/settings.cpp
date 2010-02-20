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

#include "settings.h"
#include "player_manager.h"
#include "tagger.h"
#include "playlistsettings.h"
#include "main.h"
#include "extensionproxy.h"
#include "extensionsettings.h"

NoeditDelegate::NoeditDelegate(QObject* parent) :  QItemDelegate(parent)
{
}

QWidget* NoeditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem & option, const QModelIndex &index) const
{
	return 0;
}

Settings::Settings(QList< QPair<QString, QList<QAction*> > > *actions, QWidget *parent): QDialog(parent), allactions(actions)
{
	ui.setupUi(this);
	ExtensionSettings * es = new ExtensionSettings();
	ui.tabWidget->addTab(es, tr("Extensions"));
	connect(this, SIGNAL(accepted()), es, SLOT(storeState()));

	QSettings set;
	auto_engine = tr("Auto");
	ui.comboBox_engine->addItem(auto_engine);
	ui.comboBox_engine->addItems(PlayerManager::Self().getPlayers());
	QString engine = set.value("engine", "").toString();
	if(!engine.size()) engine = auto_engine;
	ui.comboBox_engine->setCurrentIndex(ui.comboBox_engine->findText(engine));
	engineChanged(engine);

	ui.comboBox_language->addItem(auto_engine);
	//ui.comboBox_language->addItem(tr("Russian"));
	//ui.comboBox_language->addItem(tr("none"));

	//if(Tagger::autoCorrect()) ui.checkBox_autofix8bit->setCheckState(Qt::Checked);
	//if(Tagger::saveCorrected()) ui.checkBox_autosave->setCheckState(Qt::Checked);

	cbd1 = new ComboBoxDelegate(PlayerManager::Self().getPlayers());
	ui.tableWidget->setItemDelegateForColumn(1, cbd1);
	QStringList audioMimes, allMimes;
	audioMimes << "http";
	audioMimes << "https";
	audioMimes << "mms";
	// TODO other protocols
	QFreeDesktopMime mime;
	allMimes = mime.getList();
	foreach(QString m, allMimes) {
		if(m.contains("audio") || m.contains("ogg")) audioMimes << m;
	}
#if QT_VERSION >= 0x040500
	audioMimes.removeDuplicates();
#endif
	audioMimes.sort();
	cbd2 = new ComboBoxDelegate(audioMimes);
	ui.tableWidget->setItemDelegateForColumn(0, cbd2);
	foreach(QString mime, PLSet.mimeMap.keys()) {
		ui.tableWidget->insertRow(ui.tableWidget->rowCount());
		ui.tableWidget->setItem(ui.tableWidget->rowCount()-1, 0, new QTableWidgetItem(mime));
		ui.tableWidget->setItem(ui.tableWidget->rowCount()-1, 1, new QTableWidgetItem(PLSet.mimeMap[mime]));
	}
	
	if(PLSet.autoRating)
		ui.checkBox_autorating->setCheckState(Qt::Checked);

	if(PLSet.hideEmptyInCollection)
		ui.checkBox_hideEmpty->setCheckState(Qt::Checked);

	QStringList sl;
	foreach(QByteArray it, QTextCodec::availableCodecs ()) {
		sl << QString(it);
	}
	sl.sort();
	ui.comboBox_cue->addItems(sl);
	QString cue_codepage = "System";
	if(EProxy.hasVariable("cue_codepage"))
		cue_codepage = EProxy.getVariable("cue_codepage");
	if(!cue_codepage.size()) cue_codepage = "System";
	ui.comboBox_cue->setCurrentIndex(ui.comboBox_cue->findText(cue_codepage));

	ui.checkBox_proxyEnabled->setChecked(PLSet.proxyEnabled);
	ui.lineEdit_proxyHost->setText(PLSet.proxyHost);
	ui.spinBox_proxyPort->setValue(PLSet.proxyPort);
	ui.lineEdit_proxyUser->setText(PLSet.proxyUser);
	ui.lineEdit_proxyPassword->setText(PLSet.proxyPassword);

	ui.checkBox_cacheInfo->setChecked(PLSet.cacheInfo);

	ui.checkBox_hack1251->setChecked(EProxy.getVariable("hack1251") == "true");

	ui.checkBox_textToolbuttons->setChecked(EProxy.getVariable("textToolbuttons") == "true");
	ui.comboBox_sizeToolbuttons->setCurrentIndex(EProxy.getVariable("sizeToolbuttons").toInt());
	ui.checkBox_controlCuePath->setChecked(EProxy.getVariable("controlCuePath") == "true");
	ui.checkBox_trayMessage->setChecked(EProxy.getVariable("trayMessage") == "true");

	ui.comboBox_defaultPlayer->addItems(PlayerManager::Self().getPlayers());
	ui.comboBox_defaultPlayer->setCurrentIndex(ui.comboBox_defaultPlayer->findText(EProxy.getVariable("defaultPlayer")));

	ui.groupBox_popupMessages->setChecked(EProxy.getVariable("popupMessage") == "true");
	ui.comboBox_popupSize->setCurrentIndex(EProxy.getVariable("popupSize").toInt());
	switch(EProxy.getVariable("popupPosition").toInt()) {
	case 0:
		ui.radioButton_ptl->setChecked(true);
		break;
	case 1:
		ui.radioButton_ptr->setChecked(true);
		break;
	case 2:
		ui.radioButton_pbl->setChecked(true);
		break;
	case 3:
		ui.radioButton_pbr->setChecked(true);
		break;
	}

	// actions
	if(allactions) {
		for(int i = 0; i< allactions->size(); i++) {
			QTreeWidgetItem *it = new QTreeWidgetItem(ui.shortcutTreeWidget);
			it->setText(0, (*allactions)[i].first);
			foreach(QAction* act, (*allactions)[i].second) {
				if(act->text().size()) {
					QTreeWidgetItem *item = new QTreeWidgetItem(it);
					item->setText(0, act->text());
					item->setIcon(0, act->icon());
					item->setText(1, act->shortcut().toString());
					item->setFlags(item->flags() | Qt::ItemIsEditable);
					item->setData(0, Qt::UserRole, QVariant::fromValue((QObject*)act));
				}
			}
		}
	}
	ui.shortcutTreeWidget->setItemDelegateForColumn(0, new NoeditDelegate(ui.shortcutTreeWidget));
}

Settings::~Settings()
{
}

void Settings::accept()
{
	QSettings set;
	QString engine = ui.comboBox_engine->currentText();
	bool s = false;
	if(engine == auto_engine) {
		engine = "";
	}
	s = PlayerManager::Self().setPrefferedPlayer(engine);
	if(s) set.setValue("engine", engine);

	/*
	Tagger::setAutoCorrect(ui.checkBox_autofix8bit->checkState() == Qt::Checked);
	set.setValue("correctTag", Tagger::autoCorrect());
	Tagger::setSaveCorrected(ui.checkBox_autosave->checkState() == Qt::Checked);
	set.setValue("saveCorrected", Tagger::saveCorrected());
	*/
	
	PLSet.autoRating = ui.checkBox_autorating->checkState() == Qt::Checked;

	PLSet.hideEmptyInCollection = ui.checkBox_hideEmpty->checkState() == Qt::Checked;

	EProxy.setVariable("cue_codepage", ui.comboBox_cue->currentText());

	PLSet.proxyEnabled = ui.checkBox_proxyEnabled->isChecked();
	PLSet.proxyHost = ui.lineEdit_proxyHost->text();
	PLSet.proxyPort = ui.spinBox_proxyPort->value();
	PLSet.proxyUser = ui.lineEdit_proxyUser->text();
	PLSet.proxyPassword = ui.lineEdit_proxyPassword->text();

	PLSet.cacheInfo = ui.checkBox_cacheInfo->isChecked();

	EProxy.setVariable("hack1251", ui.checkBox_hack1251->isChecked() ? "true": "false");

	EProxy.setVariable("textToolbuttons", ui.checkBox_textToolbuttons->isChecked()? "true": "false");
	EProxy.setVariable("sizeToolbuttons", QString::number(ui.comboBox_sizeToolbuttons->currentIndex()));
	EProxy.setVariable("controlCuePath", ui.checkBox_controlCuePath->isChecked()? "true": "false");
	EProxy.setVariable("trayMessage", ui.checkBox_trayMessage->isChecked()? "true": "false");

	PLSet.mimeMap.clear();
	for(int i = 0; i<ui.tableWidget->rowCount(); i++) {
		QString mime = ui.tableWidget->item(i, 0)->text();
		QString engine = ui.tableWidget->item(i, 1)->text();
		PLSet.mimeMap[mime] = engine;
	}
	EProxy.setVariable("defaultPlayer", ui.comboBox_defaultPlayer->currentText());
	EProxy.setVariable("popupMessage", ui.groupBox_popupMessages->isChecked()? "true": "false");
	EProxy.setVariable("popupSize", QString::number(ui.comboBox_popupSize->currentIndex()));
	if(ui.radioButton_ptl->isChecked()) EProxy.setVariable("popupPosition", "0");
	else if(ui.radioButton_ptr->isChecked()) EProxy.setVariable("popupPosition", "1");
	else if(ui.radioButton_pbl->isChecked()) EProxy.setVariable("popupPosition", "2");
	else if(ui.radioButton_pbr->isChecked()) EProxy.setVariable("popupPosition", "3");

	// action shortcut
	QTreeWidgetItem *root = ui.shortcutTreeWidget->invisibleRootItem();
	for(int i=0; i<root->childCount(); i++) {
		for(int j=0; j<root->child(i)->childCount(); j++) {
			QAction *act = (QAction*)root->child(i)->child(j)->data(0, Qt::UserRole).value<QObject*>();
			act->setShortcut(QKeySequence::fromString(root->child(i)->child(j)->data(1, Qt::DisplayRole).toString()));
		}
	}
	PLSet.save();
	QDialog::accept();
}

void Settings::engineChanged(QString en)
{
	ui.label_currentEngine->setText(tr("Current engine is '%1'").arg(en));
	if(en == auto_engine) {
		ui.stackedWidget->setCurrentIndex(1);
	} else {
		// no settings
		ui.stackedWidget->setCurrentIndex(0);
	}
}

void Settings::addRow()
{
	ui.tableWidget->insertRow(ui.tableWidget->rowCount());
}

void Settings::removeRow()
{
	ui.tableWidget->removeRow(ui.tableWidget->currentRow());
}

void Settings::shortcutChanged(QTreeWidgetItem* item, int column)
{
	if(column == 0) return;
	QString key = item->data(column, Qt::DisplayRole).toString();
	QString key2 = QKeySequence::fromString(key).toString();
	item->setData(column, Qt::EditRole, key2);
}
