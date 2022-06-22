#include "../headers/Point.hpp"

Point::Point()
{
    this->occupiedColor = notOccupied;
}

Point::Point(CheckerColor color, int numberOfCheckers)
{
    this->occupiedColor = notOccupied;
    this->addNewCheckersToEmptyPoint(color, numberOfCheckers);
}

void Point::initializeCopiedPoint(PointColor occupiedColor, int checkerAmount)
{
    if (occupiedColor != notOccupied)
    {
        CheckerColor checkerColor = this->occupiedColor == blackOccupied ? black : white;
        addNewCheckersToEmptyPoint(checkerColor, checkerAmount);
    }
}

Point::~Point()
{
    std::list<Checker *>::iterator it;
    for (it = this->checkers.begin(); it != this->checkers.end(); ++it)
    {
        delete (*it);
    }
}

PointColor Point::getOccupiedColor()
{
    return this->occupiedColor;
}

int Point::getCheckerAmount()
{
    return this->checkers.size();
}

int Point::getCheckerAmount(CheckerColor color)
{
    return (color == black && this->occupiedColor == blackOccupied) || (color == white && this->occupiedColor == whiteOccupied) ? this->getCheckerAmount() : 0;
}

//! Remove this method later
std::list<Checker *> Point::getCheckers()
{
    return this->checkers;
}

Checker *&Point::getFrontChecker()
{
    return this->checkers.front();
}

void Point::popChecker()
{
    this->checkers.pop_front();

    if (checkers.empty())
        this->occupiedColor = notOccupied;
}

void Point::addChecker(Checker *newChecker)
{
    this->checkers.push_back(newChecker);
    this->occupiedColor = newChecker->getColor() == black ? blackOccupied : whiteOccupied;
}

void Point::addNewCheckersToEmptyPoint(CheckerColor color, int numberOfCheckers)
{
    if (this->occupiedColor == notOccupied)
    {
        this->occupiedColor = color == black ? blackOccupied : whiteOccupied; // TODO Conversion between enums in private method
        for (int i = 0; i < numberOfCheckers; i++)
        {
            this->addChecker(new Checker(color));
        }
    }
};