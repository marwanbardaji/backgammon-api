#pragma once

#include "string"
#include "MoveType.hpp"
#include "Board.hpp"
#include <vector>
#include <stdlib.h>

class Move
{
    bool noMove;
    Board *nextBoard;
    std::string diceRole;
    std::vector<MoveType> fromType;
    std::vector<MoveType> toType;
    std::vector<int> from;
    std::vector<int> to;

public:
    Move(std::vector<int> dices, Board board);
    Move(Move &source);
    ~Move();
    void appendMove(int from, int to, MoveType fromType, MoveType toType);
    void setNoMove();
    int getDiceIndexOfMove();
    Board &getNextBoard();
    std::vector<int> getFrom();
    std::vector<int> getTo();
    std::vector<MoveType> getFromType();
    std::vector<MoveType> getToType();
    std::string getMove();
};
