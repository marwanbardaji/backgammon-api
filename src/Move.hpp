#ifndef MOVE_HPP
#define MOVE_HPP

#include "string"
#include <vector>

class Move
{
    std::string diceRole;
    std::vector<std::string> from;
    std::vector<std::string> to;

public:
    Move(int firstDice, int secondDice);

    void AppendMove(std::string from, std::string to);

    std::vector<std::string> GetFrom();

    std::vector<std::string> GetTo();

    std::string GetMove();
};

#endif