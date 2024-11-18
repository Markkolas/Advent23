#include "adventbasics.h"

using namespace std;

string adbasic::readInput(){
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

string adbasic::readTest(){
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

void adbasic::getFromConsole(string& s){
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

void adbasic::cleanIndents(string& s, string r){
    size_t i = s.find("\n");
    while(i != string::npos){
        s.replace(i,1,r);
        i = s.find("\n");
    }
}

int adbasic::getNumberLines(string & s){

    int n_lines = 0;

    for(size_t i = 0; i < s.size(); i++){
        if(s[i] == '\n')
            n_lines++;
    }

    return n_lines;
}

void adbasic::textToStrarr(string & s, string arr[], int arrsize, char separator){
    int prev_occ = 0, next_occ = 0;

    if(arrsize <= 0){
        cout << "Array size must be above 0!" << endl;
        return;
    }

    next_occ = s.find(separator);

    arr[0] = s.substr(0, next_occ);
    cout << arr[0];

    prev_occ = next_occ;
    next_occ = s.find(separator, prev_occ+1);

    for(int i = 1; i < arrsize; i++){
        arr[i] = s.substr(prev_occ+1, next_occ-prev_occ-1);
        //cout << arr[i];
        prev_occ = next_occ;
        next_occ = s.find(separator, prev_occ+1);
    }
}

// void adbasic::stoiNumbersBySpaces(string & s, array<T,N>) See the .h
// OBSOLETE
void adbasic::stoiNumbersBySpaces(string & s, int num_list[], int n_numbers){
    int index_of_next_space = 0, index_of_prev_space = 0, num_index = 0;
    string s_num;

    if(s.back() != ' ')
        s = s+" ";

    //cout << "Converting: " << s << endl;

    index_of_next_space = s.find(' ');

    if(!index_of_next_space){
        index_of_prev_space = index_of_next_space;
        index_of_next_space = s.find(' ', index_of_prev_space+1);
    }

    while(num_index < n_numbers){
        if(index_of_next_space - index_of_prev_space >= 1){
            //Dont get two contiguous spaces
            //cout << "Converting index:" << num_index++ << endl;
            //cout << s.substr(index_of_prev_space, index_of_next_space) << endl;
            num_list[num_index++] = stoi(s.substr(index_of_prev_space, index_of_next_space));
        }

        index_of_prev_space = index_of_next_space;
        index_of_next_space = s.find(' ', index_of_next_space + 1);
    }

}
