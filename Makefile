# Makefile for C/C++ ASCII programs

CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -std=c99
CXXFLAGS = -Wall -Wextra -std=c++11

# Windows specific libraries
ifeq ($(OS),Windows_NT)
    LDFLAGS = -lsetupapi -lwbemuuid -lole32 -loleaut32
else
    LDFLAGS = 
endif

# Targets
TARGETS = colorful_ascii ascii_art_cpp game_ascii system_info advanced_system_info

all: $(TARGETS)

colorful_ascii: colorful_ascii.c
	$(CC) $(CFLAGS) -o colorful_ascii colorful_ascii.c

ascii_art_cpp: ascii_art_cpp.cpp
	$(CXX) $(CXXFLAGS) -o ascii_art_cpp ascii_art_cpp.cpp

game_ascii: game_ascii.c
	$(CC) $(CFLAGS) -o game_ascii game_ascii.c

system_info: system_info.c
	$(CC) $(CFLAGS) -o system_info system_info.c $(LDFLAGS)

advanced_system_info: advanced_system_info.cpp
	$(CXX) $(CXXFLAGS) -o advanced_system_info advanced_system_info.cpp $(LDFLAGS)

clean:
	rm -f $(TARGETS)
ifeq ($(OS),Windows_NT)
	del /Q *.exe 2>nul || true
endif

run-c: colorful_ascii
	./colorful_ascii

run-cpp: ascii_art_cpp
	./ascii_art_cpp

run-game: game_ascii
	./game_ascii

run-sysinfo: system_info
	./system_info

run-advanced: advanced_system_info
	./advanced_system_info

# Windows specific targets
ifeq ($(OS),Windows_NT)
run-c-win: colorful_ascii.exe
	colorful_ascii.exe

run-cpp-win: ascii_art_cpp.exe
	ascii_art_cpp.exe

run-game-win: game_ascii.exe
	game_ascii.exe

run-sysinfo-win: system_info.exe
	system_info.exe

run-advanced-win: advanced_system_info.exe
	advanced_system_info.exe
endif

.PHONY: all clean run-c run-cpp run-game run-sysinfo run-advanced