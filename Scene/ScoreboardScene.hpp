#ifndef ScoreboardScene_HPP
#define ScoreboardScene_HPP

#include <allegro5/allegro_audio.h>
#include <memory>
#include <vector>
#include "Engine/IScene.hpp"

class ScoreboardScene final : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    int currentPage = 0;
    const int scoresPerPage = 10;
    std::vector<Engine::Label*> scoreLabels;
    std::vector<std::pair<std::string, int>> scores;
    std::vector<std::string> times;
    std::vector<Engine::Label*> timeLabels;
    std::vector<std::string> dates;
    std::vector<Engine::Label*> dateLabels;
public:
    explicit ScoreboardScene() = default;

    void Initialize() override;

    void Terminate() override;

    void clearScores();

    void displayScores();

    void BackOnClick(int stage);
    
    void prevPage();

    void nextPage();

};

#endif // ScoreboardScene_HPP
