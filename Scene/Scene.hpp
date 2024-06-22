#ifndef SCENE_HPP
#define SCENE_HPP

#include "Engine/IScene.hpp"
#include "Character/Warrior.hpp"
#include <allegro5/allegro.h>

class TestScene : public Engine::IScene {
private:
    Character* character1;  // Add this line
    Character* character2;  // Add this line
    float time;
public:
    Group* CharacterGroup;
    explicit TestScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void Draw() const override;
};

#endif // SCENE_HPP
