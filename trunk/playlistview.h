#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <unistd.h>
#include <QtGui>
#include "playlistmodel.h"
#include "player.h"
#include "main.h"

using namespace audiere;

class PlaylistView : public QTreeView
{
    Q_OBJECT

public:
    PlaylistView(QString &str, QWidget *parent = 0);
    ~PlaylistView();
    bool isPlaying();
    void dropEvent(QDropEvent *event);
    void startDrag(Qt::DropActions supportedActions);
	void storeList(QString fname);
	void setAutosave(bool);
    
protected:
	virtual void hideEvent ( QHideEvent * event );

private:
    QModelIndex nextItem();
    QModelIndex prevItem();
    void resetTags(QModelIndex& ind);
    
	QString plistname;
    PlaylistModel plmodel;
    QSortFilterProxyModel model;
    QModelIndex insindex;
    QModelIndex curindex;
    QModelIndex plindex;
    QList<QModelIndex> queue;
    QList<QModelIndex> prev_queue;
    QString info;
    bool correct;
    bool playing;
    bool dragStarted;
	bool autosave;
    
private slots:
	void addItem(QVariant item, int id, QModelIndex* ind = 0);
	void playFinished();
	void onClick( const QModelIndex & index );
	void onDoubleClick( const QModelIndex & index );
	void position(double pos);
	void updateTag(int);
	void setColVisible(int,bool);
	void setColWidth(int,int);

public slots:
	void prev();
	void next();
	void play();
	void stop();
	void clear();
	void queueNext();
/* 	void viewAlbum(bool); */
/* 	void viewArtist(bool); */
/* 	void viewComment(bool); */
/* 	void viewTrack(bool); */
/* 	void viewTitle(bool); */
/* 	void viewYear(bool); */
/* 	void viewGenre(bool); */
/* 	void viewFile(bool); */
/* 	void viewLength(bool); */
	void editTag();
	void removeSong();
signals:
	void status(QString/*, QString**/);
	void started(PlaylistView*);
	void songPosition(int);
};

#endif // PLAYLISTVIEW_H
