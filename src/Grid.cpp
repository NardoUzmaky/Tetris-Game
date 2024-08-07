#include "../include/Class.hpp"
#include <iostream>

void Grid::draw() {
    for (int i = 0; i < BOARD_WIDTH+1; ++i) {
        std::cout << "__";
    }
    std::cout << "\n";
    for(auto it = board.begin(); it != board.end(); ++it) {
        std::cout << "| ";
        for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
            std::cout << *it2 << " "; 
        };
        std::cout << "|";
        std::cout << "\n";
    }
    for (int i = 0; i < BOARD_WIDTH*2+3; ++i) {
        std::cout << "-";
    }
}