#include "Game.hpp"
#include <iostream>

bool Game::GameEnded()
{
    return (board.GetHomeCheckers(white) == 15 || board.GetHomeCheckers(black) == 15) ? true : false;
}

void Game::NextGameState()
{
    std::vector<int> diceRolls = RollDice();
    Move move(diceRolls, 0);
    do
    {
        GetPossibleMoves(true, diceRolls);
        if (possiboleMoves.empty())
        {
            move.SetNoMove();
            std::cout << "No moves possibole skipping" << std::endl;
            break;
        }
        for (size_t i = 0; i < possiboleMoves.size(); i++)
        {
            std::cout << std::to_string(i + 1) << ": " << possiboleMoves[i].GetFrom()[0] << "/" << possiboleMoves[i].GetTo()[0] << std::endl;
        }

        // Ai make decision
        int moveIndex;
        std::cout << "Type index of move to make: " << std::endl;
        std::cin >> moveIndex;
        //

        move.AppendMove(possiboleMoves[moveIndex - 1].GetFrom()[0], possiboleMoves[moveIndex - 1].GetTo()[0]);
        diceRolls.erase(diceRolls.begin() + possiboleMoves[moveIndex - 1].GetDiceIndexOfMove());
    } while (!diceRolls.empty());

    std::cout << "Final move was " << move.GetMove() << std::endl;
    MakeMove(move);
    SwapTurn();
}

void Game::GetPossibleMoves(bool firstMove, std::vector<int> &diceRolls)
{
    possiboleMoves.clear();
    turn = white;

    bool canOffCheckers = false;

    if (board.GetCheckersInHomeQuadrant(turn) == 15)
        canOffCheckers = true;

    for (size_t i = 0; i < diceRolls.size(); i++)
    {
        for (int j = 0; j < 24; j++)
        {
            if (board.GetBarCheckers(turn) > 0)
            {
                // Force bar checker move
            }

            if (board.GetPoints()[j].GetOccupiedColor() == turn && j - diceRolls[i] >= 0)
            {
                int moveType = board.GetPoints()[j - diceRolls[i]].CanMoveTo(turn);
                if (moveType == 0)
                {
                    Move move(diceRolls, i);
                    move.AppendMove(std::to_string(j + 1), std::to_string(j - diceRolls[i] + 1));
                    possiboleMoves.push_back(move);
                }
                else if (moveType == 1)
                {
                    Move move(diceRolls, i);
                    move.AppendMove(std::to_string(j + 1), std::to_string(j - diceRolls[i] + 1) + "*");
                    possiboleMoves.push_back(move);
                }
            }
            else if (board.GetPoints()[j].GetOccupiedColor() == turn && j - diceRolls[i] < 0 && canOffCheckers)
            {
                Move move(diceRolls, i);
                move.AppendMove(std::to_string(j + 1), "off");
                possiboleMoves.push_back(move);
            }
        }
    }
}

void Game::SwapTurn()
{
    if (turn == white)
    {
        turn = black;
    }
    else
    {
        turn = white;
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

void Game::MakeMove(Move move)
{
    std::vector<std::string> from = move.GetFrom();
    std::vector<std::string> to = move.GetTo();

    for (size_t i = 0; i < from.size(); i++)
    {
        if (from[i] == "bar")
        {
            board.DecreaseBarCheckers(turn);
        }
        else
        {
            board.GetPoints()[std::stoi(from[i])].RemoveCheckerFromPoint();
        }

        if (to[i] == "off")
        {
            board.IncreaseHomeCheckers(turn);
        }
        else if (to[i].back() == '*')
        {
            if (turn == white)
            {
                board.IncreaseBarCheckers(black);
            }
            else
            {
                board.IncreaseBarCheckers(white);
            }
            board.GetPoints()[std::stoi(from[i])].KnockOutPiece(turn);
        }
        else
        {
            board.GetPoints()[std::stoi(to[i])].AddCheckerToPoint();
        }
    }

    history.push_back(move);
    SwapTurn();
}
