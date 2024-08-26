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

enum class Color {
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37
};

class Tetromino {
    private: 
        PieceType type;
        Color color;
        std::vector<std::vector<int>> shape;
        //int alignment; // 0 = default, 1 = rotated 90 deg to the right, 2 = etc..
        int x, y; // coordinates of top left corner of shape

    public:
        Tetromino(PieceType t) : type(t), x((int)((BOARD_WIDTH)/2)), y(0) {
            //setRandomColor();
            setColor();
            init_shape();
        }

        void init_shape();

        std::vector<std::vector<int>> getShape() {
            return shape;
        }

        void setRandomColor() {
            color = Color(rand()%7); 
        }

        void setColor();

        Color getColor() const;

        void rotate_shape(int direction);

        void move_shape(int direction);

        int get_shape_width();

        int get_shape_height();

        int get_x();
        int get_y();

        std::vector<std::vector<int>>& get_shape();
};

class Grid {
    private: 
        std::vector<std::vector<int>> board;
    public:
        Grid() : board(BOARD_HEIGHT, std::vector<int>(BOARD_WIDTH, 0)) {}

        void draw(Tetromino& currentPiece, int score);

        void update(Tetromino& currentPiece);

        bool hasCollided(Tetromino& currentPiece);

        int filledLines();

};

class Game {
    private:
        std::atomic<bool> isRunning{true};
        std::atomic<char> lastInput{0};
        Grid board;
        Tetromino currentPiece;
        int score{0};
        int level{1};

        void inputThread();
    public:
        Game() : currentPiece(PieceType(rand()%7)) {}
        
        void run();
        
        void processInput(char &input);

        void newPiece();

        //input: number of lines cleared after having placed a piece
        void updateScore(int nLinesCleared);
};

#endif