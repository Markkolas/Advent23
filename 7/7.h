const char CARDS[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

struct Poker_Tuple{
    char hand[5];
    int bid;

    Poker_Tuple(char h[5], int b);
};

bool hasRepoker(Poker_Tuple&);
bool hasPoker(Poker_Tuple&);
bool hasFull(Poker_Tuple&);
bool hasThree(Poker_Tuple&);
bool hasTwo(Poker_Tuple&);
