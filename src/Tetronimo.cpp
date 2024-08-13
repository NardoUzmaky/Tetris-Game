#include "../include/Class.hpp"
#include "../include/helper_functions.hpp"

#include <cmath>

// move one tile to the left if direction = 0, right if direction ==1 and down if direction == 2
void Tetromino::move_shape(int direction) {
    if (direction == 0) {
        ++x;
    } else if (direction == 1) {
        --x;
    } else if (direction == 2){ // move down 
        ++y;
    } else if (direction == 3) { // move up
        --y;
    }
    return;
}

int Tetromino::get_shape_height() {
    return shape.size();
}

int Tetromino::get_shape_width() {
    return shape[0].size();
}

int Tetromino::get_x() {
    return x;
}
int Tetromino::get_y() {
    return y;
}

std::vector<std::vector<int>>& Tetromino::get_shape() {
    return shape;
}

void Tetromino::init_shape() {
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

void Tetromino::rotate_shape(int direction) { // if direction = 0: rotate 90° to the right, if direction = 1: rotate 90° to the left
    int height = shape.size();
    int width = shape[0].size();
    int org_height = height;
    int org_width = width;
    if (height % 2 == 0) {
        int middleRow = height / 2;
        insertRow(shape, middleRow);
        ++height;  // Update height after insertion
    }
    
    if (width % 2 == 0) {
        int middleCol = width / 2;
        insertColumn(shape, middleCol);
        ++width;
    }
    //std::vector<std::vector<int>> RotM = {{(int)(std::cos(angle) + 0.5), -(int)(std::sin(angle) + 0.5)},
    //                                      {(int)(std::sin(angle) + 0.5), (int)(std::cos(angle) + 0.5)}}; // 2D for now
    //

    std::vector<std::vector<int>> RotM;
    if (direction == 0) {
        RotM = {{0, -1},
                {1, 0}};
    } else if (direction == 1){
        RotM = {{0, 1},
                {-1, 0}};
    }
    //assert(height == width); // has to be square matrix
    std::vector<std::vector<int>> new_shape(width, std::vector<int>(height, 0));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (shape[i][j]) {
                int offset_x, offset_y;
                offset_x = (height-1)/2;               
                offset_y = (width-1)/2;
               
                std::vector<int> vec = {j - offset_y, i - offset_x}; //coordinate vector of point in shape
                std::vector<int> rotated_vec = Matrix_vector_prod(RotM, vec);
                new_shape[rotated_vec[1] + offset_x][rotated_vec[0] + offset_y] = 1;
            }
        }
    }
    if (height != org_height) {
        removeColumn(new_shape, height/2);
    }
    if (width != org_width) {
        removeRow(new_shape, width/2);
    }
    shape = new_shape;
}