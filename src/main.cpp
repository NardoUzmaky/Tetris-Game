#include "../include/Class.hpp"
#include "../include/helper_functions.hpp"
#include <iostream>
#include <exception>



int FRAMES_PER_SECOND = 30;

int main() {

    //std::vector<std::vector<int>> RotMatrix = {{1, 0, 2}, 
    //                                           {0, 1, 0},
    //                                           {4, 0, 1}};
    //std::vector<int> vec = {1, 2, 3};

    //RotMatrix[0].insert(RotMatrix[0].begin()+1, 10);

    //print_Matrix(RotMatrix);
    Grid grid =  Grid();
    Tetromino piece(PieceType::T);
    try {
        grid.draw();
        //piece.rotate_shape(90);
        //auto shape = piece.getShape();
        //print_Matrix(shape);
        return 0;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 1; 
}