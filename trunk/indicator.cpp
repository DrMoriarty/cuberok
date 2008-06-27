#include "indicator.h"

Indicator::Indicator() : QObject(), counter(0), widget(0), rot(0)
{
	icon.addFile(":/icons/star.png");
	pxN = icon.pixmap(QSize(24, 24), QIcon::Normal, QIcon::On);
	pxD = icon.pixmap(QSize(24, 24), QIcon::Disabled, QIcon::On);
	QTransform matrix;
	for(int i=0; i<36; i++) {
		matrix.rotate(10);
		pxR[i] = pxN.transformed(matrix, Qt::SmoothTransformation);
	}
}

Indicator::~Indicator()
{
}

Indicator& Indicator::Self()
{
	static Indicator self;
	return self;
}

void Indicator::setWidget(QAbstractButton &w)
{
	if(widget) disconnect(widget, SIGNAL(pressed()), this, SLOT(stop()));
	widget = &w;
	connect(widget, SIGNAL(pressed()), this, SLOT(stop()));
	updateWidget();
}

int  Indicator::addTask(QString message)
{
	Task task;
	task.id = counter++;
	task.message = message;
	tasks << task;
	updateWidget();
	if(tasks.size()) time = QTime::currentTime();
	return task.id;
}

void Indicator::delTask(int ID)
{
	for(int i=0; i<tasks.size(); i++) {
		if(tasks[i].id == ID) tasks.removeAt(i);
	}
	updateWidget();
}

void Indicator::stop()
{
	tasks.clear();
	emit userStop();
	updateWidget();
}

void Indicator::update()
{
	int msec = time.msecsTo(QTime::currentTime());
	if(msec >= 100) {
		time = QTime::currentTime();//.addMSecs(100 - msec);
		rot++;
		if(rot >= 36) rot = 0;
		if(widget) {
			QIcon icon2;
			icon2.addPixmap(pxR[rot]);
			widget->setIcon(icon2);
			//widget->repaint();
		}
	}
}

void Indicator::updateWidget()
{
	if(widget) {
		QString str;
		foreach(Task t, tasks) {
			if(str.size()) str += "\n";
			str += t.message;
		}
		widget->setToolTip(str);
		QIcon icon2;
		icon2.addPixmap(tasks.size()?pxN:pxD);
		widget->setIcon(icon2);
	}
}
