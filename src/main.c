#include "colors.h"
#include "disk_info.h"
#include "driver_info.h"
#include "kernel_info.h"
#include <stdio.h>
#include <unistd.h>

void print_title(void) {
    printf(BRIGHT_YELLOW);
    printf("  ========================================\n");
    printf("                LUTBORK\n");
    printf("         System Information Tool\n");
    printf("  ========================================\n");
    printf(RESET);
}

void show_menu(void) {
    printf(BRIGHT_CYAN "\nLUTBORK - SYSTEM DIAGNOSTIC MENU\n" RESET);
    printf(BLUE "========================================\n" RESET);
    printf(GREEN "[1]" YELLOW " Hard Disk Information\n" RESET);
    printf(GREEN "[2]" YELLOW " Driver Information\n" RESET);
    printf(GREEN "[3]" YELLOW " Kernel Information\n" RESET);
    printf(GREEN "[4]" YELLOW " Complete System Scan\n" RESET);
    printf(GREEN "[0]" RED " Exit\n" RESET);
    printf(BLUE "========================================\n" RESET);
    printf(CYAN "Enter your choice: " RESET);
}

void run_complete_scan(void) {
    clear_screen();
    print_title();
    print_header("           LUTBORK - COMPREHENSIVE SYSTEM SCAN");
    
    printf(BRIGHT_CYAN "\nLUTBORK scanning your system...\n" RESET);
    beep();
    usleep(500000);  // 0.5 second delay
    
    get_disk_info();
    printf("\n");
    beep();
    
    get_driver_info();
    printf("\n");
    beep();
    
    get_kernel_info();
    
    printf(BRIGHT_GREEN "\nLUTBORK system scan completed!\n" RESET);
    beep_count(3);
}

int main(void) {
    int choice;
    
    while (1) {
        clear_screen();
        print_title();
        print_header("              LUTBORK - SYSTEM INFORMATION TOOL");
        
        show_menu();
        
        if (scanf("%d", &choice) != 1) {
            printf(RED "Invalid input! Please enter a number.\n" RESET);
            while (getchar() != '\n'); // Clear input buffer
            usleep(1000000);
            continue;
        }
        
        switch (choice) {
            case 1:
                clear_screen();
                print_title();
                get_disk_info();
                printf(CYAN "\nPress Enter to continue..." RESET);
                while (getchar() != '\n'); // Clear buffer
                getchar(); // Wait for Enter
                break;
                
            case 2:
                clear_screen();
                print_title();
                get_driver_info();
                printf(CYAN "\nPress Enter to continue..." RESET);
                while (getchar() != '\n'); // Clear buffer
                getchar(); // Wait for Enter
                break;
                
            case 3:
                clear_screen();
                print_title();
                get_kernel_info();
                printf(CYAN "\nPress Enter to continue..." RESET);
                while (getchar() != '\n'); // Clear buffer
                getchar(); // Wait for Enter
                break;
                
            case 4:
                run_complete_scan();
                printf(CYAN "\nPress Enter to continue..." RESET);
                while (getchar() != '\n'); // Clear buffer
                getchar(); // Wait for Enter
                break;
                
            case 0:
                clear_screen();
                printf(BRIGHT_GREEN "Thank you for using LUTBORK!\n" RESET);
                beep_count(2);
                return 0;
                
            default:
                printf(RED "Invalid choice! Please try again.\n" RESET);
                usleep(1000000);
                break;
        }
    }
    
    return 0;
}