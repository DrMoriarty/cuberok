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

#ifndef SRC_LIBRARY_H
#define SRC_LIBRARY_H

#include "interfaces.h"
#include "librarywidget.h"

class SrcLibrary : public Extension
{
	Q_OBJECT
	Q_INTERFACES(Extension) 

 public:
	SrcLibrary();
	virtual ~SrcLibrary();

	virtual bool prepare();
	virtual bool ready();
	virtual void update(int);
	virtual QString getName();
	virtual QString getAuthor();
	virtual QString getDescription();
	virtual QWidget* getWidget();
	virtual ExtensionSetupWidget* getSetupWidget();
	virtual int getDisturbs();
	virtual void storeState();

 private:
	LibraryWidget* widget;
};

#endif //SRC_LIBRARY_H
