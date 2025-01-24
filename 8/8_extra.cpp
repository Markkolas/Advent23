#include "../adventbasics.h"

#include <map>
#include <vector>


long long gcd(long long int a, long long int b){
    if(b == 0)
        return a;
    return gcd(b, a % b);
}

long long int lcm(long long int a, long long int b){
    return (a/gcd(a,b))*b;
}

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

    // Need to find initial starting keys (those wich end in A)
    vector<string> vkeys;

    cout << "Constructing map..." << endl;
    for(int i = 2; i < n_lines; i++){
        string key = lines[i].substr(0,3);
        string *map = new string[2];
        map[0] = lines[i].substr(7,3);
        map[1] = lines[i].substr(12,3),

        treasure_map[key] = map;

        if(key[2] == 'A')
            vkeys.push_back(key);
    }

    for(int i = 0; i < vkeys.size(); i++)
        cout << "Initial keys: " << vkeys[i] << endl;

    // Algorithm
    string instructions = lines[0];

    int n_keys = vkeys.size();
    long long int jumps = 0;
    long long int results[n_keys];
    bool hit = false;

    for(int i = 0; i < n_keys; i++){
        while(vkeys[i][2] != 'Z')
            for(string::iterator instruct = lines[0].begin();
                instruct != lines[0].end(); ++instruct){

                int val_index = (*instruct == 'L') ? 0 : 1;

                vkeys[i] = treasure_map[vkeys[i]][val_index];

                jumps++;
                if(vkeys[i][2] == 'Z')
                    break;
            }

        results[i] = jumps;

        jumps = 0;
    }

    long long int result = 0;
    result = lcm(results[0], results[1]);
    for(int i = 2; i < n_keys; i++){
        result = lcm(result, results[i]);
    }

    cout << "Result: " << result << endl;
}
