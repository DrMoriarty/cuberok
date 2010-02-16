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

#include "global.h"
#include "psi.h"
#include "psi_settings.h"
#include <QtGui>

Q_EXPORT_PLUGIN2(scrobbler_psi, PsiTune) 

PsiTune::PsiTune() : Extension(), enabled(false)
{
	QSettings set;
	psiTuneFile = set.value("PsiTuneFile", DEFAULT_PSI_TUNE).toString();
}

PsiTune::~PsiTune()
{
}

bool PsiTune::prepare()
{
	QSettings set;
	enabled = set.value("PsiTune", false).toBool();
//	return enabled;
	return true;
}

bool PsiTune::ready()
{
	return enabled;
}

void PsiTune::update(int)
{
	bool listening = false;
	bool changed = false;
	if(/*listening && */proxy->getStatus().playing == SStatus::Stopped) {
		// track finished
		listening = false;
		changed = true;
	}
	if(proxy->getStatus().playing == SStatus::Playing && proxy->getStatus().pos == .0f) {
		// track started
		listening = true;
		changed = true;
	}
	if ( changed ) {
		QFile psiTuneFile(QSettings().value("PsiTuneFile", DEFAULT_PSI_TUNE).toString());
		psiTuneFile.open(QIODevice::WriteOnly | QIODevice::Text);
		QTextStream out(&psiTuneFile);
		if ( listening ) {
			STags t = proxy->getTags();
			out << t.tag0.title << '\n';
			out << t.tag0.artist << '\n';
			out << t.tag0.album << '\n';
			out << t.tag0.track << '\n';
			out << QString::number(t.tag0.length) << '\n';
		} else {
			out << '\n';
		}
		psiTuneFile.close();
	}
}

QString PsiTune::getName()
{
	return tr("PsiTune Scrobbler");
}

QWidget* PsiTune::getWidget()
{
	return 0;
}

QWidget* PsiTune::getSetupWidget()
{
	PsiTuneSettings *set = new PsiTuneSettings();
	connect(set, SIGNAL(destroyed(QObject*)), this, SLOT(settingsUpdate(QObject*)));
	return set;
//	return 0;
}

int PsiTune::getDisturbs()
{
	return DisturbOnStatus;// | DisturbOnTags;
}

void PsiTune::settingsUpdate(QObject* o)
{
	o->disconnect();
	QSettings set;
	bool newEnabled = set.value("PsiTune", false).toBool();
	QString newPsiTuneFile = set.value("PsiTuneFile", DEFAULT_PSI_TUNE).toString();
	if(newEnabled != enabled || newPsiTuneFile != psiTuneFile) {
		enabled = newEnabled;
		psiTuneFile = newPsiTuneFile;
	}
}
