#include "indicator.h"

Indicator::Indicator() : QObject(), counter(0), widget(0), rot(0)
{
	icon.addFile(":/icons/star.png");
	pxN = icon.pixmap(QSize(16, 16), QIcon::Normal, QIcon::On);
	pxD = icon.pixmap(QSize(16, 16), QIcon::Disabled, QIcon::On);
	QTransform matrix;
	for(int i=0; i<8; i++) {
		matrix.rotate(45);
		pxR[i] = (i%2?pxN:pxD).transformed(matrix, Qt::FastTransformation);
	}
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
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
	if(widget) disconnect(widget, SIGNAL(pressed()), this, SLOT(buttonPressed()));
	widget = &w;
	connect(widget, SIGNAL(pressed()), this, SLOT(buttonPressed()));
	updateWidget();
}

int  Indicator::addTask(QString message)
{
	Task task;
	task.id = counter++;
	task.message = message;
	tasks << task;
	updateWidget();
	if(tasks.size() > 0) timer.start(500);
	return task.id;
}

void Indicator::delTask(int ID)
{
	for(int i=0; i<tasks.size(); i++) {
		if(tasks[i].id == ID) tasks.removeAt(i);
	}
	if(!tasks.size()) timer.stop();
	updateWidget();
}

void Indicator::stop()
{
	tasks.clear();
	emit userStop();
	timer.stop();
	updateWidget();
}

void Indicator::timerUpdate()
{
	rot++;
	if(rot >= 8) rot = 0;
	if(widget) {
		QIcon icon2;
		icon2.addPixmap(pxR[rot]);
		widget->setIcon(icon2);
		widget->repaint();
	}
}

void Indicator::buttonPressed()
{
	stop();
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
