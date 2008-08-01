/********************************************************************************
** Form generated from reading ui file 'aboutdialog.ui'
**
** Created: Fri 1. Aug 10:17:06 2008
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
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>

class Ui_AboutDialogClass
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QDialogButtonBox *buttonBox;
    QLabel *label_4;

    void setupUi(QDialog *AboutDialogClass)
    {
    if (AboutDialogClass->objectName().isEmpty())
        AboutDialogClass->setObjectName(QString::fromUtf8("AboutDialogClass"));
    AboutDialogClass->resize(344, 284);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(AboutDialogClass->sizePolicy().hasHeightForWidth());
    AboutDialogClass->setSizePolicy(sizePolicy);
    AboutDialogClass->setWindowIcon(QIcon(QString::fromUtf8(":/icons/application.png")));
    gridLayout = new QGridLayout(AboutDialogClass);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label = new QLabel(AboutDialogClass);
    label->setObjectName(QString::fromUtf8("label"));
    label->setPixmap(QPixmap(QString::fromUtf8(":/icons/application.png")));
    label->setAlignment(Qt::AlignCenter);

    gridLayout->addWidget(label, 0, 0, 2, 1);

    label_2 = new QLabel(AboutDialogClass);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    QFont font;
    font.setFamily(QString::fromUtf8("Arial"));
    font.setPointSize(20);
    font.setBold(true);
    font.setWeight(75);
    label_2->setFont(font);
    label_2->setTextFormat(Qt::AutoText);
    label_2->setScaledContents(true);
    label_2->setAlignment(Qt::AlignCenter);
    label_2->setWordWrap(true);

    gridLayout->addWidget(label_2, 0, 1, 1, 2);

    label_3 = new QLabel(AboutDialogClass);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    QFont font1;
    font1.setFamily(QString::fromUtf8("Arial"));
    font1.setPointSize(15);
    font1.setBold(true);
    font1.setWeight(75);
    label_3->setFont(font1);

    gridLayout->addWidget(label_3, 1, 2, 1, 1);

    buttonBox = new QDialogButtonBox(AboutDialogClass);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setStandardButtons(QDialogButtonBox::Ok);

    gridLayout->addWidget(buttonBox, 4, 0, 1, 3);

    label_4 = new QLabel(AboutDialogClass);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setTextFormat(Qt::AutoText);
    label_4->setScaledContents(false);
    label_4->setWordWrap(true);

    gridLayout->addWidget(label_4, 2, 0, 1, 3);


    retranslateUi(AboutDialogClass);
    QObject::connect(buttonBox, SIGNAL(accepted()), AboutDialogClass, SLOT(accept()));

    QMetaObject::connectSlotsByName(AboutDialogClass);
    } // setupUi

    void retranslateUi(QDialog *AboutDialogClass)
    {
    AboutDialogClass->setWindowTitle(QApplication::translate("AboutDialogClass", "AboutDialog", 0, QApplication::UnicodeUTF8));
    label->setText(QString());
    label_2->setText(QApplication::translate("AboutDialogClass", "Cuberok", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("AboutDialogClass", "v 0.0.2", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("AboutDialogClass", "Copyright (C) 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(AboutDialogClass);
    } // retranslateUi

};

namespace Ui {
    class AboutDialogClass: public Ui_AboutDialogClass {};
} // namespace Ui

#endif // UI_ABOUTDIALOG_H
