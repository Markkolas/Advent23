#include "../adventbasics.h"

#include <map>

int main(int argc, char *argv[]){
    using namespace std;
    string in;

    if(!adbasic::loadStrInput(in, argc, argv)){
        return 0;
    }

    int n_lines = adbasic::getNumberLines(in);
    string lines[n_lines];

    adbasic::textToStrarr(in, lines, n_lines, '\n');
    cout << "Input proccessed to string arr" << endl;

    map<string, string*> treasure_map;

    cout << "Constructing map..." << endl;
    for(int i = 2; i < n_lines; i++){
        string key = lines[i].substr(0,3);
        string *map = new string[2];
        map[0] = lines[i].substr(7,3);
        map[1] = lines[i].substr(12,3),

        treasure_map[key] = map;
    }

    // Algorithm
    string instructions = lines[0];

    string key = "AAA";
    int jumps = 0;
    while(key.compare("ZZZ") != 0)
        for(string::iterator instruct = lines[0].begin();
            instruct != lines[0].end(); ++instruct){

            int val_index = (*instruct == 'L') ? 0 : 1;
            key = treasure_map[key][val_index];

            jumps++;

            if(key.compare("ZZZ") == 0)
                break;
        }

    cout << "Key found, N of jumps: " << jumps << endl;
}
