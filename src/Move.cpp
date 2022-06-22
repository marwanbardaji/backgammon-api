#include "../headers/Move.hpp"

Move::Move(std::vector<int> dices, Board board)
{
    this->nextBoard = new Board(board);
    this->noMove = false;

    for (size_t i = 0; i < dices.size(); i++)
    {
        this->diceRole += std::to_string(abs(dices[i]));
    }
}

Move::~Move(){
    delete this->nextBoard;
}

Move::Move(Move &source)
{
    this->diceRole = source.diceRole;
    this->noMove = source.noMove;
    this->nextBoard = new Board(*source.nextBoard);
    this->from = source.from;
    this->to = source.to;
    this->fromType = source.fromType;
    this->toType = source.toType;
}

void Move::appendMove(int from, int to, MoveType fromType, MoveType toType)
{
    this->from.push_back(from);
    this->to.push_back(to);
    this->fromType.push_back(fromType);
    this->toType.push_back(toType);
}

Board &Move::getNextBoard()
{
    return *this->nextBoard;
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

std::vector<MoveType> Move::getFromType()
{
    return this->fromType;
}

std::vector<MoveType> Move::getToType()
{
    return this->toType;
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
        if (toType[i] == off)
        {
            move += "Off";
        }
        else if (toType[i] == hit)
        {
            move += std::to_string(to[i]) + "*";
        }
        else
        {
            move += std::to_string(to[i]);
        }
        move += " ";
    }
    return move;
}
