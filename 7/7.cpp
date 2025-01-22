#include <array>
#include <algorithm>

#include "../adventbasics.h"
#include "7.h"

Poker_Tuple::Poker_Tuple(std::string& tuple){
    tuple.copy(hand, 5, 0);
    hand[5] = '\0';
    bid = std::stoi(tuple.substr(6));
}

Poker_Tuple::Poker_Tuple(Poker_Tuple& t):bid{t.bid}{
    for(int i = 0; i < 6; i++)
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

char transformCard(char c){
    char cr;

    if(c == CARDS[8])
        cr = 'a';
    else if(c == CARDS[9])
        cr = 'b';
    else if(c == CARDS[10])
        cr = 'c';
    else if(c == CARDS[11])
        cr = 'd';
    else if(c == CARDS[12])
        cr = 'e';
    else
        cr = c;

    return cr;
}

bool handComparator(Poker_Tuple* t1, Poker_Tuple* t2){
    int i = 0;

    while(i < 5){
        char c1 = transformCard((t1->hand)[i]);
        char c2 = transformCard((t2->hand)[i]);

        if(c1 == c2)
            i++;
        else if(c1 < c2)
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
        else if(hasThree(t))
            aThree[iTh++] = new Poker_Tuple(t);
        else if(hasDoubleTwo(t))
            aDoubleTwo[iDTw++] = new Poker_Tuple(t);
        else if(hasTwo(t))
            aTwo[iTw++] = new Poker_Tuple(t);
        else
            aOne[iO++] = new Poker_Tuple(t);
    }

    cout << "Sorting..." << endl;
    if(iR > 0)
        sort(aRepoker.begin(), aRepoker.begin()+iR, handComparator);
    if(iP > 0)
        sort(aPoker.begin(), aPoker.begin()+iP, handComparator);
    if(iF > 0)
        sort(aFull.begin(), aFull.begin()+iF, handComparator);
    if(iTh > 0)
        sort(aThree.begin(), aThree.begin()+iTh, handComparator);
    if(iDTw > 0)
        sort(aDoubleTwo.begin(), aDoubleTwo.begin()+iDTw, handComparator);
    if(iTw > 0)
        sort(aTwo.begin(), aTwo.begin()+iTw, handComparator);
    if(iO > 0)
        sort(aOne.begin(), aOne.begin()+iO, handComparator);

    int rank = 1;
    int result = 0;
    cout << "\nOne" << endl;
    for(int i = 0; i < iO; i++){
        cout << "Hand: " << (*(aOne[i])).hand
             << " Bid: " << (*(aOne[i])).bid << endl;

        result += (*(aOne[i])).bid * rank++;
    }
    cout << "\nTwo" << endl;
    for(int i = 0; i < iTw; i++){
        cout << "Hand: " << (*(aTwo[i])).hand
             << " Bid: " << (*(aTwo[i])).bid << endl;

        result += (*(aTwo[i])).bid * rank++;
    }
    cout << "\nDoubleTwo" << endl;
    for(int i = 0; i < iDTw; i++){
        cout << "Hand: " << (*(aDoubleTwo[i])).hand
             << " Bid: " << (*(aDoubleTwo[i])).bid << endl;

        result += (*(aDoubleTwo[i])).bid * rank++;
    }
    cout << "\nThree" << endl;
    for(int i = 0; i < iTh; i++){
        cout << "Hand: " << (*(aThree[i])).hand
             << " Bid: " << (*(aThree[i])).bid << endl;

        result += (*(aThree[i])).bid * rank++;
    }
    cout << "\nFull" << endl;
    for(int i = 0; i < iF; i++){
        cout << "Hand: " << (*(aFull[i])).hand
             << " Bid: " << (*(aFull[i])).bid << endl;

        result += (*(aFull[i])).bid * rank++;
    }
    cout << "\nPoker" << endl;
    for(int i = 0; i < iP; i++){
        cout << "Hand: " << (*(aPoker[i])).hand
             << " Bid: " << (*(aPoker[i])).bid << endl;

        result += (*(aPoker[i])).bid * rank++;
    }
    cout << "\nRepoker:" << endl;
    for(int i = 0; i < iR; i++){
        cout << "Hand: " << (*(aRepoker[i])).hand
             << " Bid: " << (*(aRepoker[i])).bid << endl;

        result += (*(aRepoker[i])).bid * rank++;
    }

    cout << "\nResult: " << result << endl;
}
