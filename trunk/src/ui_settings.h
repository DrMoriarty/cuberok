/********************************************************************************
** Form generated from reading ui file 'settings.ui'
**
** Created: Tue 23. Dec 10:37:55 2008
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
#include <QtGui/QGroupBox>
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
    QCheckBox *checkBox_hideEmpty;
    QWidget *page_2;
    QWidget *page_3;
    QGridLayout *gridLayout1;
    QGroupBox *checkBox_proxyEnabled;
    QGridLayout *gridLayout2;
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
    QGridLayout *gridLayout3;
    QGroupBox *checkBox_lastfmScrobbling;
    QGridLayout *gridLayout4;
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
    Settings->resize(430, 395);
    vboxLayout = new QVBoxLayout(Settings);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    toolBox = new QToolBox(Settings);
    toolBox->setObjectName(QString::fromUtf8("toolBox"));
    page = new QWidget();
    page->setObjectName(QString::fromUtf8("page"));
    page->setGeometry(QRect(0, 0, 412, 226));
    gridLayout = new QGridLayout(page);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout->setHorizontalSpacing(4);
    gridLayout->setVerticalSpacing(4);
    gridLayout->setContentsMargins(4, 4, 4, 4);
    label_2 = new QLabel(page);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout->addWidget(label_2, 0, 0, 1, 1);

    comboBox_language = new QComboBox(page);
    comboBox_language->setObjectName(QString::fromUtf8("comboBox_language"));

    gridLayout->addWidget(comboBox_language, 1, 0, 1, 1);

    label = new QLabel(page);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 2, 0, 1, 1);

    comboBox_engine = new QComboBox(page);
    comboBox_engine->setObjectName(QString::fromUtf8("comboBox_engine"));

    gridLayout->addWidget(comboBox_engine, 3, 0, 1, 1);

    spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout->addItem(spacerItem, 10, 0, 1, 1);

    checkBox_autofix8bit = new QCheckBox(page);
    checkBox_autofix8bit->setObjectName(QString::fromUtf8("checkBox_autofix8bit"));

    gridLayout->addWidget(checkBox_autofix8bit, 4, 0, 1, 1);

    checkBox_autosave = new QCheckBox(page);
    checkBox_autosave->setObjectName(QString::fromUtf8("checkBox_autosave"));

    gridLayout->addWidget(checkBox_autosave, 5, 0, 1, 1);

    checkBox_autorating = new QCheckBox(page);
    checkBox_autorating->setObjectName(QString::fromUtf8("checkBox_autorating"));

    gridLayout->addWidget(checkBox_autorating, 6, 0, 1, 1);

    label_3 = new QLabel(page);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    gridLayout->addWidget(label_3, 8, 0, 1, 1);

    comboBox_cue = new QComboBox(page);
    comboBox_cue->setObjectName(QString::fromUtf8("comboBox_cue"));

    gridLayout->addWidget(comboBox_cue, 9, 0, 1, 1);

    checkBox_hideEmpty = new QCheckBox(page);
    checkBox_hideEmpty->setObjectName(QString::fromUtf8("checkBox_hideEmpty"));

    gridLayout->addWidget(checkBox_hideEmpty, 7, 0, 1, 1);

    toolBox->addItem(page, QIcon(QString::fromUtf8(":/icons/settings.png")), QApplication::translate("Settings", "Common settings", 0, QApplication::UnicodeUTF8));
    page_2 = new QWidget();
    page_2->setObjectName(QString::fromUtf8("page_2"));
    page_2->setGeometry(QRect(0, 0, 98, 28));
    toolBox->addItem(page_2, QIcon(QString::fromUtf8(":/icons/def_genre.png")), QApplication::translate("Settings", "Engine Settings", 0, QApplication::UnicodeUTF8));
    page_3 = new QWidget();
    page_3->setObjectName(QString::fromUtf8("page_3"));
    page_3->setGeometry(QRect(0, 0, 115, 138));
    gridLayout1 = new QGridLayout(page_3);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    gridLayout1->setHorizontalSpacing(4);
    gridLayout1->setVerticalSpacing(4);
    gridLayout1->setContentsMargins(4, 4, 4, 4);
    checkBox_proxyEnabled = new QGroupBox(page_3);
    checkBox_proxyEnabled->setObjectName(QString::fromUtf8("checkBox_proxyEnabled"));
    checkBox_proxyEnabled->setFlat(true);
    checkBox_proxyEnabled->setCheckable(true);
    checkBox_proxyEnabled->setChecked(false);
    gridLayout2 = new QGridLayout(checkBox_proxyEnabled);
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    gridLayout2->setHorizontalSpacing(4);
    gridLayout2->setVerticalSpacing(4);
    gridLayout2->setContentsMargins(0, 0, 0, 0);
    label_4 = new QLabel(checkBox_proxyEnabled);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    gridLayout2->addWidget(label_4, 1, 0, 1, 1);

    lineEdit_proxyHost = new QLineEdit(checkBox_proxyEnabled);
    lineEdit_proxyHost->setObjectName(QString::fromUtf8("lineEdit_proxyHost"));

    gridLayout2->addWidget(lineEdit_proxyHost, 1, 1, 1, 1);

    label_5 = new QLabel(checkBox_proxyEnabled);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    gridLayout2->addWidget(label_5, 2, 0, 1, 1);

    label_6 = new QLabel(checkBox_proxyEnabled);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    gridLayout2->addWidget(label_6, 3, 0, 1, 1);

    label_7 = new QLabel(checkBox_proxyEnabled);
    label_7->setObjectName(QString::fromUtf8("label_7"));

    gridLayout2->addWidget(label_7, 4, 0, 1, 1);

    spinBox_proxyPort = new QSpinBox(checkBox_proxyEnabled);
    spinBox_proxyPort->setObjectName(QString::fromUtf8("spinBox_proxyPort"));
    spinBox_proxyPort->setMaximum(65535);

    gridLayout2->addWidget(spinBox_proxyPort, 2, 1, 1, 1);

    lineEdit_proxyUser = new QLineEdit(checkBox_proxyEnabled);
    lineEdit_proxyUser->setObjectName(QString::fromUtf8("lineEdit_proxyUser"));

    gridLayout2->addWidget(lineEdit_proxyUser, 3, 1, 1, 1);

    lineEdit_proxyPassword = new QLineEdit(checkBox_proxyEnabled);
    lineEdit_proxyPassword->setObjectName(QString::fromUtf8("lineEdit_proxyPassword"));
    lineEdit_proxyPassword->setEchoMode(QLineEdit::Password);

    gridLayout2->addWidget(lineEdit_proxyPassword, 4, 1, 1, 1);


    gridLayout1->addWidget(checkBox_proxyEnabled, 0, 0, 1, 1);

    spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout1->addItem(spacerItem1, 1, 0, 1, 1);

    toolBox->addItem(page_3, QIcon(QString::fromUtf8(":/icons/internet.png")), QApplication::translate("Settings", "Internet connection", 0, QApplication::UnicodeUTF8));
    page_4 = new QWidget();
    page_4->setObjectName(QString::fromUtf8("page_4"));
    page_4->setGeometry(QRect(0, 0, 156, 130));
    gridLayout3 = new QGridLayout(page_4);
    gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
    gridLayout3->setHorizontalSpacing(4);
    gridLayout3->setVerticalSpacing(4);
    gridLayout3->setContentsMargins(4, 4, 4, 4);
    checkBox_lastfmScrobbling = new QGroupBox(page_4);
    checkBox_lastfmScrobbling->setObjectName(QString::fromUtf8("checkBox_lastfmScrobbling"));
    checkBox_lastfmScrobbling->setFlat(true);
    checkBox_lastfmScrobbling->setCheckable(true);
    checkBox_lastfmScrobbling->setChecked(false);
    gridLayout4 = new QGridLayout(checkBox_lastfmScrobbling);
    gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
    gridLayout4->setHorizontalSpacing(4);
    gridLayout4->setVerticalSpacing(4);
    gridLayout4->setContentsMargins(0, 0, 0, 0);
    label_8 = new QLabel(checkBox_lastfmScrobbling);
    label_8->setObjectName(QString::fromUtf8("label_8"));

    gridLayout4->addWidget(label_8, 1, 0, 1, 1);

    label_9 = new QLabel(checkBox_lastfmScrobbling);
    label_9->setObjectName(QString::fromUtf8("label_9"));

    gridLayout4->addWidget(label_9, 2, 0, 1, 1);

    lineEdit_lastfmUser = new QLineEdit(checkBox_lastfmScrobbling);
    lineEdit_lastfmUser->setObjectName(QString::fromUtf8("lineEdit_lastfmUser"));

    gridLayout4->addWidget(lineEdit_lastfmUser, 1, 1, 1, 1);

    lineEdit_lastfmPassword = new QLineEdit(checkBox_lastfmScrobbling);
    lineEdit_lastfmPassword->setObjectName(QString::fromUtf8("lineEdit_lastfmPassword"));
    lineEdit_lastfmPassword->setEchoMode(QLineEdit::Password);

    gridLayout4->addWidget(lineEdit_lastfmPassword, 2, 1, 1, 1);


    gridLayout3->addWidget(checkBox_lastfmScrobbling, 0, 0, 1, 1);

    spacerItem2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout3->addItem(spacerItem2, 3, 0, 1, 1);

    toolBox->addItem(page_4, QIcon(QString::fromUtf8(":/icons/lastfm.png")), QApplication::translate("Settings", "Last.FM", 0, QApplication::UnicodeUTF8));

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
    checkBox_hideEmpty->setText(QApplication::translate("Settings", "Hide nameless albums", 0, QApplication::UnicodeUTF8));
    toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("Settings", "Common settings", 0, QApplication::UnicodeUTF8));
    toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("Settings", "Engine Settings", 0, QApplication::UnicodeUTF8));
    checkBox_proxyEnabled->setTitle(QApplication::translate("Settings", "Use proxy", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("Settings", "Proxy host", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("Settings", "Port", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("Settings", "User name", 0, QApplication::UnicodeUTF8));
    label_7->setText(QApplication::translate("Settings", "Password", 0, QApplication::UnicodeUTF8));
    toolBox->setItemText(toolBox->indexOf(page_3), QApplication::translate("Settings", "Internet connection", 0, QApplication::UnicodeUTF8));
    checkBox_lastfmScrobbling->setTitle(QApplication::translate("Settings", "Enable Last.FM scrobbling", 0, QApplication::UnicodeUTF8));
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
