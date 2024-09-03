#include "../include/Class.hpp"
#include <thread>
#include <iostream>
#include <conio.h>

/*
#ifdef _WIN32

#include <windows.h>

#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__) 

#include <conio.h>

#endif 

*/
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

            board.draw(currentPiece, score);

            if(board.hasCollided(currentPiece)) {
                currentPiece.move_up(1);
                board.update(currentPiece);
                int linesCleared = board.filledLines(); // check and remove lines which are filled
                updateScore(linesCleared);
                numberLinesCleared += linesCleared;
                newPiece();
            }
            static int frameCount = 0;
            if(++frameCount >= (int)(FPS/level)){
                currentPiece.move_down(1);
                if(board.hasCollided(currentPiece)) {
                    currentPiece.move_up(1);
                    board.update(currentPiece);
                    int linesCleared = board.filledLines();
                    updateScore(linesCleared);
                    numberLinesCleared += linesCleared;
                    newPiece();
                }
                frameCount = 0;
            }

            updateLevel();

            board.draw(currentPiece, score);
            
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
    /*
    #ifdef _WIN32

    INPUT_RECORD irInBuf[128];
    DWORD cNumRead;
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    while (isRunning) {
        ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead);

        for (DWORD i = 0; i < cNumRead; i++) {
            if (irInBuf[i].EventType == KEY_EVENT && irInBuf[i].Event.KeyEvent.bKeyDown) {
                switch (irInBuf[i].Event.KeyEvent.wVirtualKeyCode) {
                    case 'A':
                        lastInput.store('a');
                        break;
                    case 'D':
                        lastInput.store('d');
                        break;
                    case 'S':
                        lastInput.store('s');
                        break;
                    case 'W':
                        lastInput.store('w');
                        break;
                    case 'Q':
                        lastInput.store('q');
                        break;
                }
            }
        }
    }    

    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    */
    while(isRunning) {
        char ch = getch();
        lastInput.store(ch); // replace existing value with char from input
    }

    //#endif
}

void Game::processInput(char &input)  {
    if (input != 0) {
        switch (input) { 
            case 'a': // move piece to the left
                currentPiece.move_left(1);
                if (board.hasCollided(currentPiece)) {
                    currentPiece.move_right(1);
                }
                break;
            case 'd': // move right
                currentPiece.move_right(1);
                if (board.hasCollided(currentPiece)) {
                    currentPiece.move_left(1);
                }
                break;
            case 's': //move down
                currentPiece.move_down(1);
                break;
            case 'w': // rotate to the right
                rotatePiece();
                break;
            case 'q': // quit
                isRunning = false;
                break;
        }
    }
}

// tries to rotate piece right, if it collidies tries rotating after moving piece left and right
// does nothing if not possible
void Game::rotatePiece() {
    int nTries = (int)(currentPiece.get_shape_height()/2.0+0.5); // max number of tiles to move in either direction in order to try to rotate piece
    for (int i = 0; i != nTries; ++i) {
        currentPiece.rotate_shape(0);
        if (!board.hasCollided(currentPiece)) {
            return;
        }
        currentPiece.rotate_shape(1);
        currentPiece.move_right(1);
    }
    currentPiece.move_left(nTries+1);
    for (int i = 0; i < nTries; ++i) {
        currentPiece.rotate_shape(0);
        if (!board.hasCollided(currentPiece)) {
            return;
        }
        currentPiece.rotate_shape(1);
        currentPiece.move_left(1);
    }
    currentPiece.move_right(nTries+1);
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

void Game::updateLevel() {
    level = (int)(1 + numberLinesCleared/5);
}