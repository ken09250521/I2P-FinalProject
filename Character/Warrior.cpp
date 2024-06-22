#include <string>
#include <vector>

#include "Warrior.hpp"

Warrior::Warrior(int x, int y) : Character({{Engine::AnimationType::leftMove, {"characters/warrior/Warrior-move1.png", "characters/warrior/Warrior-move2.png",
                                                "characters/warrior/Warrior-move3.png", "characters/warrior/Warrior-move4.png",
                                                "characters/warrior/Warrior-move5.png", "characters/warrior/Warrior-move6.png"}},
                {Engine::AnimationType::rightMove, {"characters/warrior/right/Warrior-move1.png", "characters/warrior/right/Warrior-move2.png",
                                                "characters/warrior/right/Warrior-move3.png", "characters/warrior/right/Warrior-move4.png",
                                                "characters/warrior/right/Warrior-move5.png", "characters/warrior/right/Warrior-move6.png"}},
                {Engine::AnimationType::leftAttack, {"characters/warrior/Warrior-attack1.png", "characters/warrior/Warrior-attack2.png",
                                                  "characters/warrior/Warrior-attack3.png", "characters/warrior/Warrior-attack4.png"}},
                {Engine::AnimationType::rightAttack, {"characters/warrior/right/Warrior-attack1.png", "characters/warrior/right/Warrior-attack2.png",
                                                  "characters/warrior/right/Warrior-attack3.png", "characters/warrior/right/Warrior-attack4.png"}}},
                x, y, 10, 10, 50, 100, 10, 2, 1) {
    // Additional initialization if necessary
}