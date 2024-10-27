#include "GameMain.h"
#include "TestScenes.h"
#include "PuzzleScene.h"
#include <iostream>

int main() {
    GameMain game(800, 600, "Scene Transition Test");

    auto startScene = std::make_shared<StartScene>(&game);
    auto puzzleScene = std::make_shared<PuzzleScene>(&game);
    auto resultScene = std::make_shared<ResultScene>(&game);

    game.GetSceneManager().AddScene("Start", startScene);
    game.GetSceneManager().AddScene("Puzzle", puzzleScene);
    game.GetSceneManager().AddScene("Result", resultScene);

    game.GetSceneManager().ChangeScene("Start");

    std::cout << "START" << std::endl;

    game.run(1000);  // FixedLoop‚ð1•bŠÔŠu‚ÅŒÄ‚Ño‚·

    return 0;
}