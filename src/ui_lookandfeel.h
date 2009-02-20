/********************************************************************************
** Form generated from reading ui file 'lookandfeel.ui'
**
** Created: Thu 19. Feb 16:28:21 2009
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_LOOKANDFEEL_H
#define UI_LOOKANDFEEL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollBar>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_LookAndFeelClass
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QVBoxLayout *vboxLayout;
    QLabel *label_4;
    QComboBox *comboBox_style;
    QGroupBox *groupBox_3;
    QVBoxLayout *vboxLayout1;
    QLabel *label_2;
    QComboBox *comboBox_group;
    QLabel *label;
    QComboBox *comboBox_role;
    QLabel *label_3;
    QComboBox *comboBox_brush;
    QPushButton *pushButton_color;
    QPushButton *pushButton_quick;
    QWidget *tab_3;
    QFrame *frame;
    QGridLayout *gridLayout1;
    QSpinBox *spinBox;
    QComboBox *comboBox_2;
    QPushButton *pushButton;
    QScrollBar *horizontalScrollBar;
    QSlider *horizontalSlider;
    QTextBrowser *textBrowser;
    QLineEdit *lineEdit;
    QGroupBox *groupBox;
    QVBoxLayout *vboxLayout2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QGroupBox *groupBox_2;
    QVBoxLayout *vboxLayout3;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QProgressBar *progressBar;
    QFrame *frame_2;
    QHBoxLayout *hboxLayout;
    QPushButton *pushButton_cancel;
    QPushButton *pushButton_apply;
    QPushButton *pushButton_ok;

    void setupUi(QDialog *LookAndFeelClass)
    {
    if (LookAndFeelClass->objectName().isEmpty())
        LookAndFeelClass->setObjectName(QString::fromUtf8("LookAndFeelClass"));
    LookAndFeelClass->resize(560, 392);
    LookAndFeelClass->setWindowIcon(QIcon(QString::fromUtf8(":/icons/application.png")));
    gridLayout = new QGridLayout(LookAndFeelClass);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    tabWidget = new QTabWidget(LookAndFeelClass);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    vboxLayout = new QVBoxLayout(tab_2);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(11);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    label_4 = new QLabel(tab_2);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    vboxLayout->addWidget(label_4);

    comboBox_style = new QComboBox(tab_2);
    comboBox_style->setObjectName(QString::fromUtf8("comboBox_style"));

    vboxLayout->addWidget(comboBox_style);

    groupBox_3 = new QGroupBox(tab_2);
    groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
    vboxLayout1 = new QVBoxLayout(groupBox_3);
    vboxLayout1->setSpacing(6);
    vboxLayout1->setMargin(11);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    label_2 = new QLabel(groupBox_3);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    vboxLayout1->addWidget(label_2);

    comboBox_group = new QComboBox(groupBox_3);
    comboBox_group->setObjectName(QString::fromUtf8("comboBox_group"));

    vboxLayout1->addWidget(comboBox_group);

    label = new QLabel(groupBox_3);
    label->setObjectName(QString::fromUtf8("label"));

    vboxLayout1->addWidget(label);

    comboBox_role = new QComboBox(groupBox_3);
    comboBox_role->setObjectName(QString::fromUtf8("comboBox_role"));

    vboxLayout1->addWidget(comboBox_role);

    label_3 = new QLabel(groupBox_3);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    vboxLayout1->addWidget(label_3);

    comboBox_brush = new QComboBox(groupBox_3);
    comboBox_brush->setObjectName(QString::fromUtf8("comboBox_brush"));

    vboxLayout1->addWidget(comboBox_brush);

    pushButton_color = new QPushButton(groupBox_3);
    pushButton_color->setObjectName(QString::fromUtf8("pushButton_color"));

    vboxLayout1->addWidget(pushButton_color);


    vboxLayout->addWidget(groupBox_3);

    pushButton_quick = new QPushButton(tab_2);
    pushButton_quick->setObjectName(QString::fromUtf8("pushButton_quick"));

    vboxLayout->addWidget(pushButton_quick);

    tabWidget->addTab(tab_2, QString());
    tab_3 = new QWidget();
    tab_3->setObjectName(QString::fromUtf8("tab_3"));
    tabWidget->addTab(tab_3, QString());

    gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

    frame = new QFrame(LookAndFeelClass);
    frame->setObjectName(QString::fromUtf8("frame"));
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
    frame->setSizePolicy(sizePolicy);
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Sunken);
    gridLayout1 = new QGridLayout(frame);
    gridLayout1->setSpacing(6);
    gridLayout1->setMargin(11);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    spinBox = new QSpinBox(frame);
    spinBox->setObjectName(QString::fromUtf8("spinBox"));

    gridLayout1->addWidget(spinBox, 2, 1, 1, 1);

    comboBox_2 = new QComboBox(frame);
    comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

    gridLayout1->addWidget(comboBox_2, 1, 1, 1, 2);

    pushButton = new QPushButton(frame);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));

    gridLayout1->addWidget(pushButton, 2, 2, 1, 1);

    horizontalScrollBar = new QScrollBar(frame);
    horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
    horizontalScrollBar->setOrientation(Qt::Horizontal);

    gridLayout1->addWidget(horizontalScrollBar, 3, 1, 1, 2);

    horizontalSlider = new QSlider(frame);
    horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
    horizontalSlider->setOrientation(Qt::Horizontal);

    gridLayout1->addWidget(horizontalSlider, 4, 1, 1, 2);

    textBrowser = new QTextBrowser(frame);
    textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

    gridLayout1->addWidget(textBrowser, 6, 1, 1, 2);

    lineEdit = new QLineEdit(frame);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

    gridLayout1->addWidget(lineEdit, 0, 1, 1, 2);

    groupBox = new QGroupBox(frame);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    vboxLayout2 = new QVBoxLayout(groupBox);
    vboxLayout2->setSpacing(6);
    vboxLayout2->setMargin(11);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    radioButton = new QRadioButton(groupBox);
    radioButton->setObjectName(QString::fromUtf8("radioButton"));
    radioButton->setChecked(true);

    vboxLayout2->addWidget(radioButton);

    radioButton_2 = new QRadioButton(groupBox);
    radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

    vboxLayout2->addWidget(radioButton_2);


    gridLayout1->addWidget(groupBox, 0, 0, 3, 1);

    groupBox_2 = new QGroupBox(frame);
    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    vboxLayout3 = new QVBoxLayout(groupBox_2);
    vboxLayout3->setSpacing(6);
    vboxLayout3->setMargin(11);
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    checkBox = new QCheckBox(groupBox_2);
    checkBox->setObjectName(QString::fromUtf8("checkBox"));
    checkBox->setChecked(true);

    vboxLayout3->addWidget(checkBox);

    checkBox_2 = new QCheckBox(groupBox_2);
    checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

    vboxLayout3->addWidget(checkBox_2);

    checkBox_3 = new QCheckBox(groupBox_2);
    checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

    vboxLayout3->addWidget(checkBox_3);


    gridLayout1->addWidget(groupBox_2, 3, 0, 4, 1);

    progressBar = new QProgressBar(frame);
    progressBar->setObjectName(QString::fromUtf8("progressBar"));
    progressBar->setValue(55);

    gridLayout1->addWidget(progressBar, 5, 1, 1, 2);


    gridLayout->addWidget(frame, 0, 1, 1, 1);

    frame_2 = new QFrame(LookAndFeelClass);
    frame_2->setObjectName(QString::fromUtf8("frame_2"));
    frame_2->setMinimumSize(QSize(16, 48));
    frame_2->setFrameShape(QFrame::NoFrame);
    frame_2->setFrameShadow(QFrame::Raised);
    hboxLayout = new QHBoxLayout(frame_2);
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(11);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    hboxLayout->setContentsMargins(1, 1, 1, 1);
    pushButton_cancel = new QPushButton(frame_2);
    pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));

    hboxLayout->addWidget(pushButton_cancel);

    pushButton_apply = new QPushButton(frame_2);
    pushButton_apply->setObjectName(QString::fromUtf8("pushButton_apply"));

    hboxLayout->addWidget(pushButton_apply);

    pushButton_ok = new QPushButton(frame_2);
    pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
    pushButton_ok->setDefault(true);

    hboxLayout->addWidget(pushButton_ok);


    gridLayout->addWidget(frame_2, 1, 0, 1, 2);


    retranslateUi(LookAndFeelClass);
    QObject::connect(pushButton_cancel, SIGNAL(clicked()), LookAndFeelClass, SLOT(reject()));
    QObject::connect(pushButton_ok, SIGNAL(clicked()), LookAndFeelClass, SLOT(acceptWithApply()));
    QObject::connect(pushButton_apply, SIGNAL(clicked()), LookAndFeelClass, SLOT(applyAll()));
    QObject::connect(comboBox_role, SIGNAL(activated(int)), LookAndFeelClass, SLOT(set_role(int)));
    QObject::connect(comboBox_group, SIGNAL(activated(int)), LookAndFeelClass, SLOT(set_group(int)));
    QObject::connect(comboBox_brush, SIGNAL(activated(int)), LookAndFeelClass, SLOT(set_brush(int)));
    QObject::connect(pushButton_color, SIGNAL(clicked()), LookAndFeelClass, SLOT(set_color()));
    QObject::connect(comboBox_style, SIGNAL(activated(QString)), LookAndFeelClass, SLOT(set_style(QString)));
    QObject::connect(pushButton_quick, SIGNAL(clicked()), LookAndFeelClass, SLOT(quick()));

    tabWidget->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(LookAndFeelClass);
    } // setupUi

    void retranslateUi(QDialog *LookAndFeelClass)
    {
    LookAndFeelClass->setWindowTitle(QApplication::translate("LookAndFeelClass", "LookAndFeel", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("LookAndFeelClass", "Style", 0, QApplication::UnicodeUTF8));
    groupBox_3->setTitle(QApplication::translate("LookAndFeelClass", "Colors", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("LookAndFeelClass", "Group", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("LookAndFeelClass", "Role", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("LookAndFeelClass", "Brush", 0, QApplication::UnicodeUTF8));
    pushButton_color->setText(QApplication::translate("LookAndFeelClass", "Color", 0, QApplication::UnicodeUTF8));
    pushButton_quick->setText(QApplication::translate("LookAndFeelClass", "Quick colors", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("LookAndFeelClass", "Colors", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("LookAndFeelClass", "Fonts", 0, QApplication::UnicodeUTF8));
    pushButton->setText(QApplication::translate("LookAndFeelClass", "PushButton", 0, QApplication::UnicodeUTF8));
    lineEdit->setText(QApplication::translate("LookAndFeelClass", "Line Edit", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("LookAndFeelClass", "GroupBox", 0, QApplication::UnicodeUTF8));
    radioButton->setText(QApplication::translate("LookAndFeelClass", "RadioButton", 0, QApplication::UnicodeUTF8));
    radioButton_2->setText(QApplication::translate("LookAndFeelClass", "RadioButton", 0, QApplication::UnicodeUTF8));
    groupBox_2->setTitle(QApplication::translate("LookAndFeelClass", "GroupBox", 0, QApplication::UnicodeUTF8));
    checkBox->setText(QApplication::translate("LookAndFeelClass", "CheckBox", 0, QApplication::UnicodeUTF8));
    checkBox_2->setText(QApplication::translate("LookAndFeelClass", "CheckBox", 0, QApplication::UnicodeUTF8));
    checkBox_3->setText(QApplication::translate("LookAndFeelClass", "CheckBox", 0, QApplication::UnicodeUTF8));
    pushButton_cancel->setText(QApplication::translate("LookAndFeelClass", "Cancel", 0, QApplication::UnicodeUTF8));
    pushButton_apply->setText(QApplication::translate("LookAndFeelClass", "Apply", 0, QApplication::UnicodeUTF8));
    pushButton_ok->setText(QApplication::translate("LookAndFeelClass", "Ok", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(LookAndFeelClass);
    } // retranslateUi

};

namespace Ui {
    class LookAndFeelClass: public Ui_LookAndFeelClass {};
} // namespace Ui

#endif // UI_LOOKANDFEEL_H
