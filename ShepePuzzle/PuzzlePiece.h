#pragma once

#include "Grid.h"
#include <memory>
#include <vector>
#include <array>
#include <chrono>



class PuzzlePiece : public GameObject {
public:
    PuzzlePiece(Grid* grid, std::vector<std::pair<int,int>> shape, GameMain* gameMain, float(&color)[3], GridPoint center);
    void FixedUpdate() override;

    void MoveLeft();
    void MoveRight();
    void MoveDown();
    void MoveUp();
    
    void RotateLeft();
    void RotateRight();
    void RotateApply(int newRotationState);
    void Start() override;
    void Draw() override;

    bool IncludeGrid(GridPoint g);//ÉsÅ[ÉXì‡ïîîªíË
    std::vector<GridPoint> GetPositions();


private:
    Grid* grid;
    std::vector<std::pair<int, int>> shape;
    GameMain* gameMain;
    GridPoint center;
    int rotationState;
    float pieceColor[3];

    
    std::vector<GridPoint> GetBlockPositions(GridPoint point);
    std::vector<GridPoint> GetRotatedPositions(int rotation);

    bool IsValidMove(std::vector<GridPoint> newPositions);

    std::pair<int, int> RotatePoint(std::pair<int, int> p, int rotation);

    

};