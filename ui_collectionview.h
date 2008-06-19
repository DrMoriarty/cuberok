/********************************************************************************
** Form generated from reading ui file 'collectionview.ui'
**
** Created: Fri 11. Jan 16:12:48 2008
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_COLLECTIONVIEW_H
#define UI_COLLECTIONVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QWidget>

class Ui_collectionviewClass
{
public:

    void setupUi(QWidget *collectionviewClass)
    {
    if (collectionviewClass->objectName().isEmpty())
        collectionviewClass->setObjectName(QString::fromUtf8("collectionviewClass"));
    collectionviewClass->resize(400, 300);

    retranslateUi(collectionviewClass);

    QMetaObject::connectSlotsByName(collectionviewClass);
    } // setupUi

    void retranslateUi(QWidget *collectionviewClass)
    {
    collectionviewClass->setWindowTitle(QApplication::translate("collectionviewClass", "collectionview", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(collectionviewClass);
    } // retranslateUi

};

namespace Ui {
    class collectionviewClass: public Ui_collectionviewClass {};
} // namespace Ui

#endif // UI_COLLECTIONVIEW_H
