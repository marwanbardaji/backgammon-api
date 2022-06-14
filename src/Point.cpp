#include "Point.hpp"

Point::Point()
{
    occupiedPlayer = none;
    checkerAmount = 0;
}

PlayerColor Point::GetOccupiedColor()
{
    return occupiedPlayer;
}

void Point::SetOccupiedColor(Player player)
{
    occupiedPlayer = player.GetColor();
}

void Point::AddCheckerToPoint()
{
    checkerAmount++;
}

void Point::RemoveCheckerFromPoint()
{
    checkerAmount--;
}

void Point::KnockOutPiece(Player player)
{
    occupiedPlayer = player.GetColor();
    checkerAmount++;
}

bool Point::CanMoveTo(Player player)
{
    if (occupiedPlayer == player.GetColor() || occupiedPlayer == none)
        return true;

    if (checkerAmount < 2)
        return true;

    return false;
}