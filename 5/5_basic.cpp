#include <list>

#include "../adventbasics.h"

template<typename T>
using Map = std::list<T>;

template<typename T>
using MapList = std::list<Map<T>>;

const int N_ORIGIN_SEEDS = 4;
const int N_COLS_IN_MAP = 3;
MapList<int[N_COLS_IN_MAP]> map_list;

int main(int argc, char *argv[]){
    using namespace std;
    string in;

    if(argc == 1){
        cout << "Specify argument.\n"
             << "0: From console\n"
             << "1: From 'test.txt' file\n"
             << "2: From 'input.txt' file" << endl;

        return 0;
    }
    if(*argv[1] == '0')
        adbasic::getFromConsole(in);
    else if(*argv[1] == '1')
        in = adbasic::readTest();
    else if(*argv[1] == '2')
        in = adbasic::readInput();
    else{
        cout << "Wrong argument, exiting..." << endl;
        return 0;
    }

    if(in.back() != '\n')
        in = in + "\n";

    int n_lines = adbasic::getNumberLines(in);
    int colon_pos = 0;
    int org_values[N_ORIGIN_SEEDS], dest_values[N_ORIGIN_SEEDS];

    string lines[n_lines];

    adbasic::textToStrarr(in, lines, n_lines, '\n');


    colon_pos = in.find(':');

    //First line are the seeds
    // line = in.substr(next_colon+1, next_ret-next_colon);
    string seeds_line = lines[0].substr(colon_pos+1, in.find('\n')-colon_pos);
    adbasic::stoiNumbersBySpaces(seeds_line, org_values, N_ORIGIN_SEEDS);

    for(int i = 0; i < N_ORIGIN_SEEDS; i++){
        cout << org_values[i] << endl;
    }

    bool rding_map = false;
    int val_arr[N_COLS_IN_MAP];
    Map<int[N_COLS_IN_MAP]> map;
    for(int i = 1; i < n_lines; i++){
        //cout << lines[i] << endl;
        if(lines[i].find("map") != string::npos){ //start of map
            rding_map = true;
            map.clear();
        }
        else if(rding_map){
            if(lines[i].size() == 0){
               rding_map = false;
               map_list.push_back(map);
            }
            else{
                adbasic::stoiNumbersBySpaces(lines[i], val_arr, N_COLS_IN_MAP);
                map.push_back(val_arr);
            }
        }
    }

    for(MapList<int[N_COLS_IN_MAP]>::iterator iit=map_list.begin(); iit != map_list.end(); ++iit){
        cout << "A map" << endl;
        for(Map<int[N_COLS_IN_MAP]>::iterator it=(*iit).begin(); it != (*iit).end(); ++it){
            cout << *it << endl;
        }
        cout << "Map finished" << endl;
    }

    return 0;
}
