#pragma once
#include "Checker.hpp"
#include "PointColor.hpp"
#include <list>

class Point
{
private:
    std::list<Checker *> checkers;
    PointColor occupiedColor;
    void changeColor();

public:
    Point();
    ~Point();
    Point(CheckerColor color, int numberOfCheckers);
    PointColor getOccupiedColor();
    int getCheckerAmount();
    bool possibleToAdd(Checker *newChecker);
    void addChecker(Checker *newChecker);
    std::list<Checker *> getCheckers();
};
