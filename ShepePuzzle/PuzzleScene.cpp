#include "PuzzleScene.h"
#include "GameMain.h"
#include "Rectangle.h"
#include "Line.h"
#include "Grid.h"
#include "PuzzlePiece.h"
#include "Text.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

PuzzleScene::PuzzleScene(GameMain* gameMain) : Scene(gameMain) {

    grid = std::make_unique<Grid>(16, 16, 30, 30, Point{ 60, 60 });

    sharedData = SharedData::getInstance();

}


void PuzzleScene::SetUpCource() {

    std::vector<std::pair<int, int>> shape1 = {
         {-1,0}, {0,0}, {1,0}, {2,0}, {0,-1} };
    float color1[3] = { 1.0f,0.0f,0.0f };
    std::shared_ptr<PuzzlePiece> piece1 = std::make_shared<PuzzlePiece>(grid.get(), shape1, gameMain, color1, GridPoint{ 12,3 });
    this->AddGameObject(piece1);

    std::vector<std::pair<int, int>> shape2 = {
         {-1,-1}, {0,-1}, {0,0}, {0,1} };
    float color2[3] = { 0.0f,1.0f,0.0f };
    std::shared_ptr<PuzzlePiece> piece2 = std::make_shared<PuzzlePiece>(grid.get(), shape2, gameMain, color2, GridPoint{ 12,6 });
    this->AddGameObject(piece2);

    std::vector<std::pair<int, int>> shape3 = {
         {0,-1}, {0,0}, {0,1}, {1,-1} };
    float color3[3] = { 0.0f,0.0f,1.0f };
    std::shared_ptr<PuzzlePiece> piece3 = std::make_shared<PuzzlePiece>(grid.get(), shape3, gameMain, color3, GridPoint{ 12,11 });
    this->AddGameObject(piece3);

    std::vector<std::pair<int, int>> shape4 = {
         {0,0}, {1,0}, {0,1} };
    float color4[3] = { 0.0f,1.0f,1.0f };
    std::shared_ptr<PuzzlePiece> piece4 = std::make_shared<PuzzlePiece>(grid.get(), shape4, gameMain, color4, GridPoint{ 7,12 });
    this->AddGameObject(piece4);

    std::vector<std::pair<int, int>> shape5 = {
         {0,0}, {1,0}, {1,-1}, {-1,0}, {-1,-1} };
    float color5[3] = { 1.0f,0.0f,1.0f };
    std::shared_ptr<PuzzlePiece> piece5 = std::make_shared<PuzzlePiece>(grid.get(), shape5, gameMain, color5, GridPoint{ 3,12 });
    this->AddGameObject(piece5);





    allPieces = { piece1, piece2, piece3, piece4, piece5 };
    int cnt = allPieces.size();
    for (int i = 0; i < cnt; i++) {
        allPieces.at(i)->SetDrawOrder(i);
    }



}


void PuzzleScene::InitState() {

    std::vector<std::vector<int>> initialOccupiedState(grid->getHeight(), std::vector<int>(grid->getWidth(), 0));

    for (int x = 0; x < grid->getWidth(); x++) {
        for (int y = 0; y < grid->getHeight(); y++) {
            if ((0 <= x && x <= 6) && (y == 0 || y == 6)) {
                initialOccupiedState[y][x] = 1;//壁
            }
            if ((0 <= y && y <= 6) && (x == 0 || x == 6)) {
                initialOccupiedState[y][x] = 1;//壁
            }
            if (6 < y || 6 < x) {
                initialOccupiedState[y][x] = 2;//外側
            }
        }
    }

    initialOccupiedState[1][4] = 1;
    initialOccupiedState[1][5] = 1;
    initialOccupiedState[4][4] = 1;
    initialOccupiedState[5][4] = 1;

    grid->addStateLayer("occupied", initialOccupiedState);
}



void PuzzleScene::Enter() {



    InitState();


    float linelight = 0.4f;
    float linecolor[3] = { linelight, linelight, linelight };
    for (int i = 0; i < grid->getWidth() + 1; i++) {
        std::shared_ptr<Line> line = grid->getLine(gameMain, GridPoint{ i,0 }, GridPoint{ i,grid->getHeight() }, linecolor, 1.0f);
        this->AddGameObject(line);
    }
    for (int i = 0; i < grid->getHeight() + 1; i++) {
        std::shared_ptr<Line> line = grid->getLine(gameMain, GridPoint{ 0,i }, GridPoint{ grid->getWidth(),i }, linecolor, 1.0f);
        this->AddGameObject(line);
    }

    SetUpCource();


 


}

void PuzzleScene::Loop() {

    HandleClick();
    HandleInput();
    DrawLayer();





}

void PuzzleScene::FixedLoop() {

    


    if (clearwait > 0) {
        gameMain->GetSceneManager().ChangeScene("Result");
    }

    if (clear) {
        clearwait++;
    }
    else {
        sharedData->countUp();
    }


}

