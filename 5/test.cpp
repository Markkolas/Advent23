#include <string>
#include <array>

#include "../adventbasics.h"

int main(){
    using namespace std;
    array<int, 3> arr = {0,0,0};
    string thing = "20 21 22";

    adbasic::sstoiNumbersBySpaces<int, 3>(thing, arr);

    for(int i = 0; i < 3; i++){
        cout << arr[i] << endl;
    }

    return 0;
}
