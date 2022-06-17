#include "../headers/Point.hpp"
#include <iostream>

Point::Point()
{
    this->occupiedColor = notOccupied;
}

Point::Point(CheckerColor color, int numberOfCheckers)
{
    this->occupiedColor = color == black ? blackOccupied : whiteOccupied;
    for (int i = 0; i < numberOfCheckers; i++)
    {
        //! MAYBE DANGEROUS
        this->addChecker(new Checker(color));
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

//! Remove this method later
std::list<Checker *> Point::getCheckers()
{
    return this->checkers;
}
bool Point::possibleToAdd(Checker *newChecker)
{
    if ((this->occupiedColor == notOccupied) || (this->occupiedColor == blackOccupied && newChecker->getColor() == black) || (this->occupiedColor == whiteOccupied && newChecker->getColor() == white))
    {
        return true;
    }
    else
    {
        throw "NotPossibleToAdd";
    }
}

// TODO: Exception if possible to add
void Point::addChecker(Checker *newChecker)
{
    try
    {
        this->possibleToAdd(newChecker);
        this->checkers.push_back(newChecker);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}