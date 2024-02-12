@echo off



set "COMPILADOR=GCC.EXE"
set "NAMEFILE=main"
set "NAME_D=FILLING_PARTS" rem DIRECT_FILL OR FILLING_PARTS


%COMPILADOR% -s -Wall -pedantic -c *.c -O2 -D%NAME_D%

%COMPILADOR% -s -Wall -pedantic -o %NAMEFILE%.exe *.o -O2

del *.o

%NAMEFILE%.exe

pause