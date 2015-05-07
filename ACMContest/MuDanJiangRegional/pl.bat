:loop
data.exe
B.exe
Bstd.exe
fc 2Bout.txt Boutstd.txt
if not errorlevel 1 goto loop
pause
