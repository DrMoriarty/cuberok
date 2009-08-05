CONFIG += qt release
QT += sql xml network

TEMPLATE = app
TARGET = 
DEPENDPATH += . 

#QMAKE_CXXFLAGS_RELEASE -= -O2 
#QMAKE_CXXFLAGS_RELEASE += -Os -fno-builtin -fomit-frame-pointer
#QMAKE_CFLAGS_RELEASE -= -O2 
#QMAKE_CFLAGS_RELEASE += -Os -fno-builtin -fomit-frame-pointer 

include(../qmakeroot.pri)

include(../plugins/plugins_path-$${QT_ARCH}.pri)

# Input
HEADERS += ../src/aboutdialog.h \
           ../src/browser.h \
           ../src/browser_viewer.h \
           ../src/collectionsettings.h \
           ../src/collectionfiller.h \
           ../src/collectionview.h \
           ../src/comboboxdelegate.h \
           ../src/console.h \
           ../src/cuberok.h \
           ../src/cuecontrol.h \
           ../src/database.h \
           ../src/downloader.h \
           ../src/firststartwizard.h \
           ../src/importcollection.h \
           ../src/info.h \
           ../src/infowidget.h \
           ../src/infowindow.h \
           ../src/indicator.h \
           ../src/jamendo_browser.h \
           ../src/lastfm.h \
           ../src/libraryview.h \
           ../src/librefm.h \
           ../src/lookandfeel.h \
           ../src/lyricwiki.h \
           ../src/magnatune_browser.h \
           ../src/main.h \
           ../src/marklistwidget.h \
           ../src/messagewindow.h \
           ../src/myapplication.h \
           ../src/player.h \
           ../src/player_proxy.h \
           ../src/playlistcontainer.h \
           ../src/playlistmodel.h \
           ../src/playlistsettings.h \
           ../src/playlistview.h \
           ../src/progressbar.h \
           ../src/settings.h \
           ../src/sqledit.h \
           ../src/stardelegate.h \
           ../src/stareditor.h \
           ../src/starrating.h \
           ../src/tageditor.h \
           ../src/tagger.h \
           ../src/url_open.h \
	   ../QFreeDesktopMime/src/freedesktopmime.h

FORMS += ../src/aboutdialog.ui \
         ../src/collectionsettings.ui \
         ../src/cuberok.ui \
         ../src/lookandfeel.ui \
         ../src/tageditor.ui \
         ../src/settings.ui \
         ../src/url_open.ui \
         ../src/authenticationdialog.ui \
         ../src/console.ui \
         ../src/info.ui \
         ../src/infowindow.ui \
         ../src/sqledit.ui \
         ../src/browser_viewer.ui \
         ../src/importcollection.ui \
         ../src/firststartwizard.ui \
         ../src/cuecontrol.ui 
TRANSLATIONS = ../translations/cuberok_ru.ts

SOURCES += ../src/aboutdialog.cpp \
           ../src/browser_viewer.cpp \
           ../src/collectionsettings.cpp \
           ../src/collectionfiller.cpp \
           ../src/collectionview.cpp \
           ../src/comboboxdelegate.cpp \
           ../src/console.cpp \
           ../src/cuberok.cpp \
           ../src/cuecontrol.cpp \
           ../src/database.cpp \
           ../src/downloader.cpp \
           ../src/firststartwizard.cpp \
           ../src/importcollection.cpp \
           ../src/info.cpp \
           ../src/infowidget.cpp \
           ../src/infowindow.cpp \
           ../src/indicator.cpp \
           ../src/jamendo_browser.cpp \
           ../src/lastfm.cpp \
           ../src/libraryview.cpp \
           ../src/librefm.cpp \
           ../src/lookandfeel.cpp \
           ../src/lyricwiki.cpp \
           ../src/magnatune_browser.cpp \
           ../src/main.cpp \
           ../src/marklistwidget.cpp \
           ../src/messagewindow.cpp \
           ../src/myapplication.cpp \
           ../src/player_proxy.cpp \
           ../src/playlistcontainer.cpp \
           ../src/playlistmodel.cpp \
           ../src/playlistsettings.cpp \
           ../src/playlistview.cpp \
           ../src/progressbar.cpp \
           ../src/settings.cpp \
           ../src/sqledit.cpp \
           ../src/stardelegate.cpp \
           ../src/stareditor.cpp \
           ../src/starrating.cpp \
           ../src/tageditor.cpp \
           ../src/tagger.cpp \
           ../src/url_open.cpp \
	   ../QFreeDesktopMime/src/freedesktopmime.cpp
RESOURCES += ../src/resource.qrc

exists(../qtagconvert/src/KCmp3Tag.ui) {
    DEFINES += QTAGCONVERT
    FORMS += ../qtagconvert/src/KCmp3Tag.ui
    HEADERS += ../qtagconvert/src/KCmp3Tag.h
    SOURCES += ../qtagconvert/src/KCmp3Tag.cpp
    #RESOURCES += ../qtagconvert/images/resources.qrc
    RESOURCES += resource_full.qrc
}

win32 {
    RC_FILE = ../cuberok.rc
    MSVC {
        DESTDIR = ../win32-vs
    } else {
        DESTDIR = ../win32
    }
    TARGET = Cuberok
    INCLUDEPATH += . \
               ../taglib/include \
               ../taglib/include/toolkit \
               ../taglib/include/mpeg \
               ../taglib/include/mpeg/id3v2
    MSVC {
        CONFIG -= embed_manifest_exe
        LIBS += ../taglib/lib/release/tag.lib
    } else {
        LIBS += ../taglib/lib/release/libtaglib.a
    }
}
unix {
    DESTDIR = ../unix
    TARGET = cuberok
    CONFIG += link_pkgconfig
    PKGCONFIG += taglib
    target.path = /bin
    documentation.path = /share/doc/cuberok
    documentation.files = README ChangeLog
#    locale.path = $$[QT_INSTALL_TRANSLATIONS]
#    locale.path = /share/qt4/translations
    locale.path = /share/cuberok/locale
    locale.files = ../translations/*.qm
    pixmap.path = /share/pixmaps
    pixmap.files = ../images/cuberok.xpm
    desktop.path = /share/applications
    desktop.files = ../cuberok.desktop
    INSTALLS += target documentation locale pixmap desktop
}

mac {
    INCLUDEPATH += . \
               /usr/local/include/taglib
    LIBS += -L/usr/local/lib  -ltag
    ICON = ../images/cuberok.icns
}

LIBS += -L$${DESTDIR}/plugins -lplayer_void

macx {
    QT += phonon
    LIBS += -L$${DESTDIR}/plugins -lplayer_phonon
}

OBJECTS_DIR = $${DESTDIR}/obj
MOC_DIR = $${DESTDIR}/obj
RCC_DIR = $${DESTDIR}/obj
UI_DIR = .

