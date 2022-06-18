#pragma once
#include "Point.hpp"
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
    int getNumberOfCheckersInHomeQuadrant(CheckerColor color); // TODO Kanske spara int
    int getHome(CheckerColor color);
    std::string printBoard(); // TODO Ta bort längre fram
    Point getPoint(int index);
};