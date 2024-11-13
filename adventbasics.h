#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace adbasic{
    std::string readInput();
    std::string readTest();
    void getFromConsole(std::string& s);
    void cleanIndents(std::string& s, std::string r);
    int getNumberLines(std::string & s);
    void textToStrarr(std::string & s, std::string arr[], int arrsize, char separator);
    void stoiNumbersBySpaces(std::string & s, int num_list[], int n_numbers);
}
