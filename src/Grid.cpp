#include "../include/Class.hpp"
#include <iostream>
#include <sstream>
#include <windows.h>

void clear() {
    #ifdef _WIN32
        std::cout<< "\033[H";
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        std::cout<< u8"\033[2J\033[1;1H";
    #endif
}

void Grid::draw(Tetromino& currentPiece, Tetromino& nextPiece, int score) {


    const int current_Piece_height = currentPiece.get_shape_height();
    const int current_Piece_width = currentPiece.get_shape_width();
    const int next_Piece_height = nextPiece.get_shape_height();
    const int next_Piece_width = nextPiece.get_shape_width();

    const int x = currentPiece.get_x();
    const int y = currentPiece.get_y();

    const int next_x = nextPiece.get_x();
    const int next_y = nextPiece.get_y();

    std::vector<std::vector<int>>& shape = currentPiece.get_shape();
    std::vector<std::vector<int>>& nextShape = nextPiece.get_shape();
    Color pieceColor = currentPiece.getColor();
    Color nextPieceColor = nextPiece.getColor();

    std::stringstream string_buffer;
    // draw next piece display
    for (int i = 0; i < BOARD_WIDTH+1; ++i) {
        string_buffer << "##";
    }
    string_buffer << "\n";
    string_buffer << "#";

    for (int i = 0; i < BOARD_WIDTH-5; ++i) {
        if (i == (int)(BOARD_WIDTH/2-3)) {
            string_buffer << "Next Piece: ";
        } else {
            string_buffer << "  ";
        }
    }
    // padding
    string_buffer << "#\n#";
    for (int i = 0; i < BOARD_WIDTH; ++i) {
        string_buffer << "  ";
    }
    string_buffer << "#\n";

    //display next piece (ignoring empty lines of shape)
    int real_piece_width = 0;
    for (int i = 0; i < next_Piece_height; ++i) {
        std::stringstream help_buffer;
        help_buffer << "#";
        bool emptyRow = true;
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            if((next_x <= j && j < next_x + next_Piece_width) && (next_y <= i && i < next_y + next_Piece_height) && nextShape[i-next_y][j-next_x]){
                help_buffer << "\033[" << static_cast<int>(nextPieceColor) << "m[]" << "\033[0m";
                emptyRow = false;
            } else {
                help_buffer << "  ";
            }
        }
        if(!emptyRow) {
            string_buffer << help_buffer.str();
            string_buffer << "#\n";
            ++real_piece_width;
        }
    }
    //calculate line_buffer
    std::stringstream line_buffer;
    const static int line_buffer_size = 5;
    for (int i = 0; i < line_buffer_size-real_piece_width; ++i) {
        line_buffer << "\n";
    }

    //padding
    string_buffer << "#";
    for (int i = 0; i < BOARD_WIDTH; ++i) {
        string_buffer << "  ";
    }
    string_buffer << "#\n";

    // top border
    string_buffer << "#";
    for (int i = 0; i < BOARD_WIDTH; ++i) {
        string_buffer << "##";
    }
    string_buffer << "#\n";

    // draw main board
    for(int i = 0;i < BOARD_HEIGHT; ++i) {
        string_buffer << "#";
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            if((x <= j && j < x + current_Piece_width) && (y <= i && i < y + current_Piece_height) && shape[i-y][j-x]){
                string_buffer << "\033[" << static_cast<int>(pieceColor) << "m[]" << "\033[0m";
            } else if (board[i][j]){
                string_buffer << "\033[" << board[i][j] << "m[]" << "\033[0m";
            } else {
                string_buffer << "  ";
            }
        };
        string_buffer << "#";
        string_buffer << "\n";
    }
    for (int i = 0; i < BOARD_WIDTH+1; ++i) {
        string_buffer << "##";
    }
    string_buffer << "\n";

    string_buffer << "Current Score: " << score << "\n";

    clear(); // clear console output
    std::cout << line_buffer.str() << string_buffer.str();
    std::cout.flush();
}

void Grid::update(Tetromino& currentPiece) { // after having collided add current piece to board.
    int PieceWidth = currentPiece.get_shape_width();
    int PieceHeight = currentPiece.get_shape_height();

    int x = currentPiece.get_x();
    int y = currentPiece.get_y();

    std::vector<std::vector<int>>& shape = currentPiece.get_shape();
    int ColorCode = static_cast<int>(currentPiece.getColor());

    for(int i = 0; i < PieceHeight; ++i) {
        for(int j = 0; j < PieceWidth; ++j) {
            if (shape[i][j]){
                board[i+y][j+x] = ColorCode;
            }
        }
    }
    return;
}

bool Grid::hasCollided(Tetromino& currentPiece) { // checks if piece is an invalid position (ouside bounds or intersecting with other tiles)

    int x = currentPiece.get_x();
    int y = currentPiece.get_y(); // stupid names

    std::vector<std::vector<int>>& shape = currentPiece.get_shape();

    for(int i = 0; i < shape.size(); ++i) {
        for(int j = 0; j < shape[i].size(); ++j) {
            if (shape[i][j] && ((i + y == BOARD_HEIGHT || board[i+y][j+x]) || (j + x < 0 || j + x > BOARD_WIDTH-1))){
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