#ifndef PLAYER_HPP
#define PLAYER_HPP

enum PlayerColor
{
    white,
    black,
    none
};

class Player
{
    PlayerColor color;
    int homeCheckers;
    int barCheckers;
    int checkersInHomeQuadrant;

public:
    Player();

    void SetColor(PlayerColor color);

    void IncreaseHomeCheckers();

    void IncreaseBarCheckers();

    void IncreaseCheckersInHomeQuadrant();

    void DecreaseBarCheckers();

    void DecreaseCheckersInHomeQuadrant();

    PlayerColor GetColor();

    int GetHomeCheckers();

    int GetBarCheckers();

    int GetCheckersInHomeQuadrant();
};

#endif