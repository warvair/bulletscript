@echo off
..\..\Shmuppet\Tools\flex.exe -o../src/bsBulletLexer.cpp -S../src/flex.skl ../src/BulletLexer.l

copy ..\src\BulletParser.y c:\Code\__Other\bison\bin
cd C:\Code\__Other\bison\bin
bison.exe -obsBulletParser.cpp -d -v BulletParser.y
cd c:\code\bulletscript
move /Y c:\Code\__Other\bison\bin\bsBulletParser.output ./build
move /Y c:\Code\__Other\bison\bin\bsBulletParser.cpp ./src
move /Y c:\Code\__Other\bison\bin\bsBulletParser.hpp ./include

pause

