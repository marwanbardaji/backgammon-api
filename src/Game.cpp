#include "Game.hpp"
#include <iostream>

bool Game::GameEnded()
{
    return (board.GetHomeCheckers(white) == 15 || board.GetHomeCheckers(black) == 15) ? true : false;
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
            turn = white;
            break;
        }
        else if (diceRolls[1] > diceRolls[0])
        {
            turn = black;
            break;
        }
        else
        {
            diceRolls = RollDice();
        }
    }

    if (turn == black)
    {
        for (size_t i = 0; i < diceRolls.size(); i++)
        {
            diceRolls[i] = -diceRolls[i];
        }
    }

    if (board.GetCheckersInHomeQuadrant(turn) == 15)
        canOffCheckers = true;

    Move originMove(diceRolls);

    GeneratePossiboleMoves(possiboleMoves, originMove, board, canOffCheckers, diceRolls, 0);

    for (int i = 0; i < 24; i++)
    {
        std::cout << std::to_string(i + 1) << " : " << board.GetPoints()[i].GetCheckerAmount() << std::endl;
    }

    return possiboleMoves;
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

void Game::GeneratePossiboleMoves(std::vector<Move> &possiboleMoves, Move move,Board tempBoard, bool canOffCheckers, std::vector<int> &diceRolls, int diceIndex)
{
    if (diceIndex == static_cast<int>(diceRolls.size()))
    {
        possiboleMoves.push_back(move);
        return;
    }

    for (int i = 0; i < 24; i++)
    {
        if (tempBoard.GetPoints()[i].GetOccupiedColor() == turn)
        {
            if (i - diceRolls[diceIndex] >= 0 && tempBoard.GetPoints()[i - diceRolls[diceIndex]].CanMoveTo(turn) == 0)
            {
                Move copyMove = move;
                copyMove.AppendMove(std::to_string(i + 1), std::to_string(i - diceRolls[diceIndex] + 1));
                Board copyBoard = board;
                copyBoard.GetPoints()[i].RemoveCheckerFromPoint();
                copyBoard.GetPoints()[i-diceRolls[diceIndex]].AddCheckerToPoint();
                GeneratePossiboleMoves(possiboleMoves, copyMove, copyBoard, canOffCheckers, diceRolls, diceIndex + 1);
            }
            else if (i - diceRolls[diceIndex] >= 0 && tempBoard.GetPoints()[i - diceRolls[diceIndex]].CanMoveTo(turn) == 1)
            {
                Move copyMove = move;
                copyMove.AppendMove(std::to_string(i + 1), std::to_string(i - diceRolls[diceIndex] + 1) + "*");
                Board copyBoard;
                copyBoard.GetPoints()[i].RemoveCheckerFromPoint();
                copyBoard.GetPoints()[i-diceRolls[diceIndex]].KnockOutPiece(turn);
                if(turn == white){
                    copyBoard.IncreaseBarCheckers(black);
                }
                else{
                    copyBoard.IncreaseBarCheckers(white);
                }
                GeneratePossiboleMoves(possiboleMoves, copyMove, copyBoard, canOffCheckers, diceRolls, diceIndex + 1);
            }
            else if(canOffCheckers && i - diceRolls[diceIndex] < 0){
                Move copyMove = move;
                copyMove.AppendMove(std::to_string(i + 1), "off");
                GeneratePossiboleMoves(possiboleMoves, copyMove, board, canOffCheckers, diceRolls, diceIndex + 1);
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

    history.push_back(possiboleMoves[index]);
    SwapTurn();
}
