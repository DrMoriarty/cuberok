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

#ifndef FILEBROWSERWIDGET_H
#define FILEBROWSERWIDGET_H

#include <QtGui>
#include "ui_filebrowser.h"

class FileBrowserWidget : public QWidget
{
	Q_OBJECT
 public:
	FileBrowserWidget(QWidget *parent = 0);
	~FileBrowserWidget();
	void storeState();

 public slots:

	void refreshTree();
	void setCurrent_files(const QModelIndex &index);
	void setBookmark();
	void removeBookmark();
	void selectBookmark(QListWidgetItem*);
	void selectBookmark(QString);
	void setRootCurrent();
	void oneLevelUp();
	void changeRootIndex_files(const QModelIndex &index);
	void rememberStart_files();
	void showFiles(bool);

 private:
	Ui::FileBrowserWidget ui;
    QDirModel dirmodel;
	bool filesShowed;
};

#endif //FILEBROWSERWIDGET_H
