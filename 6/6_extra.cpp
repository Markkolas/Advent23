#include <string>
#include "../adventbasics.h"

#define N_LINES 2

// U cant hurt me cuz I cant read
int main(int argc, char *argv[]){
    using namespace std;

    if(argc != 3){
        cout << "Introduce time[ms] and distance [mm]" << endl;
        return 0;
    }

    long int time = stol(argv[1]);
    long int record = stol(argv[2]);

    int n_records = 0;
    for(long int i = 1; i < time; i++){
        long int d = i*(time-i);
        if(d > record)
            n_records++;
    }

    cout << n_records << endl;
}
