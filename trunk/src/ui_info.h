/********************************************************************************
** Form generated from reading ui file 'info.ui'
**
** Created: Fri 6. Mar 12:27:14 2009
**      by: Qt User Interface Compiler version 4.5.0-rc1
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
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "stareditor.h"

QT_BEGIN_NAMESPACE

class Ui_Info
{
public:
    QAction *actionRateUp;
    QAction *actionRateDown;
    QAction *actionLoveIt;
    QAction *actionBan;
    QAction *actionShowArtistInfo;
    QAction *actionShowAlbumInfo;
    QAction *actionShowLyrics;
    QVBoxLayout *vboxLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *vboxLayout1;
    QToolBar *col_toolbar;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QFrame *frame_0;
    QVBoxLayout *vboxLayout2;
    QFrame *frame_3;
    QVBoxLayout *vboxLayout3;
    QLabel *label_so1;
    StarEditor *songRating;
    QFrame *frame_2;
    QVBoxLayout *vboxLayout4;
    QLabel *label_al0;
    QFrame *frame_5;
    QVBoxLayout *vboxLayout5;
    QLabel *label_al1;
    StarEditor *albumRating;
    QSpacerItem *spacerItem1;
    QSpacerItem *spacerItem2;
    QToolBar *col_toolbar2;
    QWidget *tab_2;
    QVBoxLayout *vboxLayout6;
    QTextBrowser *textEdit;
    QWidget *tab_3;
    QVBoxLayout *vboxLayout7;
    QTextBrowser *textEdit_2;

    void setupUi(QWidget *Info)
    {
        if (Info->objectName().isEmpty())
            Info->setObjectName(QString::fromUtf8("Info"));
        Info->resize(217, 325);
        actionRateUp = new QAction(Info);
        actionRateUp->setObjectName(QString::fromUtf8("actionRateUp"));
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/star.png")), QIcon::Normal, QIcon::Off);
        actionRateUp->setIcon(icon);
        actionRateDown = new QAction(Info);
        actionRateDown->setObjectName(QString::fromUtf8("actionRateDown"));
        QIcon icon1;
        icon1.addPixmap(QPixmap(QString::fromUtf8(":/icons/antistar.png")), QIcon::Normal, QIcon::Off);
        actionRateDown->setIcon(icon1);
        actionLoveIt = new QAction(Info);
        actionLoveIt->setObjectName(QString::fromUtf8("actionLoveIt"));
        QIcon icon2;
        icon2.addPixmap(QPixmap(QString::fromUtf8(":/icons/heart.png")), QIcon::Normal, QIcon::Off);
        actionLoveIt->setIcon(icon2);
        actionBan = new QAction(Info);
        actionBan->setObjectName(QString::fromUtf8("actionBan"));
        QIcon icon3;
        icon3.addPixmap(QPixmap(QString::fromUtf8(":/icons/ban.png")), QIcon::Normal, QIcon::Off);
        actionBan->setIcon(icon3);
        actionShowArtistInfo = new QAction(Info);
        actionShowArtistInfo->setObjectName(QString::fromUtf8("actionShowArtistInfo"));
        QIcon icon4;
        icon4.addPixmap(QPixmap(QString::fromUtf8(":/icons/def_artist.png")), QIcon::Normal, QIcon::Off);
        actionShowArtistInfo->setIcon(icon4);
        actionShowAlbumInfo = new QAction(Info);
        actionShowAlbumInfo->setObjectName(QString::fromUtf8("actionShowAlbumInfo"));
        QIcon icon5;
        icon5.addPixmap(QPixmap(QString::fromUtf8(":/icons/def_album.png")), QIcon::Normal, QIcon::Off);
        actionShowAlbumInfo->setIcon(icon5);
        actionShowLyrics = new QAction(Info);
        actionShowLyrics->setObjectName(QString::fromUtf8("actionShowLyrics"));
        QIcon icon6;
        icon6.addPixmap(QPixmap(QString::fromUtf8(":/icons/def_song.png")), QIcon::Normal, QIcon::Off);
        actionShowLyrics->setIcon(icon6);
        vboxLayout = new QVBoxLayout(Info);
        vboxLayout->setSpacing(0);
        vboxLayout->setMargin(0);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        tabWidget = new QTabWidget(Info);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        vboxLayout1 = new QVBoxLayout(tab);
        vboxLayout1->setSpacing(4);
        vboxLayout1->setMargin(4);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        col_toolbar = new QToolBar(tab);
        col_toolbar->setObjectName(QString::fromUtf8("col_toolbar"));

        vboxLayout1->addWidget(col_toolbar);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(0);
        hboxLayout->setMargin(0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        frame_0 = new QFrame(tab);
        frame_0->setObjectName(QString::fromUtf8("frame_0"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_0->sizePolicy().hasHeightForWidth());
        frame_0->setSizePolicy(sizePolicy);
        frame_0->setMinimumSize(QSize(0, 0));
        frame_0->setFrameShape(QFrame::NoFrame);
        frame_0->setFrameShadow(QFrame::Raised);
        vboxLayout2 = new QVBoxLayout(frame_0);
        vboxLayout2->setSpacing(0);
        vboxLayout2->setMargin(0);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        frame_3 = new QFrame(frame_0);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy1);
        frame_3->setMinimumSize(QSize(0, 0));
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Raised);
        vboxLayout3 = new QVBoxLayout(frame_3);
        vboxLayout3->setSpacing(0);
        vboxLayout3->setMargin(4);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        label_so1 = new QLabel(frame_3);
        label_so1->setObjectName(QString::fromUtf8("label_so1"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_so1->sizePolicy().hasHeightForWidth());
        label_so1->setSizePolicy(sizePolicy2);
        label_so1->setAlignment(Qt::AlignCenter);

        vboxLayout3->addWidget(label_so1);

        songRating = new StarEditor(frame_3);
        songRating->setObjectName(QString::fromUtf8("songRating"));

        vboxLayout3->addWidget(songRating);


        vboxLayout2->addWidget(frame_3);

        frame_2 = new QFrame(frame_0);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setMinimumSize(QSize(0, 0));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        vboxLayout4 = new QVBoxLayout(frame_2);
        vboxLayout4->setSpacing(0);
        vboxLayout4->setMargin(0);
        vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
        label_al0 = new QLabel(frame_2);
        label_al0->setObjectName(QString::fromUtf8("label_al0"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_al0->sizePolicy().hasHeightForWidth());
        label_al0->setSizePolicy(sizePolicy3);
        label_al0->setMinimumSize(QSize(64, 64));
        label_al0->setMaximumSize(QSize(65535, 65535));
        label_al0->setPixmap(QPixmap(QString::fromUtf8(":/icons/def_album.png")));
        label_al0->setScaledContents(true);
        label_al0->setAlignment(Qt::AlignCenter);

        vboxLayout4->addWidget(label_al0);


        vboxLayout2->addWidget(frame_2);

        frame_5 = new QFrame(frame_0);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        sizePolicy2.setHeightForWidth(frame_5->sizePolicy().hasHeightForWidth());
        frame_5->setSizePolicy(sizePolicy2);
        frame_5->setFrameShape(QFrame::NoFrame);
        frame_5->setFrameShadow(QFrame::Raised);
        vboxLayout5 = new QVBoxLayout(frame_5);
        vboxLayout5->setSpacing(0);
        vboxLayout5->setMargin(4);
        vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
        label_al1 = new QLabel(frame_5);
        label_al1->setObjectName(QString::fromUtf8("label_al1"));
        sizePolicy2.setHeightForWidth(label_al1->sizePolicy().hasHeightForWidth());
        label_al1->setSizePolicy(sizePolicy2);
        label_al1->setAlignment(Qt::AlignCenter);

        vboxLayout5->addWidget(label_al1);

        albumRating = new StarEditor(frame_5);
        albumRating->setObjectName(QString::fromUtf8("albumRating"));

        vboxLayout5->addWidget(albumRating);


        vboxLayout2->addWidget(frame_5);

        spacerItem1 = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        vboxLayout2->addItem(spacerItem1);


        hboxLayout->addWidget(frame_0);

        spacerItem2 = new QSpacerItem(1, 1, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem2);


        vboxLayout1->addLayout(hboxLayout);

        col_toolbar2 = new QToolBar(tab);
        col_toolbar2->setObjectName(QString::fromUtf8("col_toolbar2"));

        vboxLayout1->addWidget(col_toolbar2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        vboxLayout6 = new QVBoxLayout(tab_2);
        vboxLayout6->setSpacing(4);
        vboxLayout6->setMargin(4);
        vboxLayout6->setObjectName(QString::fromUtf8("vboxLayout6"));
        textEdit = new QTextBrowser(tab_2);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setAutoFormatting(QTextEdit::AutoAll);
        textEdit->setReadOnly(true);
        textEdit->setOpenExternalLinks(true);

        vboxLayout6->addWidget(textEdit);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        vboxLayout7 = new QVBoxLayout(tab_3);
        vboxLayout7->setSpacing(4);
        vboxLayout7->setMargin(4);
        vboxLayout7->setObjectName(QString::fromUtf8("vboxLayout7"));
        textEdit_2 = new QTextBrowser(tab_3);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setAutoFormatting(QTextEdit::AutoAll);
        textEdit_2->setReadOnly(true);
        textEdit_2->setOpenExternalLinks(true);

        vboxLayout7->addWidget(textEdit_2);

        tabWidget->addTab(tab_3, QString());

        vboxLayout->addWidget(tabWidget);


        col_toolbar->addSeparator();
        col_toolbar->addAction(actionBan);
        col_toolbar->addAction(actionRateDown);
        col_toolbar->addAction(actionRateUp);
        col_toolbar->addAction(actionLoveIt);
        col_toolbar2->addSeparator();
        col_toolbar2->addAction(actionShowArtistInfo);
        col_toolbar2->addAction(actionShowAlbumInfo);
        col_toolbar2->addAction(actionShowLyrics);

        retranslateUi(Info);
        QObject::connect(tabWidget, SIGNAL(currentChanged(int)), Info, SLOT(tabChanged(int)));
        QObject::connect(actionBan, SIGNAL(triggered()), Info, SLOT(slot_ban()));
        QObject::connect(actionLoveIt, SIGNAL(triggered()), Info, SLOT(slot_loveIt()));
        QObject::connect(actionRateDown, SIGNAL(triggered()), Info, SLOT(slot_rateDown()));
        QObject::connect(actionRateUp, SIGNAL(triggered()), Info, SLOT(slot_rateUp()));
        QObject::connect(actionShowArtistInfo, SIGNAL(triggered()), Info, SLOT(showArtist()));
        QObject::connect(actionShowAlbumInfo, SIGNAL(triggered()), Info, SLOT(showAlbum()));
        QObject::connect(actionShowLyrics, SIGNAL(triggered()), Info, SLOT(showLyric()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Info);
    } // setupUi

    void retranslateUi(QWidget *Info)
    {
        Info->setWindowTitle(QApplication::translate("Info", "Info", 0, QApplication::UnicodeUTF8));
        actionRateUp->setText(QApplication::translate("Info", "Rate Up", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionRateUp->setToolTip(QApplication::translate("Info", "Rate Up", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionRateDown->setText(QApplication::translate("Info", "Rate Down", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionRateDown->setToolTip(QApplication::translate("Info", "Rate Down", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionLoveIt->setText(QApplication::translate("Info", "Love it", 0, QApplication::UnicodeUTF8));
        actionBan->setText(QApplication::translate("Info", "Ban", 0, QApplication::UnicodeUTF8));
        actionShowArtistInfo->setText(QApplication::translate("Info", "Show Artist Info", 0, QApplication::UnicodeUTF8));
        actionShowAlbumInfo->setText(QApplication::translate("Info", "Show Album Info", 0, QApplication::UnicodeUTF8));
        actionShowLyrics->setText(QApplication::translate("Info", "Show Lyrics", 0, QApplication::UnicodeUTF8));
        label_so1->setText(QApplication::translate("Info", "Song Title", 0, QApplication::UnicodeUTF8));
        label_al0->setText(QString());
        label_al1->setText(QApplication::translate("Info", "Album Title", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Info", "Now Playing", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Info", "Artist", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Info", "Album", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Info: public Ui_Info {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFO_H
