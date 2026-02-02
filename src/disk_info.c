#include "disk_info.h"
#include "colors.h"
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <winioctl.h>

void get_disk_info(void) {
    print_section_header("HARD DISK INFORMATION");
    
    DWORD drives = GetLogicalDrives();
    char drive_letter[4] = "A:\\";
    
    printf(BRIGHT_GREEN "Hard Disk Drives:\n" RESET);
    
    for (int i = 0; i < 26; i++) {
        if (drives & (1 << i)) {
            drive_letter[0] = 'A' + i;
            UINT drive_type = GetDriveTypeA(drive_letter);
            
            printf(GREEN "  + Drive %c: - ", 'A' + i);
            
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
                double total_gb = (double)total_bytes.QuadPart / (1024.0 * 1024.0 * 1024.0);
                double free_gb = (double)free_bytes.QuadPart / (1024.0 * 1024.0 * 1024.0);
                double used_gb = total_gb - free_gb;
                int usage_percent = total_gb > 0 ? (int)((used_gb / total_gb) * 100) : 0;
                
                printf("\n" WHITE "      Total: %.2f GB, Used: %.2f GB, Free: %.2f GB" RESET "\n", 
                       total_gb, used_gb, free_gb);
                
                char progress_label[64];
                sprintf(progress_label, "      Usage");
                print_progress_bar(usage_percent, progress_label);
            }
            printf("\n");
        }
    }
    
    analyze_physical_disks();
}

void analyze_physical_disks(void) {
    printf(BRIGHT_GREEN "\nPhysical Disks:\n" RESET);
    
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
                
                double size_gb = (double)disk_size / (1024.0 * 1024.0 * 1024.0);
                
                printf(YELLOW "  + Physical Drive %d: %.2f GB", i, size_gb);
                
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

void show_mounted_filesystems(void) {
    // Windows doesn't have traditional mount points like Linux
    printf(CYAN "\nWindows Drive Letters are the mount points\n" RESET);
}

#else  // Linux implementation

#include <dirent.h>
#include <sys/statvfs.h>
#include <stdlib.h>

void get_disk_info(void) {
    print_section_header("HARD DISK INFORMATION");
    
    // Read /proc/partitions for disk info
    FILE *partitions = fopen("/proc/partitions", "r");
    if (partitions) {
        char line[256];
        printf(BRIGHT_GREEN "Disk Partitions:\n" RESET);
        
        // Skip header lines
        fgets(line, sizeof(line), partitions);
        fgets(line, sizeof(line), partitions);
        
        while (fgets(line, sizeof(line), partitions)) {
            int major, minor;
            unsigned long blocks;
            char name[32];
            
            if (sscanf(line, "%d %d %lu %s", &major, &minor, &blocks, name) == 4) {
                double size_gb = (double)blocks / (1024.0 * 1024.0);
                printf(GREEN "  + /dev/%s - %.2f GB" RESET, name, size_gb);
                
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
    
    show_mounted_filesystems();
}

void analyze_physical_disks(void) {
    printf(BRIGHT_GREEN "\n💾 Physical Disk Analysis:\n" RESET);
    printf(CYAN "  Use 'lsblk' or 'fdisk -l' for detailed physical disk info\n" RESET);
}

void show_mounted_filesystems(void) {
    printf(CYAN "\nMounted Filesystems:\n" RESET);
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
                        double total_gb = (double)(stat.f_blocks * stat.f_frsize) / (1024.0*1024.0*1024.0);
                        double free_gb = (double)(stat.f_bavail * stat.f_frsize) / (1024.0*1024.0*1024.0);
                        double used_gb = total_gb - free_gb;
                        int usage_percent = total_gb > 0 ? (int)((used_gb / total_gb) * 100) : 0;
                        
                        printf(YELLOW "  + %s on %s (%s)\n" RESET, device, mountpoint, fstype);
                        printf(WHITE "      Total: %.2f GB, Used: %.2f GB, Free: %.2f GB\n" RESET,
                               total_gb, used_gb, free_gb);
                        
                        char progress_label[64];
                        sprintf(progress_label, "      Usage");
                        print_progress_bar(usage_percent, progress_label);
                    }
                }
            }
        }
        fclose(mounts);
    }
}

#endif