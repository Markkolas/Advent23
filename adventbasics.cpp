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

bool adbasic::loadStrInput(std::string& s, int argc, char *argv[]){
    if(argc == 1){
        cout << "Specify argument.\n"
             << "0: From console\n"
             << "1: From 'test.txt' file\n"
             << "2: From 'input.txt' file" << endl;

        return false;
    }
    if(*argv[1] == '0')
        adbasic::getFromConsole(s);
    else if(*argv[1] == '1')
        s = adbasic::readTest();
    else if(*argv[1] == '2')
        s = adbasic::readInput();
    else{
        cout << "Wrong argument, exiting..." << endl;
        return false;
    }

    if(s.back() != '\n')
        s = s + "\n";

    return true;
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
    //cout << arr[0];

    prev_occ = next_occ;
    next_occ = s.find(separator, prev_occ+1);

    for(int i = 1; i < arrsize; i++){
        arr[i] = s.substr(prev_occ+1, next_occ-prev_occ-1);
        //cout << arr[i];
        prev_occ = next_occ;
        next_occ = s.find(separator, prev_occ+1);
    }
}

int adbasic::getMaxLen(std::string arr[], int arrsize){
    int len = 0, max_len = 0;
    for(int i = 0; i < arrsize; i++){
        len = arr[i].length();
        if(len > max_len)
            max_len = len;
    }

    return max_len;
}

// A bit brutal, but I prefer to have functions with different names
// rather than one with a template
void adbasic::stoiNumbersBySpaces(string & s, int num_list[], int n_numbers){
    int index_of_next_space = 0, index_of_prev_space = 0, num_index = 0;
    string s_num;

    if(s.back() != ' ')
        s = s+" ";

    if(s.front() != ' ')
        s = " "+s;

    //cout << "Converting: " << s << endl;
    index_of_next_space = s.find(' ', 1); //First char will always be a space

    while(num_index < n_numbers){
        int len = index_of_next_space - index_of_prev_space - 1;
        if(len > 0){
            //Dont get two contiguous spaces
            //cout << "Converting index:" << num_index++ << endl;
            //cout << s.substr(index_of_prev_space+1, len) << endl;
            //cout << "Prev space at: " << index_of_prev_space << endl;
            //cout << "Next space at: " << index_of_next_space << endl;
            num_list[num_index++] = stoi(s.substr(index_of_prev_space+1, len));
        }

        index_of_prev_space = index_of_next_space;
        index_of_next_space = s.find(' ', index_of_next_space + 1);
    }
}

void adbasic::stoiAllNumbersBySpaces(std::string &s, std::list<int> &l){
    int index_of_next_space = 0, index_of_prev_space = 0;
    string s_num;

    if(s.back() != ' ')
        s = s+" ";

    if(s.front() != ' ')
        s = " "+s;

    index_of_next_space = s.find(' ', 1); //First char will always be a space

    // cout << "Converting: " << s << endl;
    // cout << "Of size: " << s.size() << endl;
    while(index_of_next_space < s.size()){
        int len = index_of_next_space - index_of_prev_space - 1;
        if(len > 0){
            //Dont get two contiguous spaces
            // cout << "Converting index:" << num_index << endl;
            // cout << s.substr(index_of_prev_space+1, len) << endl;
            // cout << "Prev space at: " << index_of_prev_space << endl;
            // cout << "Next space at: " << index_of_next_space << endl;
            l.push_back(stoi(s.substr(index_of_prev_space+1, len)));
        }

        index_of_prev_space = index_of_next_space;
        index_of_next_space = s.find(' ', index_of_next_space + 1);
    }
}

// void adbasic::stolNumbersBySpaces(string & s, array<T,N>) See the .h
// OBSOLETE
void adbasic::stolNumbersBySpaces(string & s, long int num_list[], int n_numbers){
    int index_of_next_space = 0, index_of_prev_space = 0, num_index = 0;
    string s_num;

    if(s.back() != ' ')
        s = s+" ";

    if(s.front() != ' ')
        s = " "+s;

    //cout << "Converting: " << s << endl;
    index_of_next_space = s.find(' ', 1); //First char will always be a space

    while(num_index < n_numbers){
        int len = index_of_next_space - index_of_prev_space - 1;
        if(len > 0){
            //Dont get two contiguous spaces
            //cout << "Converting index:" << num_index++ << endl;
            //cout << s.substr(index_of_prev_space+1, len) << endl;
            //cout << "Prev space at: " << index_of_prev_space << endl;
            //cout << "Next space at: " << index_of_next_space << endl;
            num_list[num_index++] = stol(s.substr(index_of_prev_space+1, len));
        }

        index_of_prev_space = index_of_next_space;
        index_of_next_space = s.find(' ', index_of_next_space + 1);
    }
}
