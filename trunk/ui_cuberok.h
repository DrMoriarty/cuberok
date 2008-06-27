/********************************************************************************
** Form generated from reading ui file 'cuberok.ui'
**
** Created: Fri 27. Jun 15:56:36 2008
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CUBEROK_H
#define UI_CUBEROK_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <progressbar.h>
#include "collectionview.h"
#include "playlistcontainer.h"

class Ui_CuberokClass
{
public:
    QAction *actionAbout;
    QAction *actionBreak;
    QAction *actionPrev;
    QAction *actionNext;
    QAction *actionPause;
    QAction *actionPlay;
    QAction *actionShuffle;
    QAction *actionRepeat;
    QAction *actionExit;
    QAction *actionClear_playlist;
    QAction *actionQueueNext;
    QAction *actionViewFile;
    QAction *actionViewTrack;
    QAction *actionViewTitle;
    QAction *actionViewArtist;
    QAction *actionViewAlbum;
    QAction *actionViewGenre;
    QAction *actionViewYear;
    QAction *actionViewComment;
    QAction *actionCorrectTag;
    QAction *actionViewLength;
    QAction *actionEditTag;
    QAction *actionNewPlaylist;
    QAction *actionClosePlaylist;
    QAction *actionRemoveSong;
    QAction *actionLookFeel;
    QAction *actionArtistMode;
    QAction *actionAlbumMode;
    QAction *actionGenreMode;
    QAction *actionSongMode;
    QAction *actionAddToCollection;
    QAction *actionRemoveFromCollection;
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    PlaylistContainer *listView;
    QFrame *frame;
    QHBoxLayout *hboxLayout;
    ProgressBar *progressBar;
    QSlider *volumeSlider;
    QDockWidget *dockWidget1;
    QWidget *dockWidgetContents1;
    QVBoxLayout *vboxLayout1;
    QToolBar *col_toolbar;
    QFrame *frame_2;
    QHBoxLayout *hboxLayout1;
    QLabel *subsetLabel;
    QToolButton *subsetDisableButton;
    QLineEdit *filterLineEdit;
    CollectionView *colView;
    QDockWidget *dockWidget2;
    QWidget *dockWidgetContents2;
    QVBoxLayout *vboxLayout2;
    QTreeView *treeView_2;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QMenu *menuControl;
    QMenu *menuView;
    QMenu *menuColumns;
    QStatusBar *statusbar;
    QLabel *listStatus;
    QLabel *collectionStatus;
    QToolBar *toolBar;

    void setupUi(QMainWindow *CuberokClass)
    {
    if (CuberokClass->objectName().isEmpty())
        CuberokClass->setObjectName(QString::fromUtf8("CuberokClass"));
    CuberokClass->resize(591, 274);
    CuberokClass->setWindowIcon(QIcon(QString::fromUtf8(":/icons/application.png")));
    CuberokClass->setDockNestingEnabled(true);
    CuberokClass->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks|QMainWindow::ForceTabbedDocks|QMainWindow::VerticalTabs);
    actionAbout = new QAction(CuberokClass);
    actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
    actionAbout->setIcon(QIcon());
    actionAbout->setShortcutContext(Qt::WindowShortcut);
    actionAbout->setMenuRole(QAction::AboutRole);
    actionBreak = new QAction(CuberokClass);
    actionBreak->setObjectName(QString::fromUtf8("actionBreak"));
    actionBreak->setCheckable(false);
    actionPrev = new QAction(CuberokClass);
    actionPrev->setObjectName(QString::fromUtf8("actionPrev"));
    actionNext = new QAction(CuberokClass);
    actionNext->setObjectName(QString::fromUtf8("actionNext"));
    actionPause = new QAction(CuberokClass);
    actionPause->setObjectName(QString::fromUtf8("actionPause"));
    actionPause->setCheckable(true);
    actionPlay = new QAction(CuberokClass);
    actionPlay->setObjectName(QString::fromUtf8("actionPlay"));
    actionShuffle = new QAction(CuberokClass);
    actionShuffle->setObjectName(QString::fromUtf8("actionShuffle"));
    actionShuffle->setCheckable(true);
    actionRepeat = new QAction(CuberokClass);
    actionRepeat->setObjectName(QString::fromUtf8("actionRepeat"));
    actionRepeat->setCheckable(true);
    actionExit = new QAction(CuberokClass);
    actionExit->setObjectName(QString::fromUtf8("actionExit"));
    actionClear_playlist = new QAction(CuberokClass);
    actionClear_playlist->setObjectName(QString::fromUtf8("actionClear_playlist"));
    actionQueueNext = new QAction(CuberokClass);
    actionQueueNext->setObjectName(QString::fromUtf8("actionQueueNext"));
    actionViewFile = new QAction(CuberokClass);
    actionViewFile->setObjectName(QString::fromUtf8("actionViewFile"));
    actionViewFile->setCheckable(true);
    actionViewFile->setChecked(false);
    actionViewTrack = new QAction(CuberokClass);
    actionViewTrack->setObjectName(QString::fromUtf8("actionViewTrack"));
    actionViewTrack->setCheckable(true);
    actionViewTrack->setChecked(false);
    actionViewTitle = new QAction(CuberokClass);
    actionViewTitle->setObjectName(QString::fromUtf8("actionViewTitle"));
    actionViewTitle->setCheckable(true);
    actionViewTitle->setChecked(false);
    actionViewArtist = new QAction(CuberokClass);
    actionViewArtist->setObjectName(QString::fromUtf8("actionViewArtist"));
    actionViewArtist->setCheckable(true);
    actionViewArtist->setChecked(false);
    actionViewAlbum = new QAction(CuberokClass);
    actionViewAlbum->setObjectName(QString::fromUtf8("actionViewAlbum"));
    actionViewAlbum->setCheckable(true);
    actionViewAlbum->setChecked(false);
    actionViewGenre = new QAction(CuberokClass);
    actionViewGenre->setObjectName(QString::fromUtf8("actionViewGenre"));
    actionViewGenre->setCheckable(true);
    actionViewGenre->setChecked(false);
    actionViewYear = new QAction(CuberokClass);
    actionViewYear->setObjectName(QString::fromUtf8("actionViewYear"));
    actionViewYear->setCheckable(true);
    actionViewYear->setChecked(false);
    actionViewComment = new QAction(CuberokClass);
    actionViewComment->setObjectName(QString::fromUtf8("actionViewComment"));
    actionViewComment->setCheckable(true);
    actionViewComment->setChecked(false);
    actionCorrectTag = new QAction(CuberokClass);
    actionCorrectTag->setObjectName(QString::fromUtf8("actionCorrectTag"));
    actionCorrectTag->setCheckable(true);
    actionCorrectTag->setChecked(false);
    actionViewLength = new QAction(CuberokClass);
    actionViewLength->setObjectName(QString::fromUtf8("actionViewLength"));
    actionViewLength->setCheckable(true);
    actionViewLength->setChecked(false);
    actionEditTag = new QAction(CuberokClass);
    actionEditTag->setObjectName(QString::fromUtf8("actionEditTag"));
    actionNewPlaylist = new QAction(CuberokClass);
    actionNewPlaylist->setObjectName(QString::fromUtf8("actionNewPlaylist"));
    actionClosePlaylist = new QAction(CuberokClass);
    actionClosePlaylist->setObjectName(QString::fromUtf8("actionClosePlaylist"));
    actionRemoveSong = new QAction(CuberokClass);
    actionRemoveSong->setObjectName(QString::fromUtf8("actionRemoveSong"));
    actionLookFeel = new QAction(CuberokClass);
    actionLookFeel->setObjectName(QString::fromUtf8("actionLookFeel"));
    actionArtistMode = new QAction(CuberokClass);
    actionArtistMode->setObjectName(QString::fromUtf8("actionArtistMode"));
    actionAlbumMode = new QAction(CuberokClass);
    actionAlbumMode->setObjectName(QString::fromUtf8("actionAlbumMode"));
    actionGenreMode = new QAction(CuberokClass);
    actionGenreMode->setObjectName(QString::fromUtf8("actionGenreMode"));
    actionSongMode = new QAction(CuberokClass);
    actionSongMode->setObjectName(QString::fromUtf8("actionSongMode"));
    actionAddToCollection = new QAction(CuberokClass);
    actionAddToCollection->setObjectName(QString::fromUtf8("actionAddToCollection"));
    actionRemoveFromCollection = new QAction(CuberokClass);
    actionRemoveFromCollection->setObjectName(QString::fromUtf8("actionRemoveFromCollection"));
    centralwidget = new QWidget(CuberokClass);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    vboxLayout = new QVBoxLayout(centralwidget);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    listView = new PlaylistContainer(centralwidget);
    listView->setObjectName(QString::fromUtf8("listView"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(listView->sizePolicy().hasHeightForWidth());
    listView->setSizePolicy(sizePolicy);
    listView->setContextMenuPolicy(Qt::ActionsContextMenu);
    listView->setAcceptDrops(true);
    listView->setProperty("dragEnabled", QVariant(true));
    listView->setProperty("sortingEnabled", QVariant(true));
    listView->setProperty("batchSize", QVariant(100));

    vboxLayout->addWidget(listView);

    frame = new QFrame(centralwidget);
    frame->setObjectName(QString::fromUtf8("frame"));
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
    frame->setSizePolicy(sizePolicy1);
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);
    hboxLayout = new QHBoxLayout(frame);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    progressBar = new ProgressBar(frame);
    progressBar->setObjectName(QString::fromUtf8("progressBar"));
    progressBar->setMaximum(1000);
    progressBar->setValue(0);
    progressBar->setAlignment(Qt::AlignCenter);

    hboxLayout->addWidget(progressBar);

    volumeSlider = new QSlider(frame);
    volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
    QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(volumeSlider->sizePolicy().hasHeightForWidth());
    volumeSlider->setSizePolicy(sizePolicy2);
    volumeSlider->setOrientation(Qt::Horizontal);

    hboxLayout->addWidget(volumeSlider);


    vboxLayout->addWidget(frame);

    CuberokClass->setCentralWidget(centralwidget);
    dockWidget1 = new QDockWidget(CuberokClass);
    dockWidget1->setObjectName(QString::fromUtf8("dockWidget1"));
    dockWidget1->setFeatures(QDockWidget::AllDockWidgetFeatures);
    dockWidgetContents1 = new QWidget(dockWidget1);
    dockWidgetContents1->setObjectName(QString::fromUtf8("dockWidgetContents1"));
    vboxLayout1 = new QVBoxLayout(dockWidgetContents1);
    vboxLayout1->setSpacing(2);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    vboxLayout1->setContentsMargins(4, 4, 4, 4);
    col_toolbar = new QToolBar(dockWidgetContents1);
    col_toolbar->setObjectName(QString::fromUtf8("col_toolbar"));

    vboxLayout1->addWidget(col_toolbar);

    frame_2 = new QFrame(dockWidgetContents1);
    frame_2->setObjectName(QString::fromUtf8("frame_2"));
    frame_2->setFrameShape(QFrame::NoFrame);
    frame_2->setLineWidth(0);
    hboxLayout1 = new QHBoxLayout(frame_2);
    hboxLayout1->setSpacing(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    hboxLayout1->setContentsMargins(4, 0, 4, 0);
    subsetLabel = new QLabel(frame_2);
    subsetLabel->setObjectName(QString::fromUtf8("subsetLabel"));

    hboxLayout1->addWidget(subsetLabel);

    subsetDisableButton = new QToolButton(frame_2);
    subsetDisableButton->setObjectName(QString::fromUtf8("subsetDisableButton"));
    subsetDisableButton->setAcceptDrops(false);
    subsetDisableButton->setAutoFillBackground(true);
    subsetDisableButton->setIcon(QIcon(QString::fromUtf8(":/icons/images/emblem-noread.png")));
    subsetDisableButton->setIconSize(QSize(24, 24));
    subsetDisableButton->setAutoRaise(true);
    subsetDisableButton->setArrowType(Qt::NoArrow);

    hboxLayout1->addWidget(subsetDisableButton);

    filterLineEdit = new QLineEdit(frame_2);
    filterLineEdit->setObjectName(QString::fromUtf8("filterLineEdit"));

    hboxLayout1->addWidget(filterLineEdit);


    vboxLayout1->addWidget(frame_2);

    colView = new CollectionView(dockWidgetContents1);
    colView->setObjectName(QString::fromUtf8("colView"));
    colView->setContextMenuPolicy(Qt::ActionsContextMenu);
    colView->setAcceptDrops(true);
    colView->setProperty("dragEnabled", QVariant(true));
    colView->setProperty("isWrapping", QVariant(true));

    vboxLayout1->addWidget(colView);

    dockWidget1->setWidget(dockWidgetContents1);
    CuberokClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget1);
    dockWidget2 = new QDockWidget(CuberokClass);
    dockWidget2->setObjectName(QString::fromUtf8("dockWidget2"));
    dockWidget2->setFeatures(QDockWidget::AllDockWidgetFeatures);
    dockWidgetContents2 = new QWidget(dockWidget2);
    dockWidgetContents2->setObjectName(QString::fromUtf8("dockWidgetContents2"));
    vboxLayout2 = new QVBoxLayout(dockWidgetContents2);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    vboxLayout2->setContentsMargins(0, 0, 0, 0);
    treeView_2 = new QTreeView(dockWidgetContents2);
    treeView_2->setObjectName(QString::fromUtf8("treeView_2"));
    treeView_2->setDragEnabled(true);
    treeView_2->setDragDropMode(QAbstractItemView::DragOnly);
    treeView_2->setSelectionMode(QAbstractItemView::ExtendedSelection);
    treeView_2->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    treeView_2->setAutoExpandDelay(5);
    treeView_2->setUniformRowHeights(true);
    treeView_2->setSortingEnabled(true);
    treeView_2->setAnimated(true);

    vboxLayout2->addWidget(treeView_2);

    dockWidget2->setWidget(dockWidgetContents2);
    CuberokClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget2);
    menubar = new QMenuBar(CuberokClass);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 591, 19));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    menuHelp = new QMenu(menubar);
    menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
    menuControl = new QMenu(menubar);
    menuControl->setObjectName(QString::fromUtf8("menuControl"));
    menuView = new QMenu(menubar);
    menuView->setObjectName(QString::fromUtf8("menuView"));
    menuColumns = new QMenu(menuView);
    menuColumns->setObjectName(QString::fromUtf8("menuColumns"));
    CuberokClass->setMenuBar(menubar);
    statusbar = new QStatusBar(CuberokClass);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    listStatus = new QLabel(statusbar);
    listStatus->setObjectName(QString::fromUtf8("listStatus"));
    listStatus->setGeometry(QRect(0, 0, 100, 30));
    collectionStatus = new QLabel(statusbar);
    collectionStatus->setObjectName(QString::fromUtf8("collectionStatus"));
    collectionStatus->setGeometry(QRect(0, 0, 100, 30));
    CuberokClass->setStatusBar(statusbar);
    toolBar = new QToolBar(CuberokClass);
    toolBar->setObjectName(QString::fromUtf8("toolBar"));
    CuberokClass->addToolBar(Qt::TopToolBarArea, toolBar);

    listView->addAction(actionQueueNext);
    listView->addAction(actionEditTag);
    listView->addAction(actionRemoveSong);
    listView->addAction(actionClear_playlist);
    col_toolbar->addAction(actionArtistMode);
    col_toolbar->addAction(actionAlbumMode);
    col_toolbar->addAction(actionGenreMode);
    col_toolbar->addAction(actionSongMode);
    colView->addAction(actionAddToCollection);
    colView->addAction(actionRemoveFromCollection);
    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuView->menuAction());
    menubar->addAction(menuControl->menuAction());
    menubar->addAction(menuHelp->menuAction());
    menuFile->addAction(actionNewPlaylist);
    menuFile->addAction(actionClosePlaylist);
    menuFile->addAction(actionCorrectTag);
    menuFile->addSeparator();
    menuFile->addAction(actionExit);
    menuHelp->addAction(actionAbout);
    menuControl->addAction(actionBreak);
    menuControl->addAction(actionPrev);
    menuControl->addAction(actionPause);
    menuControl->addAction(actionPlay);
    menuControl->addAction(actionNext);
    menuControl->addSeparator();
    menuControl->addAction(actionShuffle);
    menuControl->addAction(actionRepeat);
    menuControl->addSeparator();
    menuControl->addAction(actionClear_playlist);
    menuView->addAction(menuColumns->menuAction());
    menuView->addAction(actionLookFeel);
    menuColumns->addAction(actionViewFile);
    menuColumns->addAction(actionViewTrack);
    menuColumns->addAction(actionViewTitle);
    menuColumns->addAction(actionViewArtist);
    menuColumns->addAction(actionViewAlbum);
    menuColumns->addAction(actionViewGenre);
    menuColumns->addAction(actionViewYear);
    menuColumns->addAction(actionViewComment);
    menuColumns->addAction(actionViewLength);
    toolBar->addAction(actionBreak);
    toolBar->addSeparator();
    toolBar->addAction(actionPrev);
    toolBar->addAction(actionPause);
    toolBar->addAction(actionPlay);
    toolBar->addAction(actionNext);
    toolBar->addSeparator();
    toolBar->addAction(actionShuffle);
    toolBar->addAction(actionRepeat);
    toolBar->addSeparator();
    toolBar->addAction(actionClear_playlist);
    toolBar->addAction(actionEditTag);
    toolBar->addSeparator();

    retranslateUi(CuberokClass);
    QObject::connect(actionAbout, SIGNAL(triggered()), CuberokClass, SLOT(on_AboutMenu()));
    QObject::connect(actionBreak, SIGNAL(triggered()), listView, SLOT(fillCancel()));
    QObject::connect(actionPrev, SIGNAL(triggered()), listView, SLOT(prev()));
    QObject::connect(actionNext, SIGNAL(triggered()), listView, SLOT(next()));
    QObject::connect(actionPause, SIGNAL(triggered(bool)), listView, SLOT(pause(bool)));
    QObject::connect(actionPlay, SIGNAL(triggered()), listView, SLOT(play()));
    QObject::connect(actionShuffle, SIGNAL(triggered(bool)), listView, SLOT(shuffle(bool)));
    QObject::connect(actionRepeat, SIGNAL(triggered(bool)), listView, SLOT(repeat(bool)));
    QObject::connect(listView, SIGNAL(status(QString)), CuberokClass, SLOT(message(QString)));
    QObject::connect(actionExit, SIGNAL(triggered()), CuberokClass, SLOT(close()));
    QObject::connect(actionClear_playlist, SIGNAL(triggered()), listView, SLOT(clear()));
    QObject::connect(actionQueueNext, SIGNAL(triggered()), listView, SLOT(queueNext()));
    QObject::connect(actionViewAlbum, SIGNAL(triggered(bool)), listView, SLOT(viewAlbum(bool)));
    QObject::connect(actionViewArtist, SIGNAL(triggered(bool)), listView, SLOT(viewArtist(bool)));
    QObject::connect(actionViewComment, SIGNAL(triggered(bool)), listView, SLOT(viewComment(bool)));
    QObject::connect(actionViewFile, SIGNAL(triggered(bool)), listView, SLOT(viewFile(bool)));
    QObject::connect(actionViewGenre, SIGNAL(triggered(bool)), listView, SLOT(viewGenre(bool)));
    QObject::connect(actionViewTitle, SIGNAL(triggered(bool)), listView, SLOT(viewTitle(bool)));
    QObject::connect(actionViewTrack, SIGNAL(triggered(bool)), listView, SLOT(viewTrack(bool)));
    QObject::connect(actionViewYear, SIGNAL(triggered(bool)), listView, SLOT(viewYear(bool)));
    QObject::connect(actionCorrectTag, SIGNAL(triggered(bool)), CuberokClass, SLOT(correctTag(bool)));
    QObject::connect(actionViewLength, SIGNAL(triggered(bool)), listView, SLOT(viewLength(bool)));
    QObject::connect(actionEditTag, SIGNAL(triggered()), listView, SLOT(editTag()));
    QObject::connect(actionNewPlaylist, SIGNAL(triggered()), listView, SLOT(addList()));
    QObject::connect(actionClosePlaylist, SIGNAL(triggered()), listView, SLOT(delList()));
    QObject::connect(actionRemoveSong, SIGNAL(triggered()), listView, SLOT(removeSong()));
    QObject::connect(actionLookFeel, SIGNAL(triggered()), CuberokClass, SLOT(lookAndFeel()));
    QObject::connect(listView, SIGNAL(songPosition(int)), progressBar, SLOT(setValue(int)));
    QObject::connect(actionArtistMode, SIGNAL(triggered()), colView, SLOT(artistMode()));
    QObject::connect(actionAlbumMode, SIGNAL(triggered()), colView, SLOT(albumMode()));
    QObject::connect(actionGenreMode, SIGNAL(triggered()), colView, SLOT(genreMode()));
    QObject::connect(actionSongMode, SIGNAL(triggered()), colView, SLOT(songMode()));
    QObject::connect(actionAddToCollection, SIGNAL(triggered()), colView, SLOT(addItem()));
    QObject::connect(actionRemoveFromCollection, SIGNAL(triggered()), colView, SLOT(removeItem()));
    QObject::connect(colView, SIGNAL(status(QString)), collectionStatus, SLOT(setText(QString)));
    QObject::connect(listView, SIGNAL(), listStatus, SLOT(setText(QString)));
    QObject::connect(filterLineEdit, SIGNAL(textChanged(QString)), colView, SLOT(filter(QString)));
    QObject::connect(colView, SIGNAL(setVisibleSubsetWidgets(bool)), subsetLabel, SLOT(setVisible(bool)));
    QObject::connect(colView, SIGNAL(setVisibleSubsetWidgets(bool)), subsetDisableButton, SLOT(setVisible(bool)));
    QObject::connect(subsetDisableButton, SIGNAL(clicked()), colView, SLOT(clearSubset()));
    QObject::connect(colView, SIGNAL(setSubsetLabel(QString)), subsetLabel, SLOT(setText(QString)));

    QMetaObject::connectSlotsByName(CuberokClass);
    } // setupUi

    void retranslateUi(QMainWindow *CuberokClass)
    {
    CuberokClass->setWindowTitle(QApplication::translate("CuberokClass", "Cuberok", 0, QApplication::UnicodeUTF8));
    actionAbout->setText(QApplication::translate("CuberokClass", "About", 0, QApplication::UnicodeUTF8));
    actionAbout->setStatusTip(QApplication::translate("CuberokClass", "About dialog", 0, QApplication::UnicodeUTF8));
    actionAbout->setShortcut(QApplication::translate("CuberokClass", "Alt+F1", 0, QApplication::UnicodeUTF8));
    actionBreak->setText(QApplication::translate("CuberokClass", "Break", 0, QApplication::UnicodeUTF8));
    actionPrev->setText(QApplication::translate("CuberokClass", "Previous", 0, QApplication::UnicodeUTF8));
    actionPrev->setIconText(QApplication::translate("CuberokClass", "<<", 0, QApplication::UnicodeUTF8));
    actionPrev->setToolTip(QApplication::translate("CuberokClass", "Previous track", 0, QApplication::UnicodeUTF8));
    actionPrev->setStatusTip(QApplication::translate("CuberokClass", "Previous track", 0, QApplication::UnicodeUTF8));
    actionNext->setText(QApplication::translate("CuberokClass", "Next", 0, QApplication::UnicodeUTF8));
    actionNext->setIconText(QApplication::translate("CuberokClass", ">>", 0, QApplication::UnicodeUTF8));
    actionNext->setToolTip(QApplication::translate("CuberokClass", "Next track", 0, QApplication::UnicodeUTF8));
    actionNext->setStatusTip(QApplication::translate("CuberokClass", "Next track", 0, QApplication::UnicodeUTF8));
    actionPause->setText(QApplication::translate("CuberokClass", "Pause", 0, QApplication::UnicodeUTF8));
    actionPause->setIconText(QApplication::translate("CuberokClass", "||", 0, QApplication::UnicodeUTF8));
    actionPause->setToolTip(QApplication::translate("CuberokClass", "Pause", 0, QApplication::UnicodeUTF8));
    actionPause->setStatusTip(QApplication::translate("CuberokClass", "Pause", 0, QApplication::UnicodeUTF8));
    actionPlay->setText(QApplication::translate("CuberokClass", "Play", 0, QApplication::UnicodeUTF8));
    actionPlay->setIconText(QApplication::translate("CuberokClass", ">", 0, QApplication::UnicodeUTF8));
    actionPlay->setToolTip(QApplication::translate("CuberokClass", "Play track", 0, QApplication::UnicodeUTF8));
    actionPlay->setStatusTip(QApplication::translate("CuberokClass", "Play track", 0, QApplication::UnicodeUTF8));
    actionShuffle->setText(QApplication::translate("CuberokClass", "Shuffle", 0, QApplication::UnicodeUTF8));
    actionShuffle->setStatusTip(QApplication::translate("CuberokClass", "Shuffle mode", 0, QApplication::UnicodeUTF8));
    actionRepeat->setText(QApplication::translate("CuberokClass", "Repeat", 0, QApplication::UnicodeUTF8));
    actionRepeat->setStatusTip(QApplication::translate("CuberokClass", "Repeat mode", 0, QApplication::UnicodeUTF8));
    actionExit->setText(QApplication::translate("CuberokClass", "Exit", 0, QApplication::UnicodeUTF8));
    actionExit->setStatusTip(QApplication::translate("CuberokClass", "Close the program", 0, QApplication::UnicodeUTF8));
    actionClear_playlist->setText(QApplication::translate("CuberokClass", "Clear playlist", 0, QApplication::UnicodeUTF8));
    actionClear_playlist->setIconText(QApplication::translate("CuberokClass", "Clear", 0, QApplication::UnicodeUTF8));
    actionClear_playlist->setStatusTip(QApplication::translate("CuberokClass", "Clear playlist", 0, QApplication::UnicodeUTF8));
    actionQueueNext->setText(QApplication::translate("CuberokClass", "Queue as Next", 0, QApplication::UnicodeUTF8));
    actionViewFile->setText(QApplication::translate("CuberokClass", "File", 0, QApplication::UnicodeUTF8));
    actionViewTrack->setText(QApplication::translate("CuberokClass", "Track", 0, QApplication::UnicodeUTF8));
    actionViewTitle->setText(QApplication::translate("CuberokClass", "Title", 0, QApplication::UnicodeUTF8));
    actionViewArtist->setText(QApplication::translate("CuberokClass", "Artist", 0, QApplication::UnicodeUTF8));
    actionViewAlbum->setText(QApplication::translate("CuberokClass", "Album", 0, QApplication::UnicodeUTF8));
    actionViewGenre->setText(QApplication::translate("CuberokClass", "Genre", 0, QApplication::UnicodeUTF8));
    actionViewYear->setText(QApplication::translate("CuberokClass", "Year", 0, QApplication::UnicodeUTF8));
    actionViewComment->setText(QApplication::translate("CuberokClass", "Comment", 0, QApplication::UnicodeUTF8));
    actionCorrectTag->setText(QApplication::translate("CuberokClass", "Correct cp1251 in ID3v1", 0, QApplication::UnicodeUTF8));
    actionViewLength->setText(QApplication::translate("CuberokClass", "Length", 0, QApplication::UnicodeUTF8));
    actionEditTag->setText(QApplication::translate("CuberokClass", "Edit Tag", 0, QApplication::UnicodeUTF8));
    actionEditTag->setIconText(QApplication::translate("CuberokClass", "Tag", 0, QApplication::UnicodeUTF8));
    actionEditTag->setToolTip(QApplication::translate("CuberokClass", "Edit Tag", 0, QApplication::UnicodeUTF8));
    actionNewPlaylist->setText(QApplication::translate("CuberokClass", "New playlist", 0, QApplication::UnicodeUTF8));
    actionClosePlaylist->setText(QApplication::translate("CuberokClass", "Close playlist", 0, QApplication::UnicodeUTF8));
    actionRemoveSong->setText(QApplication::translate("CuberokClass", "Remove song", 0, QApplication::UnicodeUTF8));
    actionLookFeel->setText(QApplication::translate("CuberokClass", "Look and Feel", 0, QApplication::UnicodeUTF8));
    actionArtistMode->setText(QApplication::translate("CuberokClass", "Artist", 0, QApplication::UnicodeUTF8));
    actionAlbumMode->setText(QApplication::translate("CuberokClass", "Album", 0, QApplication::UnicodeUTF8));
    actionGenreMode->setText(QApplication::translate("CuberokClass", "Genre", 0, QApplication::UnicodeUTF8));
    actionSongMode->setText(QApplication::translate("CuberokClass", "Song", 0, QApplication::UnicodeUTF8));
    actionAddToCollection->setText(QApplication::translate("CuberokClass", "Add Item", 0, QApplication::UnicodeUTF8));
    actionRemoveFromCollection->setText(QApplication::translate("CuberokClass", "Remove Item", 0, QApplication::UnicodeUTF8));
    dockWidget1->setWindowTitle(QApplication::translate("CuberokClass", "Collection", 0, QApplication::UnicodeUTF8));
    subsetLabel->setText(QApplication::translate("CuberokClass", "TextLabel", 0, QApplication::UnicodeUTF8));
    subsetDisableButton->setText(QApplication::translate("CuberokClass", "...", 0, QApplication::UnicodeUTF8));
    filterLineEdit->setToolTip(QApplication::translate("CuberokClass", "Enter search substring", 0, QApplication::UnicodeUTF8));
    dockWidget2->setWindowTitle(QApplication::translate("CuberokClass", "Files", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("CuberokClass", "File", 0, QApplication::UnicodeUTF8));
    menuHelp->setTitle(QApplication::translate("CuberokClass", "Help", 0, QApplication::UnicodeUTF8));
    menuControl->setTitle(QApplication::translate("CuberokClass", "Control", 0, QApplication::UnicodeUTF8));
    menuView->setTitle(QApplication::translate("CuberokClass", "View", 0, QApplication::UnicodeUTF8));
    menuColumns->setTitle(QApplication::translate("CuberokClass", "Columns", 0, QApplication::UnicodeUTF8));
    listStatus->setText(QApplication::translate("CuberokClass", "List", 0, QApplication::UnicodeUTF8));
    collectionStatus->setText(QApplication::translate("CuberokClass", "Collection", 0, QApplication::UnicodeUTF8));
    toolBar->setWindowTitle(QApplication::translate("CuberokClass", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CuberokClass: public Ui_CuberokClass {};
} // namespace Ui

#endif // UI_CUBEROK_H
