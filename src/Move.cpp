#include "Move.hpp"

Move::Move(int firstDice, int secondDice)
{
    diceRole = std::to_string(firstDice) + std::to_string(secondDice);
}

void Move::AppendMove(std::string from, std::string to)
{
    this->from.push_back(from);
    this->to.push_back(to);
}

std::vector<std::string> Move::GetFrom()
{
    return from;
}

std::vector<std::string> Move::GetTo()
{
    return to;
}

std::string Move::GetMove()
{
    std::string move = diceRole;
    for (int i = 0; i < from.size(); i++)
    {
        move += ": " + from[i] + "/" + to[i];
    }
    return move;
}
