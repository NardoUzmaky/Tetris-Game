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

void Grid::draw(Tetromino& currentPiece) {

    clear(); // clear console output

    int current_Piece_height = currentPiece.get_shape_height();
    int current_Piece_width = currentPiece.get_shape_width();
    int x = currentPiece.get_x();
    int y = currentPiece.get_y();

    std::vector<std::vector<int>>& shape = currentPiece.get_shape();

    for (int i = 0; i < BOARD_WIDTH+1; ++i) {
        std::cout << "##";
    }
    std::cout << "\n";
    for(int i = 0;i < BOARD_HEIGHT; ++i) {
        std::cout << "#";
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            if((x <= j && j < x + current_Piece_width) && (y <= i && i < y + current_Piece_height)){
                std::cout << (shape[i-y][j-x] ? "[]" : "  ");
            } else {
                std::cout << (board[i][j] ? "[]" : "  ");  
            }
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