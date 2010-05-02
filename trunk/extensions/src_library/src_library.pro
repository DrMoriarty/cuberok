 QT += sql xml network
 CONFIG       += release
 TEMPLATE      = lib
 CONFIG       += plugin static precompile_header
 PRECOMPILED_HEADER = ../../include/stable.h
 INCLUDEPATH  += ../../src ../../include
 HEADERS       = \
 	../../include/interfaces.h \
	src_library.h \
 	library_db.h \
    libraryview.h \
    libraryfiller.h \
    librarywidget.h

 SOURCES       = src_library.cpp library_db.cpp libraryview.cpp libraryfiller.cpp librarywidget.cpp
 FORMS         = librarywidget.ui
 TARGET        = $$qtLibraryTarget(src_library)

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
