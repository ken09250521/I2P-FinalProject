#ifndef SLIME_HPP
#define SLIME_HPP
#include "Turret.hpp"

class Slime: public Turret {
public:
	static const int Price;
    Slime(float x, float y);
    void Update(float deltaTime) override;
};

#endif //SLIME_HPP