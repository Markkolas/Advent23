#include "matrix.h"

enum class TILES : char {
N_S='|', //North to south
E_W='-', //East to west
N_E='L', //North to east
N_W='J', //North to west
S_W='7', //South to west
S_E='F', //South to east
CHAR='S', //Main character
NIL='.', //Nil
};

struct Character{
    int x, y; // In 2D map: x -> col, y-> row
    int dx = 0, dy = 0;
    int steps = 0;
    enum TILES curr_tile;

    Matrix *map; // Char map

    Character(Matrix*);
    Character(int, int, Matrix*);

    bool goNorth();
    bool goSouth();
    bool goWest();
    bool goEast();

    int walk(int, int); //Walk and return true if destination
                         //reached
};

struct Point{
    int x, y;
    enum TILES tile;

    Point(int row, int col, TILES t): y{row}, x{col}, tile{t}{};
    Point(int row, int col): y{row}, x{col}{};
};
