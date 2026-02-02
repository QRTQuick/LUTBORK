# LUTBORK - System Information & Colorful ASCII C/C++ Programs

**LUTBORK** is a comprehensive system diagnostic tool developed by **Chisom Life Eke**, CEO of **Quick Red Tech** (2026). This advanced system information tool provides detailed hardware analysis with a clean, professional interface.

## Author Information

**Developer**: Chisom Life Eke  
**Company**: Quick Red Tech  
**Year**: 2026  
**Role**: Chief Executive Officer  

## Programs Included

### 1. **LUTBORK Core** - Advanced System Information Tool
- **Hard disk type detection and analysis**
- **All connected drives enumeration**
- **Installed device drivers listing**
- **Kernel information and version details**
- **Physical disk analysis (SSD vs HDD detection)**
- Cross-platform support (Windows/Linux)
- Colorful presentation with clean interface
- Modular C architecture with professional build system

### 2. `colorful_ascii.c` - Basic C Color Demo
- ANSI color codes for text coloring
- ASCII box drawing characters
- Simple beep sounds using `\a`
- Animated loading spinner
- Rainbow-colored ASCII art

### 3. `ascii_art_cpp.cpp` - Advanced C++ Showcase
- Object-oriented approach with ColoredASCII class
- Animated rocket ASCII art
- Progress bar animation
- Rainbow text effects
- Special Unicode characters
- Threaded animations

### 4. `game_ascii.c` - Interactive Dice Game
- Colorful ASCII dice graphics
- Interactive gameplay
- Sound effects for different events
- Victory celebrations with animations
- Dynamic color changes based on dice value

### 5. `system_info.c` - Legacy System Information Tool
- Basic system information gathering
- Windows API integration
- Hardware detection capabilities

### 6. `advanced_system_info.cpp` - Enhanced System Diagnostic
- Comprehensive disk analysis with usage statistics
- Detailed driver information with hardware IDs
- Complete kernel and system architecture analysis
- Memory usage monitoring with progress bars
- Available kernels detection
- Hardware bus enumeration
- Advanced C++ object-oriented design
- Animated progress indicators

## LUTBORK Core Features

### Hard Disk Analysis
- **Drive Type Detection**: Identifies Fixed drives (HDD/SSD), Removable drives (USB), Network drives, Optical drives (CD/DVD), and RAM disks
- **Physical Disk Information**: Shows disk geometry, size, cylinders, tracks, sectors
- **SSD vs HDD Detection**: Uses Windows IOCTL calls to determine if drives have seek penalty (HDD) or not (SSD)
- **Disk Usage Statistics**: Total, used, and free space with visual progress bars
- **Partition Analysis**: Lists all partitions with sizes and types
- **Mount Point Information**: Shows mounted filesystems with usage statistics

### Driver Information
- **Installed Device Drivers**: Enumerates all devices with installed drivers
- **Driver Versions**: Shows driver version information where available
- **Hardware IDs**: Displays hardware identification strings
- **Device Categories**: Groups devices by type and function
- **Kernel Modules**: Lists loaded kernel modules (Linux) with size and dependency information
- **Hardware Buses**: Shows available hardware buses (PCI, USB, etc.)

### Kernel & System Analysis
- **Kernel Version**: Complete kernel version and build information
- **System Architecture**: Processor architecture (x86, x64, ARM, ARM64)
- **Available Kernels**: Lists all available kernel images in /boot (Linux)
- **Kernel Parameters**: Shows current boot parameters
- **Memory Information**: Total, used, and available RAM with usage visualization
- **System Uptime**: Shows how long the system has been running
- **Load Average**: Current system load (Linux)

### Cross-Platform Support
- **Windows**: Uses Win32 API, WMI, and IOCTL calls for comprehensive system information
- **Linux**: Reads from /proc and /sys filesystems for kernel and hardware data
- **Automatic Detection**: Code automatically adapts to the target platform

## Building and Running

### Quick Start (Windows)
```batch
# Build LUTBORK
build_modular.bat

# Run LUTBORK
bin\lutbork.exe

# Run interactive demo menu
run_all_demos.bat
```

### Using Make (Cross-platform)
```bash
# Build LUTBORK
make -f Makefile_modular

# Run LUTBORK
./bin/lutbork

# Build all demo programs
make

# Run other demos
make run-c      # Run C demo
make run-cpp    # Run C++ demo
make run-game   # Run dice game

# Clean build files
make clean
```

### Manual Compilation

