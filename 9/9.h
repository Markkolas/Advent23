#include "../adventbasics.h"

#include <memory>

struct history{
    std::list<int> hist;
    std::unique_ptr<history> diffs;

    history(std::string & s);
    history(std::list<int> & l);

    bool calcDiffs(std::list<int> & l);
};
