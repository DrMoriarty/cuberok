 QT += xml network
 CONFIG       += release
 TEMPLATE      = lib
 CONFIG       += plugin static
 INCLUDEPATH  += ../../src ../../include
 HEADERS       = \
 	../../include/interfaces.h \
 	lastfm.h \
    lastfm_settings.h

 SOURCES       = lastfm.cpp lastfm_settings.cpp
 TARGET        = $$qtLibraryTarget(scrobbler_lastfm)

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
