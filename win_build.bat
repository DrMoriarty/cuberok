rem set QTDIR=C:\Qt\4.3.1
set QTDIR=C:\Qt\2009.01\qt

%QTDIR%\bin\lupdate.exe Cuberok.pro 
%QTDIR%\bin\lrelease.exe locale\cuberok_ru.ts -qm locale\cuberok_ru.qm
copy locale\*.qm win32\
%QTDIR%\bin\qmake.exe "CONFIG+=player_phonon" Cuberok.pro -o Makefile.win
mingw32-make -f Makefile.win