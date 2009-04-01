 CONFIG       += release
 TEMPLATE      = lib
 CONFIG       += plugin
 INCLUDEPATH  += ../../src
 HEADERS       = ../../src/player_audiere.h \
                 ../../src/player.h
 SOURCES       = ../../src/player_audiere.cpp
 TARGET        = $$qtLibraryTarget(player_audiere)

win32 {
    DESTDIR = ../../win32/plugins
    INCLUDEPATH += ../../audiere/include
    LIBS += ../../audiere/lib/audiere.lib
}

unix {
    DESTDIR = ../../unix/plugins
    INCLUDEPATH += $$system(audiere-config --cxxflags)
    LIBS += $$system(audiere-config --libs)
    #plugin_audiere.files = ../../unix/plugins/libplayer_audiere.so
#    target.path = /lib/cuberok
    include(../plugins_path-$${QT_ARCH}.pri)
    INSTALLS += target
}

OBJECTS_DIR = $${DESTDIR}/../obj
MOC_DIR = $${DESTDIR}/../obj
RCC_DIR = $${DESTDIR}/../obj
