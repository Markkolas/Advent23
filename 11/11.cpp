#include "../adventbasics.h"

#include <vector>

using namespace std;

int calcResult(vector<adbasic::Point> &GPoints){
    using adbasic::Point;
    int i = 0;
    int result = 0;

    vector<Point>::iterator g1t = GPoints.begin();
    while(g1t != GPoints.end()){
        cout << "\nGalaxy in pos (" << (*g1t).p[0] << "," << (*g1t).p[1] << "):" << endl;
        for(vector<Point>::iterator g2t = g1t;
            g2t != GPoints.end(); ++g2t){

            cout << "D to (" << (*g2t).p[0] << "," << (*g2t).p[1] << "): ";
            int incry = abs((*g2t).p[0]-(*g1t).p[0]);
            int incrx = abs((*g2t).p[1]-(*g1t).p[1]);

            cout << incrx+incry << endl;
            result += incrx + incry;
        }

        i++;
        g1t = GPoints.begin()+i;
    }

    return result;
}

void correctSpaceTime(vector<adbasic::Point>& GPoints, std::string arr[], int arr_size){
    // If a colum C has no galaxies, increment x in all galaxies with x>C
    // If a row R has no galaxies, increment y in all galaxies with y>R
    using adbasic::Point;

    vector<Point> GPoints_corrected(GPoints);
    for(int y = 0; y < arr_size; y++){

        bool GalaxyDetected = false;
        for(int x = 0; x < arr[y].length(); x++){
            if(arr[y][x] == '#'){
                GalaxyDetected = true;
                break;
            }
        }


        if(!GalaxyDetected){
            cout << "No galaxies on row: " << y << endl;
            for(int i = 0; i < GPoints.size(); i++){
                if(GPoints[i].p[0] > y) GPoints_corrected[i].p[0]++;
            }
        }
    }

    for(int x = 0; x < arr[0].length(); x++){
        bool GalaxyDetected = false;
        for(int y = 0; y < arr_size; y++){
            if(arr[y][x] == '#'){
                GalaxyDetected = true;
                break;
            }
        }


        if(!GalaxyDetected){
            cout << "No galaxies on col: " << x << endl;
            for(int i = 0; i < GPoints.size(); i++){
                if(GPoints[i].p[1] > x) GPoints_corrected[i].p[1]++;
            }
        }
    }

    GPoints.swap(GPoints_corrected);
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
    // for(int i = 0; i < n_lines; i++)
    //     cout << lines[i] << endl;

    using adbasic::Point;

    //Scan for galaxies
    vector<Point> GPoints;
    for(int y = 0; y < n_lines; y++){
        for(int x = 0; x < lines[y].length(); x++){
            if(lines[y][x] == '#'){
                Point p(y,x);
                cout << p.p[0] << " " << p.p[1] << endl;
                GPoints.push_back(p);
            }
        }
    }

    cout << "N of galaxies found: " << GPoints.size() << endl;

    //Correct points for space time expansion
    correctSpaceTime(GPoints, lines, n_lines);

    // for(vector<Point>::iterator it = GPoints.begin();
    //     it != GPoints.end(); ++it){
    //     cout << "Galaxy in pos: (" << (*it).p[0] << "," << (*it).p[1] << ")" << endl;
    // }

    //Find distances for all pairs
    int res = calcResult(GPoints);
    cout << "Sum of all distances: " << res << endl;
}
