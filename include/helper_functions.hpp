#ifndef HELPER_FUNCTIONS_HPP
#define HELPER_FUNCTIONS_HPP

#include <vector>
#include <cassert>

void print_Matrix(std::vector<std::vector<int>>& mat);

//calculate matrix*vector product
template <typename T>
std::vector<T> Matrix_vector_prod(std::vector<std::vector<T>>& mat, const std::vector<T> vec) {
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

void insertColumn(std::vector<std::vector<int>>& matrix, int colIndex);

void insertRow(std::vector<std::vector<int>>& matrix, int rowIndex);

void removeColumn(std::vector<std::vector<int>>& matrix, int colIndex);

void removeRow(std::vector<std::vector<int>>& matrix, int rowIndex);

#endif