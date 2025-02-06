#include "9.h"

using namespace std;

// Simplemente quiero saber como de posible es hacer recursiones
// con constructores
//
// 1. Llamo constructor A con argumento de entrada string
// 2. Convierte string en lista de ints. Lista de ints es hist
// 3. Se calcula lista de diferencias
// 4. Crea nuevo objeto hist (en heap) llamando a constructor B con lista
//  de diferencias
// 5. Constructor B iguala argumento de entrada a hist
// 6. Se calcula lista de diferencias
// 7. Se llama a contructor B
// 8. Si uno de los elemento es 0 y el resto no, se para proceso
history::history(string &s){
    adbasic::stoiAllNumbersBySpaces(s, hist);

    list<int> diff_list;
    if(!(this -> calcDiffs(diff_list))){
        cout << "WARNING: Low level diffs are not zero" << endl;
        diffs = NULL;
        return;
    }

    diffs.reset(new history(diff_list));
}

history::history(list<int> &l):hist{l}{
    list<int> diff_list;
    if(!(this -> calcDiffs(diff_list))){
        cout << "Hist diff recursion ended" << endl;
        diffs = NULL;
        return;
    }

    diffs.reset(new history(diff_list));
}

bool history::calcDiffs(list<int> &l){

    return true;
}

int main(int argc, char *argv[]){
    string in;

    if(!adbasic::loadStrInput(in, argc, argv)){
        return 0;
    }

    int n_lines = adbasic::getNumberLines(in);
    string lines[n_lines];

    adbasic::textToStrarr(in, lines, n_lines, '\n');
    cout << "Input proccessed to string arr" << endl;

    // Build problem list
    list<history> lhist;

    // Algorithm is based in recursion in hist object construction
    lhist.push_back(lines[0]);

    return 0;
}
