#ifndef PLAYLISTMODEL_H_
#define PLAYLISTMODEL_H_

#include <QtCore>
#include <QtGui>

//QString correctStr(QString);
//extern bool corrected;

#define corstr(s) _correct ? correctStr(s) : s 

class PlaylistFiller : public QThread
{
    Q_OBJECT
public:
	PlaylistFiller ( QStringList paths, int ind, QObject * parent = 0 );
	~PlaylistFiller();
    void run();
protected:
	void proceedDir(QString path);
	
	QStringList paths;
	int index;
	bool cancel;

 private slots:
	void cancelEvent();

signals:
	void sendFile(QString str, int index, QList<QVariant>);
};

class PlaylistModel: public QAbstractListModel
{
Q_OBJECT

public:
	PlaylistModel(QObject *parent = 0);
	~PlaylistModel();
	virtual QStringList mimeTypes() const;
	virtual QMimeData *mimeData( const QModelIndexList & indexes ) const;
	virtual bool dropMimeData ( const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent );
	virtual Qt::DropActions supportedDropActions() const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex & parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant data(int role) const;
	QVariant headerData(int section, Qt::Orientation orientation,
	                    int role = Qt::DisplayRole) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role);
	bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
	bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
	//void setCurrent(int c);
	//int current();

    enum Fields {Empty=0, Stat, File, Track, Title, Artist, Album, Comment, Genre, Year, Length, Rating, ColumnCount};
    
private slots:
	void addItem(QString path, int row, QList<QVariant>);

private:
	
	struct sData {
		QVariant *values[ColumnCount];
	};
	
    QList<struct sData> _data;
    int _current;
};

#endif /*PLAYLISTMODEL_H_*/
