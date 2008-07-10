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

 signals:
	void userStop();

 public slots:
	void stop();
	void update();

 private:
	Indicator();
	void updateWidget();

	struct Task {
		int id;
		QString message;
	};
	QList<struct Task> tasks;
	int counter;
	QAbstractButton *widget;
	QIcon icon;
	QPixmap pxN, pxD, pxR[36];
	int rot;
	QTime time;
};

#endif //INDICATOR_H
