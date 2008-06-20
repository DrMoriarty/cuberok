#ifndef PLAYLISTCONTAINER_H_
#define PLAYLISTCONTAINER_H_

#include "playlistview.h"

class PlaylistContainer : public QWidget//, StopCallback
{
    Q_OBJECT

public:
	PlaylistContainer(QWidget *parent = 0);
    ~PlaylistContainer();
/*     ADR_METHOD(void) streamStopped(StopEvent* event); */
/*     ADR_METHOD(void) ref(); */
/*     ADR_METHOD(void) unref(); */
    
private:
    
    //AudioDevicePtr device;
    //    int svolume;
    QList<PlaylistView*> lists;
    QVBoxLayout *vboxLayout;
    QTabWidget *tabs;
    PlaylistView *curlist, *actlist;
    int counter;
    bool rf, sf, alv, arv, cov, trv, tiv, yev, gev, fiv, lev;
    
private slots:
	void listStarted(PlaylistView*);
	void tabChanged(int);

public slots:
	void addList();
	void delList();
	void renameList();
	void fillCancel();
	void prev();
	void next();
	void play();
	void pause(bool);
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
	void status(QString);
	void internalnext();
	void songPosition(int);
};

#endif /*PLAYLISTCONTAINER_H_*/
