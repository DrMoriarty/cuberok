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

#           src/player_void.h \
#           src/player_void.cpp \
# Input
HEADERS += aboutdialog.h \
           browser.h \
           browser_viewer.h \
           collectionsettings.h \
           collectionfiller.h \
           collectionview.h \
           console.h \
           cuberok.h \
           database.h \
           downloader.h \
           firststartwizard.h \
           importcollection.h \
           info.h \
           infowidget.h \
           infowindow.h \
           indicator.h \
           jamendo_browser.h \
           lastfm.h \
           libraryview.h \
           librefm.h \
           lookandfeel.h \
           lyricwiki.h \
           magnatune_browser.h \
           main.h \
           myapplication.h \
           player.h \
           player_manager.h \
           playlistcontainer.h \
           playlistmodel.h \
           playlistsettings.h \
           playlistview.h \
           progressbar.h \
           settings.h \
           sqledit.h \
           stardelegate.h \
           stareditor.h \
           starrating.h \
           tageditor.h \
           tagger.h \
           url_open.h

FORMS += aboutdialog.ui \
         collectionsettings.ui \
         cuberok.ui \
         lookandfeel.ui \
         tageditor.ui \
         settings.ui \
         url_open.ui \
         authenticationdialog.ui \
         console.ui \
         info.ui \
         infowindow.ui \
         sqledit.ui \
         browser_viewer.ui \
         importcollection.ui \
         firststartwizard.ui
TRANSLATIONS = ../translations/cuberok_ru.ts

SOURCES += aboutdialog.cpp \
           browser_viewer.cpp \
           collectionsettings.cpp \
           collectionfiller.cpp \
           collectionview.cpp \
           console.cpp \
           cuberok.cpp \
           database.cpp \
           downloader.cpp \
           firststartwizard.cpp \
           importcollection.cpp \
           info.cpp \
           infowidget.cpp \
           infowindow.cpp \
           indicator.cpp \
           jamendo_browser.cpp \
           lastfm.cpp \
           libraryview.cpp \
           librefm.cpp \
           lookandfeel.cpp \
           lyricwiki.cpp \
           magnatune_browser.cpp \
           main.cpp \
           myapplication.cpp \
           player_manager.cpp \
           playlistcontainer.cpp \
           playlistmodel.cpp \
           playlistsettings.cpp \
           playlistview.cpp \
           progressbar.cpp \
           settings.cpp \
           sqledit.cpp \
           stardelegate.cpp \
           stareditor.cpp \
           starrating.cpp \
           tageditor.cpp \
           tagger.cpp \
           url_open.cpp
RESOURCES += resource.qrc

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
    exists(../audiere/lib/audiere.lib) {
	CONFIG += audiere
    }
    exists(../gstreamer/lib/libgstreamer-0.10.lib) {
    	CONFIG += gstreamer
    }
    audiere {
#        INCLUDEPATH += ../audiere/include
#    	LIBS += ../audiere/lib/audiere.lib
    }
    gstreamer {
#        INCLUDEPATH += ../gstreamer/include ../gstreamer/include/glib-2.0
#    	LIBS += ../gstreamer/lib/libgstreamer-0.10.lib ../gstreamer/lib/gobject-2.0.lib "C:\Program Files\Mono-1.2.4\lib\libglib-2.0.dll.a"
    }
}
unix {
    DESTDIR = ../unix
    TARGET = cuberok
    CONFIG += link_pkgconfig
    PKGCONFIG += taglib
    system(audiere-config --version) {
	CONFIG += audiere
    }
    system(pkg-config --modversion gstreamer-0.10 2>/dev/null) {
	CONFIG += gstreamer
#	PKGCONFIG += gstreamer-0.10
    }
    # other engines
    audiere {
#	INCLUDEPATH += $$system(audiere-config --cxxflags)
#        LIBS += $$system(audiere-config --libs)
    }
    target.path = /bin
    documentation.path = /share/doc/cuberok
    documentation.files = README ChangeLog
#    locale.path = $$[QT_INSTALL_TRANSLATIONS]
    locale.path = /share/qt4/translations
    locale.files = ../translations/*.qm
    pixmap.path = /share/pixmaps
    pixmap.files = ../images/cuberok.xpm
    desktop.path = /share/applications
    desktop.files = ../cuberok.desktop
    INSTALLS += target documentation locale pixmap desktop
}

LIBS += -L$${DESTDIR}/plugins -lplayer_void

audiere {
    DEFINES += AUDIERE
#    LIBS += -lplayer_audiere
#    message(using audiere backend)
#    HEADERS += player_audiere.h 
#    SOURCES += player_audiere.cpp
}

gstreamer {
    DEFINES += GSTREAMER
#    message(using gstreamer backend)
#    HEADERS += player_gst.h
#    SOURCES += player_gst.cpp
}

OBJECTS_DIR = $${DESTDIR}/obj
MOC_DIR = $${DESTDIR}/obj
RCC_DIR = $${DESTDIR}/obj
UI_DIR = .

