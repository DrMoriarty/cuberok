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

#include "comboboxdelegate.h"

ComboBoxDelegate::ComboBoxDelegate(QStringList list, QObject *parent)
	:QItemDelegate(parent)
{
	sl = list;
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
						  const QModelIndex &index) const
{
	QComboBox *cb = new QComboBox(parent);
	cb->addItems(sl);
	return cb;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QString value = index.model()->data(index, Qt::EditRole).toString();
	QComboBox *comboBox = static_cast<QComboBox*>(editor);
	comboBox->setCurrentIndex(comboBox->findText(value));
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
					  const QModelIndex &index) const
{
	QComboBox *comboBox = static_cast<QComboBox*>(editor);
	model->setData(index, comboBox->currentText(), Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor,
							  const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	editor->setGeometry(option.rect);
}
