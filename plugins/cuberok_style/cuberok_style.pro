 CONFIG       += release
 TEMPLATE      = lib
 CONFIG       += plugin
 INCLUDEPATH  += ../../src ../../include
 HEADERS       = ../../src/style.h
 SOURCES       = ../../src/style.cpp
 TARGET        = $$qtLibraryTarget(cuberok_style)

#REQUIRES += "contains(styles, motif)"

include(../../qmakeroot.pri)

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
#    target.path = /lib/cuberok
    include(../plugins_path-$${QT_ARCH}.pri)
    INSTALLS += target
}

OBJECTS_DIR = $${DESTDIR}/../obj
MOC_DIR = $${DESTDIR}/../obj
RCC_DIR = $${DESTDIR}/../obj
