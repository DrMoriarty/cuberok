 CONFIG       += release
 TEMPLATE      = lib
 CONFIG       += plugin static
 INCLUDEPATH  += ../../src ../../include
 HEADERS       = \
 	../../src/playlist.h \
 	../../src/playlistview.h 
#    ../../src/playlistview_wa.h
 SOURCES       = ../../src/playlistview.cpp 
#                 ../../src/playlistview_wa.cpp
 TARGET        = $$qtLibraryTarget(playlist_standard)

include(../../qmakeroot.pri)

win32 {
    MSVC {
        DESTDIR = ../../win32-vs/plugins
    } else {
        DESTDIR = ../../win32/plugins
    }
}

unix {
    DESTDIR = ../../unix/plugins
}

OBJECTS_DIR = $${DESTDIR}/../obj
MOC_DIR = $${DESTDIR}/../obj
RCC_DIR = $${DESTDIR}/../obj
