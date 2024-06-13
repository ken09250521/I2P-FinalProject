#ifndef BOSSENEMY_HPP
#define BOSSENEMY_HPP
#include "Enemy.hpp"

class BossEnemy : public Enemy {
public:
	BossEnemy(int x, int y);
	float boostRadius;
    float speedBoost;
};
#endif // BOSSENEMY_HPP
