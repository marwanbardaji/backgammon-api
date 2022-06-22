#include "../headers/Game.hpp"
#include <iostream>

bool Game::gameEnded()
{
    return this->board.getHome(white) == 15 || this->board.getHome(black) == 15 ? true : false;
}

CheckerColor Game::getStartingTurn()
{
    return CheckerColor(rand() % 2);
}

void Game::nextGameState(bool firstMove)
{
    if (firstMove)
        turn = getStartingTurn();

    std::vector<Move *> possibleMoves;

    std::cout << turn << std::endl;

    getPossibleMoves(possibleMoves, rollDice());

    for (size_t i = 0; i < possibleMoves.size(); i++)
    {
        std::cout << std::to_string(i + 1) << ": " << possibleMoves[i]->getMove() << std::endl;
        // std::cout << possibleMoves[i].getNextBoard()->printBoard() << std::endl;
    }
}

void Game::getPossibleMoves(std::vector<Move *> &possibleMoves, std::vector<int> diceRoll)
{
    Move *move = new Move(diceRoll, this->board);

    if (turn == black)
    {
        for (int i = 0; i < 2; i++)
            diceRoll[i] = -diceRoll[i];
    }
    if (diceRoll[0] == diceRoll[1])
    {
        TraverseBoard(possibleMoves, diceRoll, move, 0, 4);
    }
    else
    {
        TraverseBoard(possibleMoves, diceRoll, move, 0, 2);
        std::vector<int> reversedDice;
        reversedDice.push_back(diceRoll[1]);
        reversedDice.push_back(diceRoll[0]);
        TraverseBoard(possibleMoves, reversedDice, move, 0, 2);
    }
    delete move;
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
            Checker *topChecker = newMove->getNextBoard().getBar(turn).getFrontChecker();
            newMove->getNextBoard().getBar(turn).popChecker();
            int barDice = turn == black ? 24 - diceRoll[currentDepth] : diceRoll[currentDepth] - 1;
            if (addMoveToBoard(topChecker, newMove, bar, i, barDice))
            {
                TraverseBoard(possibleMoves, diceRoll, newMove, currentDepth + 1, maxDepth);
            }
            continue;
        }
        if (checkerAndPointColorIsSame(turn, move->getNextBoard(), i))
        {
            Move *newMove = new Move(*move);
            Checker *topChecker = newMove->getNextBoard().getPoint(i).getFrontChecker();
            newMove->getNextBoard().getPoint(i).popChecker();
            if (addMoveToBoard(topChecker, newMove, regular, i, i - diceRoll[currentDepth]))
            {
                TraverseBoard(possibleMoves, diceRoll, newMove, currentDepth + 1, maxDepth);
            }
        }
    }
}

bool Game::addMoveToBoard(Checker *fromChecker, Move *move, MoveType fromType, int from, int to)
{
    switch (canMoveToPoint(move->getNextBoard(), turn, to))
    {
    case regular:
    {
        move->appendMove(from, to, fromType, regular);
        move->getNextBoard().getPoint(to).addChecker(fromChecker);
        return true;
    }
    case off:
    {
        move->appendMove(from, to, fromType, off);
        delete (fromChecker);
        move->getNextBoard().addCheckerToHome(turn);
        return true;
    }
    case hit:
    {
        Checker *hitChecker = move->getNextBoard().getPoint(to).getFrontChecker();
        move->getNextBoard().getPoint(to).popChecker();
        move->getNextBoard().getPoint(to).addChecker(fromChecker);
        CheckerColor oppositeColor = turn == black ? black : white;
        move->getNextBoard().getBar(oppositeColor).addChecker(hitChecker);
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
    this->board = move->getNextBoard();
    history.push_back(move);
    swapTurn();
}
