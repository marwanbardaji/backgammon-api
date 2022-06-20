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
    void getPossibleMoves(std::vector<Move> *possibleMoves, std::vector<int> diceRoll);
    void addTemporaryMove(std::vector<Move> *possibleMoves, Checker *fromChecker, Move *move, MoveType fromType, int nextDice, int from, int to);
    void generateLastMove(std::vector<Move> *possibleMoves, Move *move, int dice);
    bool checkerAndPointColorIsSame(CheckerColor color, int pointIndex);
    MoveType canMoveToPoint(CheckerColor checker, int pointIndex);
    void swapTurn();

public:
    bool gameEnded();

    void nextGameState();

    void makeMove(Move move);
};
