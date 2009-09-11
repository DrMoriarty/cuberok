rem set QTDIR=C:\Qt\4.3.1
set QTDIR=C:\Qt\2009.03\qt

%QTDIR%\bin\lupdate.exe Cuberok.pro 
%QTDIR%\bin\lrelease.exe translations\cuberok_ru.ts -qm translations\cuberok_ru.qm
copy translations\*.qm win32\translations\
%QTDIR%\bin\qmake.exe "CONFIG+=player_phonon" Cuberok.pro -o Makefile.win
mingw32-make -f Makefile.win