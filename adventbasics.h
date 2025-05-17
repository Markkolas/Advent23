#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <list>
#include <sstream>

namespace adbasic{
    std::string readInput();
    std::string readTest();
    void getFromConsole(std::string& s);
    bool loadStrInput(std::string& s, int argc, char *argv[]);

    void cleanIndents(std::string& s, std::string r);
    int getNumberLines(std::string & s);
    void textToStrarr(std::string & s, std::string arr[], int arrsize, char separator);
    int getMaxLen(std::string arr[], int arrsize);

    template<int N>
    void stolNumbersBySpaces(std::string & s, std::array<long int,N> & num_list);

    void stoiNumbersBySpaces(std::string & s, int num_list[], int n_numbers);
    void stoiAllNumbersBySpaces(std::string & s, std::list<int> & l);

    //OBSOLETE
    void stolNumbersBySpaces(std::string & s, long int num_list[], int n_numbers);

    //Point struct with inline definitions
    struct Point{
        int p[2];
        Point(int y, int x): p{y,x}{}
        Point(const Point& point): p{point.p[0], point.p[1]}{}

        inline bool operator==(const Point& other){
            return (p[0] == other.p[0]) && (p[1] == other.p[1]);
        }

        inline bool operator!=(const Point& other){return !(*this==other);}
    };
}

//Unfortunetly, most compilers dont support having templated definitions
//in separated .h and .cpp files. One solution would be to include the .cpp
//where is needed. "Wild but no that uncommon". I prefer to leave them in the
//.h file so I can learn C++ has its "things..."
//See: https://stackoverflow.com/questions/3261093/function-template-in-a-namespace-in-a-separate-file-compiles-fine-but-the-linke
template<int N>
void adbasic::stolNumbersBySpaces(std::string & s, std::array<long int,N> & num_list){
    using namespace std;
    int index_of_next_space = 0, index_of_prev_space = 0, num_index = 0;
    string s_num;

    if(s.back() != ' ')
        s = s+" ";

    if(s.front() != ' ')
        s = " "+s;

    cout << "Converting: " << s << endl;
    index_of_next_space = s.find(' ', 1); //First char will always be a space

    while(num_index < N){
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

    //cout << "Convesion completed" << endl;
}
