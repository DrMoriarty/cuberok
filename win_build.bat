C:\Qt\4.3.1\bin\lupdate.exe Cuberok.pro -ts locale\cuberok_ru.ts
C:\Qt\4.3.1\bin\lrelease.exe locale\cuberok_ru.ts -qm locale\cuberok_ru.qm
copy locale\*.qm win32\
C:\Qt\4.3.1\bin\qmake.exe Cuberok.pro -o Makefile.win
mingw32-make -f Makefile.win