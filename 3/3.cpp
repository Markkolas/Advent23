#include "../adventbasics.cpp"
#include <list>

using namespace std;

struct Schem{
    string data;
    int files, cols;

    Schem(string s);
    Schem(string s, int files, int cols): data{s}, files{files}, cols{cols}{}

    char& operator()(int x, int y);
    char& operator[](size_t pos){return data[pos];}
};

Schem::Schem(string s){
    cout << "Autodetecting cols... ";
    cols = s.find("\n");
    cout << "Done: " << cols << endl;

    cout << "Cleaning indents...";
    adbasic::cleanIndents(s);
    cout << " Done!" << endl;

    files = s.size()/cols;
    cout << "Schem is size: " << files << "x" << cols << endl;

    data = s;
}

char& Schem::operator()(int y, int x){
    if(x < 0) x = 0;
    if(y < 0) y = 0;

    return data[y*cols+x];
}

struct Part{
    int num;
    size_t i_indx, e_indx;

    Part(){}
    Part(int initnum): num{initnum}{}
    Part(int initnum, size_t i, size_t e): Part(initnum){
        i_indx = i;
        e_indx = e;
    }

};

int main(){
    string in;
    list<Part> numlist;

    //adbasic::getFromConsole(in);
    in = adbasic::readTest();

    Schem schem(in);

    cout << "Detecting numbers..." << endl;
    for(size_t i=0; i<schem.data.size(); i++){
        if(schem[i] >= 48 && schem[i] <= 57){
            size_t e_num_indx;
            string aux = schem.data.substr(i);
            int num = stoi(aux, &e_num_indx);
            Part part(num, i, i+e_num_indx-1);

            numlist.push_back(part);

            i += e_num_indx;
        }
    }

    for(list<Part>::iterator it=numlist.begin(); it != numlist.end(); ++it){
        cout << "Num: " << (*it).num
             << "; Init indx: " << (*it).i_indx
             << "; End indx: " << (*it).e_indx << endl;
    }

    cout << schem(9,0) << endl;
    cout << schem(9,1) << endl;
    cout << schem(9,2) << endl;
    cout << schem(9,3) << endl;
}
