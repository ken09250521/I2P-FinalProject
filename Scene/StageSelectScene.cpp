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
#include "StageSelectScene.hpp"
#include "PlayScene.hpp"
#include "Manage.hpp"

void StageSelectScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton* btn;

    int _curWonStage = Manage::getInstance().getCurWonStage();

    AddNewObject(new Engine::Image("stage-select/startBG.jpeg", halfW, halfH, w, h, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 300, halfH / 2 - 50, 100, 100, 0.5);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("1", "ferrum.otf", 48, halfW - 285, halfH / 2 + 10, 0, 0, 0, 255, 0.5, 0.5));
    if (_curWonStage >= 1){
        btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 150, halfH / 2 - 50, 100, 100, 0.5);
        btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 2));
        AddNewControlObject(btn);
        AddNewObject(new Engine::Label("2", "ferrum.otf", 48, halfW - 135, halfH / 2 + 10, 0, 0, 0, 255, 0.5, 0.5));
        if (_curWonStage >= 2){
            btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW, halfH / 2 - 50, 100, 100, 0.5);
            btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 3));
            AddNewControlObject(btn);
            AddNewObject(new Engine::Label("3", "ferrum.otf", 48, halfW + 15, halfH / 2 + 10, 0, 0, 0, 255, 0.5, 0.5));
           if (_curWonStage >= 3){
                btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 150, halfH / 2 - 50, 100, 100, 0.5);
                btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 4));
                AddNewControlObject(btn);
                AddNewObject(new Engine::Label("4", "ferrum.otf", 48, halfW + 165, halfH / 2 + 10, 0, 0, 0, 255, 0.5, 0.5));
                if (_curWonStage >= 4){
                    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 300, halfH / 2 - 50, 100, 100, 0.5);
                    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 5));
                    AddNewControlObject(btn);
                    AddNewObject(new Engine::Label("5", "ferrum.otf", 48, halfW + 315, halfH / 2 + 10, 0, 0, 0, 255, 0.5, 0.5));
                }
            }
        }
    }
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "ferrum.otf", 48, halfW, halfH * 3 / 2 + 10, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH / 2 + 250, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::ScoreboardOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Scoreboard", "ferrum.otf", 48, halfW, halfH / 2 + 310, 0, 0, 0, 255, 0.5, 0.5));

    // Not safe if release resource while playing, however we only free while change scene, so it's fine.
	if (!bgmInstance) {
       bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
    }
}
void StageSelectScene::Terminate() {
	AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}
void StageSelectScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("start");
}
void StageSelectScene::PlayOnClick(int stage) {
    PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("test"));
    scene->MapId = stage;
    Engine::GameEngine::GetInstance().ChangeScene("test");
}
void StageSelectScene::ScoreboardOnClick() {
    Engine::GameEngine::GetInstance().ChangeScene("scoreboard");
}