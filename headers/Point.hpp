#pragma once
#include "PointColor.hpp"
#include "CheckerColor.hpp"

class Point
{
private:
    PointColor occupiedColor;
    int amountOfCheckers;

public:
    Point();
    Point(CheckerColor color, int numberOfCheckers);
    PointColor getOccupiedColor();
    int getCheckerAmount();
    int getCheckerAmount(CheckerColor color);
    void initializeCopiedPoint(PointColor occupiedColor, int checkerAmount);
    void addChecker(CheckerColor color);
    void popChecker();
    void addNewCheckersToEmptyPoint(CheckerColor color, int numberOfCheckers);
};