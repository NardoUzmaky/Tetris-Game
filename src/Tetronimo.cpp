#include "../include/Class.hpp"
#include "../include/helper_functions.hpp"

#include <cmath>

// move one tile to the right if direction = 1 (or any other number thats not zero)
void Tetromino::move_shape(int direction) {
    if (direction) {
        ++x;
    } else {
        --x;
    }
    return;
}

void Tetromino::rotate_shape(double angle) {
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
    std::vector<std::vector<int>> RotM = {{(int)(std::cos(angle) + 0.5), -(int)(std::sin(angle) + 0.5)},
                                          {(int)(std::sin(angle) + 0.5), (int)(std::cos(angle) + 0.5)}}; // 2D for now

    std::vector<std::vector<int>> Rot90 = {{0, -1},
                                           {1, 0}};
    std::vector<std::vector<int>> Rot270 = {{0, 1},
                                           {-1, 0}};
    print_Matrix(RotM);
    //assert(height == width); // has to be square matrix
    std::vector<std::vector<int>> new_shape(width, std::vector<int>(height, 0));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            //std::cout << "("<< i << ", " << j << ") --> ";
            if (shape[i][j]) {
                int offset_x, offset_y;
                offset_x = (height-1)/2;               
                offset_y = (width-1)/2;
               
                std::vector<int> vec = {j - offset_y, i - offset_x}; //coordinate vector of point in shape
                //std::cout << "(" << vec[0] << ", " << vec[1] << ")   ";
                std::vector<int> rotated_vec = Matrix_vector_prod(RotM, vec);
                new_shape[rotated_vec[1] + offset_x][rotated_vec[0] + offset_y] = 1;
            }
        }
    //std::cout << "\n";
    }
    if (height != org_height) {
        removeRow(new_shape, height/2);
    }
    if (width != org_width) {
        removeColumn(new_shape, width/2);
    }
    shape = new_shape;
}