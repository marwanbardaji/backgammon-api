#ifndef POINT_HPP
#define POINT_HPP

#include "Player.hpp"

class Point
{
    Player occupiedPlayer;
    int checkerAmount;

public:
    Point();

    Player GetOccupiedColor();

    void SetOccupiedColor(Player player);

    int GetCheckerAmount();

    void AddCheckerToPoint();

    void RemoveCheckerFromPoint();

    int CanMoveTo(Player player);

    void KnockOutPiece(Player player);
};

#endif