#include <iostream>
#include <ctime>
#include "../headers/Game.hpp"

int main()
{
    srand(time(0));
    Game game;
    game.nextGameState(true);
    return 0;
}