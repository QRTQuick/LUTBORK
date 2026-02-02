#include "kernel_info.h"
#include "colors.h"
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>

void get_kernel_info(void) {
    print_section_header("KERNEL INFORMATION");
    show_system_info();
    show_memory_info();
}

void show_system_info(void) {
    printf(BRIGHT_YELLOW "Windows Kernel Information:\n" RESET);
    
    // Windows version info
    OSVERSIONINFOEXA os_info;
    ZeroMemory(&os_info, sizeof(OSVERSIONINFOEXA));
    os_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXA);
    
    #pragma warning(push)
    #pragma warning(disable: 4996)
    if (GetVersionExA((OSVERSIONINFOA*)&os_info)) {
        printf(GREEN "  + Version: %d.%d.%d\n" RESET, 
               os_info.dwMajorVersion, os_info.dwMinorVersion, os_info.dwBuildNumber);
        printf(CYAN "  + Service Pack: %s\n" RESET, os_info.szCSDVersion);
        printf(YELLOW "  + Platform ID: %d\n" RESET, os_info.dwPlatformId);
        
        // Determine Windows version name
        printf(MAGENTA "  + Windows Edition: ");
        if (os_info.dwMajorVersion == 10) {
            if (os_info.dwBuildNumber >= 22000) {
                printf("Windows 11");
            } else {
                printf("Windows 10");
            }
        } else if (os_info.dwMajorVersion == 6) {
            if (os_info.dwMinorVersion == 3) printf("Windows 8.1");
            else if (os_info.dwMinorVersion == 2) printf("Windows 8");
            else if (os_info.dwMinorVersion == 1) printf("Windows 7");
            else printf("Windows Vista");
        }
        printf(RESET "\n");
    }
    #pragma warning(pop)
    
    // System info
    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);
    
    printf(MAGENTA "\nSystem Architecture:\n" RESET);
    printf(WHITE "  + Processor Architecture: ");
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
    printf(YELLOW "  + Number of Processors: %d\n" RESET, sys_info.dwNumberOfProcessors);
    printf(CYAN "  + Page Size: %d bytes\n" RESET, sys_info.dwPageSize);
}

void show_memory_info(void) {
    printf(BRIGHT_CYAN "\nMemory Information:\n" RESET);
    
    MEMORYSTATUSEX mem_info;
    mem_info.dwLength = sizeof(MEMORYSTATUSEX);
    if (GlobalMemoryStatusEx(&mem_info)) {
        double total_ram_gb = (double)mem_info.ullTotalPhys / (1024.0 * 1024.0 * 1024.0);
        double avail_ram_gb = (double)mem_info.ullAvailPhys / (1024.0 * 1024.0 * 1024.0);
        double used_ram_gb = total_ram_gb - avail_ram_gb;
        int ram_usage = (int)((used_ram_gb / total_ram_gb) * 100);
        
        printf(WHITE "  + Total Physical RAM: %.2f GB\n" RESET, total_ram_gb);
        printf(GREEN "  + Available RAM: %.2f GB\n" RESET, avail_ram_gb);
        printf(YELLOW "  + Used RAM: %.2f GB\n" RESET, used_ram_gb);
        
        char progress_label[64];
        sprintf(progress_label, "  + RAM Usage");
        print_progress_bar(ram_usage, progress_label);
    }
}

void show_available_kernels(void) {
    printf(CYAN "\nWindows doesn't have multiple kernels like Linux\n" RESET);
}

void show_kernel_parameters(void) {
    printf(YELLOW "\nUse 'msconfig' or 'bcdedit' to view boot parameters\n" RESET);
}

#else  // Linux implementation

#include <sys/utsname.h>
#include <dirent.h>
#include <sys/sysinfo.h>
#include <unistd.h>

void get_kernel_info(void) {
    print_section_header("KERNEL INFORMATION");
    show_system_info();
    show_available_kernels();
    show_kernel_parameters();
    show_memory_info();
}

void show_system_info(void) {
    struct utsname sys_info;
    if (uname(&sys_info) == 0) {
        printf(BRIGHT_YELLOW "Linux Kernel Information:\n" RESET);
        printf(GREEN "  + System: %s\n" RESET, sys_info.sysname);
        printf(CYAN "  + Kernel Version: %s\n" RESET, sys_info.release);
        printf(YELLOW "  + Kernel Build: %s\n" RESET, sys_info.version);
        printf(MAGENTA "  + Architecture: %s\n" RESET, sys_info.machine);
        printf(WHITE "  + Hostname: %s\n" RESET, sys_info.nodename);
    }
}

void show_available_kernels(void) {
    printf(BRIGHT_GREEN "\nAvailable Kernels in /boot:\n" RESET);
    DIR *boot_dir = opendir("/boot");
    if (boot_dir) {
        struct dirent *entry;
        while ((entry = readdir(boot_dir)) != NULL) {
            if (strstr(entry->d_name, "vmlinuz")) {
                printf(BRIGHT_CYAN "  + %s\n" RESET, entry->d_name);
            }
        }
        closedir(boot_dir);
    }
}

void show_kernel_parameters(void) {
    printf(YELLOW "\nCurrent Kernel Parameters:\n" RESET);
    FILE *cmdline = fopen("/proc/cmdline", "r");
    if (cmdline) {
        char line[1024];
        if (fgets(line, sizeof(line), cmdline)) {
            printf(WHITE "  %s\n" RESET, line);
        }
        fclose(cmdline);
    }
}

void show_memory_info(void) {
    struct sysinfo si;
    if (sysinfo(&si) == 0) {
        printf(BRIGHT_BLUE "\nSystem Resources:\n" RESET);
        
        double total_ram_gb = (double)si.totalram * si.mem_unit / (1024.0 * 1024.0 * 1024.0);
        double free_ram_gb = (double)si.freeram * si.mem_unit / (1024.0 * 1024.0 * 1024.0);
        double used_ram_gb = total_ram_gb - free_ram_gb;
        int ram_usage = (int)((used_ram_gb / total_ram_gb) * 100);
        
        printf(WHITE "  + Total RAM: %.2f GB\n" RESET, total_ram_gb);
        printf(GREEN "  + Free RAM: %.2f GB\n" RESET, free_ram_gb);
        printf(YELLOW "  + Used RAM: %.2f GB\n" RESET, used_ram_gb);
        printf(CYAN "  + Uptime: %ld hours\n" RESET, si.uptime / 3600);
        printf(MAGENTA "  + Load Average: %.2f\n" RESET, (float)si.loads[0]/65536.0);
        
        char progress_label[64];
        sprintf(progress_label, "  + RAM Usage");
        print_progress_bar(ram_usage, progress_label);
    }
}

#endif