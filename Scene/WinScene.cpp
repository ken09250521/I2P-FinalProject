#include <functional>
#include <string>
#include <fstream>
#include <ctime>
#include <iostream>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "WinScene.hpp"
#include "PlayScene.hpp"

extern int finalScore;

void WinScene::Initialize() {
	ticks = 0;
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	
    PlayScene* playScene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    if (playScene != nullptr) {
		ffinalScore = playScene->finalScore;
        AddNewObject(new Engine::Label("Score: " + std::to_string(ffinalScore), "pirulen.ttf", 48, halfW, halfH / 4 - 10, 255, 255, 255, 255, 0.5, 0.5));
    }

	std::ofstream file("Resource/scoreboard.txt", std::ios::app);
	if (!file) {
		std::cout << "Failed to open file for writing. Check if you have write permissions.\n";
	} else {
		std::string data = "Player " + std::to_string(ffinalScore) + " " + getCurrentDate();
		file << data << std::endl;
		if (file.good()) {
			std::cout << "Data written successfully\n";
		} else {
			std::cout << "Failed to write to file\n";
		}
		file.close();
	}
	
	AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH, 0, 0, 0.5, 0.5));
	AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 16, 255, 255, 255, 255, 0.5, 0.5));
	//AddNewObject(new Engine::Label(std::to_string(finalScore), "pirulen.ttf", 48, halfW, halfH / 4 - 10, 255, 255, 255, 255, 0.5, 0.5));
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
	bgmId = AudioHelper::PlayAudio("win.wav");

}
void WinScene::Terminate() {

	IScene::Terminate();
	AudioHelper::StopBGM(bgmId);
}
void WinScene::Update(float deltaTime) {
	ticks += deltaTime;
	if (ticks > 4 && ticks < 100 &&
		dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
		ticks = 100;
		bgmId = AudioHelper::PlayBGM("happy.ogg");
	}


}
void WinScene::BackOnClick(int stage) {
	// Change to select scene.

	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

std::string WinScene::getCurrentDate(){
	std::time_t t = std::time(0);  
    std::tm* now = std::localtime(&t);

    std::string month = std::to_string(now->tm_mon + 1);
    std::string day = std::to_string(now->tm_mday);
	std::string hour = std::to_string(now->tm_hour);
	std::string min = std::to_string(now->tm_min);

    return month + "-" + day + " " + hour + ":" + min;
}