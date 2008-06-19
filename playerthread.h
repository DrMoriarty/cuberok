#ifndef PLAYERTHREAD_H
#define PLAYERTHREAD_H

#include <QtCore>
#include <QtGui>

class PlayerThread : public QThread
{
    Q_OBJECT

public:
	PlayerThread(int *fd, QString fname, QMutex &mp, QObject *parent = 0);
    ~PlayerThread();

protected:
    void run();
    void run_mpg123();
    void prepareTags();
    QString prepareTag(char *);
    QMutex *mutexPause;

public slots:
	void seek(double pos);

signals:
	void position(double pos1, double pos2);
	//void tagready(QString, QString, QString, QString, QString, QString);
	void tagready(QString);
	
private:
	QString file;
	int *fdescr;
	bool tags;
};

#endif // PLAYERTHREAD_H
