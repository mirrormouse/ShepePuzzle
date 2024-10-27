#pragma once
#include "PuzzlePiece.h"
#include "Rectangle.h"
#include "Line.h"
#include <iostream>





PuzzlePiece::PuzzlePiece(Grid* grid, std::vector<std::pair<int, int>> shape, GameMain* gameMain, float(&color)[3], GridPoint center)
    :GameObject(1000, 0), grid(grid), shape(shape), rotationState(0), center(center), gameMain(gameMain)
{
    pieceColor[0] = color[0];
    pieceColor[1] = color[1];
    pieceColor[2] = color[2];
}


void PuzzlePiece::RotateLeft()
{
    int newRotationState = (rotationState + 3) % 4;
    RotateApply(newRotationState);
}

void PuzzlePiece::RotateRight()
{
    int newRotationState = (rotationState + 1) % 4;
    RotateApply(newRotationState);
}

void PuzzlePiece::RotateApply(int newRotationState) {
    std::vector<GridPoint> newPositions = GetRotatedPositions(newRotationState);
    
    std::cout << newRotationState << std::endl;

    if (IsValidMove(newPositions)) {
        rotationState = newRotationState;
    }
}


std::vector<GridPoint> PuzzlePiece::GetRotatedPositions(int rotation)
{
    std::vector<GridPoint> newPositions;
    for (const auto& block : shape) {
        std::pair<int, int> pos = RotatePoint(block, rotation);
        newPositions.push_back(GridPoint{ center.x + pos.first, center.y + pos.second });
    }
    return newPositions;
}

std::vector<GridPoint> PuzzlePiece::GetPositions()
{
    return GetBlockPositions(center);
}

std::vector<GridPoint> PuzzlePiece::GetBlockPositions(GridPoint point)
{
    std::vector<GridPoint> positions;
    for (const auto& block : shape) {
        std::pair<int, int> pos = RotatePoint(block, rotationState);
        positions.push_back(GridPoint{ point.x + pos.first, point.y + pos.second });
    }
    return positions;
}


bool PuzzlePiece::IsValidMove(std::vector<GridPoint> newPositions)
{
    for (const auto& pos : newPositions) {
        if (!grid->isInBounds(pos.x, pos.y)) {
            return false;
        }
    }
    return true;
}
void PuzzlePiece::MoveLeft()
{
    GridPoint newCenter = center;
    newCenter.x--;
    std::vector<GridPoint> newPositions = GetBlockPositions(newCenter);
    if (IsValidMove(newPositions)) {
        center = newCenter;
    }
}

void PuzzlePiece::MoveRight()
{
    GridPoint newCenter = center;
    newCenter.x++;
    std::vector<GridPoint> newPositions = GetBlockPositions(newCenter);
    if (IsValidMove(newPositions)) {
        center = newCenter;
    }
}

void PuzzlePiece::MoveDown()
{
    GridPoint newCenter = center;
    newCenter.y++;
    std::vector<GridPoint> newPositions = GetBlockPositions(newCenter);
    if (IsValidMove(newPositions)) {
        center = newCenter;
    }
}

void PuzzlePiece::MoveUp()
{
    GridPoint newCenter = center;
    newCenter.y--;
    std::vector<GridPoint> newPositions = GetBlockPositions(newCenter);
    if (IsValidMove(newPositions)) {
        center = newCenter;
    }
}

void PuzzlePiece::Start() {

}

void PuzzlePiece::Draw() {


    for (const auto& block : shape) {
        std::pair<int, int> pos = RotatePoint(block, rotationState);
        Point screenPos = grid->gridToScreen(center.x + pos.first, center.y + pos.second);
        Rectangle blockRect = Rectangle(gameMain, screenPos, grid->getCellWidth(), grid->getCellHeight(), pieceColor);
        
        blockRect.Draw();
    }
}

void PuzzlePiece::FixedUpdate() {

}


bool PuzzlePiece::IncludeGrid(GridPoint g) {
    
    std::vector<GridPoint> positions = GetBlockPositions(center);

    for (auto ps : positions) {
        if (ps.x == g.x && ps.y == g.y) {
            return true;
        }
    }
    return false;
}

std::pair<int, int> PuzzlePiece::RotatePoint(std::pair<int, int> p, int rotation) {

    if (rotation == 0) {
        return p;
    }
    if (rotation == 1) {
        return {-p.second, p.first};
    }
    if (rotation == 2) {
        return { -p.first, -p.second };
    }
    if (rotation == 3) {
        return { p.second, -p.first };
    }

}