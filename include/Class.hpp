#include <vector>
#include <string>
#include <cassert>
#include <cmath>
#include <chrono>
#include <thread>

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
        }

        void init_shape() {
            switch (type) {
                case PieceType::I:
                    shape = {{0, 0, 0, 0},
                             {1, 1, 1, 1},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0}};
                    break;
                case PieceType::J:
                    shape = {{1, 0, 0},
                             {1, 1, 1},
                             {0, 0, 0}};
                    break;
                case PieceType::L:
                    shape = {{0, 0, 1},
                             {1, 1, 1},
                             {0, 0, 0}};
                    break;
                case PieceType::O:
                    shape = {{1, 1},
                             {1, 1}};
                    break;
                case PieceType::S:
                    shape = {{1, 1, 0},
                             {0, 1, 1},
                             {0, 0, 0}};
                    break;
                case PieceType::T:
                    shape = {{0, 1, 0},
                             {1, 1, 1},
                             {0, 0, 0}};
                    break;
                case PieceType::Z:
                    shape = {{0, 1, 1},
                             {1, 1, 0},
                             {0, 0, 0}};
                    break;
            }
        }
        std::vector<std::vector<int>> getShape() {
            return shape;
        }

        void setRandomColor() {
            color = Colors(rand()%7); 
        }

        void rotate_shape(double angle);
};

class Grid {
    private: 
        std::vector<std::vector<int>> board;
    public:
        Grid() : board(BOARD_HEIGHT, std::vector<int>(BOARD_WIDTH, 0)) {

        }

        void draw() {

        }
        void update() { // update game state
            //checkForCollision();
        }

};

class Game {
    private:
        bool isRunning;
        Grid board;
        Tetromino currentPiece;
        int score;
    public:
        Game() : score(0), isRunning(true), currentPiece(PieceType(rand()%7)) {
            //
        }
        
        void run() {
            while(isRunning) {
               std::this_thread::sleep_for(std::chrono::milliseconds((int)(1/FPS)));
            }
        }
        
        void newPiece() {
            PieceType t = PieceType(rand()%7);
            currentPiece = Tetromino(t);
        }
};