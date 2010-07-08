 CONFIG       += release
 TEMPLATE      = lib
 CONFIG       += plugin
 INCLUDEPATH  += ../../src ../../include
 HEADERS       = ../../src/player_audiere.h \
                 ../../src/player.h
 SOURCES       = ../../src/player_audiere.cpp
 TARGET        = $$qtLibraryTarget(player_audiere)

include(../../qmakeroot.pri)
include(../plugins_path-$${QT_ARCH}.pri)

win32 {
    MSVC {
        CONFIG += embed_manifest_dll
        DESTDIR = ../../win32-vs/plugins
    } else {
        DESTDIR = ../../win32/plugins
    }
    INCLUDEPATH += ../../audiere/include
    LIBS += ../../audiere/lib/audiere.lib
}

unix {
    DESTDIR = ../../unix/plugins
    INCLUDEPATH += $$system(audiere-config --cxxflags)
    LIBS += $$system(audiere-config --libs)
    #plugin_audiere.files = ../../unix/plugins/libplayer_audiere.so
    INSTALLS += target
}

OBJECTS_DIR = $${DESTDIR}/../obj/player_audiere
MOC_DIR = $${DESTDIR}/../obj
RCC_DIR = $${DESTDIR}/../obj
