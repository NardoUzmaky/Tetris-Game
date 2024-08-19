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

void Grid::draw(Tetromino& currentPiece, int score) {

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
                std::cout << (shape[i-y][j-x] ? "[]" : (board[i][j] ? "[]" : "  "));
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

    std::cout << "Current Score: " << score << "\n";

    std::cout.flush();
}

void Grid::update(Tetromino& currentPiece) { // after having collided add current piece to board.
    int PieceWidth = currentPiece.get_shape_width();
    int PieceHeight = currentPiece.get_shape_height();

    int x = currentPiece.get_x();
    int y = currentPiece.get_y();

    std::vector<std::vector<int>>& shape = currentPiece.get_shape();

    for(int i = 0; i < PieceHeight; ++i) {
        for(int j = 0; j < PieceWidth; ++j) {
            if (shape[i][j]){
                board[i+y][j+x] = 1;
            }
        }
    }
    return;
}

bool Grid::hasCollided(Tetromino& currentPiece) {

    int x = currentPiece.get_x();
    int y = currentPiece.get_y(); // stupid names

    std::vector<std::vector<int>>& shape = currentPiece.get_shape();

    for(int i = 0; i < shape.size(); ++i) {
        for(int j = 0; j < shape[i].size(); ++j) {
            if (shape[i][j] && ((i + y == BOARD_HEIGHT || board[i+y][j+x]) || (j + x < 0 || j + x > BOARD_WIDTH-1))){
                std::cout << "collision at " << x << ", " << y << std::endl;
                return true;
            }
        }
    }
    return false;
}

int Grid::filledLines() {
    int nLinesCleared = 0;
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        bool filledLine = true;
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            if (!board[i][j]) {
                filledLine = false;
            }
        }
        if (filledLine) {
            ++nLinesCleared;
            std::vector<int> v(BOARD_WIDTH, 0);
            board[0] = v;
            for (int k = i; k > 0; --k) {
                board[k] = board[k-1];
            }
        }

    }
    return nLinesCleared;
}