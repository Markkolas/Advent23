#include "../adventbasics.h"

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

    for(int i = 0; i < n_lines; i++)
        cout << lines[i] << endl;
}
