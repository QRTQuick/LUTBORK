#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#include <winioctl.h>
#include <setupapi.h>
#include <devguid.h>
#include <wbemidl.h>
#include <comdef.h>
#pragma comment(lib, "setupapi.lib")
#pragma comment(lib, "wbemuuid.lib")
#else
#include <sys/utsname.h>
#include <dirent.h>
#include <sys/statvfs.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#endif

using namespace std;

class SystemAnalyzer {
private:
    // ANSI color codes
    const string RESET = "\033[0m";
    const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string YELLOW = "\033[33m";
    const string BLUE = "\033[34m";
    const string MAGENTA = "\033[35m";
    const string CYAN = "\033[36m";
    const string WHITE = "\033[37m";
    const string BRIGHT_GREEN = "\033[92m";
    const string BRIGHT_YELLOW = "\033[93m";
    const string BRIGHT_BLUE = "\033[94m";
    const string BRIGHT_CYAN = "\033[96m";
    const string BRIGHT_MAGENTA = "\033[95m";

public:
    void beep(int count = 1) {
        for (int i = 0; i < count; i++) {
            cout << "\a" << flush;
            this_thread::sleep_for(chrono::milliseconds(200));
        }
    }
    
    void clearScreen() {
        cout << "\033[2J\033[H";
    }
    
