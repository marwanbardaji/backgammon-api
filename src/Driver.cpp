#include <iostream>
#include <ctime>
#include "Game.hpp"

void GetBoard()
{
}

void ChoosePlayerColor()
{
}

int main()
{
    Game game;

    std::vector<Move> moves = game.GetPossibleMoves(true);

    for (size_t i = 0; i < moves.size(); i++)
    {
        std::cout << std::to_string(i + 1) << ": " << moves[i].GetMove() << " Address to move " << &moves[i] << std::endl;
    }

    return 0;
}