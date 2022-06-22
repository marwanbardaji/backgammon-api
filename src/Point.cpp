#include "../headers/Point.hpp"

Point::Point()
{
    this->occupiedColor = notOccupied;
    this->amountOfCheckers = 0;
}

Point::Point(CheckerColor color, int numberOfCheckers)
{
    this->occupiedColor = notOccupied;
    this->amountOfCheckers = 0;
    this->addNewCheckersToEmptyPoint(color, numberOfCheckers);
}

void Point::initializeCopiedPoint(PointColor occupiedColor, int checkerAmount)
{
    if (occupiedColor != notOccupied)
    {
        CheckerColor checkerColor = occupiedColor == blackOccupied ? black : white;
        addNewCheckersToEmptyPoint(checkerColor, checkerAmount);
    }
}


PointColor Point::getOccupiedColor()
{
    return this->occupiedColor;
}

int Point::getCheckerAmount()
{
    return this->amountOfCheckers;
}

int Point::getCheckerAmount(CheckerColor color)
{
    return (color == black && this->occupiedColor == blackOccupied) || (color == white && this->occupiedColor == whiteOccupied) ? this->getCheckerAmount() : 0;
}

void Point::popChecker()
{
    this->amountOfCheckers--;

    if (this->amountOfCheckers == 0)
        this->occupiedColor = notOccupied;
}

void Point::addChecker(CheckerColor color)
{
    this->occupiedColor = color == black ? blackOccupied : whiteOccupied;
    amountOfCheckers++;
}

void Point::addNewCheckersToEmptyPoint(CheckerColor color, int numberOfCheckers)
{
    if (this->occupiedColor == notOccupied)
    {
        this->occupiedColor = color == black ? blackOccupied : whiteOccupied; // TODO Conversion between enums in private method
        this->amountOfCheckers += numberOfCheckers;
    }
};