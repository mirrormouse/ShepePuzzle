#ifndef PUZZLE_SCENE_H
#define PUZZLE_SCENE_H

#include "Scene.h"
#include "Button.h"
#include "TextDisplay.h"
#include "Text.h"
#include "PuzzlePiece.h"
#include "SharedData.h"
#include <memory>
#include <chrono>


class PuzzleScene : public Scene {
public:
    PuzzleScene(GameMain* gameMain);
    void Enter() override;
    
    void Exit() override;
    void Loop() override;
    void FixedLoop() override;
    void DrawLayer();
    void HandleClick();
    void HandleInput();
    void ReorderPieces();


private:
    std::unique_ptr<Grid>grid;
    int selectedPieceId;
    bool selected=false;
    std::vector<std::shared_ptr<PuzzlePiece>> allPieces;

    int clearwait = 0;
    bool clear = false;

    void SetUpCource();
    bool JudgeComplete();
    void InitState();

    std::shared_ptr<SharedData> sharedData;

};






#endif // PUZZLE_SCENE