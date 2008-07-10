C:\Programs\Qt\4.3.1\bin\lupdate.exe Cuberok.pro
C:\Programs\Qt\4.3.1\bin\lrelease.exe cuberok_ru.ts -qm win32\cuberok_ru.qm
C:\Programs\Qt\4.3.1\bin\qmake.exe Cuberok.pro -o Makefile.win
mingw32-make -f Makefile.win