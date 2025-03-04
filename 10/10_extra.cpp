#include "matrix.h"
#include "character.h"
#include "../adventbasics.h"

#include <iostream>
#include <vector>

using namespace std;

int rasterizeTrajectory(Matrix& m){

    return 1;
}

int main(int argc, char *argv[]){
    string in;

    if(!adbasic::loadStrInput(in, argc, argv)){
        return 0;
    }

    int n_lines = adbasic::getNumberLines(in);

    // This could be the map but I am dumb
    string lines[n_lines];

    adbasic::textToStrarr(in, lines, n_lines, '\n');
    cout << "Input proccessed to string arr" << endl;

    // Build map
    Matrix map(n_lines, adbasic::getMaxLen(lines, n_lines));
    Matrix extr_map(n_lines, adbasic::getMaxLen(lines, n_lines));
    for(int y = 0; y < map.rows; y++){
        for(int x = 0; x < map.cols; x++){
            map[y][x] = lines[y][x];
            extr_map[y][x] = '.';
        }
    }

    // for(int y = 0; y < map.rows; y++){
    //     cout << endl;
    //     for(int x = 0; x < map.cols; x++){
    //         cout << map[y][x];
    //     }
    // }

    // Main algorithm
    // There is no 'choices' for S. Only follow a path. The only choice
    // is the initial direction. Farest point is half walked length.
    Character C(&map);

    if(C.goNorth())
        cout << "Starts going North!" << endl;
    else if(C.goSouth())
        cout << "Starts going South!" << endl;
    else if(C.goEast())
        cout << "Starts going East!" << endl;
    else if(C.goWest())
        cout << "Starts going West!" << endl;

    vector<Point> pvect;
    int dest_reached = 0;

    while(dest_reached == 0){
        // Order of call matters
        pvect.push_back(Point(C.y, C.x, static_cast<TILES>(map[C.y][C.x])));

        dest_reached = C.walk(-1,-1);
    }

    if(dest_reached == 1 || dest_reached == 3){
        std::cout << "Steps done: " << C.steps << std::endl;
    } else {
        cout << "Something weird has happened! Returning..." << endl;
        return 1;
    }

    for(vector<Point>::iterator it = pvect.begin(); it != pvect.end(); ++it){
        extr_map[it->y][it->x] = map[it->y][it->x];
    }

    int n_inners = rasterizeTrajectory(extr_map);

    for(int y = 0; y < extr_map.rows; y++){
        cout << endl;
        for(int x = 0; x < extr_map.cols; x++){
            cout << extr_map[y][x];
        }
    }

    cout << "\nFound " << n_inners << " inner points!" << endl;
}
