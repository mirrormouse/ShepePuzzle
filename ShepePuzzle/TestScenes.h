#pragma once
#ifndef TEST_SCENES_H
#define TEST_SCENES_H

#include "Scene.h"
#include "Button.h"
#include "TextDisplay.h"
#include "Text.h"
#include "SharedData.h"
#include <memory>
#include <chrono>



class StartScene : public Scene {
public:
    StartScene(GameMain* gameMain);
    void Enter() override;
    void Exit() override;
    void Loop() override;
    void FixedLoop() override;

private:
    std::shared_ptr<Button> startButton;
};



class ResultScene : public Scene {
public:
    ResultScene(GameMain* gameMain);
    void Enter() override;
    void Exit() override;

private:
    std::shared_ptr<SharedData> sharedData;
};

#endif // TEST_SCENES_H