    void printAnimatedTitle() {
        vector<string> title_lines = {
            "  ███████╗██╗   ██╗███████╗████████╗███████╗███╗   ███╗",
            "  ██╔════╝╚██╗ ██╔╝██╔════╝╚══██╔══╝██╔════╝████╗ ████║",
            "  ███████╗ ╚████╔╝ ███████╗   ██║   █████╗  ██╔████╔██║",
            "  ╚════██║  ╚██╔╝  ╚════██║   ██║   ██╔══╝  ██║╚██╔╝██║",
            "  ███████║   ██║   ███████║   ██║   ███████╗██║ ╚═╝ ██║",
            "  ╚══════╝   ╚═╝   ╚══════╝   ╚═╝   ╚══════╝╚═╝     ╚═╝",
            "",
            "    ██████╗ ██╗ █████╗  ██████╗ ███╗   ██╗ ██████╗ ███████╗████████╗██╗ ██████╗",
            "    ██╔══██╗██║██╔══██╗██╔════╝ ████╗  ██║██╔═══██╗██╔════╝╚══██╔══╝██║██╔════╝",
            "    ██║  ██║██║███████║██║  ███╗██╔██╗ ██║██║   ██║███████╗   ██║   ██║██║     ",
            "    ██║  ██║██║██╔══██║██║   ██║██║╚██╗██║██║   ██║╚════██║   ██║   ██║██║     ",
            "    ██████╔╝██║██║  ██║╚██████╔╝██║ ╚████║╚██████╔╝███████║   ██║   ██║╚██████╗",
            "    ╚═════╝ ╚═╝╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚══════╝   ╚═╝   ╚═╝ ╚═════╝"
        };
        
        for (const auto& line : title_lines) {
            cout << BRIGHT_YELLOW << line << RESET << endl;
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }
    
    void printSectionHeader(const string& title) {
        cout << endl << BRIGHT_CYAN << "▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓" << RESET << endl;
        cout << BRIGHT_YELLOW << "▓▓▓ " << title << " ▓▓▓" << RESET << endl;
        cout << BRIGHT_CYAN << "▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓" << RESET << endl;
    }
    
    void printProgressBar(int percentage, const string& label) {
        cout << CYAN << label << " [";
        int filled = percentage / 5;
        
        for (int i = 0; i < 20; i++) {
            if (i < filled) {
                cout << GREEN << "█";
            } else {
                cout << WHITE << "░";
            }
        }
        cout << CYAN << "] " << YELLOW << percentage << "%" << RESET << endl;
    }

#ifdef _WIN32
    void analyzeDiskInfo() {
        printSectionHeader("HARD DISK & STORAGE ANALYSIS");
        
        cout << BRIGHT_GREEN << "🖴 Logical Drives Detection:\n" << RESET;
        DWORD drives = GetLogicalDrives();
        char drive_letter[4] = "A:\\";
        
        for (int i = 0; i < 26; i++) {
            if (drives & (1 << i)) {
                drive_letter[0] = 'A' + i;
                UINT drive_type = GetDriveTypeA(drive_letter);
                
                cout << GREEN << "  ├─ Drive " << (char)('A' + i) << ":\\ - ";
                
                switch (drive_type) {
                    case DRIVE_FIXED:
                        cout << YELLOW << "Fixed Drive (HDD/SSD)" << RESET;
                        break;
                    case DRIVE_REMOVABLE:
                        cout << MAGENTA << "Removable Drive (USB/Floppy)" << RESET;
                        break;
                    case DRIVE_REMOTE:
                        cout << CYAN << "Network Drive" << RESET;
                        break;
                    case DRIVE_CDROM:
                        cout << BRIGHT_YELLOW << "Optical Drive (CD/DVD/Blu-ray)" << RESET;
                        break;
                    case DRIVE_RAMDISK:
                        cout << BRIGHT_CYAN << "RAM Disk" << RESET;
                        break;
                    default:
                        cout << RED << "Unknown Drive Type" << RESET;
                }
                
                // Get detailed disk space information
                ULARGE_INTEGER free_bytes, total_bytes, total_free_bytes;
                if (GetDiskFreeSpaceExA(drive_letter, &free_bytes, &total_bytes, &total_free_bytes)) {
                    double total_gb = (double)total_bytes.QuadPart / (1024.0 * 1024.0 * 1024.0);
                    double free_gb = (double)free_bytes.QuadPart / (1024.0 * 1024.0 * 1024.0);
                    double used_gb = total_gb - free_gb;
                    int usage_percent = (int)((used_gb / total_gb) * 100);
                    
                    cout << endl;
                    cout << WHITE << "      Total: " << fixed << setprecision(2) << total_gb << " GB, ";
                    cout << "Used: " << used_gb << " GB, ";
                    cout << "Free: " << free_gb << " GB" << RESET << endl;
                    
                    printProgressBar(usage_percent, "      Usage");
                }
                cout << endl;
            }
        }
        
        // Physical disk analysis
        cout << BRIGHT_MAGENTA << "\n💾 Physical Disk Analysis:\n" << RESET;
        for (int i = 0; i < 10; i++) {
            char disk_path[50];
            sprintf(disk_path, "\\\\.\\PhysicalDrive%d", i);
            
            HANDLE hDisk = CreateFileA(disk_path, 0, FILE_SHARE_READ | FILE_SHARE_WRITE,
                                      NULL, OPEN_EXISTING, 0, NULL);
            
            if (hDisk != INVALID_HANDLE_VALUE) {
                cout << YELLOW << "  ├─ Physical Drive " << i << ":" << RESET << endl;
                
                // Get disk geometry
                DISK_GEOMETRY disk_geo;
                DWORD bytes_returned;
                
                if (DeviceIoControl(hDisk, IOCTL_DISK_GET_DRIVE_GEOMETRY, NULL, 0,
                                   &disk_geo, sizeof(disk_geo), &bytes_returned, NULL)) {
                    
                    ULONGLONG disk_size = disk_geo.Cylinders.QuadPart *
                                         disk_geo.TracksPerCylinder *
                                         disk_geo.SectorsPerTrack *
                                         disk_geo.BytesPerSector;
                    
                    double size_gb = (double)disk_size / (1024.0 * 1024.0 * 1024.0);
                    
                    cout << WHITE << "      Size: " << fixed << setprecision(2) << size_gb << " GB" << RESET << endl;
                    cout << CYAN << "      Cylinders: " << disk_geo.Cylinders.QuadPart << RESET << endl;
                    cout << CYAN << "      Tracks per Cylinder: " << disk_geo.TracksPerCylinder << RESET << endl;
                    cout << CYAN << "      Sectors per Track: " << disk_geo.SectorsPerTrack << RESET << endl;
                    cout << CYAN << "      Bytes per Sector: " << disk_geo.BytesPerSector << RESET << endl;
                    
                    // Determine disk type (SSD vs HDD)
                    STORAGE_PROPERTY_QUERY query;
                    query.PropertyId = StorageDeviceSeekPenaltyProperty;
                    query.QueryType = PropertyStandardQuery;
                    
                    DEVICE_SEEK_PENALTY_DESCRIPTOR penalty;
                    if (DeviceIoControl(hDisk, IOCTL_STORAGE_QUERY_PROPERTY,
                                       &query, sizeof(query), &penalty, sizeof(penalty),
                                       &bytes_returned, NULL)) {
                        if (penalty.IncursSeekPenalty) {
                            cout << BRIGHT_BLUE << "      Type: HDD (Hard Disk Drive)" << RESET << endl;
                        } else {
                            cout << BRIGHT_GREEN << "      Type: SSD (Solid State Drive)" << RESET << endl;
                        }
                    }
                }
                
                CloseHandle(hDisk);
                cout << endl;
            }
        }
    }
    
    void analyzeDriverInfo() {
        printSectionHeader("DEVICE DRIVERS & HARDWARE ANALYSIS");
        
        cout << BRIGHT_GREEN << "🔧 Installed Device Drivers:\n" << RESET;
        
        HDEVINFO device_info_set = SetupDiGetClassDevs(NULL, NULL, NULL, 
                                                       DIGCF_PRESENT | DIGCF_ALLCLASSES);
        
        if (device_info_set == INVALID_HANDLE_VALUE) {
            cout << RED << "❌ Unable to enumerate devices" << RESET << endl;
            return;
        }
        
        SP_DEVINFO_DATA device_info_data;
        device_info_data.cbSize = sizeof(SP_DEVINFO_DATA);
        
        vector<string> device_categories;
        int device_count = 0;
        
        for (DWORD i = 0; SetupDiEnumDeviceInfo(device_info_set, i, &device_info_data); i++) {
            char device_desc[256];
            char driver_version[256];
            char hardware_id[256];
            
            if (SetupDiGetDeviceRegistryPropertyA(device_info_set, &device_info_data,
                                                 SPDRP_DEVICEDESC, NULL,
                                                 (PBYTE)device_desc, sizeof(device_desc), NULL)) {
                
                cout << GREEN << "  ├─ " << device_desc << RESET;
                
                // Get driver version
                if (SetupDiGetDeviceRegistryPropertyA(device_info_set, &device_info_data,
                                                     SPDRP_DRIVER_VERSION, NULL,
                                                     (PBYTE)driver_version, sizeof(driver_version), NULL)) {
                    cout << YELLOW << " (v" << driver_version << ")" << RESET;
                }
                
                // Get hardware ID
                if (SetupDiGetDeviceRegistryPropertyA(device_info_set, &device_info_data,
                                                     SPDRP_HARDWAREID, NULL,
                                                     (PBYTE)hardware_id, sizeof(hardware_id), NULL)) {
                    cout << CYAN << endl << "      Hardware ID: " << hardware_id << RESET;
                }
                
                cout << endl;
                device_count++;
                
                if (device_count > 25) {  // Limit output for readability
                    cout << BRIGHT_CYAN << "  └─ ... and " << (i - 25) << " more devices (showing first 25)" << RESET << endl;
                    break;
                }
            }
        }
        
        SetupDiDestroyDeviceInfoList(device_info_set);
        
        cout << BRIGHT_YELLOW << "\n📊 Driver Statistics:" << RESET << endl;
        cout << WHITE << "  Total devices with drivers: " << device_count << "+" << RESET << endl;
    }
    
    void analyzeKernelInfo() {
        printSectionHeader("WINDOWS KERNEL & SYSTEM ANALYSIS");
        
        // Windows version information
        cout << BRIGHT_YELLOW << "🖥️  Windows System Information:\n" << RESET;
        
        OSVERSIONINFOEXA os_info;
        ZeroMemory(&os_info, sizeof(OSVERSIONINFOEXA));
        os_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXA);
        
        #pragma warning(push)
        #pragma warning(disable: 4996)
        if (GetVersionExA((OSVERSIONINFOA*)&os_info)) {
            cout << GREEN << "  ├─ OS Version: " << os_info.dwMajorVersion << "." 
                 << os_info.dwMinorVersion << "." << os_info.dwBuildNumber << RESET << endl;
            cout << CYAN << "  ├─ Service Pack: " << os_info.szCSDVersion << RESET << endl;
            cout << YELLOW << "  ├─ Platform ID: " << os_info.dwPlatformId << RESET << endl;
            
            // Determine Windows version name
            cout << MAGENTA << "  ├─ Windows Edition: ";
            if (os_info.dwMajorVersion == 10) {
                if (os_info.dwBuildNumber >= 22000) {
                    cout << "Windows 11";
                } else {
                    cout << "Windows 10";
                }
            } else if (os_info.dwMajorVersion == 6) {
                if (os_info.dwMinorVersion == 3) cout << "Windows 8.1";
                else if (os_info.dwMinorVersion == 2) cout << "Windows 8";
                else if (os_info.dwMinorVersion == 1) cout << "Windows 7";
                else cout << "Windows Vista";
            }
            cout << RESET << endl;
        }
        #pragma warning(pop)
        
        // System architecture information
        SYSTEM_INFO sys_info;
        GetSystemInfo(&sys_info);
        
        cout << BRIGHT_BLUE << "\n🏗️  System Architecture:\n" << RESET;
        cout << WHITE << "  ├─ Processor Architecture: ";
        switch (sys_info.wProcessorArchitecture) {
            case PROCESSOR_ARCHITECTURE_AMD64:
                cout << BRIGHT_GREEN << "x64 (AMD64)" << RESET;
                break;
            case PROCESSOR_ARCHITECTURE_INTEL:
                cout << BRIGHT_BLUE << "x86 (Intel)" << RESET;
                break;
            case PROCESSOR_ARCHITECTURE_ARM:
                cout << BRIGHT_CYAN << "ARM" << RESET;
                break;
            case PROCESSOR_ARCHITECTURE_ARM64:
                cout << BRIGHT_MAGENTA << "ARM64" << RESET;
                break;
            default:
                cout << RED << "Unknown" << RESET;
        }
        cout << endl;
        
        cout << YELLOW << "  ├─ Number of Processors: " << sys_info.dwNumberOfProcessors << RESET << endl;
        cout << CYAN << "  ├─ Page Size: " << sys_info.dwPageSize << " bytes" << RESET << endl;
        cout << GREEN << "  ├─ Processor Type: " << sys_info.dwProcessorType << RESET << endl;
        cout << MAGENTA << "  └─ Active Processor Mask: 0x" << hex << sys_info.dwActiveProcessorMask << dec << RESET << endl;
        
        // Memory information
        MEMORYSTATUSEX mem_info;
        mem_info.dwLength = sizeof(MEMORYSTATUSEX);
        if (GlobalMemoryStatusEx(&mem_info)) {
            cout << BRIGHT_CYAN << "\n💾 Memory Information:\n" << RESET;
            double total_ram_gb = (double)mem_info.ullTotalPhys / (1024.0 * 1024.0 * 1024.0);
            double avail_ram_gb = (double)mem_info.ullAvailPhys / (1024.0 * 1024.0 * 1024.0);
            double used_ram_gb = total_ram_gb - avail_ram_gb;
            int ram_usage = (int)((used_ram_gb / total_ram_gb) * 100);
            
            cout << WHITE << "  ├─ Total Physical RAM: " << fixed << setprecision(2) << total_ram_gb << " GB" << RESET << endl;
            cout << GREEN << "  ├─ Available RAM: " << avail_ram_gb << " GB" << RESET << endl;
            cout << YELLOW << "  ├─ Used RAM: " << used_ram_gb << " GB" << RESET << endl;
            
            printProgressBar(ram_usage, "  └─ RAM Usage");
        }
    }

#else  // Linux/Unix implementation

