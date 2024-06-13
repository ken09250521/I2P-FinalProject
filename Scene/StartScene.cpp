//
// Created by Hsuan on 2024/4/10.
//

#include "StartScene.h"
#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "UI/Component/Slider.hpp"
#include "Scene/StartScene.h"

void StartScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton* btn;

    AddNewObject(new Engine::Image("stage-select/startBG.jpeg", halfW, halfH, w, h, 0.5, 0.5));

    AddNewObject(new Engine::Image("stage-select/title.png", halfW, halfH / 3 + 50, 1000, 200, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH - 110, 400, 100);
    btn->SetOnClickCallback(std::bind(&StartScene::StageSelectOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Play", "ferrum.otf", 54, halfW, halfH - 50, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH + 40, 400, 100);
    btn->SetOnClickCallback(std::bind(&StartScene::ShopOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Shop", "ferrum.otf", 54, halfW, halfH + 100 , 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH + 190, 400, 100);
    btn->SetOnClickCallback(std::bind(&StartScene::SettingsOnClick, this, 3));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Settings", "ferrum.otf", 54, halfW, halfH + 250, 0, 0, 0, 255, 0.5, 0.5));


    bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
    
}
void StartScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
void StartScene::StageSelectOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
void StartScene::ShopOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("shop");
}
void StartScene::SettingsOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("settings");
}
