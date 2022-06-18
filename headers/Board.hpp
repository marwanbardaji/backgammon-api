#pragma once
#include "Point.hpp"
#include <string> //TODO Ta bot n'r printBoard tas bort

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
    int getNumberofCheckersInHomeQuadrant(CheckerColor color); // TODO Kanske spara int
    int getHome(CheckerColor color);
    std::string printBoard(); // TODO Ta bort l'ngre fram
};