TEMPLATE      = subdirs
SUBDIRS      += ./plugins/player_void 
SUBDIRS      += plugins/cuberok_style 
#		plugins/arthur_style

# install
target.path = ../Cuberok
#sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS plugandpaintplugins.pro
#sources.path = $$[QT_INSTALL_EXAMPLES]/tools/plugandpaintplugins
INSTALLS += target

eval(QT_VERSION >= "4.5.0") {
    message($$[QT_VERSION])
    CONFIG += player_phonon
}

player_phonon {
    message(using phonon backend)
    SUBDIRS += plugins/player_phonon
}

win32 {
    exists(./ffmpeg/lib/avcodec.lib) {
        message(using ffmpeg backend)
        SUBDIRS += plugins/player_ffmpeg
    }
    exists(./audiere/lib/audiere.lib) {
        message(using audiere backend)
        SUBDIRS += plugins/player_audiere
    }
    !MSVC {
    exists(./gstreamer/lib/libgstreamer-0.10.lib) {
        message(using gstreamer backend)
        SUBDIRS += plugins/player_gst
    }
    }
}
unix {
    CONFIG += link_pkgconfig
    system(pkg-config --modversion libavcodec 2>/dev/null) {
        message(using ffmpeg backend)
        SUBDIRS += plugins/player_ffmpeg
    }
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
