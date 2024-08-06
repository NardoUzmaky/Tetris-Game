#include "../include/Class.hpp"
#include <iostream>
#include <exception>

//calculate matrix*vector product
template <typename T>
std::vector<T> Matrix_vector_prod(std::vector<std::vector<T>>& mat, std::vector<T> vec) {
    std::vector<T> result;
    for (int i = 0; i < mat.size(); i++) {
        assert(mat[i].size() == vec.size());
        double sum = 0;
        for (int j = 0; j < vec.size(); j++) {
            sum += mat[i][j]*vec[j];
        }
        result.push_back(sum);
    }
    return result;
}

void print_Matrix(std::vector<std::vector<int>>& mat) {
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void insertColumn(std::vector<std::vector<int>>& matrix, int colIndex) {
    for (auto& row : matrix) {
        row.insert(row.begin() + colIndex, 0);
    }
}

void insertRow(std::vector<std::vector<int>>& matrix, int rowIndex) {
    matrix.insert(matrix.begin() + rowIndex, std::vector<int>(matrix[0].size(), 0));
}

void removeColumn(std::vector<std::vector<int>>& matrix, int colIndex) {
    for (auto& row : matrix) {
        row.erase(row.begin() + colIndex);
    }
}

void removeRow(std::vector<std::vector<int>>& matrix, int rowIndex) {
    matrix.erase(matrix.begin() + rowIndex);
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


int FRAMES_PER_SECOND = 30;

int main() {

    //std::vector<std::vector<int>> RotMatrix = {{1, 0, 2}, 
    //                                           {0, 1, 0},
    //                                           {4, 0, 1}};
    //std::vector<int> vec = {1, 2, 3};

    //RotMatrix[0].insert(RotMatrix[0].begin()+1, 10);

    //print_Matrix(RotMatrix);

    Tetromino piece(PieceType::T);
    piece.init_shape();
    try {
        piece.rotate_shape(90);
        auto shape = piece.getShape();
        print_Matrix(shape);
        return 0;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 1; 
}