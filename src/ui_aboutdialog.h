/********************************************************************************
** Form generated from reading ui file 'aboutdialog.ui'
**
** Created: Thu 10. Jul 11:29:50 2008
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
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

class Ui_AboutDialogClass
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QTextEdit *textEdit;
    QPushButton *pushButton;

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

    textEdit = new QTextEdit(AboutDialogClass);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));
    textEdit->setReadOnly(true);

    gridLayout->addWidget(textEdit, 2, 0, 1, 3);

    pushButton = new QPushButton(AboutDialogClass);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setIconSize(QSize(128, 128));

    gridLayout->addWidget(pushButton, 3, 0, 1, 3);


    retranslateUi(AboutDialogClass);
    QObject::connect(pushButton, SIGNAL(clicked()), AboutDialogClass, SLOT(accept()));

    QMetaObject::connectSlotsByName(AboutDialogClass);
    } // setupUi

    void retranslateUi(QDialog *AboutDialogClass)
    {
    AboutDialogClass->setWindowTitle(QApplication::translate("AboutDialogClass", "AboutDialog", 0, QApplication::UnicodeUTF8));
    label->setText(QString());
    label_2->setText(QApplication::translate("AboutDialogClass", "Cuberok", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("AboutDialogClass", "v 0.0.1", 0, QApplication::UnicodeUTF8));
    textEdit->setHtml(QApplication::translate("AboutDialogClass", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
    pushButton->setText(QApplication::translate("AboutDialogClass", "Close", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(AboutDialogClass);
    } // retranslateUi

};

namespace Ui {
    class AboutDialogClass: public Ui_AboutDialogClass {};
} // namespace Ui

#endif // UI_ABOUTDIALOG_H
