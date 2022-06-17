#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include "Point.hpp"
#include "Player.hpp"
#include "Move.hpp"
#include "Board.hpp"

class Game
{
private:
    Player turn;
    Board board;
    std::vector<Move> possiboleMoves;
    std::vector<Move> history;

    std::vector<int> RollDice();
    void GetPossibleMoves(bool firstMove, std::vector<int> &diceRolls);
    void SwapTurn();

public:
    bool GameEnded();

    void NextGameState();

    void MakeMove(Move move);
};

#endif