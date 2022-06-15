#include "Board.hpp"

Board::Board()
{
    for (int i = 0; i < 24; i++)
    {
        Point point;
        points.push_back(point);
    }

    points[0].SetOccupiedColor(black);
    points[23].SetOccupiedColor(white);
    points[16].SetOccupiedColor(black);
    points[7].SetOccupiedColor(white);
    points[18].SetOccupiedColor(black);
    points[5].SetOccupiedColor(white);
    points[11].SetOccupiedColor(black);
    points[12].SetOccupiedColor(white);

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

    whiteBarCheckers = 0;
    blackBarCheckers = 0;
    whiteHomeCheckers = 0;
    blackHomeCheckers = 0;
    whiteCheckersInHomeQuadrant = 2;
    blackCheckersInHomeQuadrant = 2;
}

Board::Board(const Board &board)
{
    blackHomeCheckers = board.blackHomeCheckers;
    whiteHomeCheckers = board.whiteHomeCheckers;
    blackBarCheckers = board.blackBarCheckers;
    whiteBarCheckers = board.whiteBarCheckers;
    blackCheckersInHomeQuadrant = board.blackCheckersInHomeQuadrant;
    whiteCheckersInHomeQuadrant = board.whiteCheckersInHomeQuadrant;

    points = board.points;
}

void Board::IncreaseHomeCheckers(Player color)
{
    if(color == white){
        whiteHomeCheckers++;
    }
    else{
        blackHomeCheckers++;
    }
}

void Board::IncreaseBarCheckers(Player color)
{
    if(color == white){
        whiteBarCheckers++;
    }
    else{
        blackBarCheckers++;
    }
}

void Board::IncreaseCheckersInHomeQuadrant(Player color)
{
    if(color == white){
        whiteCheckersInHomeQuadrant++;
    }
    else{
        blackCheckersInHomeQuadrant++;
    }
}

void Board::DecreaseBarCheckers(Player color)
{
    if(color == white){
        whiteHomeCheckers--;
    }
    else{
        blackHomeCheckers--;
    }
}

void Board::DecreaseCheckersInHomeQuadrant(Player color)
{
    if(color == white){
        whiteCheckersInHomeQuadrant--;
    }
    else{
        blackCheckersInHomeQuadrant--;
    }
}

int Board::GetHomeCheckers(Player color)
{
    if(color == white){
        return whiteHomeCheckers;
    }
    else{
        return blackHomeCheckers;
    }
}

int Board::GetBarCheckers(Player color)
{
    if(color == white){
        return whiteBarCheckers;;
    }
    else{
        return blackBarCheckers;
    }
}

int Board::GetCheckersInHomeQuadrant(Player color)
{
    if(color == white){
        return whiteCheckersInHomeQuadrant;
    }
    else{
        return blackCheckersInHomeQuadrant;
    }
}

std::vector<Point> Board::GetPoints(){
    return points;
}