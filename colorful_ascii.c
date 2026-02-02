#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

// Background colors
#define BG_RED     "\033[41m"
#define BG_GREEN   "\033[42m"
#define BG_YELLOW  "\033[43m"
#define BG_BLUE    "\033[44m"

void beep() {
    printf("\a");  // ASCII bell character
    fflush(stdout);
}

void clear_screen() {
    printf("\033[2J\033[H");  // Clear screen and move cursor to home
}

void draw_rainbow_box() {
    printf(RED "╔══════════════════════════════════════╗\n" RESET);
    printf(YELLOW "║" GREEN "    Welcome to Colorful ASCII Art!    " YELLOW "║\n" RESET);
    printf(BLUE "║" CYAN "                                      " BLUE "║\n" RESET);
    printf(MAGENTA "║" WHITE "  ★ ☆ ★ ☆ ★ ☆ ★ ☆ ★ ☆ ★ ☆ ★ ☆ ★   " MAGENTA "║\n" RESET);
    printf(RED "╚══════════════════════════════════════╝\n" RESET);
}

void animated_loading() {
    char spinner[] = "|/-\\";
    printf(CYAN "Loading");
    
    for (int i = 0; i < 20; i++) {
        printf(YELLOW " %c" RESET, spinner[i % 4]);
        fflush(stdout);
        usleep(200000);  // 200ms delay
        printf("\b\b");
        if (i % 5 == 0) beep();
    }
    printf(GREEN " Done!\n" RESET);
}

int main() {
    clear_screen();
    
    // Title with beep
    beep();
    printf(BG_BLUE WHITE "═══════════════════════════════════════════\n" RESET);
    printf(BG_BLUE WHITE "    C COLORFUL ASCII DEMONSTRATION        \n" RESET);
    printf(BG_BLUE WHITE "═══════════════════════════════════════════\n" RESET);
    
    printf("\n");
    draw_rainbow_box();
    
    printf("\n" MAGENTA "ASCII Characters and Symbols:\n" RESET);
    printf(RED "♠ ♣ ♥ ♦ " RESET);
    printf(GREEN "☺ ☻ ♪ ♫ " RESET);
    printf(BLUE "→ ← ↑ ↓ " RESET);
    printf(YELLOW "☀ ☁ ☂ ❄ " RESET);
    printf("\n\n");
    
    animated_loading();
    
    // Final beep sequence
    printf(CYAN "\nPress Enter to hear beep sequence..." RESET);
    getchar();
    
    for (int i = 0; i < 3; i++) {
        beep();
        usleep(300000);
    }
    
    printf(GREEN "Program completed!\n" RESET);
    return 0;
}