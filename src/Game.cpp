#include "../headers/Game.hpp"

bool Game::GameEnded()
{
    return board.getHome(white) == 15 || board.getHome(black) == 15 ? true : false;
}

void Game::NextGameState()
{
    std::vector<Move> *possibleMoves = GetPossibleMoves(&RollDice());

    SwapTurn();
}

std::vector<Move> *Game::GetPossibleMoves(std::vector<int> *diceRoll)
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 24; i++)
        {
            if (board.getPoint(i).getOccupiedColor() == turn)
            {
            }
        }
    }
}

void Game::SwapTurn()
{
}

std::vector<int> Game::RollDice()
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

void Game::MakeMove(Move move)
{
    std::vector<int> from = move.GetFrom();
    std::vector<int> to = move.GetTo();

    for (size_t i = 0; i < from.size(); i++)
    {
        Checker *fromChecker = board.getPoint(from[i]).popChecker();
        board.getPoint(from[i]).addChecker(fromChecker);
    }

    history.push_back(move);
    SwapTurn();
}
