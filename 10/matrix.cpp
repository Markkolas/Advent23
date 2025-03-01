#include "matrix.h"

Matrix::Matrix(int r, int c): rows{r}, cols{c}, m{new std::unique_ptr<char[]>[r]}{
    for(int i = 0; i < r; i++){
        (m[i]).reset(new char[c]);
    }
}

std::unique_ptr<char[]>& Matrix::operator[](std::size_t r){
    return m[r];
}
