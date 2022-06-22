#pragma once
#include "Checker.hpp"
#include "PointColor.hpp"
#include <list>

class Point
{
private:
    std::list<Checker *> checkers;
    PointColor occupiedColor;

public:
    Point();
    ~Point();
    Point(CheckerColor color, int numberOfCheckers);
    PointColor getOccupiedColor();
    int getCheckerAmount();
    int getCheckerAmount(CheckerColor color);
    bool possibleToAdd(Checker *newChecker);
    void initializeCopiedPoint(PointColor occupiedColor, int checkerAmount);
    void addChecker(Checker *newChecker);
    void popChecker();
    Checker *&getFrontChecker();
    std::list<Checker *> getCheckers();
    void addNewCheckersToEmptyPoint(CheckerColor color, int numberOfCheckers);
};