void PuzzleScene::Exit() {}



void PuzzleScene::DrawLayer() {

    for (int x = 0; x < grid->getWidth(); ++x) {
        for (int y = 0; y < grid->getHeight(); ++y) {
            int state = (grid->getState("occupied", x, y));
            Point screenPos = grid->gridToScreen(x, y);
            if (state == 1) {
                float color[3] = {1.0f,1.0f,1.0f};
                Rectangle blockRect = Rectangle(gameMain, screenPos, grid->getCellWidth(), grid->getCellHeight(), color);
                blockRect.Draw();
            }
            if (state == 2) {
                float color[3] = { 0.1f,0.1f,0.1f };
                Rectangle blockRect = Rectangle(gameMain, screenPos, grid->getCellWidth(), grid->getCellHeight(), color);
                blockRect.Draw();
            }
        }
    }
}

void PuzzleScene::ReorderPieces() {

    // 描画処理は描画順でソートしてから実行
    struct DrawOrderCompare {
        bool operator()(const std::shared_ptr<PuzzlePiece>& a, const std::shared_ptr<PuzzlePiece>& b) const {
            return a->GetDrawOrder() < b->GetDrawOrder();
        }
    };
    // 一時的なベクターを作成してソート
    std::vector<std::shared_ptr<PuzzlePiece>> sortedPieces = allPieces;
    std::sort(sortedPieces.begin(), sortedPieces.end(), DrawOrderCompare());
    int cnt = sortedPieces.size();
    for (int i = 0; i < cnt; i++) {
        sortedPieces.at(i)->SetDrawOrder(i);
    }

}


void PuzzleScene::HandleClick() {

    std::vector<GridPoint> clickedGrids = grid->getPressedGrid(gameMain, true);
    if (clickedGrids.size() == 0) return;
    GridPoint clickedGrid = clickedGrids.at(0);//1つ目のみ採用

    int clickedIdx = -1;
    int candidateOrder = -1;
    int cnt = allPieces.size();
    for (int i = 0; i < cnt; i++) {
        auto ps = allPieces.at(i);
        if (ps->IncludeGrid(clickedGrid)) {
            if (candidateOrder < ps->GetDrawOrder()) {
                clickedIdx = i;//描画順が最も大きいものを採用する
                candidateOrder = ps->GetDrawOrder();
            }
        }
    }


    if (clickedIdx >= 0) {
        selectedPieceId = clickedIdx;
        selected = true;
        
        allPieces.at(selectedPieceId)->SetDrawOrder(cnt + 1);

        //std::cout << selectedPieceId << std::endl;
        //std::cout << "order" << allPieces.at(selectedPieceId)->GetDrawOrder() << std::endl;
    }

    ReorderPieces();

    for (int i = 0; i < cnt; i++) {
        //std::cout << i << ":" << allPieces.at(i)->GetDrawOrder() << std::endl;
    }


}

void PuzzleScene::HandleInput() {

    std::vector<int> keys = gameMain->getKeyInput();
    if (!selected) return;
    if (clear) return;

    std::shared_ptr<PuzzlePiece> currentPiece = allPieces.at(selectedPieceId);

    bool moved = false;
    if (currentPiece) {
        for (int key : keys) {
            //std::cout << key << std::endl;
            switch (key) {
            case GLFW_KEY_LEFT:
                currentPiece->MoveLeft();
                moved = true;
                break;
            case GLFW_KEY_RIGHT:
                currentPiece->MoveRight();
                moved = true;
                break;
            case GLFW_KEY_DOWN:
            case GLFW_KEY_S:
                currentPiece->MoveDown();
                moved = true;
                break;
            case GLFW_KEY_UP:
            case GLFW_KEY_W:
                currentPiece->MoveUp();
                moved = true;
                break;
            case GLFW_KEY_A:
                currentPiece->RotateLeft();
                moved = true;
                break;
            case GLFW_KEY_D:
                currentPiece->RotateRight();
                moved = true;
                break;
            }
        }
    }

    if (moved) {
        if (JudgeComplete()) {
            clear = true;
        }
    }

}

bool PuzzleScene::JudgeComplete(){

    //状態を元に戻す
    InitState();

    //ピースが存在する部分について値を追加
    for (auto piece : allPieces) {
        std::vector<GridPoint> positions = piece->GetPositions();
        for (auto pos : positions) {
            grid->updateState("occupied", pos, 3);
        }
    }

    //埋まっていない部分があるか判定
    for (int x = 0; x < grid->getWidth(); x++) {
        for (int y = 0; y < grid->getHeight(); y++) {
            if (grid->getState("occupied", GridPoint{ x,y }) == 0) {
                return false;
            }
        }
    }
    return true;

}

