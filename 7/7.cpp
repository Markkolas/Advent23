#include <array>
#include <algorithm>

#include "../adventbasics.h"
#include "7.h"

Poker_Tuple::Poker_Tuple(std::string& tuple){
    tuple.copy(hand, 5, 0);
    bid = std::stoi(tuple.substr(6));
}

Poker_Tuple::Poker_Tuple(Poker_Tuple& t):bid{t.bid}{
    for(int i = 0; i < 5; i++)
        hand[i] = t.hand[i];
}

int nCharsOfA(char hand[5], char c){
    int n = 0;

    for(int i = 0; i < 5; i++){
        if(hand[i] == c)
            n++;
    }

    return n;
}

//TODO: My dumbass did this. Fix doing one method that return an enum.
bool hasRepoker(Poker_Tuple& t){
    for(int i = 0; i < 13; i++){
       if(nCharsOfA(t.hand, CARDS[i]) == 5)
           return true;
    }
    return false;
}
bool hasPoker(Poker_Tuple& t){
    for(int i = 0; i < 13; i++){
       if(nCharsOfA(t.hand, CARDS[i]) == 4)
           return true;
    }
    return false;
}
bool hasFull(Poker_Tuple& t){
    return hasThree(t) && hasTwo(t);
}
bool hasThree(Poker_Tuple& t){
    for(int i = 0; i < 13; i++){
       if(nCharsOfA(t.hand, CARDS[i]) == 3)
           return true;
    }return false;
}
bool hasDoubleTwo(Poker_Tuple& t){
    bool firstHit = true;

    for(int i = 0; i < 13; i++){
        if(nCharsOfA(t.hand, CARDS[i]) == 2){
           if(firstHit)
               firstHit = false;
           else
               return true;
        }
    }

    return false;
}
bool hasTwo(Poker_Tuple& t){
    for(int i = 0; i < 13; i++){
       if(nCharsOfA(t.hand, CARDS[i]) == 2)
           return true;
    }return false;
}

bool handComparator(Poker_Tuple* t1, Poker_Tuple* t2){
    int i = 0;

    while(i < 5){
        if((t1->hand)[i] == (t2->hand)[i])
            i++;
        else if((t1->hand)[i] < (t2->hand)[i])
            return true;
        else
            return false;
    }

    std::cout << "SHIT. Same hands. Returning true" << std::endl;
    return true;
}

int main(int argc, char *argv[]){
    using namespace std;
    string in;

    if(!adbasic::loadStrInput(in, argc, argv)){
        return 0;
    }

    int n_lines = adbasic::getNumberLines(in);
    string lines[n_lines];

    adbasic::textToStrarr(in, lines, n_lines, '\n');
    cout << "Input proccessed to string arr" << endl;

    //Algorithm
    //TODO: Create an fixed size array of struct pointers to Poker_Tuple
    // then, populate the arrays and use sort() function to do the
    // sorting

    array<Poker_Tuple*, 1000> aRepoker;
    array<Poker_Tuple*, 1000> aPoker;
    array<Poker_Tuple*, 1000> aFull;
    array<Poker_Tuple*, 1000> aThree;
    array<Poker_Tuple*, 1000> aDoubleTwo;
    array<Poker_Tuple*, 1000> aTwo;
    array<Poker_Tuple*, 1000> aOne;

    int iR=0, iP=0, iF=0, iTh=0, iDTw=0, iTw=0, iO=0;

    cout << "Populating arrays..." << endl;
    for(int i = 0; i < n_lines; i++){
        Poker_Tuple t(lines[i]);

        if(hasRepoker(t))
            aRepoker[iR++] = new Poker_Tuple(t);
        else if(hasPoker(t))
            aPoker[iP++] = new Poker_Tuple(t);
        else if(hasFull(t))
            aFull[iF++] = new Poker_Tuple(t);
    }

    cout << "Sorting..." << endl;
    if(iR > 0)
        sort(aRepoker.begin(), aRepoker.begin()+iR, handComparator);
    if(iP > 0)
        sort(aPoker.begin(), aPoker.begin()+iP, handComparator);
    if(iF > 0)
        sort(aFull.begin(), aFull.begin()+iF, handComparator);

    cout << "\nRepoker:" << endl;
    for(int i = 0; i < iR; i++){
        cout << (*(aRepoker[i])).hand << endl;
    }
    cout << "\nPoker" << endl;
    for(int i = 0; i < iP; i++){
        cout << (*(aPoker[i])).hand << endl;
    }
    cout << "\nFull" << endl;
    for(int i = 0; i < iP; i++){
        cout << (*(aFull[i])).hand << endl;
    }
}
