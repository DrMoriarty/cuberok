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

#include "marklistwidget.h"

MarkListWidget::MarkListWidget(QWidget* parent) : QListWidget(parent)
{
}

QStringList MarkListWidget::mimeTypes() const
{
    QStringList types;
	types.append("text/uri-list");
	types.append("text/plain");
    //types << QLatin1String("application/x-qabstractitemmodeldatalist");
    return types;
}

bool MarkListWidget::dropMimeData(int index, const QMimeData* data, Qt::DropAction action)
{
    if (action == Qt::IgnoreAction)
        return true;
    
	if(data->hasUrls()) {
		foreach(QUrl url, data->urls()) {
			addItem(url.toLocalFile());
		}
	} else if(data->hasText()) {
		addItem(data->text());
	} else return true;
    return true;
}
