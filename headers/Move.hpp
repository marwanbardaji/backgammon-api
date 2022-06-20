#ifndef MOVE_HPP
#define MOVE_HPP

#include "string"
#include "MoveType.hpp"
#include <vector>

class Move
{
    bool noMove;
    std::string diceRole;
    std::vector<MoveType> fromType;
    std::vector<MoveType> toType;
    std::vector<int> from;
    std::vector<int> to;

public:
    Move(std::vector<int> dices);

    void appendMove(int from, int to, MoveType fromType, MoveType toType);

    void setNoMove();

    int getDiceIndexOfMove();

    std::vector<int> getFrom();

    std::vector<int> getTo();

    std::vector<MoveType> getFromType();

    std::vector<MoveType> getToType();

    std::string getMove();
};

#endif