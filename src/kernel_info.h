#ifndef KERNEL_INFO_H
#define KERNEL_INFO_H

// Function declarations for kernel information
void get_kernel_info(void);
void show_system_info(void);
void show_memory_info(void);
void show_available_kernels(void);
void show_kernel_parameters(void);

// System information structure
typedef struct {
    char system_name[64];
    char kernel_version[128];
    char kernel_build[256];
    char architecture[32];
    char hostname[64];
    int processor_count;
    double total_ram_gb;
    double free_ram_gb;
    int ram_usage_percent;
} system_info_t;

#endif // KERNEL_INFO_H