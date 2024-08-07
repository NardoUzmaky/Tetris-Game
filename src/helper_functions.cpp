#include "../include/helper_functions.hpp"
#include <iostream>

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
