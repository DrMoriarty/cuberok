#!/bin/sh
lupdate Cuberok.pro -ts translations/cuberok_ru.ts
lrelease translations/cuberok_ru.ts -qm translations/cuberok_ru.qm
qmake "CONFIG+=player_phonon" Cuberok.pro
if make -j 2; then
	sudo make install INSTALL_ROOT=/usr/local 
fi