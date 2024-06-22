#include "Scene.hpp"
#include "Engine/GameEngine.hpp"

void TestScene::Initialize() {
    // Initialize your scene here.
    AddNewObject(CharacterGroup = new Group());
    CharacterGroup->AddNewObject(character1 = new Warrior(400, 300));
    CharacterGroup->AddNewObject(character2 = new Warrior(200, 300));
    time = 0.0f;
}

void TestScene::Terminate() {
    // Clean up the scene.
    IScene::Terminate();
}

void TestScene::Update(float deltaTime) {
    // Update the scene.
    time += deltaTime;
    
    // Change animation every 2 seconds for testing.
    if (static_cast<int>(time) % 4 < 4) {
        character1->leftMove();
    } else {
        character1->leftAttack();
    }
    
    // Call the update method of the character.
    character1->Update(deltaTime);
}

void TestScene::Draw() const {
    // Draw the scene.
    IScene::Draw();
}
