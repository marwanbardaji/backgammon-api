#include "Move.hpp"

Move::Move(std::vector<int> dices)
{
    for (size_t i = 0; i < dices.size(); i++)
    {
        diceRole += std::to_string(dices[i]);
    }
}

Move::Move(const Move &move)
{
    diceRole = move.diceRole;
    from = move.from;
    to = move.to;
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
    for (size_t i = 0; i < from.size(); i++)
    {
        move += ": " + from[i] + "/" + to[i];
    }
    return move;
}
