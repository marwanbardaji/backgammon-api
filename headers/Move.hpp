#ifndef MOVE_HPP
#define MOVE_HPP

#include "string"
#include "MoveType.hpp"
#include <vector>

class Move
{
    bool noMove;
    std::string diceRole;
    std::vector<int> from;
    std::vector<int> to;

public:
    Move(std::vector<int> dices);

    void AppendMove(int from, int to);

    void SetNoMove();

    int GetDiceIndexOfMove();

    std::vector<int> GetFrom();

    std::vector<int> GetTo();

    std::string GetMove();
};

#endif