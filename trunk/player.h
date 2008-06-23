#ifndef PLAYER_H
#define PLAYER_H

#include <QtCore>
#include "main.h"

using namespace audiere;

class Player : public QObject, StopCallback
{
    Q_OBJECT
 public:
    static Player& Self();
    ~Player();

    ADR_METHOD(void) streamStopped(StopEvent* event);
    ADR_METHOD(void) ref();
    ADR_METHOD(void) unref();

    bool open(QString fname);
    bool play();
    bool stop();
    bool setPause(bool p);
    bool close();
    bool setPosition(double pos);
    int  volume();
    void setVolume(int v);
    bool playing();

    int  repeat_mode;
    int  shuffle_mode;

 private:
    Player();
    void sync_stop();
    int svolume;
    QString file;
    AudioDevicePtr device;
    OutputStreamPtr stream;
    QTimer *timer;
    QSemaphore sem;
    bool sync;

 private slots:
    void timerUpdate();

 signals:
    void position(double);
    void finish();
};


#endif // PLAYER_H
