/********************************************************************************
** Form generated from reading ui file 'infowindow.ui'
**
** Created: Thu 19. Feb 11:44:40 2009
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_INFOWINDOW_H
#define UI_INFOWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_InfoWindow
{
public:
    QVBoxLayout *vboxLayout;
    QWidget *centralwidget;
    QTextBrowser *textEdit;

    void setupUi(QDialog *InfoWindow)
    {
    if (InfoWindow->objectName().isEmpty())
        InfoWindow->setObjectName(QString::fromUtf8("InfoWindow"));
    InfoWindow->resize(384, 279);
    vboxLayout = new QVBoxLayout(InfoWindow);
    vboxLayout->setSpacing(0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    vboxLayout->setContentsMargins(4, 4, 4, 4);
    centralwidget = new QWidget(InfoWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));

    vboxLayout->addWidget(centralwidget);

    textEdit = new QTextBrowser(InfoWindow);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));
    textEdit->setUndoRedoEnabled(false);
    textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
    textEdit->setReadOnly(true);
    textEdit->setOpenExternalLinks(true);

    vboxLayout->addWidget(textEdit);


    retranslateUi(InfoWindow);

    QMetaObject::connectSlotsByName(InfoWindow);
    } // setupUi

    void retranslateUi(QDialog *InfoWindow)
    {
    InfoWindow->setWindowTitle(QApplication::translate("InfoWindow", "Information", 0, QApplication::UnicodeUTF8));
    textEdit->setHtml(QApplication::translate("InfoWindow", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">Please wait while information loading...</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(InfoWindow);
    } // retranslateUi

};

namespace Ui {
    class InfoWindow: public Ui_InfoWindow {};
} // namespace Ui

#endif // UI_INFOWINDOW_H