#### Windows
```batch
# LUTBORK system information tool
gcc -Wall -Wextra -std=c99 -Isrc -c src/*.c
gcc obj/*.o -o bin/lutbork.exe -lsetupapi

# Other programs
gcc -Wall -Wextra -std=c99 -o colorful_ascii.exe colorful_ascii.c
gcc -Wall -Wextra -std=c99 -o game_ascii.exe game_ascii.c
g++ -Wall -Wextra -std=c++11 -o ascii_art_cpp.exe ascii_art_cpp.cpp
```

#### Linux
```bash
# LUTBORK system information tool
gcc -Wall -Wextra -std=c99 -Isrc -c src/*.c
gcc obj/*.o -o bin/lutbork

# Other programs
gcc -Wall -Wextra -std=c99 -o colorful_ascii colorful_ascii.c
gcc -Wall -Wextra -std=c99 -o game_ascii game_ascii.c
g++ -Wall -Wextra -std=c++11 -o ascii_art_cpp ascii_art_cpp.cpp
```

## System Requirements

### Windows
- Windows 7 or later
- GCC/MinGW or Visual Studio compiler
- Windows Terminal or PowerShell for best color support
- Administrator privileges recommended for complete hardware access

### Linux
- Any modern Linux distribution
- GCC compiler
- Root privileges recommended for complete system information
- Terminal with ANSI color support

## Sample Output

### LUTBORK Hard Disk Information
```
=== HARD DISK INFORMATION ===
----------------------------------------------------------------
Hard Disk Drives:
  + Drive C: - Fixed Drive (Hard Disk)
      Total: 237.47 GB, Used: 236.99 GB, Free: 0.48 GB
      Usage [###################-] 99%

Physical Disks:
  + Physical Drive 0: 238.47 GB (SSD)
  + Physical Drive 1: 465.76 GB (HDD)
```

### Driver Information
```
=== INSTALLED DRIVERS ===
----------------------------------------------------------------
Device Drivers:
  + Intel(R) Graphics Control Panel
      HW ID: SWC\101.2134_VEN8086_GFXUI
  + Samsung SSD disk drive
      HW ID: SCSI\DiskSAMSUNG_SSD_____________MVT2
  + USB Composite Device
      HW ID: USB\VID_0BDA&PID_568C&REV_6053

Total devices with drivers: 21+
```

### Kernel Information
```
=== KERNEL INFORMATION ===
----------------------------------------------------------------
Windows Kernel Information:
  + Version: 10.0.26200
  + Windows Edition: Windows 11
  + Processor Architecture: x64 (AMD64)
  + Number of Processors: 8
  + Total Physical RAM: 7.86 GB
  + RAM Usage [#################---] 88%
```

## Technical Implementation

### Windows API Usage
- **SetupDi API**: Device enumeration and driver information
- **IOCTL calls**: Direct hardware communication for disk analysis
- **WMI (Windows Management Instrumentation)**: System information queries
- **Win32 API**: File system and memory information

### Linux System Interfaces
- **/proc filesystem**: Kernel and process information
- **/sys filesystem**: Hardware and driver information
- **uname system call**: Kernel version information
- **sysinfo system call**: System statistics

### Advanced Features
- **Real-time Progress Bars**: Visual representation of disk and memory usage
- **Color-coded Output**: Different colors for different types of information
- **Sound Feedback**: Audio cues for user interaction and completion
- **Animated Displays**: Smooth transitions and loading indicators
- **Error Handling**: Graceful handling of permission and access issues

## About Quick Red Tech

**Quick Red Tech** is a technology company focused on developing innovative system tools and diagnostic software. Under the leadership of CEO **Chisom Life Eke**, the company delivers professional-grade software solutions for system administrators, developers, and technology enthusiasts.

**LUTBORK** represents Quick Red Tech's commitment to creating powerful, user-friendly tools that provide deep system insights while maintaining clean, professional interfaces.

## License

This project is developed by **Chisom Life Eke** for **Quick Red Tech** (2026). All rights reserved.

## Contact

For questions, support, or business inquiries regarding LUTBORK or other Quick Red Tech products, please contact:

**Chisom Life Eke**  
Chief Executive Officer  
Quick Red Tech  
Year: 2026

## Features Demonstrated

### Colors
- Basic ANSI color codes (Red, Green, Blue, etc.)
- Bright/bold color variants
- Background colors
- Color reset functionality

### ASCII Characters
- Box drawing characters (╔═╗║╚╝)
- Special symbols (★☆♠♣♥♦☺☻♪♫)
- Unicode characters for enhanced visuals
- Custom ASCII art designs

### Sound Effects
- System beep using `\a` (ASCII bell)
- Timed beep sequences
- Different beep patterns for events
- Audio feedback for user interactions

### Animations
- Spinning loading indicators
- Progress bar animations
- Character-by-character text reveals
- Dice rolling animations

## Building and Running

