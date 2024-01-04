#include <iostream>
#include <fstream>
#include <string>


//TODO: Try extra part with recursive function
using namespace std;
const string digarr[9][2] = {{"1", "one"},
                       {"2", "two"},
                       {"3", "three"},
                       {"4", "four"},
                       {"5", "five"},
                       {"6", "six"},
                       {"7", "seven"},
                       {"8", "eight"},
                       {"9", "nine"}};
int main(){
    fstream file;

    //Open file
    file.open("test.txt", ios::in);
    if(!file.is_open()){
        cout << "Error opening file";
        return 1;
    }

    int result = 0;
    string line;
    while(getline(file, line)){
        for(int i=0; i<9; i++){
            size_t sub_indx = line.find(digarr[i][1]);
            if(sub_indx != string::npos)
                line.replace(sub_indx, digarr[i][1].length(), digarr[i][0]);
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
