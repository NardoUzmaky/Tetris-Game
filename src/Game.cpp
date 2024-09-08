#include "../include/Class.hpp"
#include <thread>
#include <iostream>
//#include <conio.h>


#ifdef _WIN32

#include <windows.h>

#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__) 

#include <conio.h>

#elif defined (__APPLE__)
    #include <termios.h>
    #include <unistd.h>

#endif 


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

            processInput(input); // update position and alignment (rotation) of piece


            static int frameCount = 0;
            static int lock_delay_frames = (int)(FPS/3);
            static bool inLockDelay = false;

            if(++frameCount >= (int)(FPS/level)){ // gravity
                if(!board.hasCollided(*currentPiece)) {
                    currentPiece->move_down(1);
                }
                frameCount = 0;
            }

            if (inLockDelay) {
                --lock_delay_frames;
            }

            if(board.hasCollided(*currentPiece)) {
                inLockDelay = true;
                currentPiece->move_up(1);

                if (lock_delay_frames <= 0) {
                    board.update(*currentPiece);
                    int linesCleared = board.filledLines(); // check and remove lines which are filled
                    updateScore(linesCleared);
                    numberLinesCleared += linesCleared;
                    newPiece();
                    lock_delay_frames = (int)(FPS/3);
                    inLockDelay = false; 
                }
            }

            updateLevel();

            board.draw(*currentPiece, *nextPiece, score);
            
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
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }    

    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    
    while(isRunning) {
        char ch = getch();
        lastInput.store(ch); // replace existing value with char from input
    }

    #elif defined (__APPLE__)

    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while (isRunning) {
        char ch;
        if (read(STDIN_FILENO, &ch, 1) > 0) {
            lastInput.store(ch);
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    #endif
}

void Game::processInput(char &input)  {
    if (input != 0) {
        switch (input) { 
            case 'a': // move piece to the left
                currentPiece->move_left(1);
                if (board.hasCollided(*currentPiece)) {
                    currentPiece->move_right(1);
                }
                break;
            case 'd': // move right
                currentPiece->move_right(1);
                if (board.hasCollided(*currentPiece)) {
                    currentPiece->move_left(1);
                }
                break;
            case 's': //move down
                currentPiece->move_down(1);
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
    int nTries = (int)(currentPiece->get_shape_height()/2.0+0.5); // max number of tiles to move in either direction in order to try to rotate piece
    for (int i = 0; i != nTries; ++i) {
        currentPiece->rotate_shape(0);
        if (!board.hasCollided(*currentPiece)) {
            return;
        }
        currentPiece->rotate_shape(1);
        currentPiece->move_right(1);
    }
    currentPiece->move_left(nTries+1);
    for (int i = 0; i < nTries; ++i) {
        currentPiece->rotate_shape(0);
        if (!board.hasCollided(*currentPiece)) {
            return;
        }
        currentPiece->rotate_shape(1);
        currentPiece->move_left(1);
    }
    currentPiece->move_right(nTries+1);
}

void Game::newPiece() {
    delete currentPiece;
    currentPiece = nextPiece;
    nextPiece = new Tetromino(PieceType(rand()%7));
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
    level = (int)(1 + numberLinesCleared/10);
}