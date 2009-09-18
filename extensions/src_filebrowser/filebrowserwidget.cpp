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

#include "filebrowserwidget.h"

FileBrowserWidget::FileBrowserWidget(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);
	QSettings set;
	dirmodel.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
	ui.treeView_2->setModel(&dirmodel);
	ui.treeView_2->hideColumn(1);
	ui.treeView_2->hideColumn(2);
	ui.treeView_2->hideColumn(3);
	ui.treeView_2->setAllColumnsShowFocus(true);
	ui.treeView_2->sortByColumn(0, Qt::AscendingOrder);
	ui.treeViewLabel->setVisible(false);
	//ui.treeView_2->actions().append(ui.actionRefreshTree);
	setCurrent_files(dirmodel.index(set.value("filesStartDir", QDir::homePath()).toString())); // move treeView_2 to homedir
	QByteArray arr;
	arr = qVariantValue<QByteArray>(set.value("filesplitter"));
	ui.widget->restoreState(arr);

	ui.list_bookmarks->addItems(qVariantValue<QStringList>(set.value("bookmarks")));
}

FileBrowserWidget::~FileBrowserWidget()
{
}

void FileBrowserWidget::storeState()
{
	QSettings set;
	QStringList marks;
	for(int i=0; i<ui.list_bookmarks->count(); i++) {
		marks << ui.list_bookmarks->item(i)->text();
	}
	set.setValue("bookmarks", marks);
	QByteArray arr;
	arr = ui.widget->saveState();
	set.setValue("filesplitter", arr);
}

void FileBrowserWidget::refreshTree()
{
	dirmodel.refresh();
}

void FileBrowserWidget::setBookmark() // 'files' dock widget
{
	ui.list_bookmarks->addItem(dirmodel.filePath(ui.treeView_2->currentIndex()));
}

void FileBrowserWidget::removeBookmark() // 'files' dock widget
{
	if(ui.list_bookmarks->currentRow() >= 0)
		ui.list_bookmarks->model()->removeRow(ui.list_bookmarks->currentRow());
}

void FileBrowserWidget::selectBookmark(QListWidgetItem* it) // 'files' dock widget
{
	if(ui.list_bookmarks->currentRow() < 0) return;
	selectBookmark(it->text());
}

void FileBrowserWidget::selectBookmark(QString str) // 'files' dock widget
{
	const QModelIndex &i = dirmodel.index(str);
	if ( ui.treeView_2->rootIndex() != dirmodel.parent(dirmodel.index(QDir::rootPath()))
		&& ui.treeView_2->rootIndex() != i )
		changeRootIndex_files(i);
	else {
		setCurrent_files(i);
	}
}

void FileBrowserWidget::setCurrent_files(const QModelIndex &i/*index*/) { // 'files' dock widget
	ui.treeView_2->collapseAll();
	ui.treeView_2->setCurrentIndex(i);
	ui.treeView_2->expand(i);
	ui.treeView_2->scrollTo(i, QAbstractItemView::PositionAtTop);
	ui.treeView_2->resizeColumnToContents(0);
}

void FileBrowserWidget::setRootCurrent() { // 'files' dock widget
	changeRootIndex_files(ui.treeView_2->currentIndex());
}

void FileBrowserWidget::oneLevelUp() { // 'files' dock widget
	changeRootIndex_files(dirmodel.parent(ui.treeView_2->rootIndex()));
}

void FileBrowserWidget::changeRootIndex_files(const QModelIndex &index_) {
	if (!index_.isValid())
		return;
	QModelIndex index(index_);
	if ( ui.treeView_2->rootIndex() == index ) {
		if ( index == dirmodel.parent(dirmodel.index(QDir::rootPath())) )
			return;
		else
			index = dirmodel.parent(dirmodel.index(QDir::rootPath()));
	}
	if ( index != dirmodel.parent(dirmodel.index(QDir::rootPath())) && !dirmodel.fileInfo(index).isDir() )
		index = ui.treeView_2->rootIndex();
	QString oldRoot = dirmodel.filePath(ui.treeView_2->currentIndex());
	ui.treeView_2->setCurrentIndex(index);
	ui.treeView_2->setRootIndex(index);
	ui.treeView_2->collapseAll();
	ui.treeView_2->expand(ui.treeView_2->rootIndex());
	// check for very root dir
	// if it is a zero-level, turn to ald style (only dirs)
	// if not - show files and set label text to pathname
	if ( index == dirmodel.parent(dirmodel.index(QDir::rootPath())) ) {
		dirmodel.setFilter( QDir::AllDirs | QDir::NoDotAndDotDot );
		setCurrent_files(dirmodel.index(oldRoot));
		ui.actionSetRootCurrentDir->setChecked(false);
		ui.treeViewLabel->setVisible(false);
	} else {
		dirmodel.setFilter( QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Files );
		ui.actionSetRootCurrentDir->setChecked(true);
		ui.treeViewLabel->setVisible(true);
		ui.treeViewLabel->setText(dirmodel.filePath(ui.treeView_2->rootIndex()));
	}
	ui.treeView_2->resizeColumnToContents(0);
}

void FileBrowserWidget::rememberStart_files() {
	QModelIndex index(ui.treeView_2->currentIndex());
	if ( !index.isValid() || !dirmodel.isDir(index) ) {
		return;
	}
	QSettings set;
	set.setValue("filesStartDir", dirmodel.filePath(index));
}

