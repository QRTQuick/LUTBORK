/*
 * LUTBORK - Advanced System Information Tool
 * Colors and UI Implementation
 * 
 * Author: Chisom Life Eke
 * Company: Quick Red Tech
 * Year: 2026
 * Role: Chief Executive Officer
 * 
 * Description: Implementation of display functions and user interface utilities
 */

#include "colors.h"
#include <stdio.h>
#include <unistd.h>

void beep(void) {
    printf("\a");
    fflush(stdout);
}

void beep_count(int count) {
    for (int i = 0; i < count; i++) {
        beep();
        usleep(200000);  // 200ms delay
    }
}

void clear_screen(void) {
    printf("\033[2J\033[H");
}

void print_header(const char* title) {
    printf(BRIGHT_BLUE "================================================================\n");
    printf(BRIGHT_YELLOW "  %s\n" RESET, title);
    printf(BRIGHT_BLUE "================================================================\n" RESET);
}

void print_section_header(const char* section) {
    printf(CYAN "\n=== %s ===\n" RESET, section);
    printf(BLUE "----------------------------------------------------------------\n" RESET);
}

void print_progress_bar(int percentage, const char* label) {
    printf(CYAN "%s [", label);
    int filled = percentage / 5;  // 20 characters max
    
    for (int i = 0; i < 20; i++) {
        if (i < filled) {
            printf(GREEN "#");
        } else {
            printf(WHITE "-");
        }
    }
    printf(CYAN "] " YELLOW "%d%%" RESET "\n", percentage);
}