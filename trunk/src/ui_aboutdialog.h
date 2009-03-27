/********************************************************************************
** Form generated from reading ui file 'aboutdialog.ui'
**
** Created: Thu 26. Mar 10:17:54 2009
**      by: Qt User Interface Compiler version 4.5.0-rc1
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
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_AboutDialogClass
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_name;
    QLabel *label_version;
    QDialogButtonBox *buttonBox;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QDialog *AboutDialogClass)
    {
        if (AboutDialogClass->objectName().isEmpty())
            AboutDialogClass->setObjectName(QString::fromUtf8("AboutDialogClass"));
        AboutDialogClass->resize(306, 325);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AboutDialogClass->sizePolicy().hasHeightForWidth());
        AboutDialogClass->setSizePolicy(sizePolicy);
        const QIcon icon = QIcon(QString::fromUtf8(":/icons/application.png"));
        AboutDialogClass->setWindowIcon(icon);
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

        gridLayout->addWidget(buttonBox, 9, 0, 1, 3);

        label_2 = new QLabel(AboutDialogClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);
        label_2->setWordWrap(true);
        label_2->setOpenExternalLinks(true);
        label_2->setTextInteractionFlags(Qt::TextBrowserInteraction);

        gridLayout->addWidget(label_2, 3, 0, 4, 3);

        label_3 = new QLabel(AboutDialogClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFrameShape(QFrame::NoFrame);
        label_3->setAlignment(Qt::AlignCenter);
        label_3->setOpenExternalLinks(true);
        label_3->setTextInteractionFlags(Qt::TextBrowserInteraction);

        gridLayout->addWidget(label_3, 8, 0, 1, 3);

        label_4 = new QLabel(AboutDialogClass);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFrameShape(QFrame::HLine);

        gridLayout->addWidget(label_4, 7, 0, 1, 3);


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
        label_2->setText(QApplication::translate("AboutDialogClass", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">Copyright (C) 2008-2009 Vasiliy Makarov</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">&lt;<a href=\"mailto:drmoriarty.0@gmail.com\"><span style=\" text-decoration: underline; color:#0000ff;\">drmoriarty.0@gmail.com</span></a>&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt; text-decoration: underline; color:#0000ff;\"><a href=\"http://code.google.com/p/cuberok/\">http://code.google.com/p/cuberok/</a></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("AboutDialogClass", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; color:#000000;\">In Cuberok used code of QTagConvert</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt; color:#000000;\"><a href=\"http://sourceforge.net/projects/qtagconvert/\"><span style=\" text-decoration: underline; color:#0000ff;\">http://sourceforge.net/projects/qtagconvert/</span></a></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt; color:#000000;\">(C) 2007-2008 Skala &lt;<a href=\"mailto:skala@users.sourceforge.net\"><span style"
                        "=\" text-decoration: underline; color:#0000ff;\">skala@users.sourceforge.net</span></a>&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt; color:#000000;\">(C) 2009 DrMoriarty &lt;<a href=\"mailto:drmoriarty.0@gmail.com\"><span style=\" text-decoration: underline; color:#0000ff;\">drmoriarty.0@gmail.com</span></a>&gt;</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QString());
        Q_UNUSED(AboutDialogClass);
    } // retranslateUi

};

namespace Ui {
    class AboutDialogClass: public Ui_AboutDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDIALOG_H
