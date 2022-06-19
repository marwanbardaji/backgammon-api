#include "../headers/Move.hpp"

Move::Move(std::vector<int> dices)
{
    this->noMove = false;
    for (size_t i = 0; i < dices.size(); i++)
    {
        this->diceRole += std::to_string(dices[i]);
    }
}

void Move::appendMove(int from, int to)
{
    this->from.push_back(from);
    this->to.push_back(to);
}

void Move::setNoMove()
{
    this->noMove = true;
}

std::vector<int> Move::getFrom()
{
    return this->from;
}

std::vector<int> Move::getTo()
{
    return this->to;
}

std::string Move::getMove()
{
    if (noMove)
        return "(no-play)";
    std::string move = diceRole + ": ";
    for (size_t i = 0; i < from.size(); i++)
    {
        if (fromType[i] == bar)
        {
            move += "Bar";
        }
        else
        {
            move += std::to_string(from[i]);
        }
        move += "/";
        if (to[i] == off)
        {
            move += "Off";
        }
        else if (to[i] == hit)
        {
            move += std::to_string(to[i]) + "*";
        }
        else
        {
            move += std::to_string(to[i]);
        }
    }
    return move;
}
