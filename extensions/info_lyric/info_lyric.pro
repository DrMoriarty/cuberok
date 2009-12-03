 QT += xml network webkit
 CONFIG       += release
 TEMPLATE      = lib
 CONFIG       += plugin static
 INCLUDEPATH  += ../../src ../../include
 HEADERS       = \
 	../../include/interfaces.h \
 	lyric.h lyricwidget.h

 SOURCES       = lyric.cpp lyricwidget.cpp
 TARGET        = $$qtLibraryTarget(info_lyric)

include(../../qmakeroot.pri)

win32 {
    MSVC {
        DESTDIR = ../../win32-vs/plugins
    } else {
        DESTDIR = ../../win32/plugins
    }
    exists(../../yajl-1.0.5/include/yajl/yajl_parse.h) {
	INCLUDEPATH += ../../yajl-1.0.5/include/
	DEFINES += HAVE_YAJL
    }
}

unix {
    DESTDIR = ../../unix/plugins
    exists(/usr/include/yajl/yajl_parse.h) {
	DEFINES += HAVE_YAJL
    }
}

OBJECTS_DIR = $${DESTDIR}/../obj
MOC_DIR = $${DESTDIR}/../obj
RCC_DIR = $${DESTDIR}/../obj
