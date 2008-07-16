CONFIG += qt 
QT += sql

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
           src/playlistcontainer.h \
           src/playlistmodel.h \
           src/playlistsettings.h \
           src/playlistview.h \
           src/progressbar.h \
           src/stardelegate.h \
           src/stareditor.h \
           src/starrating.h \
           src/tageditor.h \
           src/tagger.h 

FORMS += src/aboutdialog.ui src/collectionview.ui src/cuberok.ui src/lookandfeel.ui src/tageditor.ui
TRANSLATIONS = cuberok_ru.ts

SOURCES += src/aboutdialog.cpp \
           src/collectionview.cpp \
           src/cuberok.cpp \
           src/database.cpp \
           src/indicator.cpp \
           src/lookandfeel.cpp \
           src/main.cpp \
           src/player.cpp \
           src/playlistcontainer.cpp \
           src/playlistmodel.cpp \
           src/playlistsettings.cpp \
           src/playlistview.cpp \
           src/progressbar.cpp \
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
    audiere {
	DEFINES += AUDIERE
	message(using audiere backend)
        INCLUDEPATH += audiere/include
    	LIBS += ./audiere/lib/audiere.lib
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
    # other engines
    audiere {
	DEFINES += AUDIERE
	message(using audiere backend)
	INCLUDEPATH += $$system(audiere-config --cxxflags)
        LIBS += $$system(audiere-config --libs)
    }
    target.path = /usr/bin
    documentation.path = /usr/share/doc/cuberok
    documentation.files = README ChangeLog
    locale.path = /usr/share/cuberok/locale
    locale.files = *.qm
    INSTALLS += target documentation locale
}
OBJECTS_DIR = $${DESTDIR}/obj
MOC_DIR = $${DESTDIR}/obj
RCC_DIR = $${DESTDIR}/obj
UI_DIR = src