#include <string>
#include <vector>

#include "Rider.hpp"

Rider::Rider(int x, int y) : Character({{Engine::AnimationType::leftMove, {"characters/rider/Rider-move1.png", "characters/rider/Rider-move2.png",
                                                "characters/rider/Rider-move3.png"}},
                {Engine::AnimationType::rightMove, {"characters/rider/right/Rider-move1.png", "characters/rider/right/Rider-move2.png",
                                                "characters/rider/right/Rider-move3.png"}},
                {Engine::AnimationType::leftAttack, {"characters/rider/Rider-attack1.png", "characters/rider/Rider-attack2.png"}},
                {Engine::AnimationType::rightAttack, {"characters/rider/right/Rider-attack1.png", "characters/rider/right/Rider-attack2.png"}}},
                x, y, 10, 10, 80, 80, 10, 4, 1) {
    // Additional initialization if necessary
}