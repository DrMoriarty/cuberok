CONFIG += qt 
QT += sql

TEMPLATE = app
TARGET = 
DEPENDPATH += . 
# Input
HEADERS += aboutdialog.h \
           collectionview.h \
           cuberok.h \
           database.h \
           indicator.h \
           lookandfeel.h \
           main.h \
           player.h \
           playlistcontainer.h \
           playlistmodel.h \
           playlistsettings.h \
           playlistview.h \
           progressbar.h \
           stardelegate.h \
           stareditor.h \
           starrating.h \
           tageditor.h \
           tagger.h 

FORMS += aboutdialog.ui collectionview.ui cuberok.ui lookandfeel.ui tageditor.ui

SOURCES += aboutdialog.cpp \
           collectionview.cpp \
           cuberok.cpp \
           database.cpp \
           indicator.cpp \
           lookandfeel.cpp \
           main.cpp \
           player.cpp \
           playlistcontainer.cpp \
           playlistmodel.cpp \
           playlistsettings.cpp \
           playlistview.cpp \
           progressbar.cpp \
           stardelegate.cpp \
           stareditor.cpp \
           starrating.cpp \
           tageditor.cpp \
           tagger.cpp
RESOURCES += resource.qrc

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
}
OBJECTS_DIR = $${DESTDIR}/obj
MOC_DIR = $${DESTDIR}/obj
RCC_DIR = $${DESTDIR}/obj
