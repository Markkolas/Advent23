#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

constexpr unsigned int MAXRED=12, MAXBLUE=13, MAXGREEN=14;

bool checkLine(string& samples){
    char * pch;
    pch = strtok(samples.data(), ",;");

    while(pch != NULL){
        string sample = string(pch);
        cout << sample << endl;
    }
    return true;
}

int main(){
    fstream file;

    //Open file
    file.open("input.txt", ios::in);
    if(!file.is_open()){
        cout << "Error opening file";
        return 1;
    }

    int result, count;
    string line;
    while(getline(file, line)){
        //Games ID are put in order of apparition
        string samples = line.substr(line.find(':'));
        checkLine(samples);
    }
}
