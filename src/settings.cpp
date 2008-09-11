/* Cuberok
 * Copyright (C) 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this software; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "settings.h"
#include "player_manager.h"
#include "tagger.h"
#include "playlistsettings.h"

Settings::Settings(QWidget *parent): QDialog(parent)
{
	ui.setupUi(this);
	QSettings set;
	auto_engine = tr("Auto");
	ui.comboBox_engine->addItem(auto_engine);
	ui.comboBox_engine->addItems(PlayerManager::Self().getPlayers());
	QString engine = set.value("engine", "").toString();
	if(!engine.size()) engine = auto_engine;
	ui.comboBox_engine->setCurrentIndex(ui.comboBox_engine->findText(engine));

	ui.comboBox_language->addItem(auto_engine);
	//ui.comboBox_language->addItem(tr("Russian"));
	//ui.comboBox_language->addItem(tr("none"));

	if(Tagger::autoCorrect()) ui.checkBox_autofix8bit->setCheckState(Qt::Checked);
	if(Tagger::saveCorrected()) ui.checkBox_autosave->setCheckState(Qt::Checked);

	if(PLSet.autoRating)
		ui.checkBox_autorating->setCheckState(Qt::Checked);

	QStringList sl;
	foreach(QByteArray it, QTextCodec::availableCodecs ()) {
		sl << QString(it);
	}
	sl.sort();
	ui.comboBox_cue->addItems(sl);
	QString cue_codepage = set.value("cue_codepage", "System").toString();
	if(!cue_codepage.size()) cue_codepage = "System";
	ui.comboBox_cue->setCurrentIndex(ui.comboBox_cue->findText(cue_codepage));

	if(PLSet.proxyEnabled) ui.checkBox_proxyEnabled->setCheckState(Qt::Checked);
	ui.lineEdit_proxyHost->setText(PLSet.proxyHost);
	ui.spinBox_proxyPort->setValue(PLSet.proxyPort);
	ui.lineEdit_proxyUser->setText(PLSet.proxyUser);
	ui.lineEdit_proxyPassword->setText(PLSet.proxyPassword);

	if(PLSet.lastfmScrobbler) ui.checkBox_lastfmScrobbling->setCheckState(Qt::Checked);
	ui.lineEdit_lastfmUser->setText(PLSet.lastfmUser);
	ui.lineEdit_lastfmPassword->setText(PLSet.lastfmPassword);
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
		s = PlayerManager::Self().prepare();
	} else {
		s = PlayerManager::Self().setPrefferedPlayer(engine);
	}
	if(s) set.setValue("engine", engine);

	Tagger::setAutoCorrect(ui.checkBox_autofix8bit->checkState() == Qt::Checked);
	set.setValue("correctTag", Tagger::autoCorrect());
	Tagger::setSaveCorrected(ui.checkBox_autosave->checkState() == Qt::Checked);
	set.setValue("saveCorrected", Tagger::saveCorrected());
	
	PLSet.autoRating = ui.checkBox_autorating->checkState() == Qt::Checked;

	PLSet.cue_codepage = ui.comboBox_cue->currentText();

	PLSet.proxyEnabled = ui.checkBox_proxyEnabled->checkState() == Qt::Checked;
	PLSet.proxyHost = ui.lineEdit_proxyHost->text();
	PLSet.proxyPort = ui.spinBox_proxyPort->value();
	PLSet.proxyUser = ui.lineEdit_proxyUser->text();
	PLSet.proxyPassword = ui.lineEdit_proxyPassword->text();

	PLSet.lastfmScrobbler = ui.checkBox_lastfmScrobbling->checkState() == Qt::Checked;
	PLSet.lastfmUser = ui.lineEdit_lastfmUser->text();
	PLSet.lastfmPassword = ui.lineEdit_lastfmPassword->text();

	PLSet.save();
	QDialog::accept();
}
