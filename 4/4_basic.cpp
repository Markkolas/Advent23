#include "../adventbasics.h"
#include <math.h>

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

void stoiNumbersBySpaces(string & s, int num_list[], int n_numbers){
    int index_of_next_space = 0, index_of_prev_space = 0, num_index = 0;
    string s_num;

    if(s.back() != ' ')
        s = s+" ";

    //cout << "Converting: " << s << endl;

    index_of_next_space = s.find(' ');

    if(!index_of_next_space){
        index_of_prev_space = index_of_next_space;
        index_of_next_space = s.find(' ');
    }

    while(num_index < n_numbers){
        if(index_of_next_space - index_of_prev_space > 1){
            //Dont get two contiguous spaces
            //cout << "Converting index:" << num_index++ << endl;
            num_list[num_index++] = stoi(s.substr(index_of_prev_space, index_of_next_space));
        }

        index_of_prev_space = index_of_next_space;
        index_of_next_space = s.find(' ', index_of_next_space + 1);
    }

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
    int win_num_list[n_lines][WIN_COLS], my_num_list[n_lines][MY_COLS];
    string line;
    string win_numbers, my_numbers;
    int prev_ret = 0, next_ret = 0;

    if(in.back() != '\n')
        in = in + "\n";

    next_ret = in.find('\n');

    for(int y = 0; y < n_lines; y++){
        line = in.substr(prev_ret+LINE_HEADER_LEN, next_ret-LINE_HEADER_LEN);
        win_numbers = line.substr(0, line.find('|'));
        my_numbers = line.substr(line.find('|')+2, string::npos);

        stoiNumbersBySpaces(win_numbers, win_num_list[y], WIN_COLS);
        stoiNumbersBySpaces(my_numbers, my_num_list[y], MY_COLS);

        prev_ret = next_ret;
        next_ret = in.find('\n', next_ret+1);
    }

    // cout << "Printing win numbers..." << endl;
    // for(int i = 0; i < n_lines; i++){
    //     for(int v = 0; v < WIN_COLS; v++){
    //        cout << win_num_list[i][v] << " ";
    //     }

    //     cout << endl;
    // }

    // cout << "Printing my numbers..." << endl;
    // for(int i = 0; i < n_lines; i++){
    //     for(int v = 0; v < MY_COLS; v++){
    //         cout << my_num_list[i][v] << " ";
    //     }

    //     cout << endl;
    // }

    int result = 0;
    for(int i = 0; i < n_lines; i++){
        int line_points_exp = 0;
        for(int xw = 0; xw < WIN_COLS; xw++){
            for(int xm = 0; xm < MY_COLS; xm++){
                if(win_num_list[i][xw] == my_num_list[i][xm]){
                    line_points_exp++;
                    break;
                }
            }
        }
        result += pow(2, line_points_exp-1); //0.5 is floored to 0 in int conversion
    }

    cout << "Result is: " << result << endl;
}
