#include "../adventbasics.h"

#include <memory>

struct History{
    std::list<int> hist;
    std::shared_ptr<History> diffs;

    History(std::string & s);
    History(std::list<int> & l);
    History(const History& h);

    bool calcDiffs(std::list<int> & l);
    void calcPrev();
    void calcNext();
};
