 QT += sql xml network
 CONFIG       += release
 TEMPLATE      = lib
 CONFIG       += plugin static
 INCLUDEPATH  += ../../src ../../include
 HEADERS       = \
 	../../include/interfaces.h \
	src_collection.h \
 	database.h \
    collectionview.h \
    collectionfiller.h \
    collectionsettings.h \
    sqledit.h \
    collectionwidget.h

 SOURCES       = src_collection.cpp database.cpp collectionview.cpp collectionfiller.cpp collectionsettings.cpp sqledit.cpp collectionwidget.cpp
 FORMS         = collectionwidget.ui collectionsettings.ui sqledit.ui
 TARGET        = $$qtLibraryTarget(src_collection)

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
