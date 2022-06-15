#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include "Point.hpp"
#include "Player.hpp"
#include "Move.hpp"

class Game
{
private:
    Player *currentPlayer;
    Player whitePlayer;
    Player blackPlayer;
    std::vector<Point> points;
    std::vector<Move> possiboleMoves;
    std::vector<Move> history;
    void GeneratePossiboleMoves(std::vector<Move> &possiboleMoves, Move move, std::vector<Point> board, bool canOffCheckers, std::vector<int> &diceRolls, int diceIndex);
    std::vector<int> RollDice();
    void SwapTurn();

public:
    Game();

    bool GameEnded();

    std::vector<Move> GetPossibleMoves(bool firstMove);

    void MakeMove(int index);
};

#endif