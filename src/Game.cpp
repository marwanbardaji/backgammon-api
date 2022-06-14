#include "Game.hpp"
#include <iostream>

Game::Game()
{
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

Game::~Game()
{
}

bool Game::GameEnded()
{
    return (whitePlayer.GetHomeCheckers() == 15 || blackPlayer.GetHomeCheckers() == 15) ? true : false;
}

std::vector<Move> Game::GetPossibleMoves()
{
    possiboleMoves.clear();
    bool canOffCheckers = false;
    int min = 1;
    int max = 6;

    int firstDice = rand() % (max - min + 1) + min;
    int secondDice = rand() % (max - min + 1) + min;
    int thirdDice = 0;
    int fourthDice = 0;

    int arrSize = 24;

    if (firstDice == secondDice)
    {
        thirdDice = firstDice;
        fourthDice = firstDice;
    }

    if (currentPlayer.GetColor() == black)
    {
        firstDice = -firstDice;
        secondDice = -secondDice;
    }

    if (currentPlayer.GetCheckersInHomeQuadrant() == 15)
        canOffCheckers = true;

    for (int i = 0; i < arrSize; i++)
    {
        if (points[i].GetOccupiedColor() == currentPlayer.GetColor() && i - firstDice >= 0 && points[i - firstDice].CanMoveTo(currentPlayer))
        {
            points[i].RemoveCheckerFromPoint();
            points[i - firstDice].AddCheckerToPoint();
            for (int j = 0; j < arrSize; j++)
            {
                if (points[j].GetOccupiedColor() == currentPlayer.GetColor() && j - secondDice >= 0 && points[j - secondDice].CanMoveTo(currentPlayer))
                {
                    Move move(firstDice, secondDice);
                    move.AppendMove(std::to_string(i + 1), std::to_string(i + 1 - firstDice));
                    move.AppendMove(std::to_string(j + 1), std::to_string(j + 1 - secondDice));
                    possiboleMoves.push_back(move);
                }
                else if (canOffCheckers && j - secondDice < 0)
                {
                    Move move(firstDice, secondDice);
                    move.AppendMove(std::to_string(i + 1), std::to_string(i + 1 - firstDice));
                    move.AppendMove(std::to_string(j + 1), "off");
                    possiboleMoves.push_back(move);
                }
            }
            points[i].AddCheckerToPoint();
            points[i - firstDice].RemoveCheckerFromPoint();
        }
    }

    return possiboleMoves;
}

void Game::MakeMove(int index)
{
    std::vector<std::string> from = possiboleMoves[index].GetFrom();
    std::vector<std::string> to = possiboleMoves[index].GetTo();

    for (int i = 0; i < from.size(); i++)
    {
        if (from[i] == "bar")
        {
            currentPlayer.DecreaseBarCheckers();
        }
        else
        {
            points[std::stoi(from[i])].RemoveCheckerFromPoint();
        }

        if (to[i] == "off")
        {
            currentPlayer.IncreaseHomeCheckers();
        }
        else
        {
            points[std::stoi(to[i])].AddCheckerToPoint();
        }
    }

    history.push_back(possiboleMoves[index]);
}
