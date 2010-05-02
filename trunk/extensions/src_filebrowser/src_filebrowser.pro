 QT += xml network
 CONFIG       += release
 TEMPLATE      = lib
 CONFIG       += plugin static precompile_header
 PRECOMPILED_HEADER = ../../include/stable.h
 INCLUDEPATH  += ../../src ../../include
 HEADERS       = \
 	../../include/interfaces.h \
 	filebrowser.h \
    filebrowserwidget.h \
    ksqueezedtextlabel.h \
    marklistwidget.h

 SOURCES       = filebrowser.cpp filebrowserwidget.cpp ksqueezedtextlabel.cpp marklistwidget.cpp
 FORMS         = filebrowser.ui
 TARGET        = $$qtLibraryTarget(src_filebrowser)

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
