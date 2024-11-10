#include <list>

#include "../adventbasics.h"

const int N_ORIGIN_SEEDS = 4;

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
    int next_ret = 0, prev_ret = 0, next_colon = 0;
    int org_values[N_ORIGIN_SEEDS], dest_values[N_ORIGIN_SEEDS];

    string line;

    next_ret = in.find('\n');
    next_colon = in.find(':');

    //First line are the seeds
    line = in.substr(next_colon+1, next_ret-next_colon);
    adbasic::stoiNumbersBySpaces(line, org_values, N_ORIGIN_SEEDS);

    prev_ret = next_ret;
    next_ret = in.find('\n', prev_ret+1);

    //TODO: After this is done, do method to split string in lines,
    //probably producing an array
    for(int y = 1; y < n_lines; y++){
        line = in.substr(prev_ret+1, next_ret-prev_ret+1);
        cout << line << endl;
        prev_ret = next_ret;
        next_ret = in.find('\n', prev_ret+1);
    }
    return 0;
}
