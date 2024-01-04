#include <iostream>
#include <fstream>
#include <string>


//TODO: Try extra part with recursive function
using namespace std;
const string digarr[9][2] = {{"o1e", "one"},
                       {"t2o", "two"},
                       {"t3e", "three"},
                       {"f4r", "four"},
                       {"f5e", "five"},
                       {"s6x", "six"},
                       {"s7n", "seven"},
                       {"e8t", "eight"},
                       {"n9e", "nine"}};
int main(){
    fstream file;

    //Open file
    file.open("input.txt", ios::in);
    if(!file.is_open()){
        cout << "Error opening file";
        return 1;
    }

    int result = 0;
    string line;
    while(getline(file, line)){
        for(int i=0; i<9; i++){
            size_t sub_indx = line.find(digarr[i][1]);
            while(sub_indx != string::npos){
                line.replace(sub_indx, digarr[i][1].length(), digarr[i][0]);
                sub_indx = line.find(digarr[i][1]);
            }
            cout << line << endl;
        }

        int len = line.length();
        char *l = line.data();
        int num = 0;

        for(int i=0; i<len; i++){
            char c = *(l+i);
            //There is always a number in the line
            if(c >= 48 && c <= 57){
                 num += (c-48)*10;
                 break;
            }
        }

        //Only first and last number is needed
        for(int i=len-1; i >=0; i--){
            char c = *(l+i);
            //There is always a number in the line
            if(c >= 48 && c <= 57){
                num += c-48;
                break;
            }
        }

        result += num;
    }

    cout << result << endl;
    file.close();

    return 0;
}
