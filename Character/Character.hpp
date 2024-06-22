#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include "Engine/Point.hpp"

#include "Engine/Sprite.hpp"

class Bullet;
class TestScene;
class Turret;

class Character : public Engine::Sprite {
protected:
 	std::vector<Engine::Point> path;
	float speed;
	float hp;
	float attack;
	int money;
	float AttackRadius = 0;
	TestScene* getPlayScene();
	//virtual void OnExplode();
public:
	float reachEndTime;
	std::list<Turret*> lockedTurrets;
	std::list<Bullet*> lockedBullets;
	Character(std::unordered_map<Engine::AnimationType, std::vector<std::string>> imgPaths, float x, float y, float Collradius, float Atkradius, float speed, float hp, float attack, int money, float frameDuration);
 	//void Hit(float damage);
	//void UpdatePath(const std::vector<std::vector<int>>& mapDistance);
	//void Update(float deltaTime) override;
	void Draw() const override;
	void leftMove();
	void leftAttack();
	void rightMove();
	void rightAttack();
};
#endif // CHARACTER_HPP
