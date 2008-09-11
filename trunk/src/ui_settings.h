/********************************************************************************
** Form generated from reading ui file 'settings.ui'
**
** Created: Wed 10. Sep 09:37:22 2008
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QToolBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_Settings
{
public:
    QVBoxLayout *vboxLayout;
    QToolBox *toolBox;
    QWidget *page;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QComboBox *comboBox_language;
    QLabel *label;
    QComboBox *comboBox_engine;
    QSpacerItem *spacerItem;
    QCheckBox *checkBox_autofix8bit;
    QCheckBox *checkBox_autosave;
    QCheckBox *checkBox_autorating;
    QLabel *label_3;
    QComboBox *comboBox_cue;
    QWidget *page_2;
    QWidget *page_3;
    QGridLayout *gridLayout1;
    QCheckBox *checkBox_proxyEnabled;
    QLabel *label_4;
    QLineEdit *lineEdit_proxyHost;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QSpinBox *spinBox_proxyPort;
    QLineEdit *lineEdit_proxyUser;
    QLineEdit *lineEdit_proxyPassword;
    QSpacerItem *spacerItem1;
    QWidget *page_4;
    QGridLayout *gridLayout2;
    QCheckBox *checkBox_lastfmScrobbling;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *lineEdit_lastfmUser;
    QLineEdit *lineEdit_lastfmPassword;
    QSpacerItem *spacerItem2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Settings)
    {
    if (Settings->objectName().isEmpty())
        Settings->setObjectName(QString::fromUtf8("Settings"));
    Settings->resize(430, 329);
    vboxLayout = new QVBoxLayout(Settings);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    toolBox = new QToolBox(Settings);
    toolBox->setObjectName(QString::fromUtf8("toolBox"));
    page = new QWidget();
    page->setObjectName(QString::fromUtf8("page"));
    page->setGeometry(QRect(0, 0, 412, 167));
    gridLayout = new QGridLayout(page);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label_2 = new QLabel(page);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout->addWidget(label_2, 0, 0, 1, 1);

    comboBox_language = new QComboBox(page);
    comboBox_language->setObjectName(QString::fromUtf8("comboBox_language"));

    gridLayout->addWidget(comboBox_language, 0, 1, 1, 1);

    label = new QLabel(page);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 1, 0, 1, 1);

    comboBox_engine = new QComboBox(page);
    comboBox_engine->setObjectName(QString::fromUtf8("comboBox_engine"));

    gridLayout->addWidget(comboBox_engine, 1, 1, 1, 1);

    spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout->addItem(spacerItem, 5, 0, 1, 1);

    checkBox_autofix8bit = new QCheckBox(page);
    checkBox_autofix8bit->setObjectName(QString::fromUtf8("checkBox_autofix8bit"));

    gridLayout->addWidget(checkBox_autofix8bit, 2, 0, 1, 1);

    checkBox_autosave = new QCheckBox(page);
    checkBox_autosave->setObjectName(QString::fromUtf8("checkBox_autosave"));

    gridLayout->addWidget(checkBox_autosave, 2, 1, 1, 1);

    checkBox_autorating = new QCheckBox(page);
    checkBox_autorating->setObjectName(QString::fromUtf8("checkBox_autorating"));

    gridLayout->addWidget(checkBox_autorating, 3, 0, 1, 1);

    label_3 = new QLabel(page);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    gridLayout->addWidget(label_3, 4, 0, 1, 1);

    comboBox_cue = new QComboBox(page);
    comboBox_cue->setObjectName(QString::fromUtf8("comboBox_cue"));

    gridLayout->addWidget(comboBox_cue, 4, 1, 1, 1);

    toolBox->addItem(page, QApplication::translate("Settings", "Common settings", 0, QApplication::UnicodeUTF8));
    page_2 = new QWidget();
    page_2->setObjectName(QString::fromUtf8("page_2"));
    page_2->setGeometry(QRect(0, 0, 96, 26));
    toolBox->addItem(page_2, QApplication::translate("Settings", "Engine Settings", 0, QApplication::UnicodeUTF8));
    page_3 = new QWidget();
    page_3->setObjectName(QString::fromUtf8("page_3"));
    page_3->setGeometry(QRect(0, 0, 399, 168));
    gridLayout1 = new QGridLayout(page_3);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    checkBox_proxyEnabled = new QCheckBox(page_3);
    checkBox_proxyEnabled->setObjectName(QString::fromUtf8("checkBox_proxyEnabled"));

    gridLayout1->addWidget(checkBox_proxyEnabled, 0, 0, 1, 1);

    label_4 = new QLabel(page_3);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    gridLayout1->addWidget(label_4, 1, 0, 1, 1);

    lineEdit_proxyHost = new QLineEdit(page_3);
    lineEdit_proxyHost->setObjectName(QString::fromUtf8("lineEdit_proxyHost"));

    gridLayout1->addWidget(lineEdit_proxyHost, 1, 2, 1, 1);

    label_5 = new QLabel(page_3);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    gridLayout1->addWidget(label_5, 2, 0, 1, 1);

    label_6 = new QLabel(page_3);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    gridLayout1->addWidget(label_6, 3, 0, 1, 1);

    label_7 = new QLabel(page_3);
    label_7->setObjectName(QString::fromUtf8("label_7"));

    gridLayout1->addWidget(label_7, 4, 0, 1, 1);

    spinBox_proxyPort = new QSpinBox(page_3);
    spinBox_proxyPort->setObjectName(QString::fromUtf8("spinBox_proxyPort"));
    spinBox_proxyPort->setMaximum(65535);

    gridLayout1->addWidget(spinBox_proxyPort, 2, 2, 1, 1);

    lineEdit_proxyUser = new QLineEdit(page_3);
    lineEdit_proxyUser->setObjectName(QString::fromUtf8("lineEdit_proxyUser"));

    gridLayout1->addWidget(lineEdit_proxyUser, 3, 2, 1, 1);

    lineEdit_proxyPassword = new QLineEdit(page_3);
    lineEdit_proxyPassword->setObjectName(QString::fromUtf8("lineEdit_proxyPassword"));
    lineEdit_proxyPassword->setEchoMode(QLineEdit::Password);

    gridLayout1->addWidget(lineEdit_proxyPassword, 4, 2, 1, 1);

    spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout1->addItem(spacerItem1, 5, 2, 1, 1);

    toolBox->addItem(page_3, QApplication::translate("Settings", "Internet connection", 0, QApplication::UnicodeUTF8));
    page_4 = new QWidget();
    page_4->setObjectName(QString::fromUtf8("page_4"));
    page_4->setGeometry(QRect(0, 0, 412, 167));
    gridLayout2 = new QGridLayout(page_4);
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    checkBox_lastfmScrobbling = new QCheckBox(page_4);
    checkBox_lastfmScrobbling->setObjectName(QString::fromUtf8("checkBox_lastfmScrobbling"));

    gridLayout2->addWidget(checkBox_lastfmScrobbling, 0, 0, 1, 1);

    label_8 = new QLabel(page_4);
    label_8->setObjectName(QString::fromUtf8("label_8"));

    gridLayout2->addWidget(label_8, 1, 0, 1, 1);

    label_9 = new QLabel(page_4);
    label_9->setObjectName(QString::fromUtf8("label_9"));

    gridLayout2->addWidget(label_9, 2, 0, 1, 1);

    lineEdit_lastfmUser = new QLineEdit(page_4);
    lineEdit_lastfmUser->setObjectName(QString::fromUtf8("lineEdit_lastfmUser"));

    gridLayout2->addWidget(lineEdit_lastfmUser, 1, 1, 1, 1);

    lineEdit_lastfmPassword = new QLineEdit(page_4);
    lineEdit_lastfmPassword->setObjectName(QString::fromUtf8("lineEdit_lastfmPassword"));
    lineEdit_lastfmPassword->setEchoMode(QLineEdit::Password);

    gridLayout2->addWidget(lineEdit_lastfmPassword, 2, 1, 1, 1);

    spacerItem2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout2->addItem(spacerItem2, 3, 0, 1, 1);

    toolBox->addItem(page_4, QApplication::translate("Settings", "Last.FM", 0, QApplication::UnicodeUTF8));

    vboxLayout->addWidget(toolBox);

    buttonBox = new QDialogButtonBox(Settings);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setLayoutDirection(Qt::LeftToRight);
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);
    buttonBox->setCenterButtons(false);

    vboxLayout->addWidget(buttonBox);


    retranslateUi(Settings);
    QObject::connect(buttonBox, SIGNAL(accepted()), Settings, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), Settings, SLOT(reject()));

    toolBox->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QDialog *Settings)
    {
    Settings->setWindowTitle(QApplication::translate("Settings", "Preferences", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("Settings", "Language", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("Settings", "Preffered audio engine", 0, QApplication::UnicodeUTF8));
    checkBox_autofix8bit->setText(QApplication::translate("Settings", "Fix local 8 bit codepage in id3v2", 0, QApplication::UnicodeUTF8));
    checkBox_autosave->setText(QApplication::translate("Settings", "Auto save fixed tags", 0, QApplication::UnicodeUTF8));
    checkBox_autorating->setText(QApplication::translate("Settings", "Enable auto rating", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("Settings", "Codepage for CUE sheets", 0, QApplication::UnicodeUTF8));
    toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("Settings", "Common settings", 0, QApplication::UnicodeUTF8));
    toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("Settings", "Engine Settings", 0, QApplication::UnicodeUTF8));
    checkBox_proxyEnabled->setText(QApplication::translate("Settings", "Use proxy", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("Settings", "Proxy host", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("Settings", "Port", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("Settings", "User name", 0, QApplication::UnicodeUTF8));
    label_7->setText(QApplication::translate("Settings", "Password", 0, QApplication::UnicodeUTF8));
    toolBox->setItemText(toolBox->indexOf(page_3), QApplication::translate("Settings", "Internet connection", 0, QApplication::UnicodeUTF8));
    checkBox_lastfmScrobbling->setText(QApplication::translate("Settings", "Enable Last.FM scrobbling", 0, QApplication::UnicodeUTF8));
    label_8->setText(QApplication::translate("Settings", "User name", 0, QApplication::UnicodeUTF8));
    label_9->setText(QApplication::translate("Settings", "Password", 0, QApplication::UnicodeUTF8));
    toolBox->setItemText(toolBox->indexOf(page_4), QApplication::translate("Settings", "Last.FM", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Settings);
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

#endif // UI_SETTINGS_H
