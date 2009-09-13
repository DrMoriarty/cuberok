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

INCLUDEPATH += ../include

# Input
HEADERS += \
           ../include/global.h \
           ../include/tagentry.h \
           ../include/interfaces.h \
           aboutdialog.h \
           browser.h \
           browser_viewer.h \
           collectionsettings.h \
           collectionfiller.h \
           collectionview.h \
           comboboxdelegate.h \
           console.h \
           consoleview.h \
           cuberok.h \
           cuecontrol.h \
           database.h \
           downloader.h \
           extensionproxy.h \
           extensionsettings.h \
           firststartwizard.h \
           importcollection.h \
#           info.h \
#           infowidget.h \
#           infowindow.h \
           indicator.h \
           jamendo_browser.h \
#           lastfm.h \
           libraryview.h \
#           librefm.h \
           lookandfeel.h \
           lyricwiki.h \
           magnatune_browser.h \
           main.h \
           marklistwidget.h \
           messagewindow.h \
           myapplication.h \
           player.h \
           player_manager.h \
           playlist.h \
           playlistcontainer.h \
           playlistmodel.h \
           playlistsettings.h \
           progressbar.h \
           settings.h \
           sqledit.h \
           stardelegate.h \
           stareditor.h \
           starrating.h \
@           tageditor.h \
           tagger.h \
           url_open.h \
	   ../QFreeDesktopMime/src/freedesktopmime.h \
	   ksqueezedtextlabel.h

FORMS += aboutdialog.ui \
         collectionsettings.ui \
         cuberok.ui \
         lookandfeel.ui \
#         tageditor.ui \
         settings.ui \
         url_open.ui \
         authenticationdialog.ui \
         console.ui \
#         info.ui \
#         infowindow.ui \
         sqledit.ui \
         browser_viewer.ui \
         importcollection.ui \
         firststartwizard.ui \
         cuecontrol.ui 
TRANSLATIONS = ../translations/cuberok_ru.ts

SOURCES += aboutdialog.cpp \
           browser_viewer.cpp \
           collectionsettings.cpp \
           collectionfiller.cpp \
           collectionview.cpp \
           comboboxdelegate.cpp \
           console.cpp \
           consoleview.cpp \
           cuberok.cpp \
           cuecontrol.cpp \
           database.cpp \
           downloader.cpp \
           extensionproxy.cpp \
           extensionsettings.cpp \
           firststartwizard.cpp \
           importcollection.cpp \
#           info.cpp \
#           infowidget.cpp \
#           infowindow.cpp \
           indicator.cpp \
           jamendo_browser.cpp \
#           lastfm.cpp \
           libraryview.cpp \
#           librefm.cpp \
           lookandfeel.cpp \
           lyricwiki.cpp \
           magnatune_browser.cpp \
           main.cpp \
           marklistwidget.cpp \
           messagewindow.cpp \
           myapplication.cpp \
           player_manager.cpp \
           playlistcontainer.cpp \
           playlistmodel.cpp \
           playlistsettings.cpp \
           progressbar.cpp \
           settings.cpp \
           sqledit.cpp \
           stardelegate.cpp \
           stareditor.cpp \
           starrating.cpp \
#           tageditor.cpp \
           tagger.cpp \
           url_open.cpp \
	   ../QFreeDesktopMime/src/freedesktopmime.cpp \
	   ksqueezedtextlabel.cpp
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

#static plugins
LIBS += -L$${DESTDIR}/plugins -lplayer_void -lplaylist_standard -lscrobbler_librefm

macx {
    QT += phonon
    LIBS += -L$${DESTDIR}/plugins -lplayer_phonon
}

OBJECTS_DIR = $${DESTDIR}/obj
MOC_DIR = $${DESTDIR}/obj
RCC_DIR = $${DESTDIR}/obj
UI_DIR = .

