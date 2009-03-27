#!/bin/sh
lupdate Cuberok.pro -ts locale\cuberok_ru.ts
lrelease locale\cuberok_ru.ts -qm locale\cuberok_ru.qm
qmake "CONFIG+=player_phonon" Cuberok.pro
make

#make install INSTALL_ROOT=/usr/local 