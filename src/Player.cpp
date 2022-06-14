#include "Player.hpp"

Player::Player()
{
    barCheckers = 0;
    homeCheckers = 0;
    checkersInHomeQuadrant = 2;
}

void Player::SetColor(PlayerColor color)
{
    this->color = color;
}

void Player::IncreaseHomeCheckers()
{
    homeCheckers++;
}

void Player::IncreaseBarCheckers()
{
    barCheckers++;
}

void Player::IncreaseCheckersInHomeQuadrant()
{
    checkersInHomeQuadrant++;
}

void Player::DecreaseBarCheckers()
{
    barCheckers--;
}

void Player::DecreaseCheckersInHomeQuadrant()
{
    checkersInHomeQuadrant--;
}

PlayerColor Player::GetColor()
{
    return color;
}

int Player::GetHomeCheckers()
{
    return homeCheckers;
}

int Player::GetBarCheckers()
{
    return barCheckers;
}

int Player::GetCheckersInHomeQuadrant()
{
    return checkersInHomeQuadrant;
}