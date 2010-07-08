 QT += xml network
 CONFIG       += release
 TEMPLATE      = lib
 CONFIG       += plugin static precompile_header
 PRECOMPILED_HEADER = ../../include/stable.h
 INCLUDEPATH  += ../../src ../../include
 HEADERS       = \
 	../../include/interfaces.h \
 	librefm.h \
    librefm_settings.h

 SOURCES       = librefm.cpp librefm_settings.cpp
 TARGET        = $$qtLibraryTarget(scrobbler_librefm)

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

OBJECTS_DIR = $${DESTDIR}/../obj/scrobbler_librefm
MOC_DIR = $${DESTDIR}/../obj
RCC_DIR = $${DESTDIR}/../obj
