#include "Game.hpp"
#include <iostream>

Game::Game()
{
    for (int i = 0; i < 24; i++)
    {
        Point point;
        points.push_back(point);
    }

    whitePlayer.SetColor(white);
    blackPlayer.SetColor(black);

    points[0].SetOccupiedColor(blackPlayer);
    points[23].SetOccupiedColor(whitePlayer);
    points[16].SetOccupiedColor(blackPlayer);
    points[7].SetOccupiedColor(whitePlayer);
    points[18].SetOccupiedColor(blackPlayer);
    points[5].SetOccupiedColor(whitePlayer);
    points[11].SetOccupiedColor(blackPlayer);
    points[12].SetOccupiedColor(whitePlayer);

    for (int i = 0; i < 2; i++)
    {
        points[0].AddCheckerToPoint();
        points[23].AddCheckerToPoint();
    }

    for (int i = 0; i < 3; i++)
    {
        points[17].AddCheckerToPoint();
        points[8].AddCheckerToPoint();
    }

    for (int i = 0; i < 5; i++)
    {
        points[19].AddCheckerToPoint();
        points[6].AddCheckerToPoint();
        points[12].AddCheckerToPoint();
        points[13].AddCheckerToPoint();
    }
}

bool Game::GameEnded()
{
    return (whitePlayer.GetHomeCheckers() == 15 || blackPlayer.GetHomeCheckers() == 15) ? true : false;
}

std::vector<Move> Game::GetPossibleMoves(bool firstMove)
{
    possiboleMoves.clear();
    bool canOffCheckers = false;
    std::vector<int> diceRolls = RollDice();

    while (firstMove)
    {
        if (diceRolls[0] > diceRolls[1])
        {
            currentPlayer = &whitePlayer;
            break;
        }
        else if (diceRolls[1] > diceRolls[0])
        {
            currentPlayer = &blackPlayer;
            break;
        }
        else
        {
            diceRolls = RollDice();
        }
    }

    if (currentPlayer->GetColor() == black)
    {
        for (size_t i = 0; i < diceRolls.size(); i++)
        {
            diceRolls[i] = -diceRolls[i];
        }
    }

    if (currentPlayer->GetCheckersInHomeQuadrant() == 15)
        canOffCheckers = true;

    Move originMove(diceRolls);

    std::cout << "STARTING PLAYER IS " << currentPlayer->GetColor() << std::endl;

    GeneratePossiboleMoves(possiboleMoves, originMove, points, canOffCheckers, diceRolls, 0);

    for (int i = 0; i < 24; i++)
    {
        std::cout << std::to_string(i + 1) << " : " << points[i].GetCheckerAmount() << std::endl;
    }

    return possiboleMoves;
}

void Game::SwapTurn()
{
    if (currentPlayer->GetColor() == white)
    {
        currentPlayer = &blackPlayer;
    }
    else
    {
        currentPlayer = &whitePlayer;
    }
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

void Game::GeneratePossiboleMoves(std::vector<Move> &possiboleMoves, Move move, std::vector<Point> board, bool canOffCheckers, std::vector<int> &diceRolls, int diceIndex)
{
    if (diceIndex == static_cast<int>(diceRolls.size()))
    {
        possiboleMoves.push_back(move);
        return;
    }

    for (int i = 0; i < 24; i++)
    {
        if (board[i].GetOccupiedColor() == currentPlayer->GetColor())
        {
            if (i - diceRolls[diceIndex] >= 0 && board[i - diceRolls[diceIndex]].CanMoveTo(*currentPlayer) == 0)
            {
                move.AppendMove(std::to_string(i + 1), std::to_string(i - diceRolls[diceIndex] + 1));
                // std::cout << "Current move " << move.GetMove() << " Current index " << diceIndex << std::endl;
                board[i].RemoveCheckerFromPoint();
                board[i - diceRolls[diceIndex]].RemoveCheckerFromPoint();
                GeneratePossiboleMoves(possiboleMoves, move, board, canOffCheckers, diceRolls, diceIndex + 1);
            }
            else if (i - diceRolls[diceIndex] >= 0 && board[i - diceRolls[diceIndex]].CanMoveTo(*currentPlayer) == 1)
            {
                move.AppendMove(std::to_string(i + 1), std::to_string(i - diceRolls[diceIndex] + 1) + "*");
                // std::cout << "Current move " << move.GetMove() << " Current index " << diceIndex << std::endl;
                board[i].RemoveCheckerFromPoint();
                board[i - diceRolls[diceIndex]].RemoveCheckerFromPoint();
                GeneratePossiboleMoves(possiboleMoves, move, board, canOffCheckers, diceRolls, diceIndex + 1);
            }
        }
    }
}

void Game::MakeMove(int index)
{
    std::vector<std::string> from = possiboleMoves[index].GetFrom();
    std::vector<std::string> to = possiboleMoves[index].GetTo();

    for (size_t i = 0; i < from.size(); i++)
    {
        if (from[i] == "bar")
        {
            currentPlayer->DecreaseBarCheckers();
        }
        else
        {
            points[std::stoi(from[i])].RemoveCheckerFromPoint();
        }

        if (to[i] == "off")
        {
            currentPlayer->IncreaseHomeCheckers();
        }
        else if (to[i].back() == '*')
        {
            if (currentPlayer->GetColor() == white)
            {
                blackPlayer.IncreaseBarCheckers();
            }
            else
            {
                whitePlayer.IncreaseBarCheckers();
            }
            points[std::stoi(from[i])].KnockOutPiece(*currentPlayer);
        }
        else
        {
            points[std::stoi(to[i])].AddCheckerToPoint();
        }
    }

    history.push_back(possiboleMoves[index]);
    SwapTurn();
}
