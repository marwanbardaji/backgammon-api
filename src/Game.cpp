#include "../headers/Game.hpp"
#include <iostream>

bool Game::gameEnded()
{
    return this->board.getHome(white) == 15 || this->board.getHome(black) == 15 ? true : false;
}

void Game::nextGameState()
{
    turn = white;
    std::vector<Move> possibleMoves;

    getPossibleMoves(&possibleMoves, rollDice());

    for (size_t i = 0; i < possibleMoves.size(); i++)
    {
        std::cout << std::to_string(i + 1) << ": " << possibleMoves[i].getMove() << std::endl;
    }
}

// TODO : Fixa generering för dubblet tärningar
// TODO : Byt tecken på tärningskast baserat på spelar tur
// TODO : Kombinera loops
void Game::getPossibleMoves(std::vector<Move> *possibleMoves, std::vector<int> diceRoll)
{
    for (int i = 0; i < 24; i++)
    {
        if (board.getBar(turn)->getCheckerAmount() > 0)
        {
            Move *move = new Move(diceRoll);
            addTemporaryMove(possibleMoves, board.getBar(turn)->popChecker(), move, bar, diceRoll[1], i, diceRoll[0] - 1);
            continue;
        }
        if (checkerAndPointColorIsSame(turn, i))
        {
            Move *move = new Move(diceRoll);
            addTemporaryMove(possibleMoves, board.getPoint(i)->popChecker(), move, regular, diceRoll[1], i, i - diceRoll[0]);
        }
    }

    for (int i = 0; i < 24; i++)
    {
        if (board.getBar(turn)->getCheckerAmount() > 0)
        {
            Move *move = new Move(diceRoll);
            addTemporaryMove(possibleMoves, board.getBar(turn)->popChecker(), move, bar, diceRoll[0], i, diceRoll[1] - 1);
            continue;
        }
        if (checkerAndPointColorIsSame(turn, i))
        {
            Move *move = new Move(diceRoll);
            addTemporaryMove(possibleMoves, board.getPoint(i)->popChecker(), move, regular, diceRoll[0], i, i - diceRoll[1]);
        }
    }
}

// TODO : Minimera kod, ta bort dubbelkod
void Game::addTemporaryMove(std::vector<Move> *possibleMoves, Checker *fromChecker, Move *move, MoveType fromType, int nextDice, int from, int to)
{
    switch (canMoveToPoint(turn, to))
    {
    case regular:
    {
        move->appendMove(from, to, fromType, regular);
        board.getPoint(to)->addChecker(fromChecker);
        generateLastMove(possibleMoves, move, nextDice);
        break;
    }
    case off:
    {
        move->appendMove(from, to, fromType, off);
        board.addCheckerToHome(turn);
        generateLastMove(possibleMoves, move, nextDice);
        board.getPoint(from)->addChecker(fromChecker);
        break;
    }
    case hit:
    {
        Checker *hitChecker = board.getPoint(to)->popChecker();
        board.getPoint(to)->addChecker(fromChecker);
        generateLastMove(possibleMoves, move, nextDice);
        board.getPoint(from)->addChecker(board.getPoint(to)->popChecker());
        board.getPoint(to)->addChecker(hitChecker);
        break;
    }
    default:
        board.getPoint(from)->addChecker(fromChecker);
        break;
    }
}

// TODO : Minimera kod
void Game::generateLastMove(std::vector<Move> *possibleMoves, Move *move, int dice)
{
    for (int i = 0; i < 24; i++)
    {
        if (checkerAndPointColorIsSame(turn, i))
        {
            switch (canMoveToPoint(turn, i - dice))
            {
            case regular:
            {
                Move *newMove = new Move(*move);
                newMove->appendMove(i, i - dice, regular, regular);
                possibleMoves->push_back(*newMove);
                break;
            }
            case off:
            {
                Move *newMove = new Move(*move);
                newMove->appendMove(i, i - dice, regular, off);
                possibleMoves->push_back(*newMove);
                break;
            }
            case hit:
            {
                Move *newMove = new Move(*move);
                newMove->appendMove(i, i - dice, regular, hit);
                possibleMoves->push_back(*newMove);
                break;
            }
            default:
                break;
            }
        }
    }
}

MoveType Game::canMoveToPoint(CheckerColor checker, int pointIndex)
{
    bool canOffCheckers = board.getNumberOfCheckersInHomeQuadrant(turn) == 15 ? true : false;

    if (!canOffCheckers && (pointIndex > 23 || pointIndex < 0))
        return illegal;

    if (canOffCheckers && ((pointIndex > 23 && checker == white) || (pointIndex < 0 && checker == black)))
        return off;

    if (board.getPoint(pointIndex)->getOccupiedColor() == notOccupied || checkerAndPointColorIsSame(checker, pointIndex))
        return regular;

    if (board.getPoint(pointIndex)->getCheckerAmount() < 2)
        return hit;

    return illegal;
}

bool Game::checkerAndPointColorIsSame(CheckerColor color, int pointIndex)
{
    return (color == black && this->board.getPoint(pointIndex)->getOccupiedColor() == blackOccupied) ||
           (color == white && this->board.getPoint(pointIndex)->getOccupiedColor() == whiteOccupied);
}

void Game::swapTurn()
{
    this->turn = turn == black ? white : black;
}

std::vector<int> Game::rollDice()
{
    std::vector<int> diceRolls;

    for (int i = 0; i < 2; i++)
    {
        diceRolls.push_back(rand() % 6 + 1);
    }

    if (diceRolls[0] == diceRolls[1])
    {
        for (int i = 0; i < 2; i++)
        {
            diceRolls.push_back(diceRolls[0]);
        }
    }

    return diceRolls;
}

void Game::makeMove(Move move)
{
    std::vector<int> from = move.getFrom();
    std::vector<int> to = move.getTo();
    std::vector<MoveType> fromType = move.getFromType();
    std::vector<MoveType> toType = move.getToType();

    for (size_t i = 0; i < from.size(); i++)
    {
        Checker *fromChecker;

        if (fromType[i] == bar)
        {
            fromChecker = board.getBar(turn)->popChecker();
        }
        else
        {
            fromChecker = board.getPoint(from[i])->popChecker();
        }

        if (toType[i] == off)
        {
            board.addCheckerToHome(turn);
            delete (fromChecker);
        }
        else if (toType[i] == hit)
        {
            CheckerColor oppositeColor = turn == black ? white : black;
            board.getBar(oppositeColor)->addChecker(board.getPoint(to[i])->popChecker());
            board.getPoint(to[i])->addChecker(fromChecker);
        }
        else
        {
            board.getPoint(to[i])->addChecker(fromChecker);
        }
    }

    history.push_back(move);
    swapTurn();
}