### Using Make (Recommended)
```bash
# Build all programs
make

# Build individual programs
make colorful_ascii
make ascii_art_cpp
make game_ascii

# Run programs
make run-c      # Run C demo
make run-cpp    # Run C++ demo
make run-game   # Run dice game

# Clean build files
make clean
```

### Manual Compilation
```bash
# C programs
gcc -Wall -Wextra -std=c99 -o colorful_ascii colorful_ascii.c
gcc -Wall -Wextra -std=c99 -o game_ascii game_ascii.c

# C++ program
g++ -Wall -Wextra -std=c++11 -o ascii_art_cpp ascii_art_cpp.cpp
```

## Platform Compatibility

### Windows
- Colors work in Windows Terminal, PowerShell, and modern command prompts
- Beeps work on most Windows systems
- Some Unicode characters may require UTF-8 support

### Linux/macOS
- Full color and Unicode support in most terminals
- Beeps work through system audio
- All features should work out of the box

## Technical Notes

### ANSI Escape Codes
- `\033[31m` - Red text
- `\033[32m` - Green text
- `\033[0m` - Reset to default
- `\033[2J\033[H` - Clear screen and move cursor home

### ASCII Bell Character
- `\a` produces system beep sound
- `printf("\a")` followed by `fflush(stdout)` ensures immediate output

### Threading (C++)
- Uses `std::this_thread::sleep_for()` for delays
- `std::chrono::milliseconds()` for precise timing

## Customization Ideas

1. **Add More Colors**: Extend color palette with 256-color ANSI codes
2. **Enhanced ASCII Art**: Create larger, more detailed ASCII graphics
3. **Interactive Menus**: Build menu systems with colored options
4. **Animation Sequences**: Create complex animated scenes
5. **Sound Patterns**: Develop musical beep sequences
6. **Game Elements**: Add scoring, levels, or multiplayer features

## Troubleshooting

- **Colors not showing**: Ensure terminal supports ANSI escape codes
- **No beep sound**: Check system audio settings and terminal audio support
- **Unicode issues**: Set terminal encoding to UTF-8
- **Compilation errors**: Verify compiler supports C99/C++11 standards

Enjoy creating colorful, interactive console applications!

## System Information Features

### Hard Disk Analysis
- **Drive Type Detection**: Identifies Fixed drives (HDD/SSD), Removable drives (USB), Network drives, Optical drives (CD/DVD), and RAM disks
- **Physical Disk Information**: Shows disk geometry, size, cylinders, tracks, sectors
- **SSD vs HDD Detection**: Uses Windows IOCTL calls to determine if drives have seek penalty (HDD) or not (SSD)
- **Disk Usage Statistics**: Total, used, and free space with visual progress bars
- **Partition Analysis**: Lists all partitions with sizes and types
- **Mount Point Information**: Shows mounted filesystems with usage statistics

### Driver Information
- **Installed Device Drivers**: Enumerates all devices with installed drivers
- **Driver Versions**: Shows driver version information where available
- **Hardware IDs**: Displays hardware identification strings
- **Device Categories**: Groups devices by type and function
- **Kernel Modules**: Lists loaded kernel modules (Linux) with size and dependency information
- **Hardware Buses**: Shows available hardware buses (PCI, USB, etc.)

### Kernel & System Analysis
- **Kernel Version**: Complete kernel version and build information
- **System Architecture**: Processor architecture (x86, x64, ARM, ARM64)
- **Available Kernels**: Lists all available kernel images in /boot (Linux)
- **Kernel Parameters**: Shows current boot parameters
- **Memory Information**: Total, used, and available RAM with usage visualization
- **System Uptime**: Shows how long the system has been running
- **Load Average**: Current system load (Linux)

### Cross-Platform Support
- **Windows**: Uses Win32 API, WMI, and IOCTL calls for comprehensive system information
- **Linux**: Reads from /proc and /sys filesystems for kernel and hardware data
- **Automatic Detection**: Code automatically adapts to the target platform

## Building and Running

### Quick Start (Windows)
```batch
# Build all programs
build.bat

# Run interactive demo menu
run_all_demos.bat
```

### Using Make (Cross-platform)
```bash
# Build all programs
make

# Build individual programs
make system_info
make advanced_system_info

# Run system information tools
make run-sysinfo      # Run basic system info
make run-advanced     # Run advanced diagnostic

# Run other demos
make run-c      # Run C demo
make run-cpp    # Run C++ demo
make run-game   # Run dice game

# Clean build files
make clean
```

### Manual Compilation

