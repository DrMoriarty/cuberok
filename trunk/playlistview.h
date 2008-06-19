#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <unistd.h>
#include <QtGui>
#include "playlistmodel.h"
#include "playerthread.h"
#include "main.h"

using namespace audiere;

class PlaylistView : public QTreeView
{
    Q_OBJECT

public:
    PlaylistView(AudioDevicePtr *, QWidget *parent = 0);
    ~PlaylistView();
    bool isPlaying();
    void dropEvent(QDropEvent *event);
    void startDrag(Qt::DropActions supportedActions);
    
private:
    QModelIndex nextItem();
    QModelIndex prevItem();
    void resetTags(QModelIndex& ind);
    
    QTimer *timer;
    PlaylistModel model;
    QModelIndex insindex;
    QModelIndex curindex;
    QModelIndex plindex;
//    PlaylistFiller *filler;
    PlayerThread *plthread;
    QList<QModelIndex> queue;
    QList<QModelIndex> prev_queue;
    bool repeat_mode;
    bool shuffle_mode;
    bool disable_signal;
    QMutex mutexPause;
    int filedescr;
    QString info;
    bool correct;
    AudioDevicePtr *device;
    OutputStreamPtr stream;
    int svolume;
    bool playing;
    bool dragStarted;
    
private slots:
	void addItem(QString item, int id, QModelIndex* ind = 0);
	void fillFinished();
	void playFinished();
	void onClick( const QModelIndex & index );
	void onDoubleClick( const QModelIndex & index );
	void position(double pos1, double pos2);
	//void tagready(QString, QString, QString, QString, QString, QString);
	void tagready(QString);
	void timerUpdate();
	void updateTag(int);

public slots:
	void fillCancel();
	void prev();
	void next();
	void play();
	void pause(bool);
	void stop();
	void repeat(bool mode);
	void shuffle(bool mode);
	void setVolume(int volume); 
	void eq1(int);
	void eq2(int);
	void eq3(int);
	void eq4(int);
	void eq5(int);
	void eq6(int);
	void eq7(int);
	void eq8(int);
	void eq9(int);
	void eq10(int);
	void eq11(int);
	void eq12(int);
	void eq13(int);
	void eq14(int);
	void eq15(int);
	void eq16(int);
	void eqalizer(bool);
	void clear();
	void queueNext();
	void viewAlbum(bool);
	void viewArtist(bool);
	void viewComment(bool);
	void viewTrack(bool);
	void viewTitle(bool);
	void viewYear(bool);
	void viewGenre(bool);
	void viewFile(bool);
	void viewLength(bool);
	void editTag();
	void removeSong();
signals:
	void status(QString/*, QString**/);
	void started(PlaylistView*);
	void songPosition(int);
};

#endif // PLAYLISTVIEW_H
