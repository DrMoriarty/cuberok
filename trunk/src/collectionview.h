#ifndef COLLECTIONVIEW_H
#define COLLECTIONVIEW_H

#include <QtGui>
#include "ui_collectionview.h"

typedef enum {M_ARTIST=0, M_ALBUM, M_GENRE, M_SONG} ListMode;

class CollectionFiller : public QThread
{
	Q_OBJECT
public:
	CollectionFiller(QList<QUrl> _urls, ListMode _mode=M_ARTIST, QString _attrname=QString(""), QObject * parent = 0);
	~CollectionFiller();
	void run();
private:
	QList<QUrl> urls;
	ListMode mode;
	QString attrname;
	void proceed(QString);
	bool cancel;
 private slots:
	void cancelEvent();

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
public slots:
	void update();
signals:
	void status(QString);
};

class CollectionView : public QListView//QAbstractItemView
{
    Q_OBJECT

public:
	CollectionView(QWidget *parent = 0);
	~CollectionView();
	
private:
	Ui::collectionviewClass ui;
	CollectionModel model;
	
	//void dragEnterEvent(QDragEnterEvent *event);
	//void dragLeaveEvent(QDragLeaveEvent *event);
	//void dragMoveEvent(QDragMoveEvent *event);
	//void dropEvent(QDropEvent *event);
	//void mousePressEvent(QMouseEvent *event);
	QList<QUrl> SelectByItem(QModelIndex i);
	QString subsetLabel;
	
public slots:
	void artistMode();
	void albumMode();
	void genreMode();
	void songMode();
	void addItem();
	void removeItem();
	void renameItem();
	void filter(QString);
	void applySubset(QModelIndex);
	void clearSubset();
signals:
	void status(QString);
	void setVisibleSubsetWidgets(bool);
	void setSubsetLabel(QString);
};

#endif // COLLECTIONVIEW_H
