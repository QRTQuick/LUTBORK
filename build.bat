@echo off
echo Building System Information Tools...
echo.

REM Set compiler flags
set CFLAGS=-Wall -Wextra -std=c99
set CXXFLAGS=-Wall -Wextra -std=c++11
set LDFLAGS=-lsetupapi -lwbemuuid -lole32 -loleaut32

echo Compiling C programs...
gcc %CFLAGS% -o colorful_ascii.exe colorful_ascii.c
gcc %CFLAGS% -o game_ascii.exe game_ascii.c
gcc %CFLAGS% -o system_info.exe system_info.c %LDFLAGS%

echo.
echo Compiling C++ programs...
g++ %CXXFLAGS% -o ascii_art_cpp.exe ascii_art_cpp.cpp
g++ %CXXFLAGS% -o advanced_system_info.exe advanced_system_info.cpp %LDFLAGS%

echo.
echo Build completed!
echo.
echo Available programs:
echo   colorful_ascii.exe     - Basic colorful ASCII demo
echo   ascii_art_cpp.exe      - Advanced C++ ASCII showcase  
echo   game_ascii.exe         - Interactive dice game
echo   system_info.exe        - System information tool (C)
echo   advanced_system_info.exe - Advanced system diagnostic (C++)
echo.
pause