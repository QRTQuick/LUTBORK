#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Colors
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

void beep_sound(int frequency) {
    printf("\a");
    fflush(stdout);
    usleep(frequency * 1000);
}

void clear_screen() {
    printf("\033[2J\033[H");
}

void draw_title() {
    printf(BRIGHT_YELLOW);
    printf("  ██████╗  █████╗ ███╗   ███╗███████╗\n");
    printf(" ██╔════╝ ██╔══██╗████╗ ████║██╔════╝\n");
    printf(" ██║  ███╗███████║██╔████╔██║█████╗  \n");
    printf(" ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  \n");
    printf(" ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗\n");
    printf("  ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝\n");
    printf(RESET);
}

void draw_dice(int value) {
    printf(WHITE "┌─────────┐\n");
    
    switch(value) {
        case 1:
            printf("│         │\n");
            printf("│    ●    │\n");
            printf("│         │\n");
            break;
        case 2:
            printf("│  ●      │\n");
            printf("│         │\n");
            printf("│      ●  │\n");
            break;
        case 3:
            printf("│  ●      │\n");
            printf("│    ●    │\n");
            printf("│      ●  │\n");
            break;
        case 4:
            printf("│  ●   ●  │\n");
            printf("│         │\n");
            printf("│  ●   ●  │\n");
            break;
        case 5:
            printf("│  ●   ●  │\n");
            printf("│    ●    │\n");
            printf("│  ●   ●  │\n");
            break;
        case 6:
            printf("│  ●   ●  │\n");
            printf("│  ●   ●  │\n");
            printf("│  ●   ●  │\n");
            break;
    }
    
    printf("└─────────┘" RESET "\n");
}

void animate_dice_roll() {
    printf(CYAN "Rolling dice");
    for (int i = 0; i < 10; i++) {
        printf(".");
        fflush(stdout);
        beep_sound(50);
        usleep(200000);
    }
    printf("\n" RESET);
}

void draw_celebration() {
    printf(BRIGHT_YELLOW "    ✨ CONGRATULATIONS! ✨\n" RESET);
    printf(BRIGHT_GREEN "  🎉 🎊 🎈 🎁 🎂 🎈 🎊 🎉\n" RESET);
    printf(MAGENTA "     ♪♫♪ WINNER! ♪♫♪\n" RESET);
    
    // Victory beeps
    for (int i = 0; i < 3; i++) {
        beep_sound(100);
        beep_sound(150);
        beep_sound(200);
    }
}

int main() {
    srand(time(NULL));
    
    clear_screen();
    draw_title();
    
    printf(BLUE "\n═══════════════════════════════════════\n" RESET);
    printf(GREEN "Welcome to the Colorful Dice Game!\n" RESET);
    printf(YELLOW "Try to roll a 6 to win!\n" RESET);
    printf(BLUE "═══════════════════════════════════════\n" RESET);
    
    int attempts = 0;
    int dice_value;
    char input;
    
    do {
        printf(CYAN "\nPress Enter to roll the dice..." RESET);
        getchar();
        
        attempts++;
        animate_dice_roll();
        
        dice_value = (rand() % 6) + 1;
        
        printf(MAGENTA "Attempt #%d:\n" RESET, attempts);
        
        if (dice_value == 6) {
            printf(BRIGHT_GREEN);
        } else if (dice_value >= 4) {
            printf(YELLOW);
        } else {
            printf(RED);
        }
        
        draw_dice(dice_value);
        
        if (dice_value == 6) {
            printf(RESET "\n");
            draw_celebration();
            printf(BRIGHT_GREEN "You won in %d attempts!\n" RESET, attempts);
            break;
        } else {
            printf(RED "You rolled a %d. Try again!\n" RESET, dice_value);
            beep_sound(300);
        }
        
    } while (dice_value != 6);
    
    printf(BLUE "\n═══════════════════════════════════════\n" RESET);
    printf(WHITE "Thanks for playing!\n" RESET);
    printf(BLUE "═══════════════════════════════════════\n" RESET);
    
    return 0;
}