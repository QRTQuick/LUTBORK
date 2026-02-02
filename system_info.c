#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#include <winioctl.h>
#include <setupapi.h>
#include <devguid.h>
#pragma comment(lib, "setupapi.lib")
#else
#include <sys/utsname.h>
#include <dirent.h>
#include <sys/statvfs.h>
#endif

// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BRIGHT_GREEN   "\033[92m"
#define BRIGHT_YELLOW  "\033[93m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_CYAN    "\033[96m"

void beep() {
    printf("\a");
    fflush(stdout);
}

void clear_screen() {
    printf("\033[2J\033[H");
}

void print_header(const char* title) {
    printf(BRIGHT_BLUE "╔══════════════════════════════════════════════════════════════╗\n");
    printf("║" BRIGHT_YELLOW "%-62s" BRIGHT_BLUE "║\n", title);
    printf("╚══════════════════════════════════════════════════════════════╝\n" RESET);
}

void print_section_header(const char* section) {
    printf(CYAN "\n▓▓▓ %s ▓▓▓\n" RESET, section);
    printf(BLUE "═══════════════════════════════════════════════════════════════\n" RESET);
}

#ifdef _WIN32
void get_disk_info() {
    print_section_header("HARD DISK INFORMATION");
    
    DWORD drives = GetLogicalDrives();
    char drive_letter[4] = "A:\\";
    
    for (int i = 0; i < 26; i++) {
        if (drives & (1 << i)) {
            drive_letter[0] = 'A' + i;
            UINT drive_type = GetDriveTypeA(drive_letter);
            
            printf(GREEN "🖴 Drive %c:\\ - ", 'A' + i);
            
            switch (drive_type) {
                case DRIVE_FIXED:
                    printf(YELLOW "Fixed Drive (Hard Disk)" RESET);
                    break;
                case DRIVE_REMOVABLE:
                    printf(MAGENTA "Removable Drive (Floppy/USB)" RESET);
                    break;
                case DRIVE_REMOTE:
                    printf(CYAN "Network Drive" RESET);
                    break;
                case DRIVE_CDROM:
                    printf(BRIGHT_YELLOW "CD-ROM/DVD Drive" RESET);
                    break;
                case DRIVE_RAMDISK:
                    printf(BRIGHT_CYAN "RAM Disk" RESET);
                    break;
                default:
                    printf(RED "Unknown Drive Type" RESET);
            }
            
            // Get disk space info
            ULARGE_INTEGER free_bytes, total_bytes;
            if (GetDiskFreeSpaceExA(drive_letter, &free_bytes, &total_bytes, NULL)) {
                double total_gb = (double)total_bytes.QuadPart / (1024 * 1024 * 1024);
                double free_gb = (double)free_bytes.QuadPart / (1024 * 1024 * 1024);
                printf(WHITE " - Total: %.2f GB, Free: %.2f GB" RESET, total_gb, free_gb);
            }
            printf("\n");
        }
    }
    
    // Get physical disk information
    printf(BRIGHT_GREEN "\n💾 Physical Disks:\n" RESET);
    for (int i = 0; i < 10; i++) {
        char disk_path[50];
        sprintf(disk_path, "\\\\.\\PhysicalDrive%d", i);
        
        HANDLE hDisk = CreateFileA(disk_path, 0, FILE_SHARE_READ | FILE_SHARE_WRITE,
                                  NULL, OPEN_EXISTING, 0, NULL);
        
        if (hDisk != INVALID_HANDLE_VALUE) {
            DISK_GEOMETRY disk_geo;
            DWORD bytes_returned;
            
            if (DeviceIoControl(hDisk, IOCTL_DISK_GET_DRIVE_GEOMETRY, NULL, 0,
                               &disk_geo, sizeof(disk_geo), &bytes_returned, NULL)) {
                
                ULONGLONG disk_size = disk_geo.Cylinders.QuadPart *
                                     disk_geo.TracksPerCylinder *
                                     disk_geo.SectorsPerTrack *
                                     disk_geo.BytesPerSector;
                
                double size_gb = (double)disk_size / (1024 * 1024 * 1024);
                
                printf(YELLOW "  📀 Physical Drive %d: %.2f GB", i, size_gb);
                
                // Try to determine if it's SSD or HDD
                STORAGE_PROPERTY_QUERY query;
                query.PropertyId = StorageDeviceSeekPenaltyProperty;
                query.QueryType = PropertyStandardQuery;
                
                DEVICE_SEEK_PENALTY_DESCRIPTOR penalty;
                if (DeviceIoControl(hDisk, IOCTL_STORAGE_QUERY_PROPERTY,
                                   &query, sizeof(query), &penalty, sizeof(penalty),
                                   &bytes_returned, NULL)) {
                    if (penalty.IncursSeekPenalty) {
                        printf(CYAN " (HDD)" RESET);
                    } else {
                        printf(BRIGHT_CYAN " (SSD)" RESET);
                    }
                }
                printf("\n");
            }
            CloseHandle(hDisk);
        }
    }
}

