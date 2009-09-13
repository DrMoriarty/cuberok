 QT += xml
 CONFIG       += release
 TEMPLATE      = lib
 CONFIG       += plugin static
 INCLUDEPATH  += ../../src ../../include
 HEADERS       = ../../src/tageditor.h ../../src/console.h \
 	../../src/playlist.h \
 	playlistview.h tageditor.h
#    ../../src/playlistview_wa.h
 SOURCES       = playlistview.cpp tageditor.cpp
 FORMS += tageditor.ui
#                 ../../src/playlistview_wa.cpp
 TARGET        = $$qtLibraryTarget(playlist_standard)

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

OBJECTS_DIR = $${DESTDIR}/../obj
MOC_DIR = $${DESTDIR}/../obj
RCC_DIR = $${DESTDIR}/../obj