#### Windows
```batch
# System information tools
gcc -Wall -Wextra -std=c99 -o system_info.exe system_info.c -lsetupapi -lwbemuuid -lole32 -loleaut32
g++ -Wall -Wextra -std=c++11 -o advanced_system_info.exe advanced_system_info.cpp -lsetupapi -lwbemuuid -lole32 -loleaut32

# Other programs
gcc -Wall -Wextra -std=c99 -o colorful_ascii.exe colorful_ascii.c
gcc -Wall -Wextra -std=c99 -o game_ascii.exe game_ascii.c
g++ -Wall -Wextra -std=c++11 -o ascii_art_cpp.exe ascii_art_cpp.cpp
```

#### Linux
```bash
# System information tools
gcc -Wall -Wextra -std=c99 -o system_info system_info.c
g++ -Wall -Wextra -std=c++11 -o advanced_system_info advanced_system_info.cpp

# Other programs
gcc -Wall -Wextra -std=c99 -o colorful_ascii colorful_ascii.c
gcc -Wall -Wextra -std=c99 -o game_ascii game_ascii.c
g++ -Wall -Wextra -std=c++11 -o ascii_art_cpp ascii_art_cpp.cpp
```

## System Requirements

### Windows
- Windows 7 or later
- GCC/MinGW or Visual Studio compiler
- Windows Terminal or PowerShell for best color support
- Administrator privileges recommended for complete hardware access

### Linux
- Any modern Linux distribution
- GCC compiler
- Root privileges recommended for complete system information
- Terminal with ANSI color support

## Sample Output

### Hard Disk Information
```
💾 Physical Disk Analysis:
  ├─ Physical Drive 0: 500.00 GB (SSD)
      Cylinders: 60801
      Tracks per Cylinder: 255
      Sectors per Track: 63
      Bytes per Sector: 512

🖴 Drive C:\ - Fixed Drive (Hard Disk) - Total: 465.76 GB, Free: 123.45 GB
Usage [████████████░░░░░░░░] 73%
```

### Driver Information
```
🔧 Installed Device Drivers:
  ├─ NVIDIA GeForce RTX 3080 (v30.0.14.9649)
      Hardware ID: PCI\VEN_10DE&DEV_2206
  ├─ Intel(R) Core(TM) i7-10700K CPU @ 3.80GHz
  ├─ Realtek High Definition Audio (v6.0.9088.1)
```

### Kernel Information
```
🖥️  Windows System Information:
  ├─ OS Version: 10.0.22000
  ├─ Windows Edition: Windows 11
  ├─ Processor Architecture: x64 (AMD64)
  ├─ Number of Processors: 16
  └─ Total Physical RAM: 32.00 GB

💾 Memory Information:
RAM Usage [██████░░░░░░░░░░░░░░] 30%
```

## Technical Implementation

### Windows API Usage
- **SetupDi API**: Device enumeration and driver information
- **IOCTL calls**: Direct hardware communication for disk analysis
- **WMI (Windows Management Instrumentation)**: System information queries
- **Win32 API**: File system and memory information

### Linux System Interfaces
- **/proc filesystem**: Kernel and process information
- **/sys filesystem**: Hardware and driver information
- **uname system call**: Kernel version information
- **sysinfo system call**: System statistics

### Advanced Features
- **Real-time Progress Bars**: Visual representation of disk and memory usage
- **Color-coded Output**: Different colors for different types of information
- **Sound Feedback**: Audio cues for user interaction and completion
- **Animated Displays**: Smooth transitions and loading indicators
- **Error Handling**: Graceful handling of permission and access issues

## Troubleshooting

### Windows Issues
- **"Access Denied" errors**: Run as Administrator for complete hardware access
- **Missing libraries**: Install MinGW-w64 or Visual Studio Build Tools
- **Colors not showing**: Use Windows Terminal or PowerShell instead of Command Prompt

### Linux Issues
- **Permission denied**: Run with sudo for complete system information
- **Missing information**: Ensure /proc and /sys are mounted
- **Compilation errors**: Install build-essential package

### General Issues
- **No beep sound**: Check system audio settings and terminal audio support
- **Unicode issues**: Set terminal encoding to UTF-8
- **Slow performance**: Some operations require hardware enumeration which can take time

## Security Considerations

- Programs request hardware-level access for complete information
- Administrator/root privileges provide more detailed system data
- No system modifications are made - read-only access only
- All system calls are standard API functions

## Customization Ideas

1. **Add Network Information**: Extend to show network adapters and connections
2. **Temperature Monitoring**: Add CPU and GPU temperature readings
3. **Performance Metrics**: Include CPU usage and performance counters
4. **Export Functionality**: Save system information to files
5. **Remote Monitoring**: Network-based system monitoring
6. **Historical Data**: Track system changes over time
7. **Alert System**: Notify when system resources are low

Enjoy exploring your system with these comprehensive diagnostic tools!