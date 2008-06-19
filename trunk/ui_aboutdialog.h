/********************************************************************************
** Form generated from reading ui file 'aboutdialog.ui'
**
** Created: Wed 9. Jan 10:09:50 2008
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ABOUTDIALOG_H
#define UI_ABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

class Ui_AboutDialogClass
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout1;
    QGraphicsView *graphicsView;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QDialog *AboutDialogClass)
    {
    if (AboutDialogClass->objectName().isEmpty())
        AboutDialogClass->setObjectName(QString::fromUtf8("AboutDialogClass"));
    AboutDialogClass->resize(400, 300);
    gridLayout = new QGridLayout(AboutDialogClass);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout1 = new QGridLayout();
    gridLayout1->setSpacing(6);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    graphicsView = new QGraphicsView(AboutDialogClass);
    graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

    gridLayout1->addWidget(graphicsView, 0, 0, 1, 1);

    label = new QLabel(AboutDialogClass);
    label->setObjectName(QString::fromUtf8("label"));
    label->setAlignment(Qt::AlignCenter);

    gridLayout1->addWidget(label, 1, 0, 1, 1);

    pushButton = new QPushButton(AboutDialogClass);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));

    gridLayout1->addWidget(pushButton, 2, 0, 1, 1);


    gridLayout->addLayout(gridLayout1, 0, 0, 1, 1);


    retranslateUi(AboutDialogClass);
    QObject::connect(pushButton, SIGNAL(clicked()), AboutDialogClass, SLOT(accept()));

    QMetaObject::connectSlotsByName(AboutDialogClass);
    } // setupUi

    void retranslateUi(QDialog *AboutDialogClass)
    {
    AboutDialogClass->setWindowTitle(QApplication::translate("AboutDialogClass", "AboutDialog", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("AboutDialogClass", "TextLabel", 0, QApplication::UnicodeUTF8));
    pushButton->setText(QApplication::translate("AboutDialogClass", "PushButton", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(AboutDialogClass);
    } // retranslateUi

};

namespace Ui {
    class AboutDialogClass: public Ui_AboutDialogClass {};
} // namespace Ui

#endif // UI_ABOUTDIALOG_H
