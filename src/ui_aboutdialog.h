/********************************************************************************
** Form generated from reading ui file 'aboutdialog.ui'
**
** Created: Thu 19. Feb 16:28:20 2009
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
#include <QtGui/QTextBrowser>

class Ui_AboutDialogClass
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_name;
    QLabel *label_version;
    QDialogButtonBox *buttonBox;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *AboutDialogClass)
    {
    if (AboutDialogClass->objectName().isEmpty())
        AboutDialogClass->setObjectName(QString::fromUtf8("AboutDialogClass"));
    AboutDialogClass->resize(342, 276);
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

    gridLayout->addWidget(label, 0, 0, 3, 1);

    label_name = new QLabel(AboutDialogClass);
    label_name->setObjectName(QString::fromUtf8("label_name"));
    QFont font;
    font.setFamily(QString::fromUtf8("Arial"));
    font.setPointSize(20);
    font.setBold(true);
    font.setWeight(75);
    label_name->setFont(font);
    label_name->setLayoutDirection(Qt::LeftToRight);
    label_name->setTextFormat(Qt::AutoText);
    label_name->setScaledContents(true);
    label_name->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    label_name->setWordWrap(true);

    gridLayout->addWidget(label_name, 0, 1, 1, 2);

    label_version = new QLabel(AboutDialogClass);
    label_version->setObjectName(QString::fromUtf8("label_version"));
    QFont font1;
    font1.setFamily(QString::fromUtf8("Arial"));
    font1.setPointSize(15);
    font1.setBold(true);
    font1.setWeight(75);
    label_version->setFont(font1);
    label_version->setLayoutDirection(Qt::LeftToRight);
    label_version->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    gridLayout->addWidget(label_version, 1, 1, 1, 2);

    buttonBox = new QDialogButtonBox(AboutDialogClass);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setStandardButtons(QDialogButtonBox::Ok);

    gridLayout->addWidget(buttonBox, 6, 0, 1, 3);

    textBrowser = new QTextBrowser(AboutDialogClass);
    textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
    textBrowser->setFrameShape(QFrame::Box);
    textBrowser->setFrameShadow(QFrame::Raised);
    textBrowser->setOpenExternalLinks(true);
    textBrowser->setOpenLinks(true);

    gridLayout->addWidget(textBrowser, 3, 0, 3, 3);


    retranslateUi(AboutDialogClass);
    QObject::connect(buttonBox, SIGNAL(accepted()), AboutDialogClass, SLOT(accept()));

    QMetaObject::connectSlotsByName(AboutDialogClass);
    } // setupUi

    void retranslateUi(QDialog *AboutDialogClass)
    {
    AboutDialogClass->setWindowTitle(QApplication::translate("AboutDialogClass", "AboutDialog", 0, QApplication::UnicodeUTF8));
    label->setText(QString());
    label_name->setText(QApplication::translate("AboutDialogClass", "Cuberok", 0, QApplication::UnicodeUTF8));
    label_version->setText(QApplication::translate("AboutDialogClass", "v 0.0.0", 0, QApplication::UnicodeUTF8));
    textBrowser->setHtml(QApplication::translate("AboutDialogClass", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">Copyright (C) 2008 Vasiliy Makarov &lt;<a href=\"mailto:drmoriarty.0@gmail.com\"><span style=\" text-decoration: underline; color:#0000ff;\">drmoriarty.0@gmail.com</span></a>&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt; text-decoration: underline; color:#0000ff;\"><a href=\"http://code.google.com/p/cuberok/\">http://code.google.com/p/cuberok/</a><br /></p></body></html>", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(AboutDialogClass);
    } // retranslateUi

};

namespace Ui {
    class AboutDialogClass: public Ui_AboutDialogClass {};
} // namespace Ui

#endif // UI_ABOUTDIALOG_H
