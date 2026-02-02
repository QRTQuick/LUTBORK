/*
 * LUTBORK - Advanced System Information Tool
 * Colors and UI Module
 * 
 * Author: Chisom Life Eke
 * Company: Quick Red Tech
 * Year: 2026
 * Role: Chief Executive Officer
 * 
 * Description: Display functions, color management, and user interface utilities
 */

#ifndef COLORS_H
#define COLORS_H

// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

// Bright colors
#define BRIGHT_RED     "\033[91m"
#define BRIGHT_GREEN   "\033[92m"
#define BRIGHT_YELLOW  "\033[93m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN    "\033[96m"

// Background colors
#define BG_RED     "\033[41m"
#define BG_GREEN   "\033[42m"
#define BG_YELLOW  "\033[43m"
#define BG_BLUE    "\033[44m"

// Function declarations
void beep(void);
void beep_count(int count);
void clear_screen(void);
void print_header(const char* title);
void print_section_header(const char* section);
void print_progress_bar(int percentage, const char* label);

#endif // COLORS_H