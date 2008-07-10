#ifndef PLAYERTHREAD_H
#define PLAYERTHREAD_H

#include <QtCore>
#include <QtGui>
#include "main.h"

class PlayerThread : public QThread
{
    Q_OBJECT

public:
	PlayerThread(QString fname, QMutex &mp, QObject *parent = 0);
    ~PlayerThread();

protected:
    void run();
    void prepareTags();
    QString prepareTag(char *);
    QMutex *mutexPause;

public slots:
	void seek(double pos);
	void timerUpdate();

signals:
	void position(double pos1, double pos2);
	void tagready(QString);
	
private:
	QString file;
	static AudioDevicePtr device = OpenDevice();
	static int count = 0;
	OutputStreamPtr stream;
	QTimer *timer;
};

#endif // PLAYERTHREAD_H
