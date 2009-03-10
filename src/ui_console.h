/********************************************************************************
** Form generated from reading ui file 'console.ui'
**
** Created: Fri 6. Mar 12:27:14 2009
**      by: Qt User Interface Compiler version 4.5.0-rc1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CONSOLE_H
#define UI_CONSOLE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConsoleWindow
{
public:
    QAction *actionAll;
    QAction *actionMessages;
    QAction *actionWarnings;
    QAction *actionErrors;
    QAction *actionFatal_Errors;
    QAction *actionExit;
    QAction *actionRefresh;
    QAction *actionAuto_Refresh;
    QAction *actionClear;
    QVBoxLayout *vboxLayout;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuView;
    QMenu *menuCommand;
    QTextEdit *textEdit;

    void setupUi(QDialog *ConsoleWindow)
    {
        if (ConsoleWindow->objectName().isEmpty())
            ConsoleWindow->setObjectName(QString::fromUtf8("ConsoleWindow"));
        ConsoleWindow->resize(384, 279);
        actionAll = new QAction(ConsoleWindow);
        actionAll->setObjectName(QString::fromUtf8("actionAll"));
        actionAll->setCheckable(true);
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/console.png")), QIcon::Normal, QIcon::Off);
        actionAll->setIcon(icon);
        actionMessages = new QAction(ConsoleWindow);
        actionMessages->setObjectName(QString::fromUtf8("actionMessages"));
        actionMessages->setCheckable(true);
        QIcon icon1;
        icon1.addPixmap(QPixmap(QString::fromUtf8(":/icons/console_mes.png")), QIcon::Normal, QIcon::Off);
        actionMessages->setIcon(icon1);
        actionWarnings = new QAction(ConsoleWindow);
        actionWarnings->setObjectName(QString::fromUtf8("actionWarnings"));
        actionWarnings->setCheckable(true);
        QIcon icon2;
        icon2.addPixmap(QPixmap(QString::fromUtf8(":/icons/console_war.png")), QIcon::Normal, QIcon::Off);
        actionWarnings->setIcon(icon2);
        actionErrors = new QAction(ConsoleWindow);
        actionErrors->setObjectName(QString::fromUtf8("actionErrors"));
        actionErrors->setCheckable(true);
        QIcon icon3;
        icon3.addPixmap(QPixmap(QString::fromUtf8(":/icons/console_err.png")), QIcon::Normal, QIcon::Off);
        actionErrors->setIcon(icon3);
        actionFatal_Errors = new QAction(ConsoleWindow);
        actionFatal_Errors->setObjectName(QString::fromUtf8("actionFatal_Errors"));
        actionFatal_Errors->setCheckable(true);
        QIcon icon4;
        icon4.addPixmap(QPixmap(QString::fromUtf8(":/icons/console_fat.png")), QIcon::Normal, QIcon::Off);
        actionFatal_Errors->setIcon(icon4);
        actionExit = new QAction(ConsoleWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon5;
        icon5.addPixmap(QPixmap(QString::fromUtf8(":/icons/quit.png")), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon5);
        actionRefresh = new QAction(ConsoleWindow);
        actionRefresh->setObjectName(QString::fromUtf8("actionRefresh"));
        QIcon icon6;
        icon6.addPixmap(QPixmap(QString::fromUtf8(":/icons/reload.png")), QIcon::Normal, QIcon::Off);
        actionRefresh->setIcon(icon6);
        actionAuto_Refresh = new QAction(ConsoleWindow);
        actionAuto_Refresh->setObjectName(QString::fromUtf8("actionAuto_Refresh"));
        actionAuto_Refresh->setCheckable(true);
        QIcon icon7;
        icon7.addPixmap(QPixmap(QString::fromUtf8(":/icons/repeat_mode.png")), QIcon::Normal, QIcon::Off);
        actionAuto_Refresh->setIcon(icon7);
        actionClear = new QAction(ConsoleWindow);
        actionClear->setObjectName(QString::fromUtf8("actionClear"));
        QIcon icon8;
        icon8.addPixmap(QPixmap(QString::fromUtf8(":/icons/col_rem.png")), QIcon::Normal, QIcon::Off);
        actionClear->setIcon(icon8);
        vboxLayout = new QVBoxLayout(ConsoleWindow);
        vboxLayout->setSpacing(0);
        vboxLayout->setMargin(4);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        centralwidget = new QWidget(ConsoleWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));

        vboxLayout->addWidget(centralwidget);

        menubar = new QMenuBar(ConsoleWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuCommand = new QMenu(menubar);
        menuCommand->setObjectName(QString::fromUtf8("menuCommand"));

        vboxLayout->addWidget(menubar);

        textEdit = new QTextEdit(ConsoleWindow);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setUndoRedoEnabled(false);
        textEdit->setLineWrapMode(QTextEdit::NoWrap);
        textEdit->setReadOnly(true);

        vboxLayout->addWidget(textEdit);


        menubar->addAction(menuCommand->menuAction());
        menubar->addAction(menuView->menuAction());
        menuView->addAction(actionAll);
        menuView->addAction(actionMessages);
        menuView->addAction(actionWarnings);
        menuView->addAction(actionErrors);
        menuView->addAction(actionFatal_Errors);
        menuCommand->addAction(actionRefresh);
        menuCommand->addAction(actionAuto_Refresh);
        menuCommand->addAction(actionClear);
        menuCommand->addSeparator();
        menuCommand->addAction(actionExit);

        retranslateUi(ConsoleWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), ConsoleWindow, SLOT(close()));
        QObject::connect(actionAuto_Refresh, SIGNAL(triggered(bool)), ConsoleWindow, SLOT(autorefresh(bool)));
        QObject::connect(actionRefresh, SIGNAL(triggered()), ConsoleWindow, SLOT(refresh()));
        QObject::connect(actionAll, SIGNAL(triggered(bool)), ConsoleWindow, SLOT(all(bool)));
        QObject::connect(actionMessages, SIGNAL(triggered(bool)), ConsoleWindow, SLOT(message(bool)));
        QObject::connect(actionWarnings, SIGNAL(triggered(bool)), ConsoleWindow, SLOT(warning(bool)));
        QObject::connect(actionErrors, SIGNAL(triggered(bool)), ConsoleWindow, SLOT(error(bool)));
        QObject::connect(actionFatal_Errors, SIGNAL(triggered(bool)), ConsoleWindow, SLOT(fatal(bool)));
        QObject::connect(actionClear, SIGNAL(triggered()), ConsoleWindow, SLOT(clear()));

        QMetaObject::connectSlotsByName(ConsoleWindow);
    } // setupUi

    void retranslateUi(QDialog *ConsoleWindow)
    {
        ConsoleWindow->setWindowTitle(QApplication::translate("ConsoleWindow", "Messages", 0, QApplication::UnicodeUTF8));
        actionAll->setText(QApplication::translate("ConsoleWindow", "All", 0, QApplication::UnicodeUTF8));
        actionMessages->setText(QApplication::translate("ConsoleWindow", "Messages", 0, QApplication::UnicodeUTF8));
        actionWarnings->setText(QApplication::translate("ConsoleWindow", "Warnings", 0, QApplication::UnicodeUTF8));
        actionErrors->setText(QApplication::translate("ConsoleWindow", "Errors", 0, QApplication::UnicodeUTF8));
        actionFatal_Errors->setText(QApplication::translate("ConsoleWindow", "Fatal Errors", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("ConsoleWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionRefresh->setText(QApplication::translate("ConsoleWindow", "Refresh", 0, QApplication::UnicodeUTF8));
        actionAuto_Refresh->setText(QApplication::translate("ConsoleWindow", "Auto Refresh", 0, QApplication::UnicodeUTF8));
        actionClear->setText(QApplication::translate("ConsoleWindow", "Clear", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("ConsoleWindow", "View", 0, QApplication::UnicodeUTF8));
        menuCommand->setTitle(QApplication::translate("ConsoleWindow", "Commands", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConsoleWindow: public Ui_ConsoleWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONSOLE_H
