#include "../adventbasics.cpp"

using namespace std;

int main(){
    string in;

    //adbasic::getFromConsole(in);
    in = adbasic::readTest();

    cout << "Autodetecting cols... ";

    int cols = in.find("\n");

    cout << "Done: " << cols << endl;
}
