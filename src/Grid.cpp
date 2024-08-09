#include "../include/Class.hpp"
#include <iostream>
#include <windows.h>



void clear() {
    #ifdef _WIN32
        system("cls");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        std::cout<< u8"\033[2J\033[1;1H";
    #endif
}

void Grid::draw() {

    clear(); // clear console output

    for (int i = 0; i < BOARD_WIDTH+1; ++i) {
        std::cout << "##";
    }
    std::cout << "\n";
    for(auto it = board.begin(); it != board.end(); ++it) {
        std::cout << "#";
        for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
            std::cout << (*it2 ? "[]" : "  "); 
        };
        std::cout << "#";
        std::cout << "\n";
    }
    for (int i = 0; i < BOARD_WIDTH+1; ++i) {
        std::cout << "##";
    }
    std::cout << "\n";

    std::cout.flush();
}

void Grid::update() {
    
}