#include "matrix.h"

#include <iostream>

int main(){
    Matrix matrix(1024,1024);

    matrix[0][0] = 'H';
    matrix[1][1] = 'e';
    matrix[2][2] = 'l';
    matrix[3][3] = 'l';
    matrix[4][4] = 'o';

    for(int i=0; i < 5 ; i++)
        std::cout << matrix[i][i] << std::endl;
}
