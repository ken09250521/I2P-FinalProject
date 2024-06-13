#include <string>

#include "BossEnemy.hpp"

BossEnemy::BossEnemy(int x, int y) : Enemy("play/enemy-6.png", x, y, 40, 20, 1000, 200){
    boostRadius = 100;
    speedBoost = 1.10;
}

