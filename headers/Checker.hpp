#pragma once
#include "CheckerColor.hpp"

class Checker
{
private:
    static int ID_GENERATOR;
    int id;
    CheckerColor color;

public:
    Checker(CheckerColor color);
    CheckerColor getColor();
    int getId();
};