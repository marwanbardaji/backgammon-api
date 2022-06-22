#pragma once
#include "Point.hpp"
#include <algorithm>
#include <iterator>

#include <string> //TODO Ta bort när printBoard tas bort

class Board
{
private:
    Point points[24];
    // TODO: Create Bar Class later
    Point blackBar;
    Point whiteBar;
    int homeWhite;
    int homeBlack;

public:
    Board();
    Board(Board &source);
    void popChecker(int index);
    int getNumberOfCheckersInHomeQuadrant(CheckerColor color); // TODO Kanske spara int
    int getHome(CheckerColor color);
    void addCheckerToHome(CheckerColor color);
    std::string printBoard(); // TODO Ta bort längre fram
    Point &getPoint(int index);
    Point &getBar(CheckerColor color);
};