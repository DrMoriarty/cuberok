#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QtGui/QDialog>
#include "ui_aboutdialog.h"

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

private:
    Ui::AboutDialogClass ui;
};

#endif // ABOUTDIALOG_H
