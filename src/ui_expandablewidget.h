/********************************************************************************
** Form generated from reading ui file 'expandablewidget.ui'
**
** Created: Wed 17. Sep 13:58:57 2008
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_EXPANDABLEWIDGET_H
#define UI_EXPANDABLEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_ExpandableWidget
{
public:
    QVBoxLayout *vboxLayout;
    QPushButton *pushButton;
    QFrame *frame;

    void setupUi(QWidget *ExpandableWidget)
    {
    if (ExpandableWidget->objectName().isEmpty())
        ExpandableWidget->setObjectName(QString::fromUtf8("ExpandableWidget"));
    ExpandableWidget->resize(400, 300);
    vboxLayout = new QVBoxLayout(ExpandableWidget);
    vboxLayout->setSpacing(4);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    vboxLayout->setContentsMargins(4, 4, 4, 4);
    pushButton = new QPushButton(ExpandableWidget);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setCheckable(true);
    pushButton->setChecked(true);
    pushButton->setFlat(true);

    vboxLayout->addWidget(pushButton);

    frame = new QFrame(ExpandableWidget);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setFrameShape(QFrame::Box);
    frame->setFrameShadow(QFrame::Sunken);

    vboxLayout->addWidget(frame);


    retranslateUi(ExpandableWidget);
    QObject::connect(pushButton, SIGNAL(toggled(bool)), frame, SLOT(setVisible(bool)));

    QMetaObject::connectSlotsByName(ExpandableWidget);
    } // setupUi

    void retranslateUi(QWidget *ExpandableWidget)
    {
    ExpandableWidget->setWindowTitle(QApplication::translate("ExpandableWidget", "ExpandableWidget", 0, QApplication::UnicodeUTF8));
    pushButton->setText(QApplication::translate("ExpandableWidget", "PushButton", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ExpandableWidget);
    } // retranslateUi

};

namespace Ui {
    class ExpandableWidget: public Ui_ExpandableWidget {};
} // namespace Ui

#endif // UI_EXPANDABLEWIDGET_H
