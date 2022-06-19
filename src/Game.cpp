#include "../headers/Game.hpp"

bool Game::gameEnded()
{
    return this->board.getHome(white) == 15 || this->board.getHome(black) == 15 ? true : false;
}

void Game::nextGameState()
{
    std::vector<Move> *possibleMoves = getPossibleMoves(rollDice());
}

std::vector<Move> *Game::getPossibleMoves(std::vector<int> diceRoll)
{
}

MoveType Game::canMoveToPoint(Checker *checker, bool canOffCheckers, int pointIndex)
{
    if (canOffCheckers && ((pointIndex > 23 && checker->getColor() == white) || (pointIndex < 0 && checker->getColor() == black)))
        return off;

    if (board.getPoint(pointIndex).getOccupiedColor() == notOccupied || checkerAndPointColorIsSame(checker->getColor(), board.getPoint(pointIndex).getOccupiedColor()))
        return regular;

    if (board.getPoint(pointIndex).getCheckerAmount() < 2)
        return hit;

    return illegal;
}

bool Game::checkerAndPointColorIsSame(CheckerColor color, int pointIndex)
{
    return (color == black && board.getPoint(pointIndex).getOccupiedColor() == blackOccupied) ||
           (color == white && board.getPoint(pointIndex).getOccupiedColor() == whiteOccupied);
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

    for (size_t i = 0; i < from.size(); i++)
    {
        Checker *fromChecker = board.getPoint(from[i]).popChecker();
        board.getPoint(from[i]).addChecker(fromChecker);
    }

    history.push_back(move);
    swapTurn();
}
