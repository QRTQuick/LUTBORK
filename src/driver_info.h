#ifndef DRIVER_INFO_H
#define DRIVER_INFO_H

// Function declarations for driver information
void get_driver_info(void);
void enumerate_devices(void);
void show_kernel_modules(void);
void show_hardware_buses(void);

// Driver information structure
typedef struct {
    char name[256];
    char version[64];
    char hardware_id[256];
    int size_kb;
    int instances;
} driver_info_t;

#endif // DRIVER_INFO_H