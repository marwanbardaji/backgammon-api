#pragma once

#include <vector>
#include <cstdlib>

#include "Point.hpp"
#include "CheckerColor.hpp"
#include "../headers/Move.hpp"
#include "Board.hpp"

class Game
{
private:
    CheckerColor turn;
    Board board;
    std::vector<Move> history;

    std::vector<int> RollDice();
    std::vector<Move> *GetPossibleMoves(std::vector<int> *diceRoll);
    void SwapTurn();

public:
    bool GameEnded();

    void NextGameState();

    void MakeMove(Move move);
};
