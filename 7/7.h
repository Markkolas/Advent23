#include <string>
const char CARDS[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

struct Poker_Tuple{
    char hand[6];
    int bid;

    Poker_Tuple(std::string& tuple);
    Poker_Tuple(Poker_Tuple& t);
};

bool hasRepoker(Poker_Tuple&);
bool hasPoker(Poker_Tuple&);
bool hasFull(Poker_Tuple&);
bool hasThree(Poker_Tuple&);
bool hasDoubleTwo(Poker_Tuple&);
bool hasTwo(Poker_Tuple&);

char transformCard(char);
bool handComparator(Poker_Tuple*, Poker_Tuple*);

int nCharsOfA(char hand[5], char c);