void get_driver_info() {
    print_section_header("INSTALLED DRIVERS");
    
    HDEVINFO device_info_set = SetupDiGetClassDevs(NULL, NULL, NULL, 
                                                   DIGCF_PRESENT | DIGCF_ALLCLASSES);
    
    if (device_info_set == INVALID_HANDLE_VALUE) {
        printf(RED "❌ Unable to enumerate devices\n" RESET);
        return;
    }
    
    SP_DEVINFO_DATA device_info_data;
    device_info_data.cbSize = sizeof(SP_DEVINFO_DATA);
    
    int device_count = 0;
    for (DWORD i = 0; SetupDiEnumDeviceInfo(device_info_set, i, &device_info_data); i++) {
        char device_desc[256];
        char driver_version[256];
        
        if (SetupDiGetDeviceRegistryPropertyA(device_info_set, &device_info_data,
                                             SPDRP_DEVICEDESC, NULL,
                                             (PBYTE)device_desc, sizeof(device_desc), NULL)) {
            
            printf(GREEN "🔧 %s" RESET, device_desc);
            
            // Try to get driver version
            if (SetupDiGetDeviceRegistryPropertyA(device_info_set, &device_info_data,
                                                 SPDRP_DRIVER_VERSION, NULL,
                                                 (PBYTE)driver_version, sizeof(driver_version), NULL)) {
                printf(YELLOW " - Version: %s" RESET, driver_version);
            }
            printf("\n");
            
            device_count++;
            if (device_count > 20) {  // Limit output
                printf(CYAN "... and more drivers (showing first 20)\n" RESET);
                break;
            }
        }
    }
    
    SetupDiDestroyDeviceInfoList(device_info_set);
    printf(BRIGHT_GREEN "\n📊 Total devices with drivers: %d+\n" RESET, device_count);
}

void get_kernel_info() {
    print_section_header("KERNEL INFORMATION");
    
    // Windows version info
    OSVERSIONINFOEXA os_info;
    ZeroMemory(&os_info, sizeof(OSVERSIONINFOEXA));
    os_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXA);
    
    // Note: GetVersionEx is deprecated but still works for demonstration
    #pragma warning(push)
    #pragma warning(disable: 4996)
    if (GetVersionExA((OSVERSIONINFOA*)&os_info)) {
        printf(BRIGHT_YELLOW "🖥️  Windows Kernel Information:\n" RESET);
        printf(GREEN "   Version: %d.%d.%d\n" RESET, 
               os_info.dwMajorVersion, os_info.dwMinorVersion, os_info.dwBuildNumber);
        printf(CYAN "   Service Pack: %s\n" RESET, os_info.szCSDVersion);
        printf(YELLOW "   Platform ID: %d\n" RESET, os_info.dwPlatformId);
    }
    #pragma warning(pop)
    
    // System info
    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);
    
    printf(MAGENTA "\n🏗️  System Architecture:\n" RESET);
    printf(WHITE "   Processor Architecture: ");
    switch (sys_info.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64:
            printf(BRIGHT_GREEN "x64 (AMD64)" RESET);
            break;
        case PROCESSOR_ARCHITECTURE_INTEL:
            printf(BRIGHT_BLUE "x86 (Intel)" RESET);
            break;
        case PROCESSOR_ARCHITECTURE_ARM:
            printf(BRIGHT_CYAN "ARM" RESET);
            break;
        case PROCESSOR_ARCHITECTURE_ARM64:
            printf(BRIGHT_MAGENTA "ARM64" RESET);
            break;
        default:
            printf(RED "Unknown" RESET);
    }
    printf("\n");
    printf(YELLOW "   Number of Processors: %d\n" RESET, sys_info.dwNumberOfProcessors);
    printf(CYAN "   Page Size: %d bytes\n" RESET, sys_info.dwPageSize);
}

