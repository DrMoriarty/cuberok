rem set QTDIR=C:\Qt\4.3.1
set QTDIR=C:\Qt\4.5.0-rc1

%QTDIR%\bin\lupdate.exe Cuberok.pro -ts locale\cuberok_ru.ts
%QTDIR%\bin\lrelease.exe locale\cuberok_ru.ts -qm locale\cuberok_ru.qm
copy locale\*.qm win32\
%QTDIR%\bin\qmake.exe Cuberok.pro -o Makefile.win
mingw32-make -f Makefile.win