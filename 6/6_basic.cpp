#include "../adventbasics.h"

#define N_LINES 2
#define N_RACES 3

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

    string lines[N_LINES];

    adbasic::textToStrarr(in, lines, N_LINES, '\n');
    cout << "Input proccessed to string arr" << endl;

    int vectors[N_LINES][N_RACES];

    // Convert to int arr
    // TODO: Maybe put all of this in a funciton, this structure is very
    //  typical in this Advent problems
    for(int i = 0; i < N_LINES; i++){
        int col_pos = lines[i].find(':');
        string vline = lines[i].substr(col_pos+1);

        adbasic::stoiNumbersBySpaces(vline, vectors[i], N_RACES);
    }

    // Main algorithm
    int n_records[N_RACES];
    for(int i = 0; i < N_RACES; i++){
        n_records[i] = 0;
        int race_time = vectors[0][i];
        int record = vectors[1][i];

        for(int j = 1; j < race_time; j++){
            int d = j*(race_time-j);
            if(d > record)
                n_records[i]++;
        }

        cout << n_records[i] << endl;
    }

    int result = n_records[0];
    for(int i = 1; i < N_RACES; i++){
        result *= n_records[i];
    }
    cout << result << endl;
}
