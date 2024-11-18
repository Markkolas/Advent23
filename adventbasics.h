#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <sstream>

namespace adbasic{
    std::string readInput();
    std::string readTest();
    void getFromConsole(std::string& s);
    void cleanIndents(std::string& s, std::string r);
    int getNumberLines(std::string & s);
    void textToStrarr(std::string & s, std::string arr[], int arrsize, char separator);

    template<typename T, int N>
    void stoiNumbersBySpaces(std::string & s, std::array<T,N> & num_list);

    //OBSOLETE
    void stoiNumbersBySpaces(std::string & s, int num_list[], int n_numbers);
}

//Unfortunetly, most compilers dont support having templated definitions
//in separated .h and .cpp files. One solution would be to include the .cpp
//where is needed. "Wild but no that uncommon". I prefer to leave them in the
//.h file so I can learn C++ has its "things..."
//See: https://stackoverflow.com/questions/3261093/function-template-in-a-namespace-in-a-separate-file-compiles-fine-but-the-linke
template<typename T, int N>
void adbasic::stoiNumbersBySpaces(std::string & s, std::array<T,N> & num_list){
    using namespace std;
    int index_of_next_space = 0, index_of_prev_space = 0, num_index = 0;
    string s_num;

    if(s.back() != ' ')
        s = s+" ";

    //cout << "Converting: " << s << endl;

    index_of_next_space = s.find(' ');
    if(index_of_next_space == 0){
        index_of_prev_space = index_of_next_space;
        index_of_next_space = s.find(' ', index_of_prev_space+1);
    }
    while(num_index < N){
        if(index_of_next_space - index_of_prev_space >= 1){
            //Dont get two contiguous spaces
            //cout << "Converting index:" << num_index++ << endl;
            //cout << s.substr(index_of_prev_space, index_of_next_space) << endl;
            //cout << "Prev space at: " << index_of_prev_space << endl;
            //cout << "Next space at: " << index_of_next_space << endl;
            num_list[num_index++] = stoi(s.substr(index_of_prev_space, index_of_next_space));
        }

        index_of_prev_space = index_of_next_space;
        index_of_next_space = s.find(' ', index_of_next_space + 1);
    }

    //cout << "Convesion completed" << endl;
}
