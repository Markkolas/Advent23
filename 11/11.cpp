#include "../adventbasics.h"

#include <vector>

using namespace std;

int calcResult(vector<adbasic::Point> &GPoints){
    using adbasic::Point;
    int i = 0;
    int result = 0;

    vector<Point>::iterator g1t = GPoints.begin();
    while(g1t != GPoints.end()){
        for(vector<Point>::iterator g2t = g1t;
            g2t != GPoints.end(); ++g2t){
            int incry = abs((*g2t).p[0]-(*g1t).p[0]);
            int incrx = abs((*g2t).p[1]-(*g1t).p[1]);

            result += incrx + incry;
        }

        i++;
        g1t = GPoints.begin()+i;
    }

    return result;
}

int main(int argc, char *argv[]){
    string in;
    if(!adbasic::loadStrInput(in, argc, argv)){
        return 0;
    }

    int n_lines = adbasic::getNumberLines(in);

    string lines[n_lines];

    adbasic::textToStrarr(in, lines, n_lines, '\n');
    cout << "Input proccessed to string arr" << endl;

    using adbasic::Point;

    //Scan for galaxies
    vector<Point> GPoints;
    for(int y = 0; y < n_lines; y++){
        for(int x = 0;
            x < adbasic::getMaxLen(lines, n_lines);
            x++){
            if(lines[y][x] == '#')
                GPoints.push_back(Point(y,x));
        }
    }

    cout << "N of galaxies found: " << GPoints.size() << endl;

    //Find distances for all pairs
    int res = calcResult(GPoints);
    cout << "Sum of all distances: " << res << endl;
}
