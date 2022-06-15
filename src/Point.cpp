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

int Point::GetCheckerAmount()
{
    return checkerAmount;
}

void Point::RemoveCheckerFromPoint()
{
    checkerAmount--;
    if (checkerAmount == 0)
        occupiedPlayer = none;
}

void Point::KnockOutPiece(Player player)
{
    occupiedPlayer = player.GetColor();
    checkerAmount = 1;
}

int Point::CanMoveTo(Player player)
{
    if (occupiedPlayer == player.GetColor() || occupiedPlayer == none)
        return 0;

    if (checkerAmount < 2)
        return 1;

    return -1;
}