    void analyzeDiskInfo() {
        printSectionHeader("HARD DISK & STORAGE ANALYSIS");
        
        cout << BRIGHT_GREEN << "💾 Block Devices:\n" << RESET;
        
        // Read /proc/partitions
        ifstream partitions("/proc/partitions");
        if (partitions.is_open()) {
            string line;
            getline(partitions, line); // Skip header
            getline(partitions, line); // Skip header
            
            while (getline(partitions, line)) {
                istringstream iss(line);
                int major, minor;
                unsigned long blocks;
                string name;
                
                if (iss >> major >> minor >> blocks >> name) {
                    double size_gb = (double)blocks / (1024.0 * 1024.0);
                    
                    cout << GREEN << "  ├─ /dev/" << name;
                    cout << WHITE << " - " << fixed << setprecision(2) << size_gb << " GB" << RESET;
                    
                    // Identify disk type
                    if (name.find("sd") == 0 && name.length() == 3) {
                        cout << YELLOW << " (SATA/SCSI Disk)" << RESET;
                    } else if (name.find("nvme") == 0 && name.find("n1") != string::npos && name.find("p") == string::npos) {
                        cout << BRIGHT_CYAN << " (NVMe SSD)" << RESET;
                    } else if (name.find("mmcblk") == 0) {
                        cout << MAGENTA << " (MMC/SD Card)" << RESET;
                    } else if (name.length() > 3) {
                        cout << CYAN << " (Partition)" << RESET;
                    }
                    cout << endl;
                }
            }
            partitions.close();
        }
        
        // Mounted filesystems
        cout << BRIGHT_BLUE << "\n📁 Mounted Filesystems:\n" << RESET;
        ifstream mounts("/proc/mounts");
        if (mounts.is_open()) {
            string line;
            while (getline(mounts, line)) {
                istringstream iss(line);
                string device, mountpoint, fstype;
                if (iss >> device >> mountpoint >> fstype) {
                    if (device.find("/dev/") == 0 && mountpoint != "/" && 
                        mountpoint.find("/proc") != 0 && mountpoint.find("/sys") != 0 &&
                        mountpoint.find("/dev") != 0) {
                        
                        struct statvfs stat;
                        if (statvfs(mountpoint.c_str(), &stat) == 0) {
                            double total_gb = (double)(stat.f_blocks * stat.f_frsize) / (1024.0*1024.0*1024.0);
                            double free_gb = (double)(stat.f_bavail * stat.f_frsize) / (1024.0*1024.0*1024.0);
                            double used_gb = total_gb - free_gb;
                            int usage_percent = total_gb > 0 ? (int)((used_gb / total_gb) * 100) : 0;
                            
                            cout << YELLOW << "  ├─ " << device << " on " << mountpoint 
                                 << " (" << fstype << ")" << RESET << endl;
                            cout << WHITE << "      Total: " << fixed << setprecision(2) << total_gb 
                                 << " GB, Used: " << used_gb << " GB, Free: " << free_gb << " GB" << RESET << endl;
                            
                            printProgressBar(usage_percent, "      Usage");
                        }
                    }
                }
            }
            mounts.close();
        }
    }
    
