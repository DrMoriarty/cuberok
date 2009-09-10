 CONFIG       += release
 TEMPLATE      = lib
 CONFIG       += plugin
 INCLUDEPATH  += ../../src ../../include
 HEADERS       = ../../src/player_gst.h \
                 ../../src/player.h
 SOURCES       = ../../src/player_gst.cpp
 TARGET        = $$qtLibraryTarget(player_gst)

include(../../qmakeroot.pri)
include(../plugins_path-$${QT_ARCH}.pri)

win32 {
    DESTDIR = ../../win32/plugins
    INCLUDEPATH += ../../gstreamer/include ../../gstreamer/include/glib-2.0 ../../gstreamer/lib/glib-2.0/include
    LIBS += ../../gstreamer/lib/libgstreamer-0.10.lib ../../gstreamer/lib/gobject-2.0.lib ../../glib/lib/libglib-2.0.dll.a
}

unix {
    DESTDIR = ../../unix/plugins
    CONFIG += link_pkgconfig
    CONFIG += gstreamer
    PKGCONFIG += gstreamer-0.10
    INSTALLS += target
}

OBJECTS_DIR = $${DESTDIR}/../obj
MOC_DIR = $${DESTDIR}/../obj
RCC_DIR = $${DESTDIR}/../obj
