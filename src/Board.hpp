#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "Point.hpp"

class Board
{
    int blackHomeCheckers;
    int whiteHomeCheckers;
    int blackBarCheckers;
    int whiteBarCheckers;
    int blackCheckersInHomeQuadrant;
    int whiteCheckersInHomeQuadrant;
    std::vector<Point> points;

public:
    Board();

    Board(const Board &);

    void IncreaseHomeCheckers(Player color);

    void IncreaseBarCheckers(Player color);

    void IncreaseCheckersInHomeQuadrant(Player color);

    void DecreaseBarCheckers(Player color);

    void DecreaseCheckersInHomeQuadrant(Player color);

    int GetHomeCheckers(Player color);

    int GetBarCheckers(Player color);

    int GetCheckersInHomeQuadrant(Player color);

    std::vector<Point> GetPoints();
};

#endif