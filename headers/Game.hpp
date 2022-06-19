#pragma once

#include <vector>

#include "Point.hpp"
#include "CheckerColor.hpp"
#include "Move.hpp"
#include "Board.hpp"

class Game
{
private:
    CheckerColor turn;
    Board board;
    std::vector<Move> history;

    std::vector<int> rollDice();
    std::vector<Move> *getPossibleMoves(std::vector<int> diceRoll);
    bool checkerAndPointColorIsSame(CheckerColor color, int pointIndex);
    MoveType canMoveToPoint(Checker *checker, bool canOffCheckers, int pointIndex);
    void swapTurn();

public:
    bool gameEnded();

    void nextGameState();

    void makeMove(Move move);
};
