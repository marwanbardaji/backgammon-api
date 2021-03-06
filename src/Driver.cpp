#include <iostream>
#include <ctime>
#include "../headers/Game.hpp"

int main()
{
    srand(time(0));
    Game game;
    bool firstMove = true;

    do
    {
        std::vector<Move *> possibleMoves = game.getPossibleMoves(firstMove);
        for (size_t i = 0; i < possibleMoves.size(); i++)
        {
            std::cout << std::to_string(i + 1) << ": " << possibleMoves[i]->getMove(game.getTurn()) << std::endl;
        }
        std::cout << "Enter index of the move you want to make" << std::endl;

        int moveIndex;
        std::cin >> moveIndex;
        game.makeMove(possibleMoves[moveIndex - 1]);

        for (size_t i = 0; i < possibleMoves.size(); i++)
        {
            if (static_cast<int>(i) == moveIndex - 1)
                continue;
            delete possibleMoves[i];
        }
        possibleMoves.clear();
        firstMove = false;
    } while (!game.gameEnded());

    return 0;
}