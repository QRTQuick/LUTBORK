@echo off
title Building LUTBORK - System Information Tool
color 0B

echo.
echo  ========================================
echo              LUTBORK BUILD
echo         System Information Tool
echo  ========================================
echo.
echo            BUILDING MODULAR SYSTEM
echo.

REM Create directories
if not exist obj mkdir obj
if not exist bin mkdir bin

REM Set compiler flags
set CFLAGS=-Wall -Wextra -std=c99 -Isrc
set LDFLAGS=-lsetupapi -lwbemuuid -lole32 -loleaut32

echo Building LUTBORK components...
echo.

echo   + Compiling colors.c...
gcc %CFLAGS% -c src/colors.c -o obj/colors.o
if errorlevel 1 goto error

echo   + Compiling disk_info.c...
gcc %CFLAGS% -c src/disk_info.c -o obj/disk_info.o
if errorlevel 1 goto error

echo   + Compiling driver_info.c...
gcc %CFLAGS% -c src/driver_info.c -o obj/driver_info.o
if errorlevel 1 goto error

echo   + Compiling kernel_info.c...
gcc %CFLAGS% -c src/kernel_info.c -o obj/kernel_info.o
if errorlevel 1 goto error

echo   + Compiling main.c...
gcc %CFLAGS% -c src/main.c -o obj/main.o
if errorlevel 1 goto error

echo.
echo Linking LUTBORK executable...
gcc obj/main.o obj/colors.o obj/disk_info.o obj/driver_info.o obj/kernel_info.o -o bin/lutbork.exe %LDFLAGS%
if errorlevel 1 goto error

echo.
echo LUTBORK build completed successfully!
echo.
echo Output: bin/lutbork.exe
echo.
echo Run LUTBORK now? (Y/N)
set /p run_choice=
if /i "%run_choice%"=="Y" (
    echo.
    echo Starting LUTBORK...
    bin\lutbork.exe
)

goto end

:error
echo.
echo LUTBORK build failed! Check the error messages above.
echo.
pause
exit /b 1

:end
echo.
echo LUTBORK build process completed.
pause