#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include "Point.hpp"
#include "Player.hpp"
#include "Move.hpp"

class Game
{
private:
    Player currentPlayer;
    Player whitePlayer;
    Player blackPlayer;
    Point points[24];
    std::vector<Move> possiboleMoves;
    std::vector<Move> history;
    void GeneratePossiboleMoves(std::vector<Move> &possiboleMoves,Move currentMove,bool canOffCheckers,int diceAmount,int diceIndex);

public:
    Game();

    ~Game();

    bool GameEnded();

    std::vector<Move> GetPossibleMoves();

    void MakeMove(int index);
};

#endif