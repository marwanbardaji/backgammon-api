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
    
    void GeneratePossiboleMoves(std::vector<Move> &possiboleMoves, Move move, Board board, bool canOffCheckers, std::vector<int> &diceRolls, int diceIndex);
    std::vector<int> RollDice();
    void SwapTurn();

public:

    bool GameEnded();

    std::vector<Move> GetPossibleMoves(bool firstMove);

    void MakeMove(int index);
};

#endif