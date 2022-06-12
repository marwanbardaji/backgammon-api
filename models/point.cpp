#include "headers/checker.h"
#include "list"

class Point
{
    std::list<Checker> checkers;

public:
    void AddCheckerToPoint(Checker checker)
    {
        checkers.push_front(checker);
    }

public:
    void RemoveCheckerFromPoint()
    {
        checkers.pop_front();
    }
};
