#!/bin/sh
lupdate Cuberok.pro -ts locale\cuberok_ru.ts
lrelease locale\cuberok_ru.ts -qm locale\cuberok_ru.qm
qmake Cuberok.pro
make

#make install INSTALL_ROOT=/usr/locale 