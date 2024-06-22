#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <random>
#include <string>
#include <vector>

#include "Engine/AudioHelper.hpp"
#include "Bullet/Bullet.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "Character.hpp"
#include "UI/Animation/ExplosionEffect.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"
#include "Engine/IScene.hpp"
#include "Engine/LOG.hpp"
#include "Scene/PlayScene.hpp"
#include "Scene/Scene.hpp"

PlayScene* Character::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

// void Character::OnExplode() {
// 	getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
// 	std::random_device dev;
// 	std::mt19937 rng(dev());
// 	std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
// 	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
// 	for (int i = 0; i < 10; i++) {
// 		// Random add 10 dirty effects.
// 		getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng), Position.x, Position.y));
// 	}
// }

Character::Character(std::unordered_map<Engine::AnimationType, std::vector<std::string>> imgPaths, float x, float y, float Collradius, float Atkradius, float speed, float hp, float attack, int money, float frameDuration) : //image, size(x, y), effect radius, speed, hp,
	Engine::Sprite(imgPaths, x, y, frameDuration), speed(speed), hp(hp), attack(attack), money(money) {
	CollisionRadius = Collradius;
	AttackRadius = Atkradius;
	reachEndTime = 0;
}

// void Character::Hit(float damage) {
// 	hp -= damage;
// 	if (hp <= 0) {
// 		OnExplode();
// 		// Remove all turret's reference to target.
// 		for (auto& it: lockedTurrets)
// 			it->Target = nullptr;
// 		for (auto& it: lockedBullets)
// 			it->Target = nullptr;
// 		getPlayScene()->EarnMoney(money);
// 		getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
// 		getPlayScene()->enemyDeathCount();

// 		AudioHelper::PlayAudio("explosion.wav");
// 	}
// }

void Character::UpdatePath(const std::vector<std::vector<int>>& mapDistance) {
	int x = static_cast<int>(floor(Position.x / PlayScene::BlockSize));
	int y = static_cast<int>(floor(Position.y / PlayScene::BlockSize));
	if (x < 0) x = 0;
	if (x >= PlayScene::MapWidth) x = PlayScene::MapWidth - 1;
	if (y < 0) y = 0;
	if (y >= PlayScene::MapHeight) y = PlayScene::MapHeight - 1;
	Engine::Point pos(x, y);
	int num = mapDistance[y][x];
	if (num == -1) {
		num = 0;
		Engine::LOG(Engine::ERROR) << "Enemy path finding error";
	}
	path = std::vector<Engine::Point>(num + 1);
	while (num != 0) {
		std::vector<Engine::Point> nextHops;
		for (auto& dir : PlayScene::directions) {
			int x = pos.x + dir.x;
			int y = pos.y + dir.y;
			if (x < 0 || x >= PlayScene::MapWidth || y < 0 || y >= PlayScene::MapHeight || mapDistance[y][x] != num - 1)
				continue;
			nextHops.emplace_back(x, y);
		}
		// Choose arbitrary one.
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist(0, nextHops.size() - 1);
		pos = nextHops[dist(rng)];
		path[num] = pos;
		num--;
	}
	path[0] = PlayScene::EndGridPoint;
}

void Character::Update(float deltaTime) {
	// Pre-calculate the velocity.
	float remainSpeed = speed * deltaTime;

	while (remainSpeed != 0) {
		if (path.empty()) {
			// Reach end point.
			Hit(hp);
			getPlayScene()->Hit();
			reachEndTime = 0;
			return;
		}
		Engine::Point target = path.back() * PlayScene::BlockSize + Engine::Point(PlayScene::BlockSize / 2, PlayScene::BlockSize / 2);
		Engine::Point vec = target - Position;
		// Add up the distances:
		// 1. to path.back()
		// 2. path.back() to border
		// 3. All intermediate block size
		// 4. to end point
		reachEndTime = (vec.Magnitude() + (path.size() - 1) * PlayScene::BlockSize - remainSpeed) / speed;
		Engine::Point normalized = vec.Normalize();
		if (remainSpeed - vec.Magnitude() > 0) {
			Position = target;
			path.pop_back();
			remainSpeed -= vec.Magnitude();
		}
		else {
			Velocity = normalized * remainSpeed / deltaTime;
			remainSpeed = 0;
		}
	}
	Rotation = atan2(Velocity.y, Velocity.x);
	Sprite::Update(deltaTime);
// }

void Character::Draw() const {
	Sprite::Draw();
	// if (TestScene::DebugMode) {
	// 	// Draw collision radius.
	// 	al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
	// }
}

void Character::leftMove() {
	SetAnimation(Engine::AnimationType::leftMove);
}	

void Character::rightMove() {
	SetAnimation(Engine::AnimationType::rightMove);
}	

void Character::leftAttack() {
	SetAnimation(Engine::AnimationType::leftAttack);
}

void Character::rightAttack() {
	SetAnimation(Engine::AnimationType::rightAttack);
}