#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <random>
#include <string>
#include <vector>

#include "Engine/AudioHelper.hpp"
#include "Bullet/Bullet.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "Enemy.hpp"
#include "UI/Animation/ExplosionEffect.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Resources.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"
#include "Engine/IScene.hpp"
#include "Engine/LOG.hpp"
#include "Scene/PlayScene.hpp"
<<<<<<< Updated upstream:Enemy/Enemy.cpp
#include "Turret/Turret.hpp"
#include "Turret/Slime.hpp"
#include "BossEnemy.hpp"
=======
>>>>>>> Stashed changes:Character/Character.cpp

PlayScene* Enemy::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
<<<<<<< Updated upstream:Enemy/Enemy.cpp
void Enemy::OnExplode() {
	getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
	for (int i = 0; i < 10; i++) {
		// Random add 10 dirty effects.
		getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng), Position.x, Position.y));
	}
}
Enemy::Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money) :
	Engine::Sprite(img, x, y), speed(speed), hp(hp), money(money) {
	CollisionRadius = radius;
	reachEndTime = 0;
=======

Character::Character(std::string imgPath, float x, float y, bool isAlly, float Collradius, float Atkradius, float w, float h, float speed, float hp, float attack, int money) : //image, size(x, y), effect radius, speed, hp,
	Engine::Sprite(imgPath, x, y, Collradius, Atkradius, w, h), speed(speed), hp(hp), attack(attack), money(money) {
	CollisionRadius = Collradius;
	AttackRadius = Atkradius;
	curState = Walk;
	curTicks = 0;
	Ally = isAlly;
>>>>>>> Stashed changes:Character/Character.cpp
}
void Enemy::Hit(float damage) {
	hp -= damage;
	if (hp <= 0) {
		OnExplode();
		// Remove all turret's reference to target.
		for (auto& it: lockedTurrets)
			it->Target = nullptr;
		for (auto& it: lockedBullets)
			it->Target = nullptr;
		getPlayScene()->EarnMoney(money);
		getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
		getPlayScene()->enemyDeathCount();

<<<<<<< Updated upstream:Enemy/Enemy.cpp
		AudioHelper::PlayAudio("explosion.wav");
	}
}
void Enemy::UpdatePath(const std::vector<std::vector<int>>& mapDistance) {
=======
void Character::LoadImages(const std::vector<std::string>& LAP, const std::vector<std::string>& RAP, const std::vector<std::string>& LMP, const std::vector<std::string>& RMP){
	for (const auto& atkpath : LAP) {
		leftAtkBmps.push_back(Engine::Resources::GetInstance().GetBitmap(atkpath));
	}
	for (const auto& atkpath : RAP) {
		rightAtkBmps.push_back(Engine::Resources::GetInstance().GetBitmap(atkpath));
	}
	for (const auto& movepath : LMP) {
		leftMoveBmps.push_back(Engine::Resources::GetInstance().GetBitmap(movepath));
	}
	for (const auto& movepath : RMP) {
		rightMoveBmps.push_back(Engine::Resources::GetInstance().GetBitmap(movepath));
	}
}

void Character::UpdatePath(const std::vector<std::vector<int>>& mapDistance, bool isAlly) {
>>>>>>> Stashed changes:Character/Character.cpp
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
	Engine::Point endGridPoint = isAlly ? PlayScene::AllyEndGridPoint : PlayScene::EnemyEndGridPoint;
    path[0] = endGridPoint;
}
void Enemy::Update(float deltaTime) {
	// Pre-calculate the velocity.
	float remainSpeed = 0;
	if (curState == Walk)
		remainSpeed = speed * deltaTime;

<<<<<<< Updated upstream:Enemy/Enemy.cpp
	auto turrets = getPlayScene()->TowerGroup->GetObjects();

	auto enemies = getPlayScene()->EnemyGroup->GetObjects();

	for (auto& obj : turrets) {
		Slime* slime = dynamic_cast<Slime*>(obj);
		if (slime) {
			Engine::Point diff = Position - slime->Position;
			float distance = diff.Magnitude();

			if (distance <= 100){
				remainSpeed *= 0.5f;
				break;
			}
		}
	}

	for (auto& obj : enemies) {
        BossEnemy* bossEnemy = dynamic_cast<BossEnemy*>(obj);
        if (bossEnemy) {
            for (auto& otherObj : enemies) {
                if (otherObj != obj) {
                    Engine::Point diff = Position - bossEnemy->Position;
                    float distance = diff.Magnitude();
                    if (distance <= bossEnemy->boostRadius) {
                        remainSpeed *= (bossEnemy->speedBoost);
                    }
                }
            }
        }
    }
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
=======
	auto enemies = getPlayScene()->EnemyGroup->GetObjects();
	auto allies = getPlayScene()->CharacterGroup->GetObjects();

	bool shouldStop = false;

	if (Ally) {
		for (auto& obj : allies){
			if (shouldStop) break;
			for (auto& otherObj : enemies) {
				Engine::Point diff = obj->Position - otherObj->Position;
				float distance = diff.Magnitude();
				//printf("Ally at (%f, %f) checking Enemy at (%f, %f), Distance: %f\n", obj->Position.x, obj->Position.y, otherObj->Position.x, otherObj->Position.y, distance);
				if (distance <= AttackRadius) {
					remainSpeed = 0;
					curState = Attack;
					shouldStop = true;
					break;
				}
			}
>>>>>>> Stashed changes:Character/Character.cpp
		}
	}
	if (!Ally){
		for (auto& obj : enemies){
			if (shouldStop) break;
			for (auto& otherObj : allies) {
				Engine::Point diff = obj->Position - otherObj->Position;
				float distance = diff.Magnitude();
				if (distance <= AttackRadius) {
					remainSpeed = 0;
					curState = Attack;
					shouldStop = true;
					break;
				}
			}

		}
	}
	
	curTicks += deltaTime;
	if (Ally){
		if (curState == Walk){
			if (curTicks >= animationSpan) {
				// Loop the animation
				curTicks = fmod(curTicks, animationSpan);
			}
			int phase = floor(curTicks / animationSpan * leftMoveBmps.size());
			// Ensure phase is within the bounds of the frames vector
			phase = std::min(phase, static_cast<int>(leftMoveBmps.size()) - 1);
			bmp = leftMoveBmps[phase];
		}	
		else if (curState == Attack){
			if (curTicks >= animationSpan) {
				// Loop the animation
				curTicks = fmod(curTicks, animationSpan);
			}
			int phase = floor(curTicks / animationSpan * leftAtkBmps.size());
			// Ensure phase is within the bounds of the frames vector
			phase = std::min(phase, static_cast<int>(leftAtkBmps.size()) - 1);
			bmp = leftAtkBmps[phase];
		}	
	} else {
		if (curState == Walk){
			if (curTicks >= animationSpan) {
				// Loop the animation
				curTicks = fmod(curTicks, animationSpan);
			}
			int phase = floor(curTicks / animationSpan * rightMoveBmps.size());
			// Ensure phase is within the bounds of the frames vector
			phase = std::min(phase, static_cast<int>(rightMoveBmps.size()) - 1);
			bmp = rightMoveBmps[phase];
		}	
		else if (curState == Attack){
			if (curTicks >= animationSpan) {
				// Loop the animation
				curTicks = fmod(curTicks, animationSpan);
			}
			int phase = floor(curTicks / animationSpan * rightAtkBmps.size());
			// Ensure phase is within the bounds of the frames vector
			phase = std::min(phase, static_cast<int>(rightAtkBmps.size()) - 1);
			bmp = rightAtkBmps[phase];
		}	
	}
	
	if (path.empty()) {
		// Reach end point.
		//Hit(hp);
		//getPlayScene()->Hit();
		//reachEndTime = 0;
		return;
	}
	Engine::Point target = path.back() * PlayScene::BlockSize + Engine::Point(PlayScene::BlockSize / 2, PlayScene::BlockSize / 2);
	Engine::Point vec = target - Position;
	// Add up the distances:
	// 1. to path.back()
	// 2. path.back() to border
	// 3. All intermediate block size
	// 4. to end point
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

	
	Sprite::Update(deltaTime);
}
<<<<<<< Updated upstream:Enemy/Enemy.cpp
void Enemy::Draw() const {
=======

void Character::Draw() const {
>>>>>>> Stashed changes:Character/Character.cpp
	Sprite::Draw();
	if (PlayScene::DebugMode) {
		// Draw collision radius.
		al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
	}
}
