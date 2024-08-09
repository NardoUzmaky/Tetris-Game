#ifndef CLASS_HPP
#define CLASS_HPP

#include "helper_functions.hpp"

#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <atomic>

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;
const int FPS = 30;

enum class PieceType {
    I, J, L, O, S, T, Z 
};

enum class Colors { 
    red, green, blue, yellow, pink, orange, lightblue
};

class Tetromino {
    private: 
        PieceType type;
        Colors color;
        std::vector<std::vector<int>> shape;
        int alignment; // 0 = default, 1 = rotated 90 deg to the right, 2 = etc..
        int x, y;

    public:
        Tetromino(PieceType t) : type(t), alignment(0) {
            setRandomColor();
            init_shape();
        }

        void init_shape();

        std::vector<std::vector<int>> getShape() {
            return shape;
        }

        void setRandomColor() {
            color = Colors(rand()%7); 
        }

        void rotate_shape(int direction);

        void move_shape(int direction);
};

class Grid {
    private: 
        std::vector<std::vector<int>> board;
    public:
        Grid() : board(BOARD_HEIGHT, std::vector<int>(BOARD_WIDTH, 0)) {

        }

        void draw();

        void update();

};

class Game {
    private:
        std::atomic<bool> isRunning;
        std::atomic<char> lastInput{0};
        Grid board;
        Tetromino currentPiece;
        int score;

        void inputThread();
    public:
        Game() : score(0), isRunning(true), currentPiece(PieceType(rand()%7)) {
            //
        }
        
        void run();
        
        void newPiece();
};

#endif