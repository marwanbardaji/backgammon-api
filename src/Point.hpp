#ifndef POINT_HPP
#define POINT_HPP

#include "Player.hpp"

class Point
{
    PlayerColor occupiedPlayer;
    int checkerAmount;

public:
    Point();

    PlayerColor GetOccupiedColor();

    void SetOccupiedColor(Player player);

    void AddCheckerToPoint();

    void RemoveCheckerFromPoint();

    bool CanMoveTo(Player player);

    void KnockOutPiece(Player player);
};

#endif