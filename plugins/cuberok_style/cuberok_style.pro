 CONFIG       += release
 TEMPLATE      = lib
 CONFIG       += plugin
 INCLUDEPATH  += ../../src ../../include
 HEADERS       = ../../src/style.h
 SOURCES       = ../../src/style.cpp
 TARGET        = $$qtLibraryTarget(cuberok_style)

#REQUIRES += "contains(styles, motif)"

include(../../qmakeroot.pri)
include(../plugins_path-$${QT_ARCH}.pri)

win32 {
    MSVC {
        CONFIG -= embed_manifest_dll
        DESTDIR = ../../win32-vs/styles
    } else {
        DESTDIR = ../../win32/styles
    }
}

unix {
    DESTDIR = ../../unix/styles
    INSTALLS += target
}

OBJECTS_DIR = $${DESTDIR}/../obj/cuberok_style
MOC_DIR = $${DESTDIR}/../obj
RCC_DIR = $${DESTDIR}/../obj
