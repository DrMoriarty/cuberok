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

#include "cuecontrol.h"

CueControl::CueControl(QString cuefile, QString wrongfile, QWidget* parent) : QDialog(parent), cue(cuefile), errorDuringSave(false)
{
	ui.setupUi(this);
	QFileInfo fi(wrongfile);
	dir = fi.absolutePath();
	ui.lineEdit->setText(fi.fileName());
}

void CueControl::browse()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Select an image file"), dir, tr("Audio images (*.flac *.ape *.wav);;All files (*.*)"));
	if(path.size()) {
		ui.lineEdit->setText(path);
	}
}

void CueControl::maybeSave(QAbstractButton* button)
{
	newfile = ui.lineEdit->text();
	switch(ui.buttonBox->standardButton(button)) {
	case QDialogButtonBox::Save:
		{
			if(QFileInfo(newfile).isRelative()) newfile = dir+QDir::separator()+newfile;
			if(!QFileInfo(newfile).exists()) {
				QMessageBox::warning(this, tr("Error"), tr("File %1 not found!").arg(newfile));
				errorDuringSave = true;
				return;
			}
			newfile = ui.lineEdit->text();
			QFileInfo cueinfo(cue);
			QFile fin(cue), fout(cueinfo.path() + QDir::separator() + cueinfo.completeBaseName()+"_fixed.cue");
			if(!fin.open(QFile::ReadOnly) || !fout.open(QFile::WriteOnly)) {
				QMessageBox::critical(this, tr("Error"), tr("Unable to create file %1").arg(fout.fileName()));
				errorDuringSave = true;
				return;
			}
			QTextStream sin(&fin), sout(&fout);
			QString line;
			do {
				line = sin.readLine();
				if(line.startsWith("FILE")) {
					//QStringList l = line.split(' ', QString::SkipEmptyParts);
					sout << "FILE \"" << newfile << "\" WAVE";// << l.last();
				} else {
					sout << line;
				}
				endl(sout);
			} while (!line.isNull());
			fin.close();
			fout.close();
			QMessageBox::information(this, tr("Success"), tr("New CUE sheet stored as %1").arg(fout.fileName()));
			accept();
			break;
		}
	default:
		break;
	}
}

void CueControl::maybeAccept()
{
	if(errorDuringSave) {
		errorDuringSave = false;
		return;
	}
	newfile = ui.lineEdit->text();
	if(QFileInfo(newfile).isRelative()) newfile = dir+QDir::separator()+newfile;
	if(!QFileInfo(newfile).exists()) {
		QMessageBox::warning(this, tr("Error"), tr("File %1 not found!").arg(newfile));
		return;
	}
	accept();
}
