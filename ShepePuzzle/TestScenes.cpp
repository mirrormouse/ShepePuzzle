#include "TestScenes.h"
#include "GameMain.h"
#include "Rectangle.h"
#include "Grid.h"
#include "Text.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

StartScene::StartScene(GameMain* gameMain) : Scene(gameMain) {}

void StartScene::Enter() {



    startButton = std::make_shared<Button>(gameMain, 0, 0, 200, 200, "Start", gameMain->getFace());
    startButton->SetTextCenterByTextSize(20, 40);
    startButton->SetOnClickHandler([this]() {
        gameMain->GetSceneManager().ChangeScene("Puzzle");
        });
    std::cout << startButton << std::endl;
    AddGameObject(startButton);


}

void StartScene::Loop() {
}

void StartScene::FixedLoop() {
}

void StartScene::Exit() {}


ResultScene::ResultScene(GameMain* gameMain) : Scene(gameMain) {
    sharedData = SharedData::getInstance();
}

void ResultScene::Enter() {
    std::stringstream ss;
    ss << "GameClear!   time:" << sharedData->getValue() << "s";
    auto text = std::make_shared<Text>(gameMain, ss.str(), 100, 100, gameMain->getFace());
    text->SetColor(1.0f, 1.0f, 1.0f);
    AddGameObject(text);
}

void ResultScene::Exit() {}