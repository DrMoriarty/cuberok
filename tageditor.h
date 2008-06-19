#ifndef TAGEDITOR_H
#define TAGEDITOR_H

//#include <QtGui/QDialog>
#include <QtGui>
#include "ui_tageditor.h"

class TagEditor : public QDialog
{
    Q_OBJECT

public:
    TagEditor(QString fname, QWidget *parent = 0);
    ~TagEditor();
    int index;

private:
    Ui::TagEditorClass ui;
    QString file;

public slots:
	void correct1();
	void correct2();
	void save();

signals:
	void editComplete(int);
};

#endif // TAGEDITOR_H
