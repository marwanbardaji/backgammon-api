#include <stdio.h>
#include <stdlib.h>

#include <list>

#include "headers/point.h"
#include "headers/checker.h"
#include "headers/color.h"

class Game
{
    Point points[24];

    Game()
    {
        for (int i = 0; i < 2; i++)
        {
            Checker checker = Checker(Color.white);
            points[0].AddCheckerToPoint(checker);
        }
    }

    void AddToPoint(int index, Checker checker)
    {
    }
};
