#include "../include/Class.hpp"
#include <thread>
#include <iostream>


void Game::run() {
    std::thread input(&Game::inputThread, this);
    while(isRunning) {
        char input = lastInput.exchange(0); // gets character and replaces it with 0
        if (input != 0) {
            switch (input) { 
                case 'a': // move piece to the left
                    currentPiece.move_shape(0);
                case 'd': // move right
                    currentPiece.move_shape(1);
;                case 's': //move down
                    currentPiece.move_shape(2);
                case 'w': // rotate to the right
                    currentPiece.rotate_shape(0);
                case 'q': // quit
                    isRunning = false;
                    break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(2000)));
        board.draw();
    }
}

void Game::inputThread() {
    while(isRunning) {
        char ch = std::cin.get();
        lastInput.store(ch); // replace existing value with char from input
    }
}

void Game::newPiece() {
    PieceType t = PieceType(rand()%7);
    currentPiece = Tetromino(t);
}