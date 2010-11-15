rem set QTDIR=C:\Qt\4.3.1
set QTDIR=C:\Qt\2010.05\qt
rem set QTDIR=C:\Qt\4.6.2

%QTDIR%\bin\lupdate.exe src/ plugins/ extensions/ -no-obsolete -ts translations/cuberok_ru.ts
%QTDIR%\bin\lrelease.exe translations\cuberok_ru.ts -qm translations\cuberok_ru.qm
copy translations\*.qm win32\translations\
rem %QTDIR%\bin\qmake.exe "CONFIG+=disable_phonon" Cuberok.pro -o Makefile.win -spec win32-g++
%QTDIR%\bin\qmake.exe Cuberok.pro -o Makefile.win -spec win32-g++
mingw32-make -j 2 -f Makefile.win