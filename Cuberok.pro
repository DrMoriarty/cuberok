TEMPLATE      = subdirs
SUBDIRS      += plugins/player_void \
		plugins/cuberok_style

# install
target.path = ../Cuberok
#sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS plugandpaintplugins.pro
#sources.path = $$[QT_INSTALL_EXAMPLES]/tools/plugandpaintplugins
INSTALLS += target


win32 {
    exists(./audiere/lib/audiere.lib) {
        message(using audiere backend)
        SUBDIRS += plugins/player_audiere
    }
    exists(./gstreamer/lib/libgstreamer-0.10.lib) {
        message(using gstreamer backend)
        SUBDIRS += plugins/player_gst
    }
}
unix {
    CONFIG += link_pkgconfig
    system(audiere-config --version) {
        message(using audiere backend)
        SUBDIRS += plugins/player_audiere
    }
    system(pkg-config --modversion gstreamer-0.10 2>/dev/null) {
        message(using gstreamer backend)
        SUBDIRS += plugins/player_gst
    }
#    pixmap.path = /share/pixmaps
#    pixmap.files = ../images/cuberok.xpm
#    desktop.path = /share/applications
#    desktop.files = ../cuberok.desktop
#    INSTALLS += pixmap desktop
}

SUBDIRS += src
