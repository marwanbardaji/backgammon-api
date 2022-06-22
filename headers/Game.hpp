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
    std::vector<Move *> history;

    std::vector<int> rollDice();
    CheckerColor getStartingTurn();
    void getPossibleMoves(std::vector<Move *> &possibleMoves, std::vector<int> diceRoll);
    void TraverseBoard(std::vector<Move *> &possibleMoves, std::vector<int> diceRoll, Move *move, int currentDepth, int maxDepth);
    bool addMoveToBoard(Checker *fromChecker, Move *move, MoveType fromType, int from, int to);
    bool checkerAndPointColorIsSame(CheckerColor color, Board &newBoard, int pointIndex);
    MoveType canMoveToPoint(Board &board, CheckerColor checker, int pointIndex);
    void swapTurn();

public:
    bool gameEnded();

    void nextGameState(bool firstMove);

    void makeMove(Move *move);
};
