CONFIG += qt release
QT += sql xml network

TEMPLATE = app
TARGET = cuberokd
DEPENDPATH += . 

#QMAKE_CXXFLAGS_RELEASE -= -O2 
#QMAKE_CXXFLAGS_RELEASE += -Os -fno-builtin -fomit-frame-pointer
#QMAKE_CFLAGS_RELEASE -= -O2 
#QMAKE_CFLAGS_RELEASE += -Os -fno-builtin -fomit-frame-pointer 

include(../qmakeroot.pri)

include(../plugins/plugins_path-$${QT_ARCH}.pri)

# Input
HEADERS += \
           ../src/maind.h \
           ../src/player.h \
           ../src/player_manager.h \
           ../QFreeDesktopMime/src/freedesktopmime.h

TRANSLATIONS = ../translations/cuberok_ru.ts

SOURCES += \
           ../src/maind.cpp \
           ../src/player_manager.cpp \
           ../QFreeDesktopMime/src/freedesktopmime.cpp
RESOURCES += ../src/resourced.qrc

win32 {
    RC_FILE = ../cuberok.rc
    MSVC {
        DESTDIR = ../win32-vs
    } else {
        DESTDIR = ../win32
    }
    MSVC {
        CONFIG -= embed_manifest_exe
    } else {
    }
}
unix {
    DESTDIR = ../unix
    CONFIG += link_pkgconfig
    target.path = /bin
    INSTALLS += target
}

mac {
}

LIBS += -L$${DESTDIR}/plugins -lplayer_void

macx {
    QT += phonon
    LIBS += -L$${DESTDIR}/plugins -lplayer_phonon
}

OBJECTS_DIR = $${DESTDIR}/obj
MOC_DIR = $${DESTDIR}/obj
RCC_DIR = $${DESTDIR}/obj
UI_DIR = .

