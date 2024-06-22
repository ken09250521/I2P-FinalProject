#include <string>
#include <vector>

#include "Giant.hpp"

Giant::Giant(int x, int y) : Character({{Engine::AnimationType::leftMove, {"characters/giant/Giant-move1.png", "characters/giant/Giant-move2.png",
                                                "characters/giant/Giant-move3.png", "characters/giant/Giant-move4.png",
                                                "characters/giant/Giant-move5.png"}},
                {Engine::AnimationType::rightMove, {"characters/giant/right/Giant-move1.png", "characters/giant/right/Giant-move2.png",
                                                "characters/giant/right/Giant-move3.png", "characters/giant/right/Giant-move4.png",
                                                "characters/giant/right/Giant-move5.png"}},
                {Engine::AnimationType::leftAttack, {"characters/giant/Giant-attack1.png", "characters/giant/Giant-attack2.png",
                                                  "charactersgiant/Giant-attack3.png", "characters/giant/Giant-attack4.png"}},
                {Engine::AnimationType::rightAttack, {"characters/giant/right/Giant-attack1.png", "characters/giant/right/Giant-attack2.png",
                                                  "characters/giant/right/Giant-attack3.png", "characters/giant/right/Giant-attack4.png"}}},
                x, y, 15, 15, 30, 200, 15, 6, 1) {
    // Additional initialization if necessary
}