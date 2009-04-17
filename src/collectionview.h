/* Cuberok
 * Copyright (C) 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this software; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef COLLECTIONVIEW_H
#define COLLECTIONVIEW_H

#include <QtGui>
#include "downloader.h"

typedef enum {M_ARTIST=0, M_ALBUM, M_GENRE, M_SONG, M_LIST, M_SQLLIST} ListMode;

class CollectionFiller : public QThread
{
	Q_OBJECT
public:
	CollectionFiller(QList<QUrl> _urls, ListMode _mode=M_ARTIST, QString _attrname=QString(""), int _param=0, QObject * parent = 0);
	~CollectionFiller();
	void run();
private:
	QList<QUrl> urls;
	ListMode mode;
	QString attrname;
	int  proceed(QString);
	bool cancel;
	int param;
private slots:
	void cancelEvent();
signals:
	void internalUpdate();

};

class CollectionModel : public QStandardItemModel
{
	Q_OBJECT
 public:
    ListMode mode;
    QString searchPattern;
	
	CollectionModel(QObject *parent = 0);
	~CollectionModel();
	virtual QStringList mimeTypes() const;
	virtual QMimeData *mimeData( const QModelIndexList & indexes ) const;
	virtual bool dropMimeData ( const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent );
	virtual Qt::DropActions supportedDropActions() const;
	void updateMode(ListMode m);
    QList<QUrl> SelectByItem(QModelIndex i) const;
    virtual bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
 private:
	void drawStars(QPixmap &bg, int rating, bool song);
 public slots:
	void update();
 signals:
	void status(QString);
	void modeChanged(int);
};

class CollectionView : public QListView//QAbstractItemView
{
    Q_OBJECT

public:
	CollectionView(QWidget *parent = 0);
	~CollectionView();
	
private:
	CollectionModel model;
	
	//void dragEnterEvent(QDragEnterEvent *event);
	//void dragLeaveEvent(QDragLeaveEvent *event);
	//void dragMoveEvent(QDragMoveEvent *event);
	//void dropEvent(QDropEvent *event);
	//void mousePressEvent(QMouseEvent *event);
	QList<QUrl> SelectByItem(QModelIndex i);
	QString commonPath(QString path1, QString path2);
	void doRequest();
	QString subsetLabel;
	QVector< QList<QString> > request_stack;
	bool wait_response;
	Downloader downloader;
	QString lfmArtist, lfmAlbum;
	
public slots:
	void artistMode();
	void albumMode();
	void genreMode();
	void songMode();
	void addItem();
	void removeItem();
	void filter(QString);
	void applySubset(QModelIndex);
	void clearSubset();
	void setImage();
	void iconView(bool);
	void loadImage();
private slots:
	void infoResponse(QString);
	void dlComplete(QString file);
	void dlCancel(QString);
signals:
	void status(QString);
	void setVisibleSubsetWidgets(bool);
	void setSubsetLabel(QString);
	void modeChanged(int);
	void addUrl(QUrl);
};

#endif // COLLECTIONVIEW_H
