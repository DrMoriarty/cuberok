/********************************************************************************
** Form generated from reading ui file 'tageditor.ui'
**
** Created: Tue 23. Dec 10:37:55 2008
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TAGEDITOR_H
#define UI_TAGEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>

class Ui_TagEditorClass
{
public:
    QGridLayout *gridLayout;
    QLineEdit *label;
    QPushButton *pushButton_Cancel;
    QPushButton *pushButton_Save;
    QPushButton *pushButton_Correct;
    QPushButton *pushButton_Correct2;
    QLineEdit *lineTitle;
    QLineEdit *lineArtist;
    QLineEdit *lineAlbum;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineComment;
    QLabel *label_5;
    QComboBox *comboBox_Genre;
    QLabel *label_6;
    QSpinBox *spinBox_Track;
    QSpinBox *spinBox_Year;
    QLabel *label_7;
    QLabel *label_8;
    QSpinBox *spinBox_Rating;
    QLabel *label_9;

    void setupUi(QDialog *TagEditorClass)
    {
    if (TagEditorClass->objectName().isEmpty())
        TagEditorClass->setObjectName(QString::fromUtf8("TagEditorClass"));
    TagEditorClass->resize(322, 382);
    TagEditorClass->setWindowIcon(QIcon(QString::fromUtf8(":/icons/application.png")));
    gridLayout = new QGridLayout(TagEditorClass);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label = new QLineEdit(TagEditorClass);
    label->setObjectName(QString::fromUtf8("label"));
    label->setReadOnly(true);

    gridLayout->addWidget(label, 1, 0, 1, 3);

    pushButton_Cancel = new QPushButton(TagEditorClass);
    pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));

    gridLayout->addWidget(pushButton_Cancel, 13, 0, 1, 1);

    pushButton_Save = new QPushButton(TagEditorClass);
    pushButton_Save->setObjectName(QString::fromUtf8("pushButton_Save"));
    pushButton_Save->setAutoDefault(true);
    pushButton_Save->setDefault(true);

    gridLayout->addWidget(pushButton_Save, 13, 2, 1, 1);

    pushButton_Correct = new QPushButton(TagEditorClass);
    pushButton_Correct->setObjectName(QString::fromUtf8("pushButton_Correct"));

    gridLayout->addWidget(pushButton_Correct, 0, 0, 1, 1);

    pushButton_Correct2 = new QPushButton(TagEditorClass);
    pushButton_Correct2->setObjectName(QString::fromUtf8("pushButton_Correct2"));

    gridLayout->addWidget(pushButton_Correct2, 0, 2, 1, 1);

    lineTitle = new QLineEdit(TagEditorClass);
    lineTitle->setObjectName(QString::fromUtf8("lineTitle"));

    gridLayout->addWidget(lineTitle, 3, 0, 1, 3);

    lineArtist = new QLineEdit(TagEditorClass);
    lineArtist->setObjectName(QString::fromUtf8("lineArtist"));

    gridLayout->addWidget(lineArtist, 5, 0, 1, 3);

    lineAlbum = new QLineEdit(TagEditorClass);
    lineAlbum->setObjectName(QString::fromUtf8("lineAlbum"));

    gridLayout->addWidget(lineAlbum, 7, 0, 1, 3);

    label_2 = new QLabel(TagEditorClass);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout->addWidget(label_2, 2, 0, 1, 3);

    label_3 = new QLabel(TagEditorClass);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    gridLayout->addWidget(label_3, 4, 0, 1, 3);

    label_4 = new QLabel(TagEditorClass);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    gridLayout->addWidget(label_4, 6, 0, 1, 3);

    lineComment = new QLineEdit(TagEditorClass);
    lineComment->setObjectName(QString::fromUtf8("lineComment"));

    gridLayout->addWidget(lineComment, 12, 0, 1, 3);

    label_5 = new QLabel(TagEditorClass);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    gridLayout->addWidget(label_5, 11, 0, 1, 3);

    comboBox_Genre = new QComboBox(TagEditorClass);
    comboBox_Genre->setObjectName(QString::fromUtf8("comboBox_Genre"));
    comboBox_Genre->setEditable(true);

    gridLayout->addWidget(comboBox_Genre, 8, 1, 1, 2);

    label_6 = new QLabel(TagEditorClass);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    gridLayout->addWidget(label_6, 8, 0, 1, 1);

    spinBox_Track = new QSpinBox(TagEditorClass);
    spinBox_Track->setObjectName(QString::fromUtf8("spinBox_Track"));
    spinBox_Track->setMaximum(999);

    gridLayout->addWidget(spinBox_Track, 10, 0, 1, 1);

    spinBox_Year = new QSpinBox(TagEditorClass);
    spinBox_Year->setObjectName(QString::fromUtf8("spinBox_Year"));
    spinBox_Year->setMaximum(9999);

    gridLayout->addWidget(spinBox_Year, 10, 1, 1, 1);

    label_7 = new QLabel(TagEditorClass);
    label_7->setObjectName(QString::fromUtf8("label_7"));

    gridLayout->addWidget(label_7, 9, 0, 1, 1);

    label_8 = new QLabel(TagEditorClass);
    label_8->setObjectName(QString::fromUtf8("label_8"));

    gridLayout->addWidget(label_8, 9, 1, 1, 1);

    spinBox_Rating = new QSpinBox(TagEditorClass);
    spinBox_Rating->setObjectName(QString::fromUtf8("spinBox_Rating"));
    spinBox_Rating->setMinimum(-99);
    spinBox_Rating->setValue(0);

    gridLayout->addWidget(spinBox_Rating, 10, 2, 1, 1);

    label_9 = new QLabel(TagEditorClass);
    label_9->setObjectName(QString::fromUtf8("label_9"));

    gridLayout->addWidget(label_9, 9, 2, 1, 1);


    retranslateUi(TagEditorClass);
    QObject::connect(pushButton_Save, SIGNAL(clicked()), TagEditorClass, SLOT(save()));
    QObject::connect(pushButton_Cancel, SIGNAL(clicked()), TagEditorClass, SLOT(close()));
    QObject::connect(pushButton_Correct, SIGNAL(clicked()), TagEditorClass, SLOT(correct1()));
    QObject::connect(pushButton_Correct2, SIGNAL(clicked()), TagEditorClass, SLOT(correct2()));

    QMetaObject::connectSlotsByName(TagEditorClass);
    } // setupUi

    void retranslateUi(QDialog *TagEditorClass)
    {
    TagEditorClass->setWindowTitle(QApplication::translate("TagEditorClass", "TagEditor", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("TagEditorClass", "File", 0, QApplication::UnicodeUTF8));
    pushButton_Cancel->setText(QApplication::translate("TagEditorClass", "Cancel", 0, QApplication::UnicodeUTF8));
    pushButton_Save->setText(QApplication::translate("TagEditorClass", "Save", 0, QApplication::UnicodeUTF8));
    pushButton_Correct->setText(QApplication::translate("TagEditorClass", "Correct cp1251", 0, QApplication::UnicodeUTF8));
    pushButton_Correct2->setText(QApplication::translate("TagEditorClass", "Correct 7bit cp1251", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("TagEditorClass", "Title", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("TagEditorClass", "Artist", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("TagEditorClass", "Album", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("TagEditorClass", "Comment", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("TagEditorClass", "Genre", 0, QApplication::UnicodeUTF8));
    label_7->setText(QApplication::translate("TagEditorClass", "Track", 0, QApplication::UnicodeUTF8));
    label_8->setText(QApplication::translate("TagEditorClass", "Year", 0, QApplication::UnicodeUTF8));
    label_9->setText(QApplication::translate("TagEditorClass", "Rating", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(TagEditorClass);
    } // retranslateUi

};

namespace Ui {
    class TagEditorClass: public Ui_TagEditorClass {};
} // namespace Ui

#endif // UI_TAGEDITOR_H
