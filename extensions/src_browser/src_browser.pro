 QT += xml network
 CONFIG       += release
 TEMPLATE      = lib
 CONFIG       += plugin static precompile_header
 PRECOMPILED_HEADER = ../../include/stable.h
 INCLUDEPATH  += ../../src ../../include
 HEADERS       = \
 	../../include/interfaces.h \
 	browser.h \
 	src_browser.h \
	browser_viewer.h \
	jamendo_browser.h \
	magnatune_browser.h

 SOURCES       = src_browser.cpp browser_viewer.cpp jamendo_browser.cpp magnatune_browser.cpp
 FORMS         = browser_viewer.ui
 TARGET        = $$qtLibraryTarget(src_browser)

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

OBJECTS_DIR = $${DESTDIR}/../obj/src_browser
MOC_DIR = $${DESTDIR}/../obj
RCC_DIR = $${DESTDIR}/../obj
