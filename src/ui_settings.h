/********************************************************************************
** Form generated from reading ui file 'settings.ui'
**
** Created: Wed 3. Sep 11:36:04 2008
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
#include <QtGui/QSpacerItem>
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
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Settings)
    {
    if (Settings->objectName().isEmpty())
        Settings->setObjectName(QString::fromUtf8("Settings"));
    Settings->resize(379, 278);
    vboxLayout = new QVBoxLayout(Settings);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    toolBox = new QToolBox(Settings);
    toolBox->setObjectName(QString::fromUtf8("toolBox"));
    page = new QWidget();
    page->setObjectName(QString::fromUtf8("page"));
    page->setGeometry(QRect(0, 0, 361, 172));
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
    Q_UNUSED(Settings);
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

#endif // UI_SETTINGS_H
