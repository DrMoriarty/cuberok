#ifndef INDICATOR_H
#define INDICATOR_H

#include <QtCore>
#include <QtGui>

class Indicator: public QObject
{
 Q_OBJECT
 public:
	static Indicator& Self();
	~Indicator();
	void setWidget(QAbstractButton &w);
	int  addTask(QString message);
	void delTask(int ID);
	void stop();

 signals:
	void userStop();

 private:
	Indicator();
	void updateWidget();

	struct Task {
		int id;
		QString message;
	};
	QList<struct Task> tasks;
	QTimer timer;
	int counter;
	QAbstractButton *widget;
	QIcon icon;
	QPixmap pxN, pxD, pxR[8];
	int rot;

 private slots:
	void timerUpdate();
	void buttonPressed();
};

#endif //INDICATOR_H
