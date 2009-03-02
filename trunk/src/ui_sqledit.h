/********************************************************************************
** Form generated from reading ui file 'sqledit.ui'
**
** Created: Mon 2. Mar 11:47:36 2009
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SQLEDIT_H
#define UI_SQLEDIT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QLabel>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>

class Ui_SQLEditDialog
{
public:
    QVBoxLayout *vboxLayout;
    QLabel *label;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SQLEditDialog)
    {
    if (SQLEditDialog->objectName().isEmpty())
        SQLEditDialog->setObjectName(QString::fromUtf8("SQLEditDialog"));
    SQLEditDialog->resize(336, 181);
    SQLEditDialog->setWindowIcon(QIcon(QString::fromUtf8(":/icons/application.png")));
    vboxLayout = new QVBoxLayout(SQLEditDialog);
    vboxLayout->setSpacing(4);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    vboxLayout->setContentsMargins(4, 4, 4, 4);
    label = new QLabel(SQLEditDialog);
    label->setObjectName(QString::fromUtf8("label"));

    vboxLayout->addWidget(label);

    textEdit = new QTextEdit(SQLEditDialog);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
    textEdit->setSizePolicy(sizePolicy);
    textEdit->setUndoRedoEnabled(false);
    textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
    textEdit->setReadOnly(false);
    textEdit->setAcceptRichText(false);

    vboxLayout->addWidget(textEdit);

    textEdit_2 = new QTextEdit(SQLEditDialog);
    textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(textEdit_2->sizePolicy().hasHeightForWidth());
    textEdit_2->setSizePolicy(sizePolicy1);
    textEdit_2->setMaximumSize(QSize(16777215, 128));
    textEdit_2->setAutoFillBackground(false);
    textEdit_2->setFrameShape(QFrame::NoFrame);
    textEdit_2->setFrameShadow(QFrame::Plain);
    textEdit_2->setReadOnly(true);
    textEdit_2->setAcceptRichText(false);

    vboxLayout->addWidget(textEdit_2);

    buttonBox = new QDialogButtonBox(SQLEditDialog);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);
    buttonBox->setCenterButtons(false);

    vboxLayout->addWidget(buttonBox);


    retranslateUi(SQLEditDialog);
    QObject::connect(buttonBox, SIGNAL(accepted()), SQLEditDialog, SLOT(saveChanges()));
    QObject::connect(buttonBox, SIGNAL(rejected()), SQLEditDialog, SLOT(reject()));

    QMetaObject::connectSlotsByName(SQLEditDialog);
    } // setupUi

    void retranslateUi(QDialog *SQLEditDialog)
    {
    SQLEditDialog->setWindowTitle(QApplication::translate("SQLEditDialog", "Edit SQL Playlist", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("SQLEditDialog", "Name of playlist", 0, QApplication::UnicodeUTF8));
    textEdit->setHtml(QApplication::translate("SQLEditDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
    textEdit_2->setHtml(QApplication::translate("SQLEditDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">Valid field names are File, Track, Title, ArtistName, AlbumName, GenreName, Year, Comment, SongRating.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">Don't forget use 'and' and 'or' between conditions.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">For example try write \"<span style=\" font-weight:600;\">ArtistName like \"The%\" and SongRating &gt; 10</span>\".</p></body></html>", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(SQLEditDialog);
    } // retranslateUi

};

namespace Ui {
    class SQLEditDialog: public Ui_SQLEditDialog {};
} // namespace Ui

#endif // UI_SQLEDIT_H
