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

#ifndef PSISCROBBLER_H
#define PSISCROBBLER_H

#include "interfaces.h"

class PsiTune : public Extension
{
	Q_OBJECT
	Q_INTERFACES(Extension) 

 public:
	PsiTune();
	virtual ~PsiTune();

	virtual bool prepare();
	virtual bool ready();
	virtual void update(int);
	virtual QString getName();
	virtual QWidget* getWidget();
	virtual QWidget* getSetupWidget();
	virtual int getDisturbs();

 private:
	bool enabled, kopeteEnabled, kdeNotify;
	QString psiTuneFile, kopeteStatus;

 private slots:
	void settingsUpdate(QObject*);
};

#endif // PSISCROBBLER_H
