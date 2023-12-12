#include <iostream>
#include <fstream>
#include <string>


//TODO: Try extra part with recursive function
using namespace std;
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
