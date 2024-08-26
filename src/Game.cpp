#include "../include/Class.hpp"
#include <thread>
#include <iostream>
#include <conio.h>


void Game::run() {
    std::thread input(&Game::inputThread, this);
    try
    {
    #ifdef _WIN32
        system("cls");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        std::cout<< u8"\033[2J\033[1;1H";
    #endif
        while(this->isRunning) {

            char input = lastInput.exchange(0); // gets character and replaces it with 0

            
            processInput(input);

            if(board.hasCollided(currentPiece)) {
                currentPiece.move_shape(3);
                board.update(currentPiece);
                int linesCleared = board.filledLines(); // check and remove lines which are filled
                updateScore(linesCleared);
                board.draw(currentPiece, score);
                newPiece();
            } else {
                board.draw(currentPiece, score);
            }
            static int frameCount = 0;
            if(++frameCount >= (int)(FPS/2)){
                currentPiece.move_shape(2);
                if(board.hasCollided(currentPiece)) {
                    currentPiece.move_shape(3);
                    board.update(currentPiece);
                    int linesCleared = board.filledLines();
                    updateScore(linesCleared);
                    board.draw(currentPiece, score);
                    newPiece();
                }
                frameCount = 0;
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000/FPS)));
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

void Game::processInput(char &input)  {
    if (input != 0) {
        switch (input) { 
            case 'a': // move piece to the left
                currentPiece.move_shape(1);
                if (board.hasCollided(currentPiece)) {
                    currentPiece.move_shape(0);
                }
                break;
            case 'd': // move right
                currentPiece.move_shape(0);
                if (board.hasCollided(currentPiece)) {
                    currentPiece.move_shape(1);
                }
                break;
            case 's': //move down
                currentPiece.move_shape(2);
                break;
            case 'w': // rotate to the right
                currentPiece.rotate_shape(0);
                if (board.hasCollided(currentPiece)) {
                    currentPiece.rotate_shape(1); 
                    currentPiece.move_shape(0);
                    currentPiece.rotate_shape(0);
                    if (board.hasCollided(currentPiece)) {
                        currentPiece.rotate_shape(1); 
                        currentPiece.move_shape(0);
                        currentPiece.rotate_shape(0);
                        if (board.hasCollided(currentPiece)) { // this means its probably collided on the left side
                            currentPiece.rotate_shape(1); 
                            currentPiece.move_shape(1);
                            currentPiece.move_shape(1);
                            currentPiece.move_shape(1);
                            currentPiece.rotate_shape(0);
                            if (board.hasCollided(currentPiece)) {
                                currentPiece.rotate_shape(1); 
                                currentPiece.move_shape(1);
                                currentPiece.rotate_shape(0);
                                
                            }
                        }
                    }
                }
                if (board.hasCollided(currentPiece)) { // if still colliding, move to original position
                    
                }
    
                break;
            case 'q': // quit
                isRunning = false;
                break;
        }
    }
}

void Game::newPiece() {
    PieceType t = PieceType(rand()%7);
    currentPiece = Tetromino(t);
}

void Game::updateScore(int nLinesCleared) {
    switch (nLinesCleared) {
        case 0:
            return;
        case 1:
            score += 40*(level+1);
            return;
        case 2:
            score += 100*(level+1);
            return;
        case 3:
            score += 300*(level+1);
            return;
        case 4:
            score += 1200*(level+1);
            return;
        default:
            return;
    }
}