#else  // Linux/Unix systems

void get_disk_info() {
    print_section_header("HARD DISK INFORMATION");
    
    // Read /proc/partitions for disk info
    FILE *partitions = fopen("/proc/partitions", "r");
    if (partitions) {
        char line[256];
        printf(BRIGHT_GREEN "💾 Disk Partitions:\n" RESET);
        
        // Skip header lines
        fgets(line, sizeof(line), partitions);
        fgets(line, sizeof(line), partitions);
        
        while (fgets(line, sizeof(line), partitions)) {
            int major, minor;
            unsigned long blocks;
            char name[32];
            
            if (sscanf(line, "%d %d %lu %s", &major, &minor, &blocks, name) == 4) {
                double size_gb = (double)blocks / (1024 * 1024);
                printf(GREEN "🖴 /dev/%s - %.2f GB" RESET, name, size_gb);
                
                // Check if it's a full disk (not partition)
                if (strstr(name, "sd") && strlen(name) == 3) {
                    printf(YELLOW " (Full Disk)" RESET);
                } else if (strstr(name, "nvme") && strstr(name, "n1") && !strstr(name, "p")) {
                    printf(BRIGHT_CYAN " (NVMe SSD)" RESET);
                }
                printf("\n");
            }
        }
        fclose(partitions);
    }
    
    // Check mounted filesystems
    printf(CYAN "\n📁 Mounted Filesystems:\n" RESET);
    FILE *mounts = fopen("/proc/mounts", "r");
    if (mounts) {
        char line[512];
        while (fgets(line, sizeof(line), mounts)) {
            char device[128], mountpoint[128], fstype[32];
            if (sscanf(line, "%s %s %s", device, mountpoint, fstype) == 3) {
                if (strstr(device, "/dev/") && strcmp(mountpoint, "/") != 0 && 
                    strcmp(mountpoint, "/proc") != 0 && strcmp(mountpoint, "/sys") != 0) {
                    
                    struct statvfs stat;
                    if (statvfs(mountpoint, &stat) == 0) {
                        double total_gb = (double)(stat.f_blocks * stat.f_frsize) / (1024*1024*1024);
                        double free_gb = (double)(stat.f_bavail * stat.f_frsize) / (1024*1024*1024);
                        
                        printf(YELLOW "  📂 %s on %s (%s) - %.2f GB total, %.2f GB free\n" RESET,
                               device, mountpoint, fstype, total_gb, free_gb);
                    }
                }
            }
        }
        fclose(mounts);
    }
}

void get_driver_info() {
    print_section_header("LOADED KERNEL MODULES (DRIVERS)");
    
    FILE *modules = fopen("/proc/modules", "r");
    if (modules) {
        char line[256];
        int count = 0;
        
        while (fgets(line, sizeof(line), modules) && count < 30) {
            char module_name[64];
            int size, instances;
            char dependencies[128];
            
            if (sscanf(line, "%s %d %d %s", module_name, &size, &instances, dependencies) >= 3) {
                printf(GREEN "🔧 %s" RESET, module_name);
                printf(YELLOW " - Size: %d KB" RESET, size);
                if (instances > 0) {
                    printf(CYAN " - Used by: %d" RESET, instances);
                }
                printf("\n");
                count++;
            }
        }
        fclose(modules);
        
        if (count >= 30) {
            printf(BRIGHT_CYAN "... and more modules (showing first 30)\n" RESET);
        }
    }
    
    // Show driver directories
    printf(MAGENTA "\n📁 Driver Directories:\n" RESET);
    DIR *driver_dir = opendir("/sys/bus");
    if (driver_dir) {
        struct dirent *entry;
        while ((entry = readdir(driver_dir)) != NULL) {
            if (entry->d_name[0] != '.') {
                printf(BRIGHT_BLUE "  🚌 Bus Type: %s\n" RESET, entry->d_name);
            }
        }
        closedir(driver_dir);
    }
}

