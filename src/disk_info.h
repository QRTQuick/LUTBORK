#ifndef DISK_INFO_H
#define DISK_INFO_H

// Function declarations for disk information
void get_disk_info(void);
void analyze_physical_disks(void);
void show_mounted_filesystems(void);

// Cross-platform disk structure
typedef struct {
    char name[32];
    char type[64];
    double size_gb;
    double free_gb;
    double used_gb;
    int usage_percent;
    int is_ssd;
} disk_info_t;

#endif // DISK_INFO_H