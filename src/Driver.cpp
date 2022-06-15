#include <iostream>
#include <ctime>
#include "Game.hpp"

void MakeMove(int index)
{
}

void GetHistory()
{
}

void GetBoard()
{
}

void ChoosePlayerColor()
{
}

int main()
{
    srand(time(0));
    Game game;

    std::vector<Move> moves = game.GetPossibleMoves(true);

    for (size_t i = 0; i < moves.size(); i++)
    {
        std::cout << std::to_string(i + 1) << ": " << moves[i].GetMove() << std::endl;
    }

    return 0;
}