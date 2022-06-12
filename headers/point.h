#pragma once

#include "headers/checker.h"

class Point
{
    Checker checkers[10];

    void AddCheckerToPoint();

    void RemoveCheckerFromPoint();
};
