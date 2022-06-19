#include "../headers/Point.hpp"
#include <iostream>

Point::Point()
{
    this->occupiedColor = notOccupied;
}

Point::Point(CheckerColor color, int numberOfCheckers)
{
    this->occupiedColor = notOccupied;
    this->addNewCheckersToEmptyPoint(color, numberOfCheckers);
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

Checker *Point::popChecker()
{
    Checker *topChecker = this->checkers.front();

    //! Kanske raderar topChecker
    this->checkers.pop_front();

    return topChecker;
}

// ? Låta game klassen sköta regel funktioner
/*bool Point::possibleToAdd(Checker *newChecker)
{
    if ((this->occupiedColor == notOccupied) || (this->occupiedColor == blackOccupied && newChecker->getColor() == black) || (this->occupiedColor == whiteOccupied && newChecker->getColor() == white))
    {
        return true;
    }
    else
    {
        throw "NotPossibleToAdd";
    }
}*/

// TODO: Exception if possible to add
void Point::addChecker(Checker *newChecker)
{
    this->checkers.push_back(newChecker);
    this->occupiedColor = newChecker->getColor() == black ? blackOccupied : whiteOccupied;

    // ? Låta game klassen sköta regel funktioner
    /*
    try
    {
        this->possibleToAdd(newChecker);
        this->occupiedColor = newChecker->getColor() == black ? blackOccupied : whiteOccupied;
        this->checkers.push_back(newChecker);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }*/
}

void Point::addNewCheckersToEmptyPoint(CheckerColor color, int numberOfCheckers)
{
    if (this->occupiedColor == notOccupied)
    {
        this->occupiedColor = color == black ? blackOccupied : whiteOccupied; // TODO Conversion between enums in private method
        for (int i = 0; i < numberOfCheckers; i++)
        {
            //! MAYBE DANGEROUS
            this->addChecker(new Checker(color));
        }
    } // TODO Exception
};