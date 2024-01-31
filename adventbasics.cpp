#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace adbasic{
    using namespace std;

    string readInput(){
        fstream f;
        f.open("input.txt", ios::in);
        if(!f.is_open()){
            cout << "Error opening file";
            exit(1);
        }

        stringstream buff;
        buff << f.rdbuf();

        return buff.str();
    }

    string readTest(){
        fstream f;
        f.open("test.txt", ios::in);
        if(!f.is_open()){
            cout << "Error opening file";
            exit(1);
        }

        stringstream buff;
        buff << f.rdbuf();

        return buff.str();
    }

    void getFromConsole(string& s){
        string inst = "INSTRUCTIONS:\n"
            "1. Paste problem input.\n"
            "2. Press enter.\n"
            "3. On Linux, press C-D. On Windows, press C-Z and then Enter.\n"
            "This funtion will automatically eliminate the last newline\n"
            "\nINSERT PROBLEM INPUT\n";
        cout << inst << endl;

        s = "";
        char c;
        while(cin.get(c)){ //loop getting single characters
            s += c;
        }
        s.pop_back();

        cout << "Input read successfully" << endl;

        return;
    }
}
