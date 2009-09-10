 CONFIG       += release
 TEMPLATE      = lib
 CONFIG       += plugin
 INCLUDEPATH  += ../../src ../../include
 HEADERS       = ../../src/player_ffmpeg.h \
                 ../../src/player.h
 SOURCES       = ../../src/player_ffmpeg.cpp
 TARGET        = $$qtLibraryTarget(player_ffmpeg)

include(../../qmakeroot.pri)
include(../plugins_path-$${QT_ARCH}.pri)

win32 {
    MSVC {
        CONFIG += embed_manifest_dll
        DESTDIR = ../../win32-vs/plugins
    } else {
        DESTDIR = ../../win32/plugins
    }
    INCLUDEPATH += ../../ffmpeg/include
    LIBS += ../../ffmpeg/lib/avcodec.lib \
	../../ffmpeg/lib/avformat.lib \
	../../ffmpeg/lib/avutil.lib 

    INCLUDEPATH += ../../SDL-1.2.13/include
    LIBS += ../../SDL-1.2.13/lib/SDL.lib
}

unix {
    DESTDIR = ../../unix/plugins
    CONFIG += link_pkgconfig
    CONFIG += ffmpeg
    PKGCONFIG += libavcodec libavformat libavutil sdl
    INSTALLS += target
}

OBJECTS_DIR = $${DESTDIR}/../obj
MOC_DIR = $${DESTDIR}/../obj
RCC_DIR = $${DESTDIR}/../obj
