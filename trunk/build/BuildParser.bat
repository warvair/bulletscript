@echo off
..\..\Tools\flex.exe -o../Src/shBulletLexer.cpp -S../Src/flex.skl ../Src/BulletLexer.l

copy ..\Src\BulletParser.y c:\Code\__Other\bison\bin
cd C:\Code\__Other\bison\bin
bison.exe -oshBulletParser.cpp -d -v BulletParser.y
cd c:\code\Shmuppet\BulletScript
move /Y c:\Code\__Other\bison\bin\shBulletParser.output ./Build
move /Y c:\Code\__Other\bison\bin\shBulletParser.cpp ./Src
move /Y c:\Code\__Other\bison\bin\shBulletParser.hpp ./Include

pause