    void analyzeDriverInfo() {
        printSectionHeader("KERNEL MODULES & DRIVERS ANALYSIS");
        
        cout << BRIGHT_GREEN << "🔧 Loaded Kernel Modules:\n" << RESET;
        
        ifstream modules("/proc/modules");
        if (modules.is_open()) {
            string line;
            int count = 0;
            
            while (getline(modules, line) && count < 30) {
                istringstream iss(line);
                string module_name, dependencies;
                int size, instances;
                
                if (iss >> module_name >> size >> instances >> dependencies) {
                    cout << GREEN << "  ├─ " << module_name << RESET;
                    cout << YELLOW << " (" << size << " KB)" << RESET;
                    
                    if (instances > 0) {
                        cout << CYAN << " - Used by: " << instances << RESET;
                    }
                    
                    if (dependencies != "-") {
                        cout << MAGENTA << " - Deps: " << dependencies << RESET;
                    }
                    cout << endl;
                    count++;
                }
            }
            modules.close();
            
            if (count >= 30) {
                cout << BRIGHT_CYAN << "  └─ ... and more modules (showing first 30)" << RESET << endl;
            }
        }
        
        // Hardware information
        cout << BRIGHT_MAGENTA << "\n🖥️  Hardware Buses:\n" << RESET;
        DIR* bus_dir = opendir("/sys/bus");
        if (bus_dir) {
            struct dirent* entry;
            while ((entry = readdir(bus_dir)) != NULL) {
                if (entry->d_name[0] != '.') {
                    cout << BRIGHT_BLUE << "  ├─ " << entry->d_name << " bus" << RESET << endl;
                }
            }
            closedir(bus_dir);
        }
        
        // PCI devices
        cout << BRIGHT_YELLOW << "\n🔌 PCI Devices:\n" << RESET;
        system("lspci 2>/dev/null | head -15 | while read line; do echo \"  ├─ $line\"; done");
    }
    
