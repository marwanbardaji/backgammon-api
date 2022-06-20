#include "../headers/Board.hpp"
#include <string> //TODO Ta bot när printBoard tas bort
Board::Board()
{
    this->points[0].addNewCheckersToEmptyPoint(white, 2);
    this->points[23].addNewCheckersToEmptyPoint(black, 2);
    this->points[16].addNewCheckersToEmptyPoint(white, 3);
    this->points[7].addNewCheckersToEmptyPoint(black, 3);
    this->points[18].addNewCheckersToEmptyPoint(white, 5);
    this->points[5].addNewCheckersToEmptyPoint(black, 5);
    this->points[11].addNewCheckersToEmptyPoint(white, 5);
    this->points[12].addNewCheckersToEmptyPoint(black, 5);
    this->homeBlack = 0;
    this->homeWhite = 0;
    this->blackBar = Point(black, 0);
    this->whiteBar = Point(white, 0);
}

int Board::getNumberOfCheckersInHomeQuadrant(CheckerColor color)
{
    int numberOfCheckers = 0;
    int startPoint = color == black ? 18 : 0;
    for (int i = startPoint; i < startPoint + 6; i++)
    {
        numberOfCheckers += this->points[i].getCheckerAmount(color);
    }
    return numberOfCheckers;
} // TODO Kanske spara int

int Board::getHome(CheckerColor color)
{
    return color == black ? this->homeBlack : this->homeWhite;
}

void Board::addCheckerToHome(CheckerColor color)
{
    if (color == white)
    {
        this->homeWhite++;
        return;
    }
    this->homeBlack++;
}

Point *Board::getBar(CheckerColor color)
{
    return color == black ? &this->blackBar : &this->whiteBar;
}

Point *Board::getPoint(int index)
{
    return &this->points[index];
}

std::string Board::printBoard()
{
    std::string returnString = "";
    for (int i = 12; i < 24; i++)
    {
        PointColor occupiedColor = this->points[i].getOccupiedColor();
        returnString += occupiedColor == notOccupied ? " " : (occupiedColor == blackOccupied ? "B" : "W");
        returnString += i == 17 ? " | " : " ";
    }
    returnString += "\n";
    for (int i = 12; i < 24; i++)
    {
        returnString += std::to_string(this->points[i].getCheckerAmount());
        returnString += i == 17 ? " | " : " ";
        // TODO HEXA DECIMAL För värden större än 9
    }
    returnString += "\n";
    returnString += "\n";
    for (int i = 11; i >= 0; i--)
    {
        returnString += std::to_string(this->points[i].getCheckerAmount());
        returnString += i == 6 ? " | " : " ";
        // TODO HEXA DECIMAL För värden större än 9
    }
    returnString += "\n";
    for (int i = 11; i >= 0; i--)
    {
        PointColor occupiedColor = this->points[i].getOccupiedColor();
        returnString += occupiedColor == notOccupied ? " " : (occupiedColor == blackOccupied ? "B" : "W");
        returnString += i == 6 ? " | " : " ";
    }
    returnString += "\n";
    returnString += "HW" + std::to_string(this->getHome(white)) + "   " + "HB" + std::to_string(this->getHome(black)) + "   ";
    returnString += "BW" + std::to_string(this->blackBar.getCheckerAmount()) + "   " + "BB" + std::to_string(this->whiteBar.getCheckerAmount());
    returnString += "\n";
    return returnString;
}