#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include <list>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include "Engine/Point.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Sprite.hpp"

class Bullet;
class TestScene;
class Turret;

class Character : public Engine::Sprite {
public:
	enum State {
		Walk,
		Attack
	};
protected:
 	std::vector<Engine::Point> path;
	float speed;
	float hp;
	float attack;
	int money;
	PlayScene* getPlayScene();
	//virtual void OnExplode();

private:
	State curState;
public:
	bool Ally;
	float curTicks;
	float animationSpan = 1.5f;
	float AttackRadius;
	std::list<Turret*> lockedTurrets;
	std::list<Bullet*> lockedBullets;
	std::vector<std::shared_ptr<ALLEGRO_BITMAP>> leftAtkBmps;
	std::vector<std::shared_ptr<ALLEGRO_BITMAP>> leftMoveBmps;
	std::vector<std::shared_ptr<ALLEGRO_BITMAP>> rightAtkBmps;
	std::vector<std::shared_ptr<ALLEGRO_BITMAP>> rightMoveBmps;
	Character(std::string imgPath, float x, float y, bool isAlly, float Collradius, float Atkradius, float w, float h, float speed, float hp, float attack, int money);
 	//void Hit(float damage);
	void LoadImages(const std::vector<std::string>& LAP, const std::vector<std::string>& RAP, const std::vector<std::string>& LMP, const std::vector<std::string>& RMP);
	void UpdatePath(const std::vector<std::vector<int>>& mapDistance, bool isAlly);
	void Update(float deltaTime) override;
	void Draw() const override;
	// void leftMove();
	// void leftAttack();
	// void rightMove();
	// void rightAttack();
};
#endif // CHARACTER_HPP
