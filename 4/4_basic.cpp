#include "../adventbasics.h"

const int WIN_COLS = 10;
const int MY_COLS = 25;
const int LINE_HEADER_LEN = 10;

using namespace std;

int getNumberLines(string & s){

    int n_lines = 0;

    for(size_t i = 0; i < s.size(); i++){
        if(s[i] == '\n')
            n_lines++;
    }

    return n_lines;
}

int main(int argc, char *argv[]){
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

    int n_lines = getNumberLines(in);
    string win_numbers_list[n_lines];
    string my_numbers_list[n_lines];

    for(int i = 0; i < n_lines; i++){

    }

}
