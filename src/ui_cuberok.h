/********************************************************************************
** Form generated from reading ui file 'cuberok.ui'
**
** Created: Wed 25. Mar 17:46:45 2009
**      by: Qt User Interface Compiler version 4.5.0-rc1
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
#include <QtGui/QHeaderView>
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
#include "collectionview.h"
#include "info.h"
#include "libraryview.h"
#include "playlistcontainer.h"
#include "progressbar.h"

QT_BEGIN_NAMESPACE

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
    QAction *actionAddToLibrary;
    QAction *actionRemoveFromCollection;
    QAction *actionRemoveFromLibrary;
    QAction *actionStop;
    QAction *actionSavePlaylist;
    QAction *actionLoadPlaylist;
    QAction *actionAboutQt;
    QAction *actionReloadTags;
    QAction *actionViewRating;
    QAction *actionSettings;
    QAction *actionSetImage;
    QAction *actionLibrarySetImage;
    QAction *actionIconView;
    QAction *actionOpenUrl;
    QAction *actionGetImageFromLastFM;
    QAction *actionConsole;
    QAction *actionLibrarySQLPlaylist;
    QAction *actionLibraryRegularPlaylist;
    QAction *actionSQLListEdit;
    QAction *actionQTagConvert;
    QAction *actionRefreshTree;
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    PlaylistContainer *listView;
    QFrame *frame;
    QHBoxLayout *hboxLayout;
    ProgressBar *progressBar;
    QLabel *label;
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
    QDockWidget *dockWidget3;
    QWidget *dockWidgetContents3;
    QVBoxLayout *vboxLayout3;
    QToolBar *lib_toolbar;
    LibraryView *libView;
    QDockWidget *dockWidget4;
    QWidget *dockWidgetContents4;
    QVBoxLayout *vboxLayout4;
    Info *infoWidget;
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
        CuberokClass->resize(651, 525);
        const QIcon icon = QIcon(QString::fromUtf8(":/icons/application.png"));
        CuberokClass->setWindowIcon(icon);
        CuberokClass->setDockNestingEnabled(true);
        CuberokClass->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks|QMainWindow::VerticalTabs);
        actionAbout = new QAction(CuberokClass);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAbout->setIcon(icon);
        actionAbout->setShortcutContext(Qt::WindowShortcut);
        actionAbout->setMenuRole(QAction::AboutRole);
        actionBreak = new QAction(CuberokClass);
        actionBreak->setObjectName(QString::fromUtf8("actionBreak"));
        actionBreak->setCheckable(false);
        const QIcon icon1 = QIcon(QString::fromUtf8(":/icons/star.png"));
        actionBreak->setIcon(icon1);
        actionPrev = new QAction(CuberokClass);
        actionPrev->setObjectName(QString::fromUtf8("actionPrev"));
        const QIcon icon2 = QIcon(QString::fromUtf8(":/icons/butt_backward.png"));
        actionPrev->setIcon(icon2);
        actionPrev->setShortcutContext(Qt::ApplicationShortcut);
        actionNext = new QAction(CuberokClass);
        actionNext->setObjectName(QString::fromUtf8("actionNext"));
        const QIcon icon3 = QIcon(QString::fromUtf8(":/icons/butt_forward.png"));
        actionNext->setIcon(icon3);
        actionNext->setShortcutContext(Qt::ApplicationShortcut);
        actionPause = new QAction(CuberokClass);
        actionPause->setObjectName(QString::fromUtf8("actionPause"));
        actionPause->setCheckable(true);
        const QIcon icon4 = QIcon(QString::fromUtf8(":/icons/butt_pause.png"));
        actionPause->setIcon(icon4);
        actionPause->setShortcutContext(Qt::ApplicationShortcut);
        actionPlay = new QAction(CuberokClass);
        actionPlay->setObjectName(QString::fromUtf8("actionPlay"));
        const QIcon icon5 = QIcon(QString::fromUtf8(":/icons/butt_play.png"));
        actionPlay->setIcon(icon5);
        actionPlay->setShortcutContext(Qt::ApplicationShortcut);
        actionShuffle = new QAction(CuberokClass);
        actionShuffle->setObjectName(QString::fromUtf8("actionShuffle"));
        actionShuffle->setCheckable(true);
        const QIcon icon6 = QIcon(QString::fromUtf8(":/icons/shuffle_mode.png"));
        actionShuffle->setIcon(icon6);
        actionRepeat = new QAction(CuberokClass);
        actionRepeat->setObjectName(QString::fromUtf8("actionRepeat"));
        actionRepeat->setCheckable(true);
        const QIcon icon7 = QIcon(QString::fromUtf8(":/icons/repeat_mode.png"));
        actionRepeat->setIcon(icon7);
        actionExit = new QAction(CuberokClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        const QIcon icon8 = QIcon(QString::fromUtf8(":/icons/quit.png"));
        actionExit->setIcon(icon8);
        actionClear_playlist = new QAction(CuberokClass);
        actionClear_playlist->setObjectName(QString::fromUtf8("actionClear_playlist"));
        const QIcon icon9 = QIcon(QString::fromUtf8(":/icons/clearlist.png"));
        actionClear_playlist->setIcon(icon9);
        actionQueueNext = new QAction(CuberokClass);
        actionQueueNext->setObjectName(QString::fromUtf8("actionQueueNext"));
        const QIcon icon10 = QIcon(QString::fromUtf8(":/icons/next.png"));
        actionQueueNext->setIcon(icon10);
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
        actionViewLength = new QAction(CuberokClass);
        actionViewLength->setObjectName(QString::fromUtf8("actionViewLength"));
        actionViewLength->setCheckable(true);
        actionViewLength->setChecked(false);
        actionEditTag = new QAction(CuberokClass);
        actionEditTag->setObjectName(QString::fromUtf8("actionEditTag"));
        const QIcon icon11 = QIcon(QString::fromUtf8(":/icons/edittag.png"));
        actionEditTag->setIcon(icon11);
        actionNewPlaylist = new QAction(CuberokClass);
        actionNewPlaylist->setObjectName(QString::fromUtf8("actionNewPlaylist"));
        const QIcon icon12 = QIcon(QString::fromUtf8(":/icons/newtab.png"));
        actionNewPlaylist->setIcon(icon12);
        actionClosePlaylist = new QAction(CuberokClass);
        actionClosePlaylist->setObjectName(QString::fromUtf8("actionClosePlaylist"));
        const QIcon icon13 = QIcon(QString::fromUtf8(":/icons/deltab.png"));
        actionClosePlaylist->setIcon(icon13);
        actionRemoveSong = new QAction(CuberokClass);
        actionRemoveSong->setObjectName(QString::fromUtf8("actionRemoveSong"));
        const QIcon icon14 = QIcon(QString::fromUtf8(":/icons/col_rem.png"));
        actionRemoveSong->setIcon(icon14);
        actionLookFeel = new QAction(CuberokClass);
        actionLookFeel->setObjectName(QString::fromUtf8("actionLookFeel"));
        const QIcon icon15 = QIcon(QString::fromUtf8(":/icons/looknfeel.png"));
        actionLookFeel->setIcon(icon15);
        actionArtistMode = new QAction(CuberokClass);
        actionArtistMode->setObjectName(QString::fromUtf8("actionArtistMode"));
        actionArtistMode->setCheckable(true);
        const QIcon icon16 = QIcon(QString::fromUtf8(":/icons/def_artist.png"));
        actionArtistMode->setIcon(icon16);
        actionAlbumMode = new QAction(CuberokClass);
        actionAlbumMode->setObjectName(QString::fromUtf8("actionAlbumMode"));
        actionAlbumMode->setCheckable(true);
        const QIcon icon17 = QIcon(QString::fromUtf8(":/icons/def_album.png"));
        actionAlbumMode->setIcon(icon17);
        actionGenreMode = new QAction(CuberokClass);
        actionGenreMode->setObjectName(QString::fromUtf8("actionGenreMode"));
        actionGenreMode->setCheckable(true);
        const QIcon icon18 = QIcon(QString::fromUtf8(":/icons/def_genre.png"));
        actionGenreMode->setIcon(icon18);
        actionSongMode = new QAction(CuberokClass);
        actionSongMode->setObjectName(QString::fromUtf8("actionSongMode"));
        actionSongMode->setCheckable(true);
        const QIcon icon19 = QIcon(QString::fromUtf8(":/icons/def_song.png"));
        actionSongMode->setIcon(icon19);
        actionAddToCollection = new QAction(CuberokClass);
        actionAddToCollection->setObjectName(QString::fromUtf8("actionAddToCollection"));
        const QIcon icon20 = QIcon(QString::fromUtf8(":/icons/col_add.png"));
        actionAddToCollection->setIcon(icon20);
        actionAddToLibrary = new QAction(CuberokClass);
        actionAddToLibrary->setObjectName(QString::fromUtf8("actionAddToLibrary"));
        actionAddToLibrary->setIcon(icon20);
        actionRemoveFromCollection = new QAction(CuberokClass);
        actionRemoveFromCollection->setObjectName(QString::fromUtf8("actionRemoveFromCollection"));
        actionRemoveFromCollection->setIcon(icon14);
        actionRemoveFromLibrary = new QAction(CuberokClass);
        actionRemoveFromLibrary->setObjectName(QString::fromUtf8("actionRemoveFromLibrary"));
        actionRemoveFromLibrary->setIcon(icon14);
        actionStop = new QAction(CuberokClass);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        const QIcon icon21 = QIcon(QString::fromUtf8(":/icons/butt_stop.png"));
        actionStop->setIcon(icon21);
        actionStop->setShortcutContext(Qt::ApplicationShortcut);
        actionSavePlaylist = new QAction(CuberokClass);
        actionSavePlaylist->setObjectName(QString::fromUtf8("actionSavePlaylist"));
        const QIcon icon22 = QIcon(QString::fromUtf8(":/icons/save.png"));
        actionSavePlaylist->setIcon(icon22);
        actionLoadPlaylist = new QAction(CuberokClass);
        actionLoadPlaylist->setObjectName(QString::fromUtf8("actionLoadPlaylist"));
        const QIcon icon23 = QIcon(QString::fromUtf8(":/icons/open.png"));
        actionLoadPlaylist->setIcon(icon23);
        actionAboutQt = new QAction(CuberokClass);
        actionAboutQt->setObjectName(QString::fromUtf8("actionAboutQt"));
        const QIcon icon24 = QIcon(QString::fromUtf8(":/icons/qt.png"));
        actionAboutQt->setIcon(icon24);
        actionReloadTags = new QAction(CuberokClass);
        actionReloadTags->setObjectName(QString::fromUtf8("actionReloadTags"));
        const QIcon icon25 = QIcon(QString::fromUtf8(":/icons/reload.png"));
        actionReloadTags->setIcon(icon25);
        actionViewRating = new QAction(CuberokClass);
        actionViewRating->setObjectName(QString::fromUtf8("actionViewRating"));
        actionViewRating->setCheckable(true);
        actionViewRating->setChecked(false);
        actionSettings = new QAction(CuberokClass);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        const QIcon icon26 = QIcon(QString::fromUtf8(":/icons/settings.png"));
        actionSettings->setIcon(icon26);
        actionSetImage = new QAction(CuberokClass);
        actionSetImage->setObjectName(QString::fromUtf8("actionSetImage"));
        const QIcon icon27 = QIcon(QString::fromUtf8(":/icons/col_art.png"));
        actionSetImage->setIcon(icon27);
        actionLibrarySetImage = new QAction(CuberokClass);
        actionLibrarySetImage->setObjectName(QString::fromUtf8("actionLibrarySetImage"));
        actionLibrarySetImage->setIcon(icon27);
        actionIconView = new QAction(CuberokClass);
        actionIconView->setObjectName(QString::fromUtf8("actionIconView"));
        actionIconView->setCheckable(true);
        const QIcon icon28 = QIcon(QString::fromUtf8(":/icons/iconview.png"));
        actionIconView->setIcon(icon28);
        actionOpenUrl = new QAction(CuberokClass);
        actionOpenUrl->setObjectName(QString::fromUtf8("actionOpenUrl"));
        actionOpenUrl->setIcon(icon23);
        actionGetImageFromLastFM = new QAction(CuberokClass);
        actionGetImageFromLastFM->setObjectName(QString::fromUtf8("actionGetImageFromLastFM"));
        actionGetImageFromLastFM->setEnabled(false);
        const QIcon icon29 = QIcon(QString::fromUtf8(":/icons/download_art.png"));
        actionGetImageFromLastFM->setIcon(icon29);
        actionConsole = new QAction(CuberokClass);
        actionConsole->setObjectName(QString::fromUtf8("actionConsole"));
        const QIcon icon30 = QIcon(QString::fromUtf8(":/icons/console.png"));
        actionConsole->setIcon(icon30);
        actionLibrarySQLPlaylist = new QAction(CuberokClass);
        actionLibrarySQLPlaylist->setObjectName(QString::fromUtf8("actionLibrarySQLPlaylist"));
        actionLibrarySQLPlaylist->setCheckable(true);
        const QIcon icon31 = QIcon(QString::fromUtf8(":/icons/sql.png"));
        actionLibrarySQLPlaylist->setIcon(icon31);
        actionLibraryRegularPlaylist = new QAction(CuberokClass);
        actionLibraryRegularPlaylist->setObjectName(QString::fromUtf8("actionLibraryRegularPlaylist"));
        actionLibraryRegularPlaylist->setCheckable(true);
        const QIcon icon32 = QIcon(QString::fromUtf8(":/icons/def_list.png"));
        actionLibraryRegularPlaylist->setIcon(icon32);
        actionSQLListEdit = new QAction(CuberokClass);
        actionSQLListEdit->setObjectName(QString::fromUtf8("actionSQLListEdit"));
        actionSQLListEdit->setIcon(icon11);
        actionQTagConvert = new QAction(CuberokClass);
        actionQTagConvert->setObjectName(QString::fromUtf8("actionQTagConvert"));
        const QIcon icon33 = QIcon(QString::fromUtf8(":/icons/qtagconvert.png"));
        actionQTagConvert->setIcon(icon33);
        actionRefreshTree = new QAction(CuberokClass);
        actionRefreshTree->setObjectName(QString::fromUtf8("actionRefreshTree"));
        actionRefreshTree->setIcon(icon25);
        centralwidget = new QWidget(CuberokClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setSpacing(4);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(4, 4, 4, 4);
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
        hboxLayout->setSpacing(2);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(4, 4, 4, 4);
        progressBar = new ProgressBar(frame);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMaximum(1000);
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);

        hboxLayout->addWidget(progressBar);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setMaximumSize(QSize(24, 24));
        label->setPixmap(QPixmap(QString::fromUtf8(":/icons/volume.png")));
        label->setScaledContents(true);

        hboxLayout->addWidget(label);

        volumeSlider = new QSlider(frame);
        volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(volumeSlider->sizePolicy().hasHeightForWidth());
        volumeSlider->setSizePolicy(sizePolicy3);
        volumeSlider->setMaximum(200);
        volumeSlider->setOrientation(Qt::Horizontal);

        hboxLayout->addWidget(volumeSlider);


        vboxLayout->addWidget(frame);

        CuberokClass->setCentralWidget(centralwidget);
        dockWidget1 = new QDockWidget(CuberokClass);
        dockWidget1->setObjectName(QString::fromUtf8("dockWidget1"));
        dockWidget1->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockWidgetContents1 = new QWidget();
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
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        subsetLabel = new QLabel(frame_2);
        subsetLabel->setObjectName(QString::fromUtf8("subsetLabel"));

        hboxLayout1->addWidget(subsetLabel);

        subsetDisableButton = new QToolButton(frame_2);
        subsetDisableButton->setObjectName(QString::fromUtf8("subsetDisableButton"));
        subsetDisableButton->setAcceptDrops(false);
        subsetDisableButton->setAutoFillBackground(true);
        const QIcon icon34 = QIcon(QString::fromUtf8(":/icons/clear_filter.png"));
        subsetDisableButton->setIcon(icon34);
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
        colView->setDragEnabled(true);
        colView->setFlow(QListView::TopToBottom);
        colView->setProperty("isWrapping", QVariant(true));

        vboxLayout1->addWidget(colView);

        dockWidget1->setWidget(dockWidgetContents1);
        CuberokClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget1);
        dockWidget2 = new QDockWidget(CuberokClass);
        dockWidget2->setObjectName(QString::fromUtf8("dockWidget2"));
        dockWidget2->setFloating(false);
        dockWidget2->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockWidgetContents2 = new QWidget();
        dockWidgetContents2->setObjectName(QString::fromUtf8("dockWidgetContents2"));
        vboxLayout2 = new QVBoxLayout(dockWidgetContents2);
        vboxLayout2->setSpacing(2);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        vboxLayout2->setContentsMargins(4, 4, 4, 4);
        treeView_2 = new QTreeView(dockWidgetContents2);
        treeView_2->setObjectName(QString::fromUtf8("treeView_2"));
        treeView_2->setContextMenuPolicy(Qt::ActionsContextMenu);
        treeView_2->setDragEnabled(true);
        treeView_2->setDragDropMode(QAbstractItemView::DragOnly);
        treeView_2->setSelectionMode(QAbstractItemView::ExtendedSelection);
        treeView_2->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
        treeView_2->setAutoExpandDelay(5);
        treeView_2->setUniformRowHeights(true);
        treeView_2->setSortingEnabled(true);
        treeView_2->setAnimated(true);
        treeView_2->setProperty("headerHidden", QVariant(true));

        vboxLayout2->addWidget(treeView_2);

        dockWidget2->setWidget(dockWidgetContents2);
        CuberokClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget2);
        dockWidget3 = new QDockWidget(CuberokClass);
        dockWidget3->setObjectName(QString::fromUtf8("dockWidget3"));
        dockWidget3->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockWidgetContents3 = new QWidget();
        dockWidgetContents3->setObjectName(QString::fromUtf8("dockWidgetContents3"));
        vboxLayout3 = new QVBoxLayout(dockWidgetContents3);
        vboxLayout3->setSpacing(2);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        vboxLayout3->setContentsMargins(4, 4, 4, 4);
        lib_toolbar = new QToolBar(dockWidgetContents3);
        lib_toolbar->setObjectName(QString::fromUtf8("lib_toolbar"));

        vboxLayout3->addWidget(lib_toolbar);

        libView = new LibraryView(dockWidgetContents3);
        libView->setObjectName(QString::fromUtf8("libView"));
        libView->setContextMenuPolicy(Qt::ActionsContextMenu);
        libView->setAcceptDrops(true);
        libView->setDragEnabled(true);
        libView->setFlow(QListView::TopToBottom);
        libView->setProperty("isWrapping", QVariant(true));

        vboxLayout3->addWidget(libView);

        dockWidget3->setWidget(dockWidgetContents3);
        CuberokClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget3);
        dockWidget4 = new QDockWidget(CuberokClass);
        dockWidget4->setObjectName(QString::fromUtf8("dockWidget4"));
        dockWidgetContents4 = new QWidget();
        dockWidgetContents4->setObjectName(QString::fromUtf8("dockWidgetContents4"));
        vboxLayout4 = new QVBoxLayout(dockWidgetContents4);
        vboxLayout4->setSpacing(4);
        vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
        vboxLayout4->setContentsMargins(4, 4, 4, 4);
        infoWidget = new Info(dockWidgetContents4);
        infoWidget->setObjectName(QString::fromUtf8("infoWidget"));

        vboxLayout4->addWidget(infoWidget);

        dockWidget4->setWidget(dockWidgetContents4);
        CuberokClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget4);
        menubar = new QMenuBar(CuberokClass);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 651, 21));
        menubar->setDefaultUp(false);
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFile->setTearOffEnabled(true);
        menuFile->setSeparatorsCollapsible(true);
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuHelp->setTearOffEnabled(true);
        menuHelp->setSeparatorsCollapsible(true);
        menuControl = new QMenu(menubar);
        menuControl->setObjectName(QString::fromUtf8("menuControl"));
        menuControl->setTearOffEnabled(true);
        menuControl->setSeparatorsCollapsible(true);
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuView->setTearOffEnabled(true);
        menuView->setSeparatorsCollapsible(true);
        menuColumns = new QMenu(menuView);
        menuColumns->setObjectName(QString::fromUtf8("menuColumns"));
        menuColumns->setTearOffEnabled(true);
        menuColumns->setSeparatorsCollapsible(true);
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
        listView->addAction(actionReloadTags);
        listView->addAction(actionRemoveSong);
        listView->addAction(actionClear_playlist);
        col_toolbar->addAction(actionGenreMode);
        col_toolbar->addAction(actionArtistMode);
        col_toolbar->addAction(actionAlbumMode);
        col_toolbar->addAction(actionSongMode);
        col_toolbar->addAction(actionIconView);
        col_toolbar->addSeparator();
        col_toolbar->addAction(actionSetImage);
        col_toolbar->addAction(actionGetImageFromLastFM);
        colView->addAction(actionAddToCollection);
        colView->addAction(actionRemoveFromCollection);
        colView->addAction(actionSetImage);
        colView->addAction(actionGetImageFromLastFM);
        treeView_2->addAction(actionRefreshTree);
        lib_toolbar->addAction(actionLibraryRegularPlaylist);
        lib_toolbar->addAction(actionLibrarySQLPlaylist);
        libView->addAction(actionAddToLibrary);
        libView->addAction(actionSQLListEdit);
        libView->addAction(actionRemoveFromLibrary);
        libView->addAction(actionLibrarySetImage);
        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuControl->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpenUrl);
        menuFile->addAction(actionNewPlaylist);
        menuFile->addAction(actionLoadPlaylist);
        menuFile->addAction(actionSavePlaylist);
        menuFile->addAction(actionClosePlaylist);
        menuFile->addAction(actionSettings);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionAboutQt);
        menuControl->addAction(actionPrev);
        menuControl->addAction(actionPlay);
        menuControl->addAction(actionPause);
        menuControl->addAction(actionNext);
        menuControl->addSeparator();
        menuControl->addAction(actionShuffle);
        menuControl->addAction(actionRepeat);
        menuControl->addSeparator();
        menuControl->addAction(actionClear_playlist);
        menuView->addAction(menuColumns->menuAction());
        menuView->addAction(actionLookFeel);
        menuView->addAction(actionConsole);
        menuView->addSeparator();
        menuColumns->addAction(actionViewFile);
        menuColumns->addAction(actionViewTrack);
        menuColumns->addAction(actionViewTitle);
        menuColumns->addAction(actionViewArtist);
        menuColumns->addAction(actionViewAlbum);
        menuColumns->addAction(actionViewGenre);
        menuColumns->addAction(actionViewYear);
        menuColumns->addAction(actionViewComment);
        menuColumns->addAction(actionViewLength);
        menuColumns->addAction(actionViewRating);
        toolBar->addAction(actionBreak);
        toolBar->addSeparator();
        toolBar->addAction(actionPrev);
        toolBar->addAction(actionPlay);
        toolBar->addAction(actionPause);
        toolBar->addAction(actionStop);
        toolBar->addAction(actionNext);
        toolBar->addSeparator();
        toolBar->addAction(actionShuffle);
        toolBar->addAction(actionRepeat);
        toolBar->addSeparator();
        toolBar->addAction(actionClear_playlist);
        toolBar->addAction(actionEditTag);
        toolBar->addAction(actionQTagConvert);
        toolBar->addSeparator();
        toolBar->addAction(actionConsole);
        toolBar->addSeparator();

        retranslateUi(CuberokClass);
        QObject::connect(actionAbout, SIGNAL(triggered()), CuberokClass, SLOT(aboutMenu()));
        QObject::connect(actionPrev, SIGNAL(triggered()), listView, SLOT(prev()));
        QObject::connect(actionNext, SIGNAL(triggered()), listView, SLOT(next()));
        QObject::connect(actionPause, SIGNAL(triggered(bool)), listView, SLOT(pause(bool)));
        QObject::connect(actionPlay, SIGNAL(triggered()), listView, SLOT(play()));
        QObject::connect(actionShuffle, SIGNAL(triggered(bool)), listView, SLOT(shuffle(bool)));
        QObject::connect(actionRepeat, SIGNAL(triggered(bool)), listView, SLOT(repeat(bool)));
        QObject::connect(listView, SIGNAL(message(QString,QString,QString)), CuberokClass, SLOT(message(QString,QString,QString)));
        QObject::connect(actionExit, SIGNAL(triggered()), CuberokClass, SLOT(reallyClose()));
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
        QObject::connect(libView, SIGNAL(status(QString)), collectionStatus, SLOT(setText(QString)));
        QObject::connect(listView, SIGNAL(status(QString)), listStatus, SLOT(setText(QString)));
        QObject::connect(filterLineEdit, SIGNAL(textChanged(QString)), colView, SLOT(filter(QString)));
        QObject::connect(colView, SIGNAL(setVisibleSubsetWidgets(bool)), subsetLabel, SLOT(setVisible(bool)));
        QObject::connect(colView, SIGNAL(setVisibleSubsetWidgets(bool)), subsetDisableButton, SLOT(setVisible(bool)));
        QObject::connect(subsetDisableButton, SIGNAL(clicked()), colView, SLOT(clearSubset()));
        QObject::connect(colView, SIGNAL(setSubsetLabel(QString)), subsetLabel, SLOT(setText(QString)));
        QObject::connect(actionStop, SIGNAL(triggered()), listView, SLOT(stop()));
        QObject::connect(actionLoadPlaylist, SIGNAL(triggered()), listView, SLOT(loadList()));
        QObject::connect(actionSavePlaylist, SIGNAL(triggered()), listView, SLOT(saveList()));
        QObject::connect(actionAboutQt, SIGNAL(triggered()), CuberokClass, SLOT(aboutQtMenu()));
        QObject::connect(actionReloadTags, SIGNAL(triggered()), listView, SLOT(reloadTags()));
        QObject::connect(actionViewRating, SIGNAL(triggered(bool)), listView, SLOT(viewRating(bool)));
        QObject::connect(actionSettings, SIGNAL(triggered()), CuberokClass, SLOT(settings()));
        QObject::connect(actionSetImage, SIGNAL(triggered()), colView, SLOT(setImage()));
        QObject::connect(actionIconView, SIGNAL(triggered(bool)), colView, SLOT(iconView(bool)));
        QObject::connect(actionOpenUrl, SIGNAL(triggered()), listView, SLOT(openUrl()));
        QObject::connect(actionAddToLibrary, SIGNAL(triggered()), libView, SLOT(addItem()));
        QObject::connect(actionRemoveFromLibrary, SIGNAL(triggered()), libView, SLOT(removeItem()));
        QObject::connect(actionLibrarySetImage, SIGNAL(triggered()), libView, SLOT(setImage()));
        QObject::connect(actionGetImageFromLastFM, SIGNAL(triggered()), colView, SLOT(loadImage()));
        QObject::connect(actionConsole, SIGNAL(triggered()), CuberokClass, SLOT(viewConsole()));
        QObject::connect(infoWidget, SIGNAL(ban()), listView, SLOT(rateBan()));
        QObject::connect(infoWidget, SIGNAL(loveIt()), listView, SLOT(rateLove()));
        QObject::connect(infoWidget, SIGNAL(rateDown()), listView, SLOT(rateDown()));
        QObject::connect(infoWidget, SIGNAL(rateUp()), listView, SLOT(rateUp()));
        QObject::connect(actionLibraryRegularPlaylist, SIGNAL(triggered(bool)), libView, SLOT(regularPlaylist(bool)));
        QObject::connect(actionLibrarySQLPlaylist, SIGNAL(triggered(bool)), libView, SLOT(sqlPlaylist(bool)));
        QObject::connect(actionSQLListEdit, SIGNAL(triggered()), libView, SLOT(sqlListEdit()));
        QObject::connect(actionQTagConvert, SIGNAL(triggered()), CuberokClass, SLOT(qTagConvert()));
        QObject::connect(actionRefreshTree, SIGNAL(triggered()), CuberokClass, SLOT(refreshTree()));

        QMetaObject::connectSlotsByName(CuberokClass);
    } // setupUi

    void retranslateUi(QMainWindow *CuberokClass)
    {
        CuberokClass->setWindowTitle(QApplication::translate("CuberokClass", "Cuberok", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("CuberokClass", "About", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionAbout->setStatusTip(QApplication::translate("CuberokClass", "About dialog", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionAbout->setShortcut(QApplication::translate("CuberokClass", "Alt+F1", 0, QApplication::UnicodeUTF8));
        actionBreak->setText(QApplication::translate("CuberokClass", "Break", 0, QApplication::UnicodeUTF8));
        actionPrev->setText(QApplication::translate("CuberokClass", "Previous", 0, QApplication::UnicodeUTF8));
        actionPrev->setIconText(QApplication::translate("CuberokClass", "<<", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPrev->setToolTip(QApplication::translate("CuberokClass", "Previous track", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionPrev->setStatusTip(QApplication::translate("CuberokClass", "Previous track", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionPrev->setShortcut(QApplication::translate("CuberokClass", "Alt+Shift+Z", 0, QApplication::UnicodeUTF8));
        actionNext->setText(QApplication::translate("CuberokClass", "Next", 0, QApplication::UnicodeUTF8));
        actionNext->setIconText(QApplication::translate("CuberokClass", ">>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionNext->setToolTip(QApplication::translate("CuberokClass", "Next track", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionNext->setStatusTip(QApplication::translate("CuberokClass", "Next track", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionNext->setShortcut(QApplication::translate("CuberokClass", "Alt+Shift+B", 0, QApplication::UnicodeUTF8));
        actionPause->setText(QApplication::translate("CuberokClass", "Pause", 0, QApplication::UnicodeUTF8));
        actionPause->setIconText(QApplication::translate("CuberokClass", "||", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPause->setToolTip(QApplication::translate("CuberokClass", "Pause", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionPause->setStatusTip(QApplication::translate("CuberokClass", "Pause", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionPause->setShortcut(QApplication::translate("CuberokClass", "Alt+Shift+C", 0, QApplication::UnicodeUTF8));
        actionPlay->setText(QApplication::translate("CuberokClass", "Play", 0, QApplication::UnicodeUTF8));
        actionPlay->setIconText(QApplication::translate("CuberokClass", ">", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPlay->setToolTip(QApplication::translate("CuberokClass", "Play track", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionPlay->setStatusTip(QApplication::translate("CuberokClass", "Play track", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionPlay->setShortcut(QApplication::translate("CuberokClass", "Alt+Shift+X", 0, QApplication::UnicodeUTF8));
        actionShuffle->setText(QApplication::translate("CuberokClass", "Shuffle", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionShuffle->setStatusTip(QApplication::translate("CuberokClass", "Shuffle mode", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionRepeat->setText(QApplication::translate("CuberokClass", "Repeat", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionRepeat->setStatusTip(QApplication::translate("CuberokClass", "Repeat mode", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionExit->setText(QApplication::translate("CuberokClass", "Exit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionExit->setStatusTip(QApplication::translate("CuberokClass", "Close the program", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionClear_playlist->setText(QApplication::translate("CuberokClass", "Clear playlist", 0, QApplication::UnicodeUTF8));
        actionClear_playlist->setIconText(QApplication::translate("CuberokClass", "Clear", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionClear_playlist->setStatusTip(QApplication::translate("CuberokClass", "Clear playlist", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionQueueNext->setText(QApplication::translate("CuberokClass", "Queue as Next", 0, QApplication::UnicodeUTF8));
        actionQueueNext->setShortcut(QApplication::translate("CuberokClass", "Ctrl+D", 0, QApplication::UnicodeUTF8));
        actionViewFile->setText(QApplication::translate("CuberokClass", "File", 0, QApplication::UnicodeUTF8));
        actionViewTrack->setText(QApplication::translate("CuberokClass", "Track", 0, QApplication::UnicodeUTF8));
        actionViewTitle->setText(QApplication::translate("CuberokClass", "Title", 0, QApplication::UnicodeUTF8));
        actionViewArtist->setText(QApplication::translate("CuberokClass", "Artist", 0, QApplication::UnicodeUTF8));
        actionViewAlbum->setText(QApplication::translate("CuberokClass", "Album", 0, QApplication::UnicodeUTF8));
        actionViewGenre->setText(QApplication::translate("CuberokClass", "Genre", 0, QApplication::UnicodeUTF8));
        actionViewYear->setText(QApplication::translate("CuberokClass", "Year", 0, QApplication::UnicodeUTF8));
        actionViewComment->setText(QApplication::translate("CuberokClass", "Comment", 0, QApplication::UnicodeUTF8));
        actionViewLength->setText(QApplication::translate("CuberokClass", "Length", 0, QApplication::UnicodeUTF8));
        actionEditTag->setText(QApplication::translate("CuberokClass", "Edit Tag", 0, QApplication::UnicodeUTF8));
        actionEditTag->setIconText(QApplication::translate("CuberokClass", "Tag", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionEditTag->setToolTip(QApplication::translate("CuberokClass", "Edit Tag", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionNewPlaylist->setText(QApplication::translate("CuberokClass", "New playlist", 0, QApplication::UnicodeUTF8));
        actionClosePlaylist->setText(QApplication::translate("CuberokClass", "Close playlist", 0, QApplication::UnicodeUTF8));
        actionRemoveSong->setText(QApplication::translate("CuberokClass", "Remove song", 0, QApplication::UnicodeUTF8));
        actionLookFeel->setText(QApplication::translate("CuberokClass", "Look and Feel", 0, QApplication::UnicodeUTF8));
        actionArtistMode->setText(QApplication::translate("CuberokClass", "Artist", 0, QApplication::UnicodeUTF8));
        actionAlbumMode->setText(QApplication::translate("CuberokClass", "Album", 0, QApplication::UnicodeUTF8));
        actionGenreMode->setText(QApplication::translate("CuberokClass", "Genre", 0, QApplication::UnicodeUTF8));
        actionSongMode->setText(QApplication::translate("CuberokClass", "Song", 0, QApplication::UnicodeUTF8));
        actionAddToCollection->setText(QApplication::translate("CuberokClass", "Add Item", 0, QApplication::UnicodeUTF8));
        actionAddToLibrary->setText(QApplication::translate("CuberokClass", "Add Item", 0, QApplication::UnicodeUTF8));
        actionRemoveFromCollection->setText(QApplication::translate("CuberokClass", "Remove Item", 0, QApplication::UnicodeUTF8));
        actionRemoveFromLibrary->setText(QApplication::translate("CuberokClass", "Remove Item", 0, QApplication::UnicodeUTF8));
        actionStop->setText(QApplication::translate("CuberokClass", "Stop", 0, QApplication::UnicodeUTF8));
        actionStop->setIconText(QApplication::translate("CuberokClass", "[]", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionStop->setStatusTip(QApplication::translate("CuberokClass", "Stop", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionStop->setShortcut(QApplication::translate("CuberokClass", "Alt+Shift+V", 0, QApplication::UnicodeUTF8));
        actionSavePlaylist->setText(QApplication::translate("CuberokClass", "Save playlist", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSavePlaylist->setToolTip(QApplication::translate("CuberokClass", "Save playlist into file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionLoadPlaylist->setText(QApplication::translate("CuberokClass", "Open playlist", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionLoadPlaylist->setToolTip(QApplication::translate("CuberokClass", "Load playlist from a file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionAboutQt->setText(QApplication::translate("CuberokClass", "About Qt", 0, QApplication::UnicodeUTF8));
        actionReloadTags->setText(QApplication::translate("CuberokClass", "Reload tags", 0, QApplication::UnicodeUTF8));
        actionViewRating->setText(QApplication::translate("CuberokClass", "Rating", 0, QApplication::UnicodeUTF8));
        actionSettings->setText(QApplication::translate("CuberokClass", "Preferences", 0, QApplication::UnicodeUTF8));
        actionSetImage->setText(QApplication::translate("CuberokClass", "Set Image", 0, QApplication::UnicodeUTF8));
        actionLibrarySetImage->setText(QApplication::translate("CuberokClass", "Set Image", 0, QApplication::UnicodeUTF8));
        actionIconView->setText(QApplication::translate("CuberokClass", "Icon View", 0, QApplication::UnicodeUTF8));
        actionOpenUrl->setText(QApplication::translate("CuberokClass", "Open Url", 0, QApplication::UnicodeUTF8));
        actionGetImageFromLastFM->setText(QApplication::translate("CuberokClass", "Load image from Last.FM", 0, QApplication::UnicodeUTF8));
        actionConsole->setText(QApplication::translate("CuberokClass", "Messages", 0, QApplication::UnicodeUTF8));
        actionLibrarySQLPlaylist->setText(QApplication::translate("CuberokClass", "View SQL Playlists", 0, QApplication::UnicodeUTF8));
        actionLibraryRegularPlaylist->setText(QApplication::translate("CuberokClass", "View Regular Playlists", 0, QApplication::UnicodeUTF8));
        actionSQLListEdit->setText(QApplication::translate("CuberokClass", "Edit SQL Playist", 0, QApplication::UnicodeUTF8));
        actionQTagConvert->setText(QApplication::translate("CuberokClass", "QTagConvert", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionQTagConvert->setToolTip(QApplication::translate("CuberokClass", "Edit tags with QTagConvert", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionRefreshTree->setText(QApplication::translate("CuberokClass", "Refresh Tree", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        dockWidget1->setWindowTitle(QApplication::translate("CuberokClass", "Collection", 0, QApplication::UnicodeUTF8));
        subsetLabel->setText(QApplication::translate("CuberokClass", "TextLabel", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        subsetDisableButton->setToolTip(QApplication::translate("CuberokClass", "Reset filter", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        subsetDisableButton->setText(QApplication::translate("CuberokClass", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        filterLineEdit->setToolTip(QApplication::translate("CuberokClass", "Enter search substring", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        colView->setToolTip(QApplication::translate("CuberokClass", "Drag'n'Drop files to the collection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        dockWidget2->setWindowTitle(QApplication::translate("CuberokClass", "Files", 0, QApplication::UnicodeUTF8));
        dockWidget3->setWindowTitle(QApplication::translate("CuberokClass", "Library", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        libView->setToolTip(QApplication::translate("CuberokClass", "Drag'n'Drop playlists to the library", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        dockWidget4->setWindowTitle(QApplication::translate("CuberokClass", "Information", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("CuberokClass", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("CuberokClass", "Help", 0, QApplication::UnicodeUTF8));
        menuControl->setTitle(QApplication::translate("CuberokClass", "Control", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("CuberokClass", "View", 0, QApplication::UnicodeUTF8));
        menuColumns->setTitle(QApplication::translate("CuberokClass", "Columns", 0, QApplication::UnicodeUTF8));
        listStatus->setText(QApplication::translate("CuberokClass", "List", 0, QApplication::UnicodeUTF8));
        collectionStatus->setText(QApplication::translate("CuberokClass", "Collection", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("CuberokClass", "Toolbar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CuberokClass: public Ui_CuberokClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUBEROK_H
