 CONFIG       += release
 TEMPLATE      = lib
 CONFIG       += plugin static
 INCLUDEPATH  += ../../src
 HEADERS       = ../../src/player_void.h
 SOURCES       = ../../src/player_void.cpp
 TARGET        = $$qtLibraryTarget(player_void)

include(../../qmakeroot.pri)

win32 {
    DESTDIR = ../../win32/plugins
}

unix {
    DESTDIR = ../../unix/plugins
}

OBJECTS_DIR = $${DESTDIR}/../obj
MOC_DIR = $${DESTDIR}/../obj
RCC_DIR = $${DESTDIR}/../obj
