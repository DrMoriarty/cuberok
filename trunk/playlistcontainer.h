#ifndef PLAYLISTCONTAINER_H_
#define PLAYLISTCONTAINER_H_

#include "playlistview.h"

class PlaylistContainer : public QWidget
{
    Q_OBJECT

public:
	PlaylistContainer(QWidget *parent = 0);
    ~PlaylistContainer();
	void newList(QString listname = "");
    
private:
    
    QList<PlaylistView*> lists;
    QVBoxLayout *vboxLayout;
    QTabWidget *tabs;
	QToolButton *newButton;
	QToolButton *closeButton;
    PlaylistView *curlist, *actlist;
    int counter;
    bool alv, arv, cov, trv, tiv, yev, gev, fiv, lev;
    
private slots:
	void listStarted(PlaylistView*);
	void tabChanged(int);

public slots:
	void addList();
	void delList();
	void renameList();
	void prev();
	void next();
	void play();
	void pause(bool);
	void repeat(bool mode);
	void shuffle(bool mode);
	void setVolume(int volume); 
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
	void status(QString);
	void internalnext();
	void songPosition(int);
};

#endif /*PLAYLISTCONTAINER_H_*/
