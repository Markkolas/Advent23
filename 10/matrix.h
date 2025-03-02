#ifndef MATRIX_H_
#define MATRIX_H_

#include <memory>
#include <iostream>
#include <string>

struct Matrix{
    // A more syntactically simple solution can be archived with a double pointer and
    // Destructor() definition so deacollate heap memory. Also, usage of vectors is
    // recommended in C++ for dynamic Matrices
    // char** m;
    // m = new char*[rows];
    // loop -> m[i] = new char[cols]
    std::unique_ptr<std::unique_ptr<char[]>[]> m;
    int rows, cols;

    Matrix(int r, int c);
    std::unique_ptr<char[]>& operator[](std::size_t r);
};

#endif // MATRIX_H_
