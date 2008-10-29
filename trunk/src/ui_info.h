/********************************************************************************
** Form generated from reading ui file 'info.ui'
**
** Created: Wed 17. Sep 15:37:40 2008
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_INFO_H
#define UI_INFO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_Info
{
public:
    QVBoxLayout *vboxLayout;
    QScrollArea *widget;
    QVBoxLayout *vboxLayout1;
    QPushButton *pushButton_artist;
    QFrame *frame_artist;
    QVBoxLayout *vboxLayout2;
    QFrame *frame;
    QHBoxLayout *hboxLayout;
    QLabel *label_artistPicture;
    QFrame *frame_3;
    QVBoxLayout *vboxLayout3;
    QLabel *label_artist1;
    QLabel *label_artist2;
    QLabel *label_artist3;
    QListWidget *listWidget_2;
    QPushButton *pushButton_album;
    QFrame *frame_album;
    QVBoxLayout *vboxLayout4;
    QFrame *frame_5;
    QHBoxLayout *hboxLayout1;
    QLabel *label_albumPicture;
    QFrame *frame_4;
    QVBoxLayout *vboxLayout5;
    QLabel *label_album1;
    QListWidget *listWidget;

    void setupUi(QWidget *Info)
    {
    if (Info->objectName().isEmpty())
        Info->setObjectName(QString::fromUtf8("Info"));
    Info->resize(264, 356);
    vboxLayout = new QVBoxLayout(Info);
    vboxLayout->setSpacing(4);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    vboxLayout->setContentsMargins(4, 4, 4, 4);
    widget = new QScrollArea(Info);
    widget->setObjectName(QString::fromUtf8("widget"));
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
    widget->setSizePolicy(sizePolicy);
    widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    vboxLayout1 = new QVBoxLayout(widget);
    vboxLayout1->setSpacing(4);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    vboxLayout1->setContentsMargins(4, 4, 4, 4);
    pushButton_artist = new QPushButton(widget);
    pushButton_artist->setObjectName(QString::fromUtf8("pushButton_artist"));
    QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(pushButton_artist->sizePolicy().hasHeightForWidth());
    pushButton_artist->setSizePolicy(sizePolicy1);
    pushButton_artist->setCheckable(true);
    pushButton_artist->setChecked(true);
    pushButton_artist->setFlat(true);

    vboxLayout1->addWidget(pushButton_artist);

    frame_artist = new QFrame(widget);
    frame_artist->setObjectName(QString::fromUtf8("frame_artist"));
    QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(frame_artist->sizePolicy().hasHeightForWidth());
    frame_artist->setSizePolicy(sizePolicy2);
    frame_artist->setFrameShape(QFrame::Box);
    frame_artist->setFrameShadow(QFrame::Sunken);
    vboxLayout2 = new QVBoxLayout(frame_artist);
    vboxLayout2->setSpacing(4);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    vboxLayout2->setContentsMargins(4, 4, 4, 4);
    frame = new QFrame(frame_artist);
    frame->setObjectName(QString::fromUtf8("frame"));
    sizePolicy2.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
    frame->setSizePolicy(sizePolicy2);
    frame->setFrameShape(QFrame::NoFrame);
    frame->setFrameShadow(QFrame::Raised);
    hboxLayout = new QHBoxLayout(frame);
    hboxLayout->setSpacing(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    hboxLayout->setContentsMargins(0, 0, 0, 0);
    label_artistPicture = new QLabel(frame);
    label_artistPicture->setObjectName(QString::fromUtf8("label_artistPicture"));
    QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(label_artistPicture->sizePolicy().hasHeightForWidth());
    label_artistPicture->setSizePolicy(sizePolicy3);

    hboxLayout->addWidget(label_artistPicture);

    frame_3 = new QFrame(frame);
    frame_3->setObjectName(QString::fromUtf8("frame_3"));
    QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    sizePolicy4.setHorizontalStretch(0);
    sizePolicy4.setVerticalStretch(0);
    sizePolicy4.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
    frame_3->setSizePolicy(sizePolicy4);
    frame_3->setFrameShape(QFrame::Box);
    frame_3->setFrameShadow(QFrame::Plain);
    vboxLayout3 = new QVBoxLayout(frame_3);
    vboxLayout3->setSpacing(4);
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    vboxLayout3->setContentsMargins(4, 4, 4, 4);
    label_artist1 = new QLabel(frame_3);
    label_artist1->setObjectName(QString::fromUtf8("label_artist1"));
    sizePolicy2.setHeightForWidth(label_artist1->sizePolicy().hasHeightForWidth());
    label_artist1->setSizePolicy(sizePolicy2);
    label_artist1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    vboxLayout3->addWidget(label_artist1);

    label_artist2 = new QLabel(frame_3);
    label_artist2->setObjectName(QString::fromUtf8("label_artist2"));
    sizePolicy2.setHeightForWidth(label_artist2->sizePolicy().hasHeightForWidth());
    label_artist2->setSizePolicy(sizePolicy2);
    label_artist2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    vboxLayout3->addWidget(label_artist2);

    label_artist3 = new QLabel(frame_3);
    label_artist3->setObjectName(QString::fromUtf8("label_artist3"));
    sizePolicy2.setHeightForWidth(label_artist3->sizePolicy().hasHeightForWidth());
    label_artist3->setSizePolicy(sizePolicy2);
    label_artist3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    vboxLayout3->addWidget(label_artist3);


    hboxLayout->addWidget(frame_3);


    vboxLayout2->addWidget(frame);

    listWidget_2 = new QListWidget(frame_artist);
    listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));
    QSizePolicy sizePolicy5(QSizePolicy::Ignored, QSizePolicy::Ignored);
    sizePolicy5.setHorizontalStretch(0);
    sizePolicy5.setVerticalStretch(0);
    sizePolicy5.setHeightForWidth(listWidget_2->sizePolicy().hasHeightForWidth());
    listWidget_2->setSizePolicy(sizePolicy5);
    listWidget_2->setFrameShape(QFrame::Box);

    vboxLayout2->addWidget(listWidget_2);


    vboxLayout1->addWidget(frame_artist);

    pushButton_album = new QPushButton(widget);
    pushButton_album->setObjectName(QString::fromUtf8("pushButton_album"));
    sizePolicy1.setHeightForWidth(pushButton_album->sizePolicy().hasHeightForWidth());
    pushButton_album->setSizePolicy(sizePolicy1);
    pushButton_album->setCheckable(true);
    pushButton_album->setChecked(true);
    pushButton_album->setFlat(true);

    vboxLayout1->addWidget(pushButton_album);

    frame_album = new QFrame(widget);
    frame_album->setObjectName(QString::fromUtf8("frame_album"));
    sizePolicy2.setHeightForWidth(frame_album->sizePolicy().hasHeightForWidth());
    frame_album->setSizePolicy(sizePolicy2);
    frame_album->setFrameShape(QFrame::Box);
    frame_album->setFrameShadow(QFrame::Sunken);
    vboxLayout4 = new QVBoxLayout(frame_album);
    vboxLayout4->setSpacing(4);
    vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
    vboxLayout4->setContentsMargins(4, 4, 4, 4);
    frame_5 = new QFrame(frame_album);
    frame_5->setObjectName(QString::fromUtf8("frame_5"));
    QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy6.setHorizontalStretch(0);
    sizePolicy6.setVerticalStretch(0);
    sizePolicy6.setHeightForWidth(frame_5->sizePolicy().hasHeightForWidth());
    frame_5->setSizePolicy(sizePolicy6);
    frame_5->setFrameShape(QFrame::NoFrame);
    frame_5->setFrameShadow(QFrame::Plain);
    hboxLayout1 = new QHBoxLayout(frame_5);
    hboxLayout1->setSpacing(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    hboxLayout1->setContentsMargins(0, 0, 0, 0);
    label_albumPicture = new QLabel(frame_5);
    label_albumPicture->setObjectName(QString::fromUtf8("label_albumPicture"));
    sizePolicy3.setHeightForWidth(label_albumPicture->sizePolicy().hasHeightForWidth());
    label_albumPicture->setSizePolicy(sizePolicy3);

    hboxLayout1->addWidget(label_albumPicture);

    frame_4 = new QFrame(frame_5);
    frame_4->setObjectName(QString::fromUtf8("frame_4"));
    sizePolicy1.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
    frame_4->setSizePolicy(sizePolicy1);
    frame_4->setFrameShape(QFrame::Box);
    frame_4->setFrameShadow(QFrame::Plain);
    vboxLayout5 = new QVBoxLayout(frame_4);
    vboxLayout5->setSpacing(4);
    vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
    vboxLayout5->setContentsMargins(4, 4, 4, 4);
    label_album1 = new QLabel(frame_4);
    label_album1->setObjectName(QString::fromUtf8("label_album1"));
    sizePolicy.setHeightForWidth(label_album1->sizePolicy().hasHeightForWidth());
    label_album1->setSizePolicy(sizePolicy);
    label_album1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    vboxLayout5->addWidget(label_album1);


    hboxLayout1->addWidget(frame_4);


    vboxLayout4->addWidget(frame_5);

    listWidget = new QListWidget(frame_album);
    listWidget->setObjectName(QString::fromUtf8("listWidget"));
    sizePolicy5.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
    listWidget->setSizePolicy(sizePolicy5);
    listWidget->setFrameShape(QFrame::Box);

    vboxLayout4->addWidget(listWidget);


    vboxLayout1->addWidget(frame_album);


    vboxLayout->addWidget(widget);


    retranslateUi(Info);
    QObject::connect(pushButton_album, SIGNAL(toggled(bool)), frame_album, SLOT(setVisible(bool)));
    QObject::connect(pushButton_artist, SIGNAL(toggled(bool)), frame_artist, SLOT(setVisible(bool)));

    QMetaObject::connectSlotsByName(Info);
    } // setupUi

    void retranslateUi(QWidget *Info)
    {
    Info->setWindowTitle(QApplication::translate("Info", "Info", 0, QApplication::UnicodeUTF8));
    pushButton_artist->setText(QApplication::translate("Info", "Artist", 0, QApplication::UnicodeUTF8));
    label_artistPicture->setText(QApplication::translate("Info", "TextLabel", 0, QApplication::UnicodeUTF8));
    label_artist1->setText(QApplication::translate("Info", "TextLabel", 0, QApplication::UnicodeUTF8));
    label_artist2->setText(QApplication::translate("Info", "TextLabel", 0, QApplication::UnicodeUTF8));
    label_artist3->setText(QApplication::translate("Info", "TextLabel", 0, QApplication::UnicodeUTF8));
    pushButton_album->setText(QApplication::translate("Info", "Album", 0, QApplication::UnicodeUTF8));
    label_albumPicture->setText(QApplication::translate("Info", "TextLabel", 0, QApplication::UnicodeUTF8));
    label_album1->setText(QApplication::translate("Info", "TextLabel", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Info);
    } // retranslateUi

};

namespace Ui {
    class Info: public Ui_Info {};
} // namespace Ui

#endif // UI_INFO_H
