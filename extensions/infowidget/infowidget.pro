 QT += xml network
 CONFIG       += release
 TEMPLATE      = lib
 CONFIG       += plugin static precompile_header
 PRECOMPILED_HEADER = ../../include/stable.h
 INCLUDEPATH  += ../../src ../../include
 HEADERS       = \
		../../include/interfaces.h \
 		info.h \
		infowindow.h infowidget.h

 SOURCES       = info.cpp infowindow.cpp infowidget.cpp
 FORMS += info.ui infowindow.ui
 TARGET        = $$qtLibraryTarget(infowidget)

include(../../qmakeroot.pri)

win32 {
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
    MSVC {
        DESTDIR = ../../win32-vs/plugins
    } else {
        DESTDIR = ../../win32/plugins
    }
}

unix {
    DESTDIR = ../../unix/plugins
    CONFIG += link_pkgconfig
    PKGCONFIG += taglib
}
mac {
    INCLUDEPATH += . \
               /usr/local/include/taglib
    LIBS += -L/usr/local/lib  -ltag
    ICON = ../images/cuberok.icns
}

OBJECTS_DIR = $${DESTDIR}/../obj/infowidget
MOC_DIR = $${DESTDIR}/../obj
RCC_DIR = $${DESTDIR}/../obj
