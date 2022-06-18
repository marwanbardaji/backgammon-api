#include "../headers/Checker.hpp"

int Checker::ID_GENERATOR = 1;

Checker::Checker(CheckerColor color)
{
    this->color = color;
    this->id = ID_GENERATOR++;
}

CheckerColor Checker::getColor()
{
    return this->color;
}

int Checker::getId()
{
    return this->id;
}