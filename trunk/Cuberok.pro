CONFIG += qt 
QT += sql xml

TEMPLATE = app
TARGET = 
DEPENDPATH += . 
# Input
HEADERS += src/aboutdialog.h \
           src/collectionview.h \
           src/cuberok.h \
           src/database.h \
           src/indicator.h \
           src/lookandfeel.h \
           src/main.h \
           src/player.h \
           src/player_void.h \
           src/playlistcontainer.h \
           src/playlistmodel.h \
           src/playlistsettings.h \
           src/playlistview.h \
           src/progressbar.h \
           src/settings.h \
           src/stardelegate.h \
           src/stareditor.h \
           src/starrating.h \
           src/tageditor.h \
           src/tagger.h 

FORMS += src/aboutdialog.ui src/collectionview.ui src/cuberok.ui src/lookandfeel.ui src/tageditor.ui src/settings.ui
TRANSLATIONS = cuberok_ru.ts

SOURCES += src/aboutdialog.cpp \
           src/collectionview.cpp \
           src/cuberok.cpp \
           src/database.cpp \
           src/indicator.cpp \
           src/lookandfeel.cpp \
           src/main.cpp \
           src/player.cpp \
           src/player_void.cpp \
           src/playlistcontainer.cpp \
           src/playlistmodel.cpp \
           src/playlistsettings.cpp \
           src/playlistview.cpp \
           src/progressbar.cpp \
           src/settings.cpp \
           src/stardelegate.cpp \
           src/stareditor.cpp \
           src/starrating.cpp \
           src/tageditor.cpp \
           src/tagger.cpp
RESOURCES += src/resource.qrc

win32 {
    DESTDIR = ./win32
    TARGET = Cuberok
    INCLUDEPATH += . \
               mpg123 \
               taglib/include \
               taglib/include/toolkit \
               taglib/include/mpeg \
               taglib/include/mpeg/id3v2
    LIBS += taglib/lib/release/libtaglib.a
    exists(./audiere/lib/audiere.lib) {
	CONFIG += audiere
    }
    exists(./gstreamer/lib/libgstreamer-0.10.lib) {
    	CONFIG += gstreamer
    }
    audiere {
        INCLUDEPATH += audiere/include
    	LIBS += ./audiere/lib/audiere.lib
    }
    gstreamer {
        INCLUDEPATH += gstreamer/include gstreamer/include/glib-2.0
    	LIBS += gstreamer/lib/libgstreamer-0.10.lib gstreamer/lib/gobject-2.0.lib
    }
}
unix {
    DESTDIR = ./unix
    TARGET = cuberok
    CONFIG += link_pkgconfig
    PKGCONFIG += taglib
    system(audiere-config --version) {
	CONFIG += audiere
    }
    system(pkg-config --modversion gstreamer-0.10 2>/dev/null) {
	CONFIG += gstreamer
	PKGCONFIG += gstreamer-0.10
    }
    # other engines
    audiere {
	INCLUDEPATH += $$system(audiere-config --cxxflags)
        LIBS += $$system(audiere-config --libs)
    }
    target.path = /usr/bin
    documentation.path = /usr/share/doc/cuberok
    documentation.files = README ChangeLog
    locale.path = /usr/share/cuberok/locale
    locale.files = locale/*.qm
    INSTALLS += target documentation locale
}

audiere {
    DEFINES += AUDIERE
    message(using audiere backend)
    HEADERS += src/player_audiere.h 
    SOURCES += src/player_audiere.cpp
}

gstreamer {
    DEFINES += GSTREAMER
    message(using gstreamer backend)
    HEADERS += src/player_gst.h
    SOURCES += src/player_gst.cpp
}

OBJECTS_DIR = $${DESTDIR}/obj
MOC_DIR = $${DESTDIR}/obj
RCC_DIR = $${DESTDIR}/obj
UI_DIR = src