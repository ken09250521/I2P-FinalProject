#include <string>
#include <vector>

#include "Rider.hpp"

Rider::Rider(int x, int y, bool isAlly) : Character("characters/rider/Rider-move1.png",x, y, isAlly, 15, 15, 50, 50, 80, 80, 10, 4) {
    leftMovePaths = {"characters/rider/Rider-move1.png", "characters/rider/Rider-move2.png", "characters/rider/Rider-move3.png"};
    rightMovePaths = {"characters/rider/right/Rider-move1.png", "characters/rider/right/Rider-move2.png", "characters/rider/right/Rider-move3.png"};
    leftAtkPaths = {"characters/rider/Rider-atk1.png", "characters/rider/Rider-atk2.png"};
    rightAtkPaths = {"characters/rider/right/Rider-atk1.png", "characters/rider/right/Rider-atk2.png"};
    LoadImages(leftAtkPaths, rightAtkPaths, leftMovePaths, rightMovePaths);
}