/* Cuberok
 * Copyright (C) 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef LOOKANDFEEL_H
#define LOOKANDFEEL_H

#include <QtGui>
#include "ui_lookandfeel.h"

class LookAndFeel : public QDialog
{
    Q_OBJECT

public:
    LookAndFeel(QWidget *parent = 0);
    ~LookAndFeel();
    void previewStyle(QStyle * style);
    void previewPalette(QPalette &palette);

private:
	void setStyleRecursive(QStyle *style, QWidget *wid);
	void setPaletteRecursive(QPalette &palette, QWidget *wid);
	
    Ui::LookAndFeelClass ui;
    QStyle *_style;
    QPalette _palette;
    int _role, _group;

public slots:
	void applyAll();
	void set_style(QString);
	void set_brush(int);
	void set_group(int);
	void set_role(int);
	void set_color();
	void acceptWithApply();
	void quick();
};

#endif // LOOKANDFEEL_H
