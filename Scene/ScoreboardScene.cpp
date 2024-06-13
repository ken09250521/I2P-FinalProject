#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "UI/Component/Slider.hpp"
#include "ScoreboardScene.hpp"

void ScoreboardScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    //scoreboard deets
    AddNewObject(new Engine::Label("Scoreboard", "pirulen.ttf", 45, halfW, halfH / 16, 0, 255, 0, 255, 0.5, 0.5));
    //scores
    //clearScores();
    std::ifstream file("Resource/scoreboard.txt");
    // if (scores.empty()){
    //     if (!file){
    //         std::cerr << "Unable to open scoreboard.txt";
    //         exit(1);
    //     }
        
    //     std::string name;
    //     int score;
    //     while (file >> name >> score){
    //         scores.push_back({name, score});
    //     }

    //     for (int i = currentPage * scoresPerPage; i < (currentPage + 1) * scoresPerPage && i < scores.size(); i++){
    //         std::string scoreText = scores[i].first + " " + std::to_string(scores[i].second);
    //         Engine::Label* scoreLabel = new Engine::Label(scoreText, "pirulen.ttf", 40, halfW, halfH / 4 + (i * scoresPerPage) * 50, 0, 255, 0, 125, 0.5, 0.5);
    //         AddNewObject(scoreLabel);
    //         scoreLabels.push_back(scoreLabel);
    //     }
    // }
    if (!file){
        std::cerr << "Unable to open scoreboard.txt";
        exit(1);
    }

    std::string name;
    int score;
    std::string date;
    std::string time;
    while (file >> name >> score >> date >> time){
        scores.push_back({name, score});
        dates.push_back({date});
        times.push_back({time});
    }
    file.close();

    for (int i = currentPage * scoresPerPage; i < (currentPage + 1) * scoresPerPage && i < scores.size(); i++){
        std::string scoreText = scores[i].first + " " + std::to_string(scores[i].second);
        Engine::Label* scoreLabel = new Engine::Label(scoreText, "pirulen.ttf", 40, halfW, halfH / 4 + (i % scoresPerPage) * 50, 0, 255, 0, 125, 0.5, 0.5);
        AddNewObject(scoreLabel);
        scoreLabels.push_back(scoreLabel);
        Engine::Label* dateLabel = new Engine::Label(dates[i], "pirulen.ttf", 40, halfW + 500, halfH / 4 + (i % scoresPerPage) * 50, 0, 255, 0, 125, 0.5, 0.5);
        AddNewObject(dateLabel);
        dateLabels.push_back(dateLabel);
        Engine::Label* timeLabel = new Engine::Label(times[i], "pirulen.ttf", 40, halfW + 650, halfH / 4 + (i % scoresPerPage) * 50, 0, 255, 0, 125, 0.5, 0.5);
        AddNewObject(timeLabel);
        timeLabels.push_back(timeLabel);
    }

    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 700, halfH * 3 / 2, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::prevPage, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Prev Page", "pirulen.ttf", 48, halfW - 500, halfH * 3 / 2 + 50, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2 + 50, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 300, halfH * 3 / 2, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::nextPage, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Next Page", "pirulen.ttf", 48, halfW + 500, halfH * 3 / 2 + 50, 0, 0, 0, 255, 0.5, 0.5));



    // Not safe if release resource while playing, however we only free while change scene, so it's fine.
    if (!bgmInstance) {
        bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
    }

}

void ScoreboardScene::Terminate() {
    if (!scores.empty())
        scores.clear();
    if (!times.empty())
        times.clear();
    if (!scoreLabels.empty() && !timeLabels.empty() && !dateLabels.empty())
       clearScores();
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}

void ScoreboardScene::clearScores() {
    for (Engine::Label* scoreLabel : scoreLabels){
        auto it = scoreLabel->GetObjectIterator();
        RemoveObject(it);
    }
    scoreLabels.clear();
    for (Engine::Label* timeLabel : timeLabels){
        auto it = timeLabel->GetObjectIterator();
        RemoveObject(it);
    }
    timeLabels.clear();
    for (Engine::Label* dateLabel : dateLabels){
        auto it = dateLabel->GetObjectIterator();
        RemoveObject(it);
    }
    dateLabels.clear();
}

void ScoreboardScene::displayScores() {
    int halfW = Engine::GameEngine::GetInstance().GetScreenWidth() / 2;
    int halfH = Engine::GameEngine::GetInstance().GetScreenHeight() / 2;

    for (int i = currentPage * scoresPerPage; i < (currentPage + 1) * scoresPerPage && i < scores.size(); i++){
        std::string scoreText = scores[i].first + " " + std::to_string(scores[i].second);
        Engine::Label* scoreLabel = new Engine::Label(scoreText, "pirulen.ttf", 40, halfW, halfH / 4 + (i % scoresPerPage) * 50, 0, 255, 0, 125, 0.5, 0.5);
        AddNewObject(scoreLabel);
        scoreLabels.push_back(scoreLabel);
        Engine::Label* dateLabel = new Engine::Label(dates[i], "pirulen.ttf", 40, halfW + 500, halfH / 4 + (i % scoresPerPage) * 50, 0, 255, 0, 125, 0.5, 0.5);
        AddNewObject(dateLabel);
        dateLabels.push_back(dateLabel);
        Engine::Label* timeLabel = new Engine::Label(times[i], "pirulen.ttf", 40, halfW + 650, halfH / 4 + (i % scoresPerPage) * 50, 0, 255, 0, 125, 0.5, 0.5);
        AddNewObject(timeLabel);
        timeLabels.push_back(timeLabel);
    }
}

void ScoreboardScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void ScoreboardScene::nextPage() {
    if (!scoreLabels.empty() && !timeLabels.empty())
        clearScores();
    currentPage++;
    displayScores();
}
void ScoreboardScene::prevPage() {
    if (!scoreLabels.empty() && !timeLabels.empty())
        clearScores();
    if (currentPage > 0) {
        currentPage--;
    }

    displayScores();
}