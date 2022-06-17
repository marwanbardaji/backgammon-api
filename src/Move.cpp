#include "Move.hpp"

Move::Move(std::vector<int> dices, int diceIndexOfMove)
{
    this->diceIndexOfMove = diceIndexOfMove;
    noMove = false;
    for (size_t i = 0; i < dices.size(); i++)
    {
        diceRole += std::to_string(dices[i]);
    }
}

void Move::AppendMove(std::string from, std::string to)
{
    this->from.push_back(from);
    this->to.push_back(to);
}

void Move::SetNoMove()
{
    noMove = true;
}

int Move::GetDiceIndexOfMove()
{
    return this->diceIndexOfMove;
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
    if (noMove)
        return "(no-play)";
    std::string move = diceRole + ": ";
    for (size_t i = 0; i < from.size(); i++)
    {
        move += from[i] + "/" + to[i] + " ";
    }
    return move;
}
