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
History::History(string &s){
    adbasic::stoiAllNumbersBySpaces(s, hist);

    list<int> diff_list;
    if((this -> calcDiffs(diff_list))){
        cout << "WARNING: Low level diffs are not zero" << endl;
        diffs = NULL;
        return;
    }
    diffs.reset(new History(diff_list));
}

History::History(list<int> &l):hist{l}{
    list<int> diff_list;
    if((this -> calcDiffs(diff_list))){
        cout << "Hist diff recursion ended" << endl;
        diffs = NULL;
        return;
    }

    diffs.reset(new History(diff_list));
}

History::History(const History& h):hist{h.hist}{
    diffs = h.diffs;
}

bool History::calcDiffs(list<int> &l){
    typedef list<int>::iterator l_it;
    bool full_zeros = true, has_negatives = false;

    // cout << "Calc differences..." << endl;
    for(l_it it = (this -> hist).begin();
        it != prev((this -> hist).end()); ++it){
        int d = *next(it,1) - *it;
        cout << d << " ";

        if(d != 0){
            full_zeros = false;
        } else if (d < 0) {
            cout << "\nWARNING: Negative value found" << endl;
            has_negatives = true;
        }

        l.push_back(d);
    }
    cout << endl;

    return full_zeros | has_negatives;
}

void History::calcNext(){
    if(diffs != NULL){
        int end_val = (this -> hist).back();
        (*(this -> diffs)).calcNext();
        cout << "End val: " << end_val << endl;
        (this -> hist).push_back(end_val +
                                 (*(this -> diffs)).hist.back());
    } else {
        cout << "At the bottom" << endl;
        (this -> hist).push_back((this -> hist).back());
    }

    cout << "Next calculated value: " << (this -> hist).back() << endl;
}

void History::calcPrev(){
    if(diffs != NULL){
        int first_val = (this -> hist).front();
        (*(this -> diffs)).calcPrev();
        cout << "First val: " << first_val << endl;
        (this -> hist).push_front(first_val -
                                 (*(this -> diffs)).hist.front());
    } else {
        cout << "At the bottom" << endl;
        (this -> hist).push_front((this -> hist).front());
    }

    cout << "Next calculated value: " << (this -> hist).front() << endl;
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
    list<History> lhist;

    // Algorithm is based in recursion in hist object construction
    // Build list with histories
    for(int i = 0; i < n_lines; i++){
        // cout << lines[i] << endl;
        History h(lines[i]);
        lhist.push_back(h);
    }

    int result = 0;
    for(list<History>::iterator it = lhist.begin(); it != lhist.end(); ++it){
        (*it).calcPrev();
        result += (*it).hist.front();
    }
    cout << "\nRESULT: " << result << endl;
    return 0;
}
