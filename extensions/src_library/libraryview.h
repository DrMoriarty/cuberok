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

#ifndef LIBRARYVIEW_H
#define LIBRARYVIEW_H

#include <QtGui>

class LibraryModel : public QStandardItemModel
{
	Q_OBJECT
 public:
    QString searchPattern;
	
	LibraryModel(QObject *parent = 0);
	~LibraryModel();
	virtual QStringList mimeTypes() const;
	virtual QMimeData *mimeData( const QModelIndexList & indexes ) const;
	virtual bool dropMimeData ( const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent );
	virtual Qt::DropActions supportedDropActions() const;
    QList<QUrl> SelectByItem(QModelIndex i) const;
    virtual bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
 private:
	void drawStars(QPixmap &bg, int rating, bool song);
 public slots:
	void update();
 signals:
	void status(QString);
};

class LibraryView: public QListView
{
	Q_OBJECT

public:
	LibraryView(QWidget *parent = 0);
	~LibraryView();

public slots:
	void addItem();
	void removeItem();
	void setImage();
	void setStatus(QString);
	void storeState();

 private slots:
	void sendToPlaylist(QModelIndex);

 signals:
	void status(QString);
	void addUrl(QUrl);

 private:
	LibraryModel model;
	QString stat;

 protected:
	virtual void enterEvent ( QEvent * event );
};

#endif // LIBRARYVIEW_H
