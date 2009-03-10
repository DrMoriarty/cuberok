/********************************************************************************
** Form generated from reading ui file 'KCmp3Tag.ui'
**
** Created: Fri 6. Mar 09:56:05 2009
**      by: Qt User Interface Compiler version 4.5.0-rc1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_KCMP3TAG_H
#define UI_KCMP3TAG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTreeView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mp3Dialog
{
public:
    QAction *actionExit;
    QAction *actionAbout;
    QAction *actionAbout_Qt;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout1;
    QPushButton *upButton;
    QTreeView *treeDir;
    QSpacerItem *spacerItem;
    QComboBox *comboPath;
    QPushButton *homeButton;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout2;
    QLabel *label_13;
    QLabel *label_14;
    QComboBox *comboBox_action;
    QComboBox *comboBox_codepage;
    QGroupBox *groupBox;
    QGridLayout *gridLayout3;
    QComboBox *comboGenreV1;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEditYearV1;
    QLabel *label_4;
    QLineEdit *lineEditnameV1;
    QLineEdit *lineEditGroupV1;
    QLineEdit *lineEditAlbum;
    QLineEdit *lineCommentV1;
    QPushButton *pushButton_doTitle1;
    QPushButton *pushButton_doArtist1;
    QPushButton *pushButton_doAlbum1;
    QPushButton *pushButton_doComment1;
    QPushButton *pushButton_reloadTitle1;
    QPushButton *pushButton_reloadArtist1;
    QPushButton *pushButton_reloadAlbum1;
    QPushButton *pushButton_reloadComment1;
    QPushButton *v1tov2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout4;
    QComboBox *comboGenreV2;
    QLabel *label_12;
    QLabel *label_11;
    QLabel *label_10;
    QLabel *label_9;
    QLabel *label_8;
    QLineEdit *lineEditYearV2;
    QLabel *label_7;
    QLineEdit *lineEditnameV2;
    QLineEdit *lineEditGroupV2;
    QLineEdit *lineEditAlbumV2;
    QLineEdit *lineCommenV2;
    QPushButton *v2tov1;
    QPushButton *ButtonSaveTags;
    QCheckBox *checkBox_ID3v1;
    QCheckBox *checkBox_ID3v2;
    QPushButton *pushButton_reloadTitle2;
    QPushButton *pushButton_reloadArtist2;
    QPushButton *pushButton_reloadAlbum2;
    QPushButton *pushButton_reloadComment2;
    QPushButton *pushButton_doTitle2;
    QPushButton *pushButton_doArtist2;
    QPushButton *pushButton_doAlbum2;
    QPushButton *pushButton_doComment2;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout5;
    QCheckBox *GenreAllFiles;
    QCheckBox *GroupAllFiles;
    QCheckBox *AlbumAllfiles;
    QCheckBox *YearAllfiles;
    QCheckBox *CommentAllFiles;
    QPushButton *SaveAllFiles;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout6;
    QPushButton *CovertForAll;
    QCheckBox *checkBox_allID3v1;
    QCheckBox *checkBox_allID3v2;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;

    void setupUi(QMainWindow *mp3Dialog)
    {
        if (mp3Dialog->objectName().isEmpty())
            mp3Dialog->setObjectName(QString::fromUtf8("mp3Dialog"));
        mp3Dialog->resize(570, 560);
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/recycle.png")), QIcon::Normal, QIcon::Off);
        mp3Dialog->setWindowIcon(icon);
        actionExit = new QAction(mp3Dialog);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionAbout = new QAction(mp3Dialog);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAbout_Qt = new QAction(mp3Dialog);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        centralwidget = new QWidget(mp3Dialog);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout1 = new QGridLayout();
#ifndef Q_OS_MAC
        gridLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout1->setMargin(0);
#endif
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        upButton = new QPushButton(centralwidget);
        upButton->setObjectName(QString::fromUtf8("upButton"));
        QIcon icon1;
        icon1.addPixmap(QPixmap(QString::fromUtf8(":/icons/up.png")), QIcon::Normal, QIcon::Off);
        upButton->setIcon(icon1);

        gridLayout1->addWidget(upButton, 0, 0, 1, 1);

        treeDir = new QTreeView(centralwidget);
        treeDir->setObjectName(QString::fromUtf8("treeDir"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeDir->sizePolicy().hasHeightForWidth());
        treeDir->setSizePolicy(sizePolicy);
        treeDir->setUniformRowHeights(true);

        gridLayout1->addWidget(treeDir, 2, 0, 1, 3);

        spacerItem = new QSpacerItem(111, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout1->addItem(spacerItem, 0, 2, 1, 1);

        comboPath = new QComboBox(centralwidget);
        comboPath->setObjectName(QString::fromUtf8("comboPath"));
        comboPath->setEnabled(true);
        comboPath->setEditable(true);

        gridLayout1->addWidget(comboPath, 1, 0, 1, 3);

        homeButton = new QPushButton(centralwidget);
        homeButton->setObjectName(QString::fromUtf8("homeButton"));
        QIcon icon2;
        icon2.addPixmap(QPixmap(QString::fromUtf8(":/icons/home.png")), QIcon::Normal, QIcon::Off);
        homeButton->setIcon(icon2);

        gridLayout1->addWidget(homeButton, 0, 1, 1, 1);


        gridLayout->addLayout(gridLayout1, 0, 0, 3, 1);

        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy1);
        gridLayout2 = new QGridLayout(groupBox_5);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        label_13 = new QLabel(groupBox_5);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy1.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy1);

        gridLayout2->addWidget(label_13, 0, 0, 1, 1);

        label_14 = new QLabel(groupBox_5);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy1.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy1);

        gridLayout2->addWidget(label_14, 0, 1, 1, 1);

        comboBox_action = new QComboBox(groupBox_5);
        comboBox_action->setObjectName(QString::fromUtf8("comboBox_action"));

        gridLayout2->addWidget(comboBox_action, 1, 0, 1, 1);

        comboBox_codepage = new QComboBox(groupBox_5);
        comboBox_codepage->setObjectName(QString::fromUtf8("comboBox_codepage"));

        gridLayout2->addWidget(comboBox_codepage, 1, 1, 1, 1);


        gridLayout->addWidget(groupBox_5, 0, 1, 1, 1);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        gridLayout3 = new QGridLayout(groupBox);
        gridLayout3->setSpacing(2);
        gridLayout3->setMargin(4);
        gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
        comboGenreV1 = new QComboBox(groupBox);
        comboGenreV1->setObjectName(QString::fromUtf8("comboGenreV1"));

        gridLayout3->addWidget(comboGenreV1, 3, 1, 1, 3);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout3->addWidget(label_6, 0, 0, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout3->addWidget(label_5, 1, 0, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout3->addWidget(label, 2, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout3->addWidget(label_2, 3, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout3->addWidget(label_3, 4, 0, 1, 1);

        lineEditYearV1 = new QLineEdit(groupBox);
        lineEditYearV1->setObjectName(QString::fromUtf8("lineEditYearV1"));
        lineEditYearV1->setMinimumSize(QSize(4, 0));

        gridLayout3->addWidget(lineEditYearV1, 4, 1, 1, 2);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout3->addWidget(label_4, 5, 0, 1, 1);

        lineEditnameV1 = new QLineEdit(groupBox);
        lineEditnameV1->setObjectName(QString::fromUtf8("lineEditnameV1"));

        gridLayout3->addWidget(lineEditnameV1, 0, 1, 1, 3);

        lineEditGroupV1 = new QLineEdit(groupBox);
        lineEditGroupV1->setObjectName(QString::fromUtf8("lineEditGroupV1"));

        gridLayout3->addWidget(lineEditGroupV1, 1, 1, 1, 3);

        lineEditAlbum = new QLineEdit(groupBox);
        lineEditAlbum->setObjectName(QString::fromUtf8("lineEditAlbum"));

        gridLayout3->addWidget(lineEditAlbum, 2, 1, 1, 3);

        lineCommentV1 = new QLineEdit(groupBox);
        lineCommentV1->setObjectName(QString::fromUtf8("lineCommentV1"));

        gridLayout3->addWidget(lineCommentV1, 5, 1, 1, 3);

        pushButton_doTitle1 = new QPushButton(groupBox);
        pushButton_doTitle1->setObjectName(QString::fromUtf8("pushButton_doTitle1"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_doTitle1->sizePolicy().hasHeightForWidth());
        pushButton_doTitle1->setSizePolicy(sizePolicy2);
        pushButton_doTitle1->setMaximumSize(QSize(24, 24));
        QIcon icon3;
        icon3.addPixmap(QPixmap(QString::fromUtf8(":/icons/gear.png")), QIcon::Normal, QIcon::Off);
        pushButton_doTitle1->setIcon(icon3);
        pushButton_doTitle1->setFlat(true);

        gridLayout3->addWidget(pushButton_doTitle1, 0, 5, 1, 1);

        pushButton_doArtist1 = new QPushButton(groupBox);
        pushButton_doArtist1->setObjectName(QString::fromUtf8("pushButton_doArtist1"));
        sizePolicy2.setHeightForWidth(pushButton_doArtist1->sizePolicy().hasHeightForWidth());
        pushButton_doArtist1->setSizePolicy(sizePolicy2);
        pushButton_doArtist1->setMaximumSize(QSize(24, 24));
        pushButton_doArtist1->setIcon(icon3);
        pushButton_doArtist1->setFlat(true);

        gridLayout3->addWidget(pushButton_doArtist1, 1, 5, 1, 1);

        pushButton_doAlbum1 = new QPushButton(groupBox);
        pushButton_doAlbum1->setObjectName(QString::fromUtf8("pushButton_doAlbum1"));
        sizePolicy2.setHeightForWidth(pushButton_doAlbum1->sizePolicy().hasHeightForWidth());
        pushButton_doAlbum1->setSizePolicy(sizePolicy2);
        pushButton_doAlbum1->setMaximumSize(QSize(24, 24));
        pushButton_doAlbum1->setIcon(icon3);
        pushButton_doAlbum1->setFlat(true);

        gridLayout3->addWidget(pushButton_doAlbum1, 2, 5, 1, 1);

        pushButton_doComment1 = new QPushButton(groupBox);
        pushButton_doComment1->setObjectName(QString::fromUtf8("pushButton_doComment1"));
        sizePolicy2.setHeightForWidth(pushButton_doComment1->sizePolicy().hasHeightForWidth());
        pushButton_doComment1->setSizePolicy(sizePolicy2);
        pushButton_doComment1->setMaximumSize(QSize(24, 24));
        pushButton_doComment1->setIcon(icon3);
        pushButton_doComment1->setFlat(true);

        gridLayout3->addWidget(pushButton_doComment1, 5, 5, 1, 1);

        pushButton_reloadTitle1 = new QPushButton(groupBox);
        pushButton_reloadTitle1->setObjectName(QString::fromUtf8("pushButton_reloadTitle1"));
        sizePolicy2.setHeightForWidth(pushButton_reloadTitle1->sizePolicy().hasHeightForWidth());
        pushButton_reloadTitle1->setSizePolicy(sizePolicy2);
        pushButton_reloadTitle1->setMaximumSize(QSize(24, 24));
        QIcon icon4;
        icon4.addPixmap(QPixmap(QString::fromUtf8(":/icons/reload.png")), QIcon::Normal, QIcon::Off);
        pushButton_reloadTitle1->setIcon(icon4);
        pushButton_reloadTitle1->setFlat(true);

        gridLayout3->addWidget(pushButton_reloadTitle1, 0, 4, 1, 1);

        pushButton_reloadArtist1 = new QPushButton(groupBox);
        pushButton_reloadArtist1->setObjectName(QString::fromUtf8("pushButton_reloadArtist1"));
        sizePolicy2.setHeightForWidth(pushButton_reloadArtist1->sizePolicy().hasHeightForWidth());
        pushButton_reloadArtist1->setSizePolicy(sizePolicy2);
        pushButton_reloadArtist1->setMaximumSize(QSize(24, 24));
        pushButton_reloadArtist1->setIcon(icon4);
        pushButton_reloadArtist1->setFlat(true);

        gridLayout3->addWidget(pushButton_reloadArtist1, 1, 4, 1, 1);

        pushButton_reloadAlbum1 = new QPushButton(groupBox);
        pushButton_reloadAlbum1->setObjectName(QString::fromUtf8("pushButton_reloadAlbum1"));
        sizePolicy2.setHeightForWidth(pushButton_reloadAlbum1->sizePolicy().hasHeightForWidth());
        pushButton_reloadAlbum1->setSizePolicy(sizePolicy2);
        pushButton_reloadAlbum1->setMaximumSize(QSize(24, 24));
        pushButton_reloadAlbum1->setIcon(icon4);
        pushButton_reloadAlbum1->setFlat(true);

        gridLayout3->addWidget(pushButton_reloadAlbum1, 2, 4, 1, 1);

        pushButton_reloadComment1 = new QPushButton(groupBox);
        pushButton_reloadComment1->setObjectName(QString::fromUtf8("pushButton_reloadComment1"));
        sizePolicy2.setHeightForWidth(pushButton_reloadComment1->sizePolicy().hasHeightForWidth());
        pushButton_reloadComment1->setSizePolicy(sizePolicy2);
        pushButton_reloadComment1->setMaximumSize(QSize(24, 24));
        pushButton_reloadComment1->setIcon(icon4);
        pushButton_reloadComment1->setFlat(true);

        gridLayout3->addWidget(pushButton_reloadComment1, 5, 4, 1, 1);

        v1tov2 = new QPushButton(groupBox);
        v1tov2->setObjectName(QString::fromUtf8("v1tov2"));

        gridLayout3->addWidget(v1tov2, 6, 1, 1, 1);


        gridLayout->addWidget(groupBox, 1, 1, 1, 1);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        gridLayout4 = new QGridLayout(groupBox_2);
        gridLayout4->setSpacing(2);
        gridLayout4->setMargin(4);
        gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
        comboGenreV2 = new QComboBox(groupBox_2);
        comboGenreV2->setObjectName(QString::fromUtf8("comboGenreV2"));

        gridLayout4->addWidget(comboGenreV2, 3, 1, 1, 3);

        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout4->addWidget(label_12, 0, 0, 1, 1);

        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout4->addWidget(label_11, 1, 0, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout4->addWidget(label_10, 2, 0, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout4->addWidget(label_9, 3, 0, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout4->addWidget(label_8, 4, 0, 1, 1);

        lineEditYearV2 = new QLineEdit(groupBox_2);
        lineEditYearV2->setObjectName(QString::fromUtf8("lineEditYearV2"));
        lineEditYearV2->setMinimumSize(QSize(4, 0));

        gridLayout4->addWidget(lineEditYearV2, 4, 1, 1, 2);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout4->addWidget(label_7, 5, 0, 1, 1);

        lineEditnameV2 = new QLineEdit(groupBox_2);
        lineEditnameV2->setObjectName(QString::fromUtf8("lineEditnameV2"));

        gridLayout4->addWidget(lineEditnameV2, 0, 1, 1, 3);

        lineEditGroupV2 = new QLineEdit(groupBox_2);
        lineEditGroupV2->setObjectName(QString::fromUtf8("lineEditGroupV2"));

        gridLayout4->addWidget(lineEditGroupV2, 1, 1, 1, 3);

        lineEditAlbumV2 = new QLineEdit(groupBox_2);
        lineEditAlbumV2->setObjectName(QString::fromUtf8("lineEditAlbumV2"));

        gridLayout4->addWidget(lineEditAlbumV2, 2, 1, 1, 3);

        lineCommenV2 = new QLineEdit(groupBox_2);
        lineCommenV2->setObjectName(QString::fromUtf8("lineCommenV2"));

        gridLayout4->addWidget(lineCommenV2, 5, 1, 1, 3);

        v2tov1 = new QPushButton(groupBox_2);
        v2tov1->setObjectName(QString::fromUtf8("v2tov1"));

        gridLayout4->addWidget(v2tov1, 6, 1, 1, 1);

        ButtonSaveTags = new QPushButton(groupBox_2);
        ButtonSaveTags->setObjectName(QString::fromUtf8("ButtonSaveTags"));
        QIcon icon5;
        icon5.addPixmap(QPixmap(QString::fromUtf8(":/icons/document_save_as.png")), QIcon::Normal, QIcon::Off);
        ButtonSaveTags->setIcon(icon5);

        gridLayout4->addWidget(ButtonSaveTags, 7, 2, 1, 4);

        checkBox_ID3v1 = new QCheckBox(groupBox_2);
        checkBox_ID3v1->setObjectName(QString::fromUtf8("checkBox_ID3v1"));
        checkBox_ID3v1->setChecked(true);

        gridLayout4->addWidget(checkBox_ID3v1, 7, 0, 1, 1);

        checkBox_ID3v2 = new QCheckBox(groupBox_2);
        checkBox_ID3v2->setObjectName(QString::fromUtf8("checkBox_ID3v2"));
        checkBox_ID3v2->setChecked(true);

        gridLayout4->addWidget(checkBox_ID3v2, 7, 1, 1, 1);

        pushButton_reloadTitle2 = new QPushButton(groupBox_2);
        pushButton_reloadTitle2->setObjectName(QString::fromUtf8("pushButton_reloadTitle2"));
        sizePolicy2.setHeightForWidth(pushButton_reloadTitle2->sizePolicy().hasHeightForWidth());
        pushButton_reloadTitle2->setSizePolicy(sizePolicy2);
        pushButton_reloadTitle2->setMaximumSize(QSize(24, 24));
        pushButton_reloadTitle2->setIcon(icon4);
        pushButton_reloadTitle2->setFlat(true);

        gridLayout4->addWidget(pushButton_reloadTitle2, 0, 4, 1, 1);

        pushButton_reloadArtist2 = new QPushButton(groupBox_2);
        pushButton_reloadArtist2->setObjectName(QString::fromUtf8("pushButton_reloadArtist2"));
        sizePolicy2.setHeightForWidth(pushButton_reloadArtist2->sizePolicy().hasHeightForWidth());
        pushButton_reloadArtist2->setSizePolicy(sizePolicy2);
        pushButton_reloadArtist2->setMaximumSize(QSize(24, 24));
        pushButton_reloadArtist2->setIcon(icon4);
        pushButton_reloadArtist2->setFlat(true);

        gridLayout4->addWidget(pushButton_reloadArtist2, 1, 4, 1, 1);

        pushButton_reloadAlbum2 = new QPushButton(groupBox_2);
        pushButton_reloadAlbum2->setObjectName(QString::fromUtf8("pushButton_reloadAlbum2"));
        sizePolicy2.setHeightForWidth(pushButton_reloadAlbum2->sizePolicy().hasHeightForWidth());
        pushButton_reloadAlbum2->setSizePolicy(sizePolicy2);
        pushButton_reloadAlbum2->setMaximumSize(QSize(24, 24));
        pushButton_reloadAlbum2->setIcon(icon4);
        pushButton_reloadAlbum2->setFlat(true);

        gridLayout4->addWidget(pushButton_reloadAlbum2, 2, 4, 1, 1);

        pushButton_reloadComment2 = new QPushButton(groupBox_2);
        pushButton_reloadComment2->setObjectName(QString::fromUtf8("pushButton_reloadComment2"));
        sizePolicy2.setHeightForWidth(pushButton_reloadComment2->sizePolicy().hasHeightForWidth());
        pushButton_reloadComment2->setSizePolicy(sizePolicy2);
        pushButton_reloadComment2->setMaximumSize(QSize(24, 24));
        pushButton_reloadComment2->setIcon(icon4);
        pushButton_reloadComment2->setFlat(true);

        gridLayout4->addWidget(pushButton_reloadComment2, 5, 4, 1, 1);

        pushButton_doTitle2 = new QPushButton(groupBox_2);
        pushButton_doTitle2->setObjectName(QString::fromUtf8("pushButton_doTitle2"));
        sizePolicy2.setHeightForWidth(pushButton_doTitle2->sizePolicy().hasHeightForWidth());
        pushButton_doTitle2->setSizePolicy(sizePolicy2);
        pushButton_doTitle2->setMaximumSize(QSize(24, 24));
        pushButton_doTitle2->setIcon(icon3);
        pushButton_doTitle2->setFlat(true);

        gridLayout4->addWidget(pushButton_doTitle2, 0, 5, 1, 1);

        pushButton_doArtist2 = new QPushButton(groupBox_2);
        pushButton_doArtist2->setObjectName(QString::fromUtf8("pushButton_doArtist2"));
        sizePolicy2.setHeightForWidth(pushButton_doArtist2->sizePolicy().hasHeightForWidth());
        pushButton_doArtist2->setSizePolicy(sizePolicy2);
        pushButton_doArtist2->setMaximumSize(QSize(24, 24));
        pushButton_doArtist2->setIcon(icon3);
        pushButton_doArtist2->setFlat(true);

        gridLayout4->addWidget(pushButton_doArtist2, 1, 5, 1, 1);

        pushButton_doAlbum2 = new QPushButton(groupBox_2);
        pushButton_doAlbum2->setObjectName(QString::fromUtf8("pushButton_doAlbum2"));
        sizePolicy2.setHeightForWidth(pushButton_doAlbum2->sizePolicy().hasHeightForWidth());
        pushButton_doAlbum2->setSizePolicy(sizePolicy2);
        pushButton_doAlbum2->setMaximumSize(QSize(24, 24));
        pushButton_doAlbum2->setIcon(icon3);
        pushButton_doAlbum2->setFlat(true);

        gridLayout4->addWidget(pushButton_doAlbum2, 2, 5, 1, 1);

        pushButton_doComment2 = new QPushButton(groupBox_2);
        pushButton_doComment2->setObjectName(QString::fromUtf8("pushButton_doComment2"));
        sizePolicy2.setHeightForWidth(pushButton_doComment2->sizePolicy().hasHeightForWidth());
        pushButton_doComment2->setSizePolicy(sizePolicy2);
        pushButton_doComment2->setMaximumSize(QSize(24, 24));
        pushButton_doComment2->setIcon(icon3);
        pushButton_doComment2->setFlat(true);

        gridLayout4->addWidget(pushButton_doComment2, 5, 5, 1, 1);


        gridLayout->addWidget(groupBox_2, 2, 1, 3, 1);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        gridLayout5 = new QGridLayout(groupBox_3);
        gridLayout5->setSpacing(2);
        gridLayout5->setMargin(4);
        gridLayout5->setObjectName(QString::fromUtf8("gridLayout5"));
        GenreAllFiles = new QCheckBox(groupBox_3);
        GenreAllFiles->setObjectName(QString::fromUtf8("GenreAllFiles"));

        gridLayout5->addWidget(GenreAllFiles, 0, 2, 1, 1);

        GroupAllFiles = new QCheckBox(groupBox_3);
        GroupAllFiles->setObjectName(QString::fromUtf8("GroupAllFiles"));

        gridLayout5->addWidget(GroupAllFiles, 0, 0, 1, 1);

        AlbumAllfiles = new QCheckBox(groupBox_3);
        AlbumAllfiles->setObjectName(QString::fromUtf8("AlbumAllfiles"));

        gridLayout5->addWidget(AlbumAllfiles, 1, 0, 1, 1);

        YearAllfiles = new QCheckBox(groupBox_3);
        YearAllfiles->setObjectName(QString::fromUtf8("YearAllfiles"));

        gridLayout5->addWidget(YearAllfiles, 1, 2, 1, 1);

        CommentAllFiles = new QCheckBox(groupBox_3);
        CommentAllFiles->setObjectName(QString::fromUtf8("CommentAllFiles"));

        gridLayout5->addWidget(CommentAllFiles, 0, 3, 1, 1);

        SaveAllFiles = new QPushButton(groupBox_3);
        SaveAllFiles->setObjectName(QString::fromUtf8("SaveAllFiles"));
        QIcon icon6;
        icon6.addPixmap(QPixmap(QString::fromUtf8(":/icons/save_all.png")), QIcon::Normal, QIcon::Off);
        SaveAllFiles->setIcon(icon6);

        gridLayout5->addWidget(SaveAllFiles, 1, 3, 1, 1);


        gridLayout->addWidget(groupBox_3, 3, 0, 1, 1);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        sizePolicy1.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy1);
        gridLayout6 = new QGridLayout(groupBox_4);
        gridLayout6->setSpacing(2);
        gridLayout6->setMargin(4);
        gridLayout6->setObjectName(QString::fromUtf8("gridLayout6"));
        CovertForAll = new QPushButton(groupBox_4);
        CovertForAll->setObjectName(QString::fromUtf8("CovertForAll"));
        CovertForAll->setIcon(icon3);

        gridLayout6->addWidget(CovertForAll, 0, 2, 1, 1);

        checkBox_allID3v1 = new QCheckBox(groupBox_4);
        checkBox_allID3v1->setObjectName(QString::fromUtf8("checkBox_allID3v1"));
        checkBox_allID3v1->setChecked(true);

        gridLayout6->addWidget(checkBox_allID3v1, 0, 0, 1, 1);

        checkBox_allID3v2 = new QCheckBox(groupBox_4);
        checkBox_allID3v2->setObjectName(QString::fromUtf8("checkBox_allID3v2"));
        checkBox_allID3v2->setChecked(true);

        gridLayout6->addWidget(checkBox_allID3v2, 1, 0, 1, 1);


        gridLayout->addWidget(groupBox_4, 4, 0, 1, 1);

        mp3Dialog->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(mp3Dialog);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        mp3Dialog->setStatusBar(statusbar);
        menuBar = new QMenuBar(mp3Dialog);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 570, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        mp3Dialog->setMenuBar(menuBar);
        QWidget::setTabOrder(homeButton, comboPath);
        QWidget::setTabOrder(comboPath, lineEditnameV1);
        QWidget::setTabOrder(lineEditnameV1, lineEditGroupV1);
        QWidget::setTabOrder(lineEditGroupV1, lineEditAlbum);
        QWidget::setTabOrder(lineEditAlbum, comboGenreV1);
        QWidget::setTabOrder(comboGenreV1, lineEditYearV1);
        QWidget::setTabOrder(lineEditYearV1, lineCommentV1);
        QWidget::setTabOrder(lineCommentV1, lineEditnameV2);
        QWidget::setTabOrder(lineEditnameV2, lineEditGroupV2);
        QWidget::setTabOrder(lineEditGroupV2, lineEditAlbumV2);
        QWidget::setTabOrder(lineEditAlbumV2, lineEditYearV2);
        QWidget::setTabOrder(lineEditYearV2, lineCommenV2);
        QWidget::setTabOrder(lineCommenV2, GroupAllFiles);
        QWidget::setTabOrder(GroupAllFiles, GenreAllFiles);
        QWidget::setTabOrder(GenreAllFiles, upButton);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionExit);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionAbout_Qt);

        retranslateUi(mp3Dialog);
        QObject::connect(actionExit, SIGNAL(triggered()), mp3Dialog, SLOT(close()));
        QObject::connect(comboBox_action, SIGNAL(currentIndexChanged(int)), mp3Dialog, SLOT(setAction(int)));
        QObject::connect(comboBox_codepage, SIGNAL(currentIndexChanged(QString)), mp3Dialog, SLOT(setCodepage(QString)));
        QObject::connect(pushButton_doAlbum1, SIGNAL(clicked()), mp3Dialog, SLOT(doAlbum1()));
        QObject::connect(pushButton_doArtist1, SIGNAL(clicked()), mp3Dialog, SLOT(doArtist1()));
        QObject::connect(pushButton_doComment1, SIGNAL(clicked()), mp3Dialog, SLOT(doComment1()));
        QObject::connect(pushButton_doTitle1, SIGNAL(clicked()), mp3Dialog, SLOT(doTitle1()));
        QObject::connect(pushButton_reloadAlbum1, SIGNAL(clicked()), mp3Dialog, SLOT(reloadAlbum1()));
        QObject::connect(pushButton_reloadArtist1, SIGNAL(clicked()), mp3Dialog, SLOT(reloadArtist1()));
        QObject::connect(pushButton_reloadComment1, SIGNAL(clicked()), mp3Dialog, SLOT(reloadComment1()));
        QObject::connect(pushButton_reloadTitle1, SIGNAL(clicked()), mp3Dialog, SLOT(reloadTitle1()));
        QObject::connect(pushButton_doAlbum2, SIGNAL(clicked()), mp3Dialog, SLOT(doAlbum2()));
        QObject::connect(pushButton_doArtist2, SIGNAL(clicked()), mp3Dialog, SLOT(doArtist2()));
        QObject::connect(pushButton_doComment2, SIGNAL(clicked()), mp3Dialog, SLOT(doComment2()));
        QObject::connect(pushButton_doTitle2, SIGNAL(clicked()), mp3Dialog, SLOT(doTitle2()));
        QObject::connect(pushButton_reloadAlbum2, SIGNAL(clicked()), mp3Dialog, SLOT(reloadAlbum2()));
        QObject::connect(pushButton_reloadArtist2, SIGNAL(clicked()), mp3Dialog, SLOT(reloadArtist2()));
        QObject::connect(pushButton_reloadComment2, SIGNAL(clicked()), mp3Dialog, SLOT(reloadComment2()));
        QObject::connect(pushButton_reloadTitle2, SIGNAL(clicked()), mp3Dialog, SLOT(reloadTitle2()));
        QObject::connect(actionAbout, SIGNAL(triggered()), mp3Dialog, SLOT(on_AboutMenu()));
        QObject::connect(actionAbout_Qt, SIGNAL(triggered()), mp3Dialog, SLOT(on_AboutQtMenu()));

        QMetaObject::connectSlotsByName(mp3Dialog);
    } // setupUi

    void retranslateUi(QMainWindow *mp3Dialog)
    {
        mp3Dialog->setWindowTitle(QApplication::translate("mp3Dialog", "QTagConvert", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("mp3Dialog", "E&xit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionExit->setStatusTip(QApplication::translate("mp3Dialog", "Exit", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionAbout->setText(QApplication::translate("mp3Dialog", "About", 0, QApplication::UnicodeUTF8));
        actionAbout_Qt->setText(QApplication::translate("mp3Dialog", "About Qt", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        upButton->setToolTip(QApplication::translate("mp3Dialog", "Go up", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        upButton->setText(QApplication::translate("mp3Dialog", "Up", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        treeDir->setToolTip(QApplication::translate("mp3Dialog", "Select file or folder", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        homeButton->setToolTip(QApplication::translate("mp3Dialog", "Go Home", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        homeButton->setText(QApplication::translate("mp3Dialog", "Go Home", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("mp3Dialog", "Convert Settings", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("mp3Dialog", "Action", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("mp3Dialog", "From codepage", 0, QApplication::UnicodeUTF8));
        comboBox_action->clear();
        comboBox_action->insertItems(0, QStringList()
         << QApplication::translate("mp3Dialog", "Convert", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Fix broken UTF", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        comboBox_action->setToolTip(QApplication::translate("mp3Dialog", "Select action from combo box", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        comboBox_codepage->setToolTip(QApplication::translate("mp3Dialog", "What codepage tags will be converted from?", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBox->setTitle(QApplication::translate("mp3Dialog", "ID3v1", 0, QApplication::UnicodeUTF8));
        comboGenreV1->clear();
        comboGenreV1->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("mp3Dialog", "Blues", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Classic Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Country", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Dance", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Disco", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Funk", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Grunge", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Hip-Hop", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Jazz", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Metal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "New Age", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Oldies", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Other", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Pop", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "R&B", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Rap", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Reggae", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Techno", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Industrial", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Alternative", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Ska", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Death Metal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Pranks", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Soundtrack", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Euro-Techno", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Ambient", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Trip-Hop", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Vocal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Jazz+Funk", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Fusion", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Trance", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Classical", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Instrumental", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Acid", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "House", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Game", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Sound Clip", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Gospel", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Noise", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Alt. Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Bass", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Soul", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Punk", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Space", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Meditative", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Instrumental Pop", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Instrumental Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Ethnic", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Gothic", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Darkwave", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Techno-Industrial", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Electronic", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Pop-Folk", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Eurodance", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Dream", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Southern Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Comedy", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Cult", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Gangsta Rap", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Top 40", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Christian Rap", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Pop/Funk", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Jungle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Native American", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Cabaret", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "New Wave", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Psychedelic", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Rave", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Showtunes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Trailer", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Lo-Fi", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Tribal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Acid Punk", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Acid Jazz", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Polka", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Retro", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Musical", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Rock & Roll", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Hard Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Folk", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Folk/Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "National Folk", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Swing", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Fast-Fusion", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Bebob", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Latin", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Revival", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Celtic", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Bluegrass", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Avantgarde", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Gothic Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Progressive Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Psychedelic Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Symphonic Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Slow Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Big Band", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Chorus", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Easy Listening", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Acoustic", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Humour", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Speech", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Chanson", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Opera", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Chamber Music", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Sonata", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Symphony", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Booty Bass", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Primus", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Porn Groove", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Satire", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Slow Jam", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Club", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Tango", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Samba", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Folklore", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Ballad", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Power Ballad", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Rhythmic Soul", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Freestyle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Duet", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Punk Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Drum Solo", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "A Cappella", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Euro-House", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Dance Hall", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Goa", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Drum & Bass", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Club-House", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Hardcore", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Terror", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Indie", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "BritPop", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Negerpunk", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Polsk Punk", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Beat", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Christian Gangsta Rap", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Heavy Metal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Black Metal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Crossover", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Contemporary Christian", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Christian Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Merengue", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Salsa", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Thrash Metal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Anime", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "JPop", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Synthpop", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("mp3Dialog", "Title", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("mp3Dialog", "Artist", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("mp3Dialog", "Album", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("mp3Dialog", "Genre", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("mp3Dialog", "Year", 0, QApplication::UnicodeUTF8));
        lineEditYearV1->setInputMask(QApplication::translate("mp3Dialog", "0000; ", 0, QApplication::UnicodeUTF8));
        lineEditYearV1->setText(QString());
        label_4->setText(QApplication::translate("mp3Dialog", "Comment", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_doTitle1->setToolTip(QApplication::translate("mp3Dialog", "Convert", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_doTitle1->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_doArtist1->setToolTip(QApplication::translate("mp3Dialog", "Convert", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_doArtist1->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_doAlbum1->setToolTip(QApplication::translate("mp3Dialog", "Convert", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_doAlbum1->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_doComment1->setToolTip(QApplication::translate("mp3Dialog", "Convert", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_doComment1->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_reloadTitle1->setToolTip(QApplication::translate("mp3Dialog", "Reload", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_reloadTitle1->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_reloadArtist1->setToolTip(QApplication::translate("mp3Dialog", "Reload", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_reloadArtist1->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_reloadAlbum1->setToolTip(QApplication::translate("mp3Dialog", "Reload", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_reloadAlbum1->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_reloadComment1->setToolTip(QApplication::translate("mp3Dialog", "Reload", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_reloadComment1->setText(QString());
#ifndef QT_NO_TOOLTIP
        v1tov2->setToolTip(QApplication::translate("mp3Dialog", "Copy ID3v1 tags into ID3v2", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        v1tov2->setText(QApplication::translate("mp3Dialog", "ID3v1 -> ID3v2", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("mp3Dialog", "ID3v2", 0, QApplication::UnicodeUTF8));
        comboGenreV2->clear();
        comboGenreV2->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("mp3Dialog", "Blues", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Classic Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Country", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Dance", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Disco", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Funk", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Grunge", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Hip-Hop", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Jazz", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Metal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "New Age", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Oldies", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Other", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Pop", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "R&B", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Rap", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Reggae", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Techno", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Industrial", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Alternative", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Ska", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Death Metal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Pranks", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Soundtrack", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Euro-Techno", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Ambient", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Trip-Hop", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Vocal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Jazz+Funk", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Fusion", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Trance", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Classical", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Instrumental", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Acid", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "House", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Game", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Sound Clip", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Gospel", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Noise", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Alt. Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Bass", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Soul", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Punk", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Space", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Meditative", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Instrumental Pop", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Instrumental Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Ethnic", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Gothic", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Darkwave", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Techno-Industrial", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Electronic", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Pop-Folk", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Eurodance", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Dream", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Southern Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Comedy", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Cult", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Gangsta Rap", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Top 40", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Christian Rap", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Pop/Funk", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Jungle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Native American", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Cabaret", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "New Wave", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Psychedelic", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Rave", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Showtunes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Trailer", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Lo-Fi", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Tribal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Acid Punk", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Acid Jazz", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Polka", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Retro", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Musical", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Rock & Roll", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Hard Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Folk", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Folk/Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "National Folk", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Swing", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Fast-Fusion", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Bebob", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Latin", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Revival", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Celtic", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Bluegrass", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Avantgarde", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Gothic Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Progressive Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Psychedelic Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Symphonic Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Slow Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Big Band", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Chorus", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Easy Listening", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Acoustic", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Humour", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Speech", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Chanson", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Opera", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Chamber Music", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Sonata", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Symphony", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Booty Bass", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Primus", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Porn Groove", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Satire", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Slow Jam", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Club", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Tango", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Samba", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Folklore", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Ballad", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Power Ballad", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Rhythmic Soul", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Freestyle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Duet", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Punk Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Drum Solo", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "A Cappella", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Euro-House", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Dance Hall", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Goa", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Drum & Bass", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Club-House", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Hardcore", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Terror", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Indie", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "BritPop", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Negerpunk", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Polsk Punk", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Beat", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Christian Gangsta Rap", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Heavy Metal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Black Metal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Crossover", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Contemporary Christian", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Christian Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Merengue", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Salsa", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Thrash Metal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Anime", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "JPop", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mp3Dialog", "Synthpop", 0, QApplication::UnicodeUTF8)
        );
        label_12->setText(QApplication::translate("mp3Dialog", "Title", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("mp3Dialog", "Artist", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("mp3Dialog", "Album", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("mp3Dialog", "Genre", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("mp3Dialog", "Year", 0, QApplication::UnicodeUTF8));
        lineEditYearV2->setInputMask(QApplication::translate("mp3Dialog", "0000; ", 0, QApplication::UnicodeUTF8));
        lineEditYearV2->setText(QString());
        label_7->setText(QApplication::translate("mp3Dialog", "Comment", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        v2tov1->setToolTip(QApplication::translate("mp3Dialog", "Copy ID3v2 tags into ID3v1", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        v2tov1->setText(QApplication::translate("mp3Dialog", "ID3v2 -> ID3v1", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ButtonSaveTags->setToolTip(QApplication::translate("mp3Dialog", "Save selected tags in file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ButtonSaveTags->setText(QApplication::translate("mp3Dialog", "Save Tags", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        checkBox_ID3v1->setToolTip(QApplication::translate("mp3Dialog", "Save ID3v1 tags or remove them", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        checkBox_ID3v1->setText(QApplication::translate("mp3Dialog", "ID3v1", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        checkBox_ID3v2->setToolTip(QApplication::translate("mp3Dialog", "Save ID3v2 tags or remove them", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        checkBox_ID3v2->setText(QApplication::translate("mp3Dialog", "ID3v2", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_reloadTitle2->setToolTip(QApplication::translate("mp3Dialog", "Reload", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_reloadTitle2->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_reloadArtist2->setToolTip(QApplication::translate("mp3Dialog", "Reload", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_reloadArtist2->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_reloadAlbum2->setToolTip(QApplication::translate("mp3Dialog", "Reload", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_reloadAlbum2->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_reloadComment2->setToolTip(QApplication::translate("mp3Dialog", "Reload", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_reloadComment2->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_doTitle2->setToolTip(QApplication::translate("mp3Dialog", "Convert", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_doTitle2->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_doArtist2->setToolTip(QApplication::translate("mp3Dialog", "Convert", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_doArtist2->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_doAlbum2->setToolTip(QApplication::translate("mp3Dialog", "Convert", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_doAlbum2->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_doComment2->setToolTip(QApplication::translate("mp3Dialog", "Convert", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_doComment2->setText(QString());
#ifndef QT_NO_TOOLTIP
        groupBox_3->setToolTip(QApplication::translate("mp3Dialog", "Save selected tags from ID3v2 group in all files in current directory", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBox_3->setTitle(QApplication::translate("mp3Dialog", "Save for all mp3 files in folder", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        GenreAllFiles->setToolTip(QApplication::translate("mp3Dialog", "Use this Genre tag for all files", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        GenreAllFiles->setText(QApplication::translate("mp3Dialog", "Genre", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        GroupAllFiles->setToolTip(QApplication::translate("mp3Dialog", "Use this Artist tag for all files", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        GroupAllFiles->setText(QApplication::translate("mp3Dialog", "Artist", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        AlbumAllfiles->setToolTip(QApplication::translate("mp3Dialog", "Use this Album tag for all files", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        AlbumAllfiles->setText(QApplication::translate("mp3Dialog", "Album", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        YearAllfiles->setToolTip(QApplication::translate("mp3Dialog", "Use this Year tag for all files", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        YearAllfiles->setText(QApplication::translate("mp3Dialog", "Year", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        CommentAllFiles->setToolTip(QApplication::translate("mp3Dialog", "Use this Comment tag for all files", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        CommentAllFiles->setText(QApplication::translate("mp3Dialog", "Comment", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        SaveAllFiles->setToolTip(QApplication::translate("mp3Dialog", "Save selected tags for all files", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        SaveAllFiles->setText(QApplication::translate("mp3Dialog", "Save All", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("mp3Dialog", "Convert codepage for all mp3 files in folder", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        CovertForAll->setToolTip(QApplication::translate("mp3Dialog", "Convert selected groups of tags for all files in current directory", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        CovertForAll->setText(QApplication::translate("mp3Dialog", "Convert", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        checkBox_allID3v1->setToolTip(QApplication::translate("mp3Dialog", "Convert ID3v1 tags or keep them as is", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        checkBox_allID3v1->setText(QApplication::translate("mp3Dialog", "Convert ID3v1", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        checkBox_allID3v2->setToolTip(QApplication::translate("mp3Dialog", "Convert ID3v2 tags or keep them as is", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        checkBox_allID3v2->setText(QApplication::translate("mp3Dialog", "Convert ID3v2", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("mp3Dialog", "&Menu", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("mp3Dialog", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mp3Dialog: public Ui_mp3Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KCMP3TAG_H
