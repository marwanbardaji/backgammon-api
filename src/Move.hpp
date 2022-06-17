#ifndef MOVE_HPP
#define MOVE_HPP

#include "string"
#include <vector>

class Move
{
    bool noMove;
    int diceIndexOfMove;
    std::string diceRole;
    std::vector<std::string> from;
    std::vector<std::string> to;

public:
    Move(std::vector<int> dices, int diceIndexOfMove);

    void AppendMove(std::string from, std::string to);

    void SetNoMove();

    int GetDiceIndexOfMove();

    std::vector<std::string> GetFrom();

    std::vector<std::string> GetTo();

    std::string GetMove();
};

#endif