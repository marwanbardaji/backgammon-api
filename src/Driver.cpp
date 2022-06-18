#include <iostream>
#include <ctime>
#include "../headers/Board.hpp"
#include <string>

int main()
{
    srand(time(0));
    Board b;
    std::cout << b.printBoard() << std::endl;
    return 0;
}