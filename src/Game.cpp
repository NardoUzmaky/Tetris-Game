#include "../include/Class.hpp"
#include <thread>
#include <iostream>
#include <conio.h>


void Game::run() {
    std::thread input(&Game::inputThread, this);
    try
    {
        while(this->isRunning) {

            char input = lastInput.exchange(0); // gets character and replaces it with 0

            if (input != 0) {
                switch (input) { 
                    case 'a': // move piece to the left
                        currentPiece.move_shape(1);
                        break;
                    case 'd': // move right
                        currentPiece.move_shape(0);
                        break;
    ;                case 's': //move down
                        currentPiece.move_shape(2);
                        break;
                    case 'w': // rotate to the right
                        currentPiece.rotate_shape(0);
                        break;
                    case 'q': // quit
                        isRunning = false;
                        break;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(20)));
            if(board.hasCollided(currentPiece)) {
                board.update(currentPiece);
                board.draw(currentPiece);
                newPiece();
            } else {
                board.draw(currentPiece);
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    input.join();
}

void Game::inputThread() {
    while(isRunning) {
        char ch = getch();
        lastInput.store(ch); // replace existing value with char from input
    }
}

void Game::newPiece() {
    PieceType t = PieceType(rand()%7);
    currentPiece = Tetromino(t);
}