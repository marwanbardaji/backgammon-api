#include "../headers/Game.hpp"
#include <iostream>

Game::Game()
{
    board = new Board();
}

Game::~Game()
{
    delete board;
}

bool Game::gameEnded()
{
    return this->board->getHome(white) == 15 || this->board->getHome(black) == 15 ? true : false;
}

CheckerColor Game::getStartingTurn()
{
    return CheckerColor(rand() % 2);
}

CheckerColor Game::getTurn()
{
    return this->turn;
}

std::vector<Move *> &Game::getPossibleMoves(bool firstMove)
{
    std::cout << this->board->printBoard() << std::endl;
    if (firstMove)
        turn = getStartingTurn();
    std::vector<Move *> *possibleMoves = new std::vector<Move *>;
    generateDiceVariants(*possibleMoves, rollDice());
    return *possibleMoves;
}

void Game::generateDiceVariants(std::vector<Move *> &possibleMoves, std::vector<int> diceRoll)
{
    if (turn == white)
    {
        for (int i = 0; i < 2; i++)
            diceRoll[i] = -diceRoll[i];
    }
    if (diceRoll[0] == diceRoll[1])
    {
        Move *doubleDiceMove = new Move(diceRoll, *this->board);
        TraverseBoard(possibleMoves, diceRoll, doubleDiceMove, 0, 4);
    }
    else
    {
        Move *move = new Move(diceRoll, *this->board);
        TraverseBoard(possibleMoves, diceRoll, move, 0, 2);
        std::vector<int> reversedDice;
        reversedDice.push_back(diceRoll[1]);
        reversedDice.push_back(diceRoll[0]);
        Move *inverseMove = new Move(diceRoll, *this->board);
        TraverseBoard(possibleMoves, reversedDice, inverseMove, 0, 2);
    }
}

void Game::TraverseBoard(std::vector<Move *> &possibleMoves, std::vector<int> diceRoll, Move *move, int currentDepth, int maxDepth)
{
    if (currentDepth == maxDepth)
    {
        possibleMoves.push_back(move);
        return;
    }
    for (int i = 0; i < 24; i++)
    {
        if (move->getNextBoard().getBar(turn).getCheckerAmount() > 0)
        {
            Move *newMove = new Move(*move);
            newMove->getNextBoard().getBar(turn).popChecker();
            int barDice = turn == black ? 24 + diceRoll[currentDepth] : diceRoll[currentDepth] - 1;
            if (addMoveToBoard(newMove, bar, i, barDice))
            {
                TraverseBoard(possibleMoves, diceRoll, newMove, currentDepth + 1, maxDepth);
            }
            continue;
        }
        else if (checkerAndPointColorIsSame(turn, move->getNextBoard(), i))
        {
            Move *newMove = new Move(*move);
            newMove->getNextBoard().getPoint(i).popChecker();
            if (addMoveToBoard(newMove, regular, i, i - diceRoll[currentDepth]))
            {
                TraverseBoard(possibleMoves, diceRoll, newMove, currentDepth + 1, maxDepth);
            }
        }
    }
    delete move;
}

bool Game::addMoveToBoard(Move *move, MoveType fromType, int from, int to)
{
    switch (canMoveToPoint(move->getNextBoard(), turn, to))
    {
    case regular:
    {
        move->appendMove(from, to, fromType, regular);
        move->getNextBoard().getPoint(to).addChecker(turn);
        return true;
    }
    case off:
    {
        move->appendMove(from, to, fromType, off);
        move->getNextBoard().addCheckerToHome(turn);
        return true;
    }
    case hit:
    {
        move->getNextBoard().getPoint(to).popChecker();
        move->getNextBoard().getPoint(to).addChecker(turn);
        CheckerColor oppositeColor = turn == black ? black : white;
        move->getNextBoard().getBar(oppositeColor).addChecker(oppositeColor);
        return true;
    }
    default:
        delete move;
        return false;
    }
}

MoveType Game::canMoveToPoint(Board &newBoard, CheckerColor checker, int pointIndex)
{
    bool canOffCheckers = newBoard.getNumberOfCheckersInHomeQuadrant(turn) == 15 ? true : false;

    if (!canOffCheckers && (pointIndex > 23 || pointIndex < 0))
        return illegal;

    if (canOffCheckers && ((pointIndex > 23 && checker == white) || (pointIndex < 0 && checker == black)))
        return off;

    if (newBoard.getPoint(pointIndex).getOccupiedColor() == notOccupied || checkerAndPointColorIsSame(checker, newBoard, pointIndex))
        return regular;

    if (newBoard.getPoint(pointIndex).getCheckerAmount() < 2)
        return hit;

    return illegal;
}

bool Game::checkerAndPointColorIsSame(CheckerColor color, Board &newBoard, int pointIndex)
{
    return (color == black && newBoard.getPoint(pointIndex).getOccupiedColor() == blackOccupied) ||
           (color == white && newBoard.getPoint(pointIndex).getOccupiedColor() == whiteOccupied);
}

void Game::swapTurn()
{
    this->turn = turn == black ? white : black;
}

std::vector<int> Game::rollDice()
{
    std::vector<int> diceRolls;

    for (int i = 0; i < 2; i++)
        diceRolls.push_back(rand() % 6 + 1);

    if (diceRolls[0] == diceRolls[1])
    {
        for (int i = 0; i < 2; i++)
            diceRolls.push_back(diceRolls[0]);
    }

    return diceRolls;
}

void Game::makeMove(Move *move)
{
    delete (this->board);
    this->board = &move->getNextBoard();
    history.push_back(move);
    swapTurn();
}
