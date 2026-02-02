#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>

using namespace std;

class ColoredASCII {
private:
    // ANSI escape codes for colors
    const string RESET = "\033[0m";
    const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string YELLOW = "\033[33m";
    const string BLUE = "\033[34m";
    const string MAGENTA = "\033[35m";
    const string CYAN = "\033[36m";
    const string WHITE = "\033[37m";
    
    // Bright colors
    const string BRIGHT_RED = "\033[91m";
    const string BRIGHT_GREEN = "\033[92m";
    const string BRIGHT_YELLOW = "\033[93m";
    const string BRIGHT_BLUE = "\033[94m";
    const string BRIGHT_MAGENTA = "\033[95m";
    const string BRIGHT_CYAN = "\033[96m";

public:
    void beep(int count = 1) {
        for (int i = 0; i < count; i++) {
            cout << "\a" << flush;
            this_thread::sleep_for(chrono::milliseconds(200));
        }
    }
    
    void clearScreen() {
        cout << "\033[2J\033[H";
    }
    
    void drawRocket() {
        cout << RED << "        /\\" << RESET << endl;
        cout << RED << "       /  \\" << RESET << endl;
        cout << YELLOW << "      /____\\" << RESET << endl;
        cout << BLUE << "     |      |" << RESET << endl;
        cout << BLUE << "     | NASA |" << RESET << endl;
        cout << BLUE << "     |______|" << RESET << endl;
        cout << BRIGHT_RED << "     /^^^^^^\\" << RESET << endl;
        cout << BRIGHT_YELLOW << "    ^^^^^^^^" << RESET << endl;
        cout << BRIGHT_MAGENTA << "   ^^^^^^^^^^" << RESET << endl;
    }
    
    void drawProgressBar(int percentage) {
        cout << CYAN << "[";
        int filled = percentage / 5;  // 20 characters max
        
        for (int i = 0; i < 20; i++) {
            if (i < filled) {
                cout << GREEN << "█";
            } else {
                cout << WHITE << "░";
            }
        }
        cout << CYAN << "] " << YELLOW << percentage << "%" << RESET << endl;
    }
    
    void animatedText(const string& text) {
        vector<string> colors = {RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN};
        
        for (char c : text) {
            string color = colors[rand() % colors.size()];
            cout << color << c << RESET << flush;
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        cout << endl;
    }
    
    void drawBorder() {
        cout << BRIGHT_BLUE;
        cout << "╔════════════════════════════════════════════════╗" << endl;
        cout << "║                                                ║" << endl;
        cout << "║" << BRIGHT_YELLOW << "        C++ COLORFUL ASCII SHOWCASE            " << BRIGHT_BLUE << "║" << endl;
        cout << "║                                                ║" << endl;
        cout << "╚════════════════════════════════════════════════╝" << RESET << endl;
    }
    
    void demoRun() {
        clearScreen();
        beep(2);
        
        drawBorder();
        cout << endl;
        
        cout << MAGENTA << "🎨 Drawing ASCII Rocket:" << RESET << endl;
        drawRocket();
        cout << endl;
        
        beep();
        cout << CYAN << "🌈 Animated Rainbow Text:" << RESET << endl;
        animatedText("Hello Colorful World!");
        cout << endl;
        
        cout << YELLOW << "📊 Progress Bar Animation:" << RESET << endl;
        for (int i = 0; i <= 100; i += 10) {
            cout << "\033[A";  // Move cursor up
            drawProgressBar(i);
            this_thread::sleep_for(chrono::milliseconds(300));
            if (i % 30 == 0) beep();
        }
        
        cout << endl;
        cout << BRIGHT_GREEN << "✨ Special Characters: ";
        cout << "★ ☆ ♠ ♣ ♥ ♦ ☺ ☻ ♪ ♫ ☀ ☁ ⚡ ❄ ✓ ✗" << RESET << endl;
        
        cout << endl;
        cout << BRIGHT_MAGENTA << "Press Enter to finish with beep sequence..." << RESET;
        cin.get();
        
        // Final beep melody
        for (int i = 0; i < 5; i++) {
            beep();
            this_thread::sleep_for(chrono::milliseconds(150));
        }
        
        cout << BRIGHT_GREEN << "🎉 Demo completed!" << RESET << endl;
    }
};

int main() {
    ColoredASCII demo;
    demo.demoRun();
    return 0;
}