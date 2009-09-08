 QT           += phonon
 CONFIG       += release
 TEMPLATE      = lib
 CONFIG       += plugin
 INCLUDEPATH  += ../../src ../../include
 HEADERS       = ../../src/player_phonon.h \
                 ../../src/player.h
 SOURCES       = ../../src/player_phonon.cpp
 TARGET        = $$qtLibraryTarget(player_phonon)

include(../../qmakeroot.pri)

win32 {
    MSVC {
        CONFIG -= embed_manifest_dll
        DESTDIR = ../../win32-vs/plugins
    } else {
        DESTDIR = ../../win32/plugins
    }
    #INCLUDEPATH += ../../audiere/include
    #LIBS += ../../audiere/lib/audiere.lib
}

unix {
    macx {
        CONFIG += static
    }
    DESTDIR = ../../unix/plugins
    #INCLUDEPATH += $$system(audiere-config --cxxflags)
    #LIBS += $$system(audiere-config --libs)
    PKGCONFIG += phonon
#    target.path = /lib/cuberok
    include(../plugins_path-$${QT_ARCH}.pri)
    INSTALLS += target
}


OBJECTS_DIR = $${DESTDIR}/../obj
MOC_DIR = $${DESTDIR}/../obj
RCC_DIR = $${DESTDIR}/../obj
