#include <iostream>
#include <ctime>
#include "../headers/Point.hpp"
#include <string>

int main()
{
    srand(time(0));
    Checker a(black);

    Point p(black, 4);

    Checker *oldReference = p.getCheckers().front();
    std::cout << p.getCheckers().front()->getId() << std::endl;
    std::cout << oldReference->getId() << std::endl;
    p.~Point();
    std::cout << oldReference->getId() << std::endl;

    return 0;
}