@echo off



set "COMPILADOR=GCC.EXE"
set "NAMEFILE=main"


%COMPILADOR% -s -Wall -pedantic -c *.c -O2

%COMPILADOR% -s -Wall -pedantic -o %NAMEFILE%.exe *.o -O2

del *.o

%NAMEFILE%.exe

pause