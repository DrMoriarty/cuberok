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

#include "infowidget.h"

Q_EXPORT_PLUGIN2(infowidget, InfoWidget) 

InfoWidget::InfoWidget(QWidget *parent) : Extension(), info(0)
{
}

InfoWidget::~InfoWidget()
{
}

bool InfoWidget::prepare()
{
	return true;
}

bool InfoWidget::ready()
{
	return enabled;
}

void InfoWidget::update(int d)
{
	if(d & DisturbOnTags) info->updateTags(proxy->getTags());
	if(d & DisturbOnInfo) info->updateInfo();
}

QString InfoWidget::getName()
{
	return tr("Info widget");
}

QWidget* InfoWidget::getWidget()
{
	if(!info) info = new Info();
	return info;
}

QWidget* InfoWidget::getSetupWidget()
{
	return 0;
}

int InfoWidget::getDisturbs()
{
	return /*DisturbOnStatus |*/ DisturbOnTags | DisturbOnInfo;
}
