 CONFIG       += release
 TEMPLATE      = lib
 CONFIG       += plugin
 INCLUDEPATH  += ../../src
 HEADERS       = ../../src/style.h
 SOURCES       = ../../src/style.cpp
 TARGET        = $$qtLibraryTarget(cuberok_style)

#REQUIRES += "contains(styles, motif)"

win32 {
    DESTDIR = ../../win32/styles
}

unix {
    DESTDIR = ../../unix/styles
    target.path = /lib/cuberok
    INSTALLS += target
}

OBJECTS_DIR = $${DESTDIR}/../obj
MOC_DIR = $${DESTDIR}/../obj
RCC_DIR = $${DESTDIR}/../obj
