@echo off  
:loop  
    data.exe>in.txt  
    Dstd.exe<in.txt>std.txt
    D.exe<in.txt>out.txt 
    fc out.txt std.txt  
if not errorlevel 1 goto loop  
pause  
goto loop