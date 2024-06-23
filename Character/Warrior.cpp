#include <string>
#include <vector>

#include "Warrior.hpp"

Warrior::Warrior(int x, int y, bool isAlly) : Character("characters/warrior/Warrior-move1.png", x, y, isAlly, 15, 15, 50, 50, 50, 100, 10, 2) {

    leftMovePaths = {"characters/warrior/Warrior-move1.png", "characters/warrior/Warrior-move2.png", "characters/warrior/Warrior-move3.png", "characters/warrior/Warrior-move4.png",
                "characters/warrior/Warrior-move5.png", "characters/warrior/Warrior-move6.png"};
    rightMovePaths = {"characters/warrior/right/Warrior-move1.png", "characters/warrior/right/Warrior-move2.png", "characters/warrior/right/Warrior-move3.png", "characters/warrior/right/Warrior-move4.png",
                "characters/warrior/right/Warrior-move5.png", "characters/warrior/right/Warrior-move6.png"};
    leftAtkPaths = {"characters/warrior/Warrior-atk1.png", "characters/warrior/Warrior-atk2.png",
                "characters/warrior/Warrior-atk3.png", "characters/warrior/Warrior-atk4.png"};
    rightAtkPaths = {"characters/warrior/right/Warrior-atk1.png", "characters/warrior/right/Warrior-atk2.png",
                "characters/warrior/right/Warrior-atk3.png", "characters/warrior/right/Warrior-atk4.png"};
    LoadImages(leftAtkPaths, rightAtkPaths, leftMovePaths, rightMovePaths);
}