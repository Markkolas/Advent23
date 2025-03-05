#include "matrix.h"
#include "character.h"
#include "../adventbasics.h"

#include <iostream>
#include <vector>

using namespace std;

int searchInDir(Matrix& m, Point& org, Point& norm_dir, char c){
    int searchy = org.y+norm_dir.y, searchx = org.x+norm_dir.x;
    int result = 0;

    while(searchy >= 0 && searchy < m.rows &&
          searchx >= 0 && searchx < m.cols &&
          m[searchy][searchx] == '.'){
        m[searchy][searchx] = c;
        result++;
        searchx += norm_dir.x;
        searchy += norm_dir.y;
    }

    return result;
}

void rasterizeTrajectory(Matrix& m, vector<Point>& traj){
    // There are to zones, A and B. One of those is inner,
    // the other one is outer
    int resultA = 0, resultB = 0;

    Point dTnormprev(0,0);
    Point ndTnormprev(0,0);
    for(int i = 0; i < traj.size()-1; i++){
        int x = traj[i].x;
        int y = traj[i].y;
        int r = 1;

        Point dT(traj[i+1].y-y, traj[i+1].x-x);

        //90 degree rotated vector
        Point dTnorm(-dT.x, dT.y);
        Point org(y,x);

        //Check dir A
        resultA += searchInDir(m, org, dTnorm, 'A');
        resultA += searchInDir(m, org, dTnormprev, 'A');

        //Check dir B
        Point ndTnorm(dTnorm.y*-1, dTnorm.x*-1);
        resultB += searchInDir(m, org, ndTnorm, 'B');
        resultB += searchInDir(m, org, ndTnormprev, 'B');

        dTnormprev.x = dTnorm.x;
        dTnormprev.x = dTnorm.x;
        ndTnormprev.y = ndTnorm.y;
        ndTnormprev.y = ndTnorm.y;
    }

    cout << "\n Found " << resultA << " points in side A" << endl;
    cout << "\n Found " << resultB << " points in side B" << endl;
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
    Matrix extr_map(n_lines+2, adbasic::getMaxLen(lines, n_lines)+2);

    for(int y = 0; y < map.rows; y++){
        for(int x = 0; x < map.cols; x++){
            map[y][x] = lines[y][x];
        }
    }
    for(int y = 0; y < extr_map.rows; y++){
        for(int x = 0; x < extr_map.cols; x++){
            extr_map[y][x] = '.';
        }
    }

    // cout << endl;
    // for(int y = 0; y < map.rows; y++){
    //     for(int x = 0; x < map.cols; x++){
    //         cout << map[y][x];
    //     }
    //     cout << endl;
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
        extr_map[it->y+1][it->x+1] = map[it->y][it->x];
        (*it).x++;
        (*it).y++;
    }

    rasterizeTrajectory(extr_map, pvect);

    for(int y = 0; y < extr_map.rows; y++){
        cout << endl;
        for(int x = 0; x < extr_map.cols; x++){
            cout << extr_map[y][x];
        }
    }

    //cout << "\nFound " << n_inners << " inner points!" << endl;
}
