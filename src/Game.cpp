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
    std::vector<int> diceRolls;
    
    for(int i = 0; i < 2;i++){
        diceRolls.push_back(rand() % 6 + 1);
    }

    if(diceRolls[0] == diceRolls[1]){
        for(int i = 0; i < 2;i++){
            diceRolls.push_back(diceRolls[0]);
        }
    }

    int arrSize = 24;

    if (currentPlayer.GetColor() == black)
    {
        for(int i = 0; i < diceRolls.size();i++){
            diceRolls[i] = -diceRolls[i];
        }
    }

    if (currentPlayer.GetCheckersInHomeQuadrant() == 15)
        canOffCheckers = true;

    Move originMove(diceRolls);

    for(int i = 0;i < diceRolls.size();i++){
        GeneratePossiboleMoves(possiboleMoves,originMove,canOffCheckers,diceRolls.size(),i+1);
    }

    return possiboleMoves;
}

void Game::GeneratePossiboleMoves(std::vector<Move> &possiboleMoves,Move currentMove,bool canOffCheckers,int diceAmount,int diceIndex){
    for(int i = 0; i < 24;i++){
        
    }
    
    if(diceIndex == diceAmount){
        possiboleMoves.push_back(currentMove);
    }
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
