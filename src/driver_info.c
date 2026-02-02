#include "driver_info.h"
#include "colors.h"
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>

void get_driver_info(void) {
    print_section_header("INSTALLED DRIVERS");
    enumerate_devices();
}

void enumerate_devices(void) {
    printf(BRIGHT_GREEN "Device Drivers:\n" RESET);
    
    HDEVINFO device_info_set = SetupDiGetClassDevs(NULL, NULL, NULL, 
                                                   DIGCF_PRESENT | DIGCF_ALLCLASSES);
    
    if (device_info_set == INVALID_HANDLE_VALUE) {
        printf(RED "Error: Unable to enumerate devices\n" RESET);
        return;
    }
    
    SP_DEVINFO_DATA device_info_data;
    device_info_data.cbSize = sizeof(SP_DEVINFO_DATA);
    
    int device_count = 0;
    for (DWORD i = 0; SetupDiEnumDeviceInfo(device_info_set, i, &device_info_data); i++) {
        char device_desc[256];
        char driver_version[256];
        char hardware_id[256];
        
        if (SetupDiGetDeviceRegistryPropertyA(device_info_set, &device_info_data,
                                             SPDRP_DEVICEDESC, NULL,
                                             (PBYTE)device_desc, sizeof(device_desc), NULL)) {
            
            printf(GREEN "  + %s" RESET, device_desc);
            
            // Try to get driver version
            if (SetupDiGetDeviceRegistryPropertyA(device_info_set, &device_info_data,
                                                 SPDRP_DRIVER, NULL,
                                                 (PBYTE)driver_version, sizeof(driver_version), NULL)) {
                printf(YELLOW " (Driver: %s)" RESET, driver_version);
            }
            
            // Try to get hardware ID
            if (SetupDiGetDeviceRegistryPropertyA(device_info_set, &device_info_data,
                                                 SPDRP_HARDWAREID, NULL,
                                                 (PBYTE)hardware_id, sizeof(hardware_id), NULL)) {
                printf(CYAN "\n      HW ID: %s" RESET, hardware_id);
            }
            
            printf("\n");
            device_count++;
            
            if (device_count > 20) {  // Limit output
                printf(CYAN "  ... and more drivers (showing first 20)\n" RESET);
                break;
            }
        }
    }
    
    SetupDiDestroyDeviceInfoList(device_info_set);
    printf(BRIGHT_GREEN "\nTotal devices with drivers: %d+\n" RESET, device_count);
}

void show_kernel_modules(void) {
    // Windows doesn't have kernel modules like Linux
    printf(MAGENTA "\nWindows uses device drivers instead of kernel modules\n" RESET);
}

void show_hardware_buses(void) {
    printf(BRIGHT_BLUE "\nHardware Information:\n" RESET);
    printf(CYAN "  Use Device Manager for detailed hardware bus information\n" RESET);
}

#else  // Linux implementation

#include <dirent.h>
#include <stdlib.h>

void get_driver_info(void) {
    print_section_header("LOADED KERNEL MODULES (DRIVERS)");
    show_kernel_modules();
    show_hardware_buses();
}

void enumerate_devices(void) {
    // Linux device enumeration would be more complex
    printf(CYAN "Use 'lspci' and 'lsusb' for detailed device information\n" RESET);
}

void show_kernel_modules(void) {
    printf(BRIGHT_GREEN "Kernel Modules:\n" RESET);
    
    FILE *modules = fopen("/proc/modules", "r");
    if (modules) {
        char line[256];
        int count = 0;
        
        while (fgets(line, sizeof(line), modules) && count < 25) {
            char module_name[64];
            int size, instances;
            char dependencies[128];
            
            if (sscanf(line, "%s %d %d %s", module_name, &size, &instances, dependencies) >= 3) {
                printf(GREEN "  + %s" RESET, module_name);
                printf(YELLOW " (%d KB)" RESET, size);
                if (instances > 0) {
                    printf(CYAN " - Used by: %d" RESET, instances);
                }
                if (strcmp(dependencies, "-") != 0) {
                    printf(MAGENTA " - Deps: %s" RESET, dependencies);
                }
                printf("\n");
                count++;
            }
        }
        fclose(modules);
        
        if (count >= 25) {
            printf(BRIGHT_CYAN "  ... and more modules (showing first 25)\n" RESET);
        }
    }
}

void show_hardware_buses(void) {
    printf(BRIGHT_MAGENTA "\nHardware Buses:\n" RESET);
    DIR *driver_dir = opendir("/sys/bus");
    if (driver_dir) {
        struct dirent *entry;
        while ((entry = readdir(driver_dir)) != NULL) {
            if (entry->d_name[0] != '.') {
                printf(BRIGHT_BLUE "  + %s bus\n" RESET, entry->d_name);
            }
        }
        closedir(driver_dir);
    }
}

#endif