void get_kernel_info() {
    print_section_header("KERNEL INFORMATION");
    
    struct utsname sys_info;
    if (uname(&sys_info) == 0) {
        printf(BRIGHT_YELLOW "🐧 Linux Kernel Information:\n" RESET);
        printf(GREEN "   System: %s\n" RESET, sys_info.sysname);
        printf(CYAN "   Kernel Version: %s\n" RESET, sys_info.release);
        printf(YELLOW "   Kernel Build: %s\n" RESET, sys_info.version);
        printf(MAGENTA "   Architecture: %s\n" RESET, sys_info.machine);
        printf(WHITE "   Hostname: %s\n" RESET, sys_info.nodename);
    }
    
    // Check available kernels in /boot
    printf(BRIGHT_GREEN "\n🥾 Available Kernels in /boot:\n" RESET);
    DIR *boot_dir = opendir("/boot");
    if (boot_dir) {
        struct dirent *entry;
        while ((entry = readdir(boot_dir)) != NULL) {
            if (strstr(entry->d_name, "vmlinuz")) {
                printf(BRIGHT_CYAN "  🔧 %s\n" RESET, entry->d_name);
            }
        }
        closedir(boot_dir);
    }
    
    // Kernel parameters
    printf(YELLOW "\n⚙️  Current Kernel Parameters:\n" RESET);
    FILE *cmdline = fopen("/proc/cmdline", "r");
    if (cmdline) {
        char line[1024];
        if (fgets(line, sizeof(line), cmdline)) {
            printf(WHITE "   %s\n" RESET, line);
        }
        fclose(cmdline);
    }
}

#endif

int main() {
    clear_screen();
    beep();
    
    // Main title
    printf(BRIGHT_YELLOW);
    printf("  ███████╗██╗   ██╗███████╗████████╗███████╗███╗   ███╗\n");
    printf("  ██╔════╝╚██╗ ██╔╝██╔════╝╚══██╔══╝██╔════╝████╗ ████║\n");
    printf("  ███████╗ ╚████╔╝ ███████╗   ██║   █████╗  ██╔████╔██║\n");
    printf("  ╚════██║  ╚██╔╝  ╚════██║   ██║   ██╔══╝  ██║╚██╔╝██║\n");
    printf("  ███████║   ██║   ███████║   ██║   ███████╗██║ ╚═╝ ██║\n");
    printf("  ╚══════╝   ╚═╝   ╚══════╝   ╚═╝   ╚══════╝╚═╝     ╚═╝\n");
    printf("                                                        \n");
    printf("  ██╗███╗   ██╗███████╗ ██████╗                        \n");
    printf("  ██║████╗  ██║██╔════╝██╔═══██╗                       \n");
    printf("  ██║██╔██╗ ██║█████╗  ██║   ██║                       \n");
    printf("  ██║██║╚██╗██║██╔══╝  ██║   ██║                       \n");
    printf("  ██║██║ ╚████║██║     ╚██████╔╝                       \n");
    printf("  ╚═╝╚═╝  ╚═══╝╚═╝      ╚═════╝                        \n");
    printf(RESET);
    
    print_header("    COMPREHENSIVE SYSTEM INFORMATION TOOL");
    
    printf(BRIGHT_CYAN "\n🔍 Scanning your system...\n" RESET);
    beep();
    usleep(500000);  // 0.5 second delay
    
    get_disk_info();
    printf("\n");
    beep();
    
    get_driver_info();
    printf("\n");
    beep();
    
    get_kernel_info();
    
    printf(BRIGHT_GREEN "\n✅ System scan completed!\n" RESET);
    printf(CYAN "Press Enter to exit..." RESET);
    getchar();
    
    // Final beep sequence
    for (int i = 0; i < 3; i++) {
        beep();
        usleep(200000);
    }
    
    return 0;
}