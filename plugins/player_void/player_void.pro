 CONFIG       += release
 TEMPLATE      = lib
 CONFIG       += plugin static
 INCLUDEPATH  += ../../src ../../include
 HEADERS       = ../../src/player_void.h
 SOURCES       = ../../src/player_void.cpp
 TARGET        = $$qtLibraryTarget(player_void)

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
