TEMPLATE      = subdirs
SUBDIRS      += ./plugins/player_void 
SUBDIRS      += extensions 
CONFIG += ordered
# install
target.path = ../Cuberok
INSTALLS += target

disable_all {
    CONFIG += disable_audiere disable_gst disable_phonon disable_ffmpeg
}

eval(QT_VERSION >= "4.5.0") {
#    message($$[QT_VERSION])
    CONFIG += player_phonon
}

player_phonon {
    disable_phonon {
        message(phonon disabled)
    } else {
        message(using phonon backend)
        SUBDIRS += plugins/player_phonon
    }
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
        system(pkg-config --modversion sdl 2>/dev/null) {
            disable_ffmpeg {
                message(ffmpeg disabled)
            } else {
                message(using ffmpeg backend)
                SUBDIRS += plugins/player_ffmpeg
            }
        }
    }
    system(audiere-config --version) {
        disable_audiere {
            message(audiere disabled)
        } else {
            message(using audiere backend)
            SUBDIRS += plugins/player_audiere
        }
    }
    system(pkg-config --modversion gstreamer-0.10 2>/dev/null) {
        disable_gst {
            message(gst disabled)
        } else {
            message(using gstreamer backend)
            SUBDIRS += plugins/player_gst
        }
    }
}

#client_server {
#    SUBDIRS += cuberok_client cuberok_daemon
#} else {
    SUBDIRS += src
#}