    void analyzeKernelInfo() {
        printSectionHeader("LINUX KERNEL & SYSTEM ANALYSIS");
        
        struct utsname sys_info;
        if (uname(&sys_info) == 0) {
            cout << BRIGHT_YELLOW << "🐧 Linux Kernel Information:\n" << RESET;
            cout << GREEN << "  ├─ System: " << sys_info.sysname << RESET << endl;
            cout << CYAN << "  ├─ Kernel Version: " << sys_info.release << RESET << endl;
            cout << YELLOW << "  ├─ Kernel Build: " << sys_info.version << RESET << endl;
            cout << MAGENTA << "  ├─ Architecture: " << sys_info.machine << RESET << endl;
            cout << WHITE << "  └─ Hostname: " << sys_info.nodename << RESET << endl;
        }
        
        // Available kernels
        cout << BRIGHT_GREEN << "\n🥾 Available Kernels:\n" << RESET;
        DIR* boot_dir = opendir("/boot");
        if (boot_dir) {
            struct dirent* entry;
            while ((entry = readdir(boot_dir)) != NULL) {
                string filename = entry->d_name;
                if (filename.find("vmlinuz") == 0) {
                    cout << BRIGHT_CYAN << "  ├─ " << filename << RESET << endl;
                }
            }
            closedir(boot_dir);
        }
        
        // Kernel parameters
        cout << YELLOW << "\n⚙️  Current Kernel Parameters:\n" << RESET;
        ifstream cmdline("/proc/cmdline");
        if (cmdline.is_open()) {
            string line;
            if (getline(cmdline, line)) {
                cout << WHITE << "  " << line << RESET << endl;
            }
            cmdline.close();
        }
        
        // System information
        struct sysinfo si;
        if (sysinfo(&si) == 0) {
            cout << BRIGHT_BLUE << "\n💾 System Resources:\n" << RESET;
            
            double total_ram_gb = (double)si.totalram * si.mem_unit / (1024.0 * 1024.0 * 1024.0);
            double free_ram_gb = (double)si.freeram * si.mem_unit / (1024.0 * 1024.0 * 1024.0);
            double used_ram_gb = total_ram_gb - free_ram_gb;
            int ram_usage = (int)((used_ram_gb / total_ram_gb) * 100);
            
            cout << WHITE << "  ├─ Total RAM: " << fixed << setprecision(2) << total_ram_gb << " GB" << RESET << endl;
            cout << GREEN << "  ├─ Free RAM: " << free_ram_gb << " GB" << RESET << endl;
            cout << YELLOW << "  ├─ Used RAM: " << used_ram_gb << " GB" << RESET << endl;
            cout << CYAN << "  ├─ Uptime: " << si.uptime / 3600 << " hours" << RESET << endl;
            cout << MAGENTA << "  └─ Load Average: " << (float)si.loads[0]/65536.0 << RESET << endl;
            
            printProgressBar(ram_usage, "  RAM Usage");
        }
    }

#endif

    void runDiagnostic() {
        clearScreen();
        beep(2);
        
        printAnimatedTitle();
        
        cout << endl << BRIGHT_CYAN << "🔍 Initializing comprehensive system diagnostic..." << RESET << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        
        beep();
        analyzeDiskInfo();
        this_thread::sleep_for(chrono::milliseconds(500));
        
        beep();
        analyzeDriverInfo();
        this_thread::sleep_for(chrono::milliseconds(500));
        
        beep();
        analyzeKernelInfo();
        
        cout << endl << BRIGHT_GREEN << "✅ System diagnostic completed successfully!" << RESET << endl;
        cout << BRIGHT_YELLOW << "📊 All system components analyzed and reported." << RESET << endl;
        
        cout << endl << CYAN << "Press Enter to exit..." << RESET;
        cin.get();
        
        // Victory beep sequence
        for (int i = 0; i < 5; i++) {
            beep();
            this_thread::sleep_for(chrono::milliseconds(150));
        }
    }
};

int main() {
    SystemAnalyzer analyzer;
    analyzer.runDiagnostic();
    return 0;
}