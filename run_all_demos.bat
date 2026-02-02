@echo off
title System Information & ASCII Demo Suite
color 0A

echo.
echo  ███████╗██╗   ██╗███████╗████████╗███████╗███╗   ███╗
echo  ██╔════╝╚██╗ ██╔╝██╔════╝╚══██╔══╝██╔════╝████╗ ████║
echo  ███████╗ ╚████╔╝ ███████╗   ██║   █████╗  ██╔████╔██║
echo  ╚════██║  ╚██╔╝  ╚════██║   ██║   ██╔══╝  ██║╚██╔╝██║
echo  ███████║   ██║   ███████║   ██║   ███████╗██║ ╚═╝ ██║
echo  ╚══════╝   ╚═╝   ╚══════╝   ╚═╝   ╚══════╝╚═╝     ╚═╝
echo.
echo            DEMO SUITE - Choose your experience:
echo.
echo  [1] Colorful ASCII Demo (C)
echo  [2] Advanced ASCII Showcase (C++)  
echo  [3] Interactive Dice Game (C)
echo  [4] System Information Tool (C)
echo  [5] Advanced System Diagnostic (C++)
echo  [6] Run All Demos in Sequence
echo  [0] Exit
echo.

:menu
set /p choice="Enter your choice (0-6): "

if "%choice%"=="1" (
    echo.
    echo Running Colorful ASCII Demo...
    colorful_ascii.exe
    goto menu
)

if "%choice%"=="2" (
    echo.
    echo Running Advanced ASCII Showcase...
    ascii_art_cpp.exe
    goto menu
)

if "%choice%"=="3" (
    echo.
    echo Running Interactive Dice Game...
    game_ascii.exe
    goto menu
)

if "%choice%"=="4" (
    echo.
    echo Running System Information Tool...
    system_info.exe
    goto menu
)

if "%choice%"=="5" (
    echo.
    echo Running Advanced System Diagnostic...
    advanced_system_info.exe
    goto menu
)

if "%choice%"=="6" (
    echo.
    echo Running all demos in sequence...
    echo.
    echo === Demo 1: Colorful ASCII ===
    colorful_ascii.exe
    echo.
    echo === Demo 2: Advanced ASCII Showcase ===
    ascii_art_cpp.exe
    echo.
    echo === Demo 3: Interactive Dice Game ===
    game_ascii.exe
    echo.
    echo === Demo 4: System Information ===
    system_info.exe
    echo.
    echo === Demo 5: Advanced System Diagnostic ===
    advanced_system_info.exe
    echo.
    echo All demos completed!
    pause
    goto menu
)

if "%choice%"=="0" (
    echo.
    echo Thank you for using the System Demo Suite!
    echo.
    exit /b 0
)

echo Invalid choice. Please try again.
goto menu