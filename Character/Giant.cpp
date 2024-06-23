#include <string>
#include <vector>

#include "Giant.hpp"

Giant::Giant(int x, int y, bool isAlly) : Character("characters/giant/Giant-move1.png", x, y, isAlly, 15, 15, 50, 50, 30, 200, 15, 6) {
    leftMovePaths = {"characters/giant/Giant-move1.png", "characters/giant/Giant-move2.png", "characters/giant/Giant-move3.png", "characters/giant/Giant-move4.png", 
                "characters/giant/Giant-move5.png"};
    rightMovePaths = {"characters/giant/right/Giant-move1.png", "characters/giant/right/Giant-move2.png", "characters/giant/right/Giant-move3.png", "characters/giant/right/Giant-move4.png", 
                "characters/giant/right/Giant-move5.png"};
    leftAtkPaths = {"characters/giant/Giant-atk1.png", "characters/giant/Giant-atk2.png",
                "characters/giant/Giant-atk3.png", "characters/giant/Giant-atk4.png"};
    rightAtkPaths = {"characters/giant/right/Giant-atk1.png", "characters/giant/right/Giant-atk2.png",
                "characters/giant/right/Giant-atk3.png", "characters/giant/right/Giant-atk4.png"};
    LoadImages(leftAtkPaths, rightAtkPaths, leftMovePaths, rightMovePaths);
}