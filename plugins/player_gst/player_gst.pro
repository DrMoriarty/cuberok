 CONFIG       += release
 TEMPLATE      = lib
 CONFIG       += plugin
 INCLUDEPATH  += ../../src
 HEADERS       = ../../src/player_gst.h \
                 ../../src/player.h
 SOURCES       = ../../src/player_gst.cpp
 TARGET        = $$qtLibraryTarget(player_gst)

win32 {
    DESTDIR = ../../win32/plugins
    INCLUDEPATH += ../../gstreamer/include ../../gstreamer/include/glib-2.0
    LIBS += ../../gstreamer/lib/libgstreamer-0.10.lib ../../gstreamer/lib/gobject-2.0.lib "C:\Program Files\Mono-1.2.4\lib\libglib-2.0.dll.a"
}

unix {
    DESTDIR = ../../unix/plugins
    CONFIG += link_pkgconfig
    CONFIG += gstreamer
    PKGCONFIG += gstreamer-0.10
}

OBJECTS_DIR = $${DESTDIR}/../obj
MOC_DIR = $${DESTDIR}/../obj
RCC_DIR = $${DESTDIR}/../obj
