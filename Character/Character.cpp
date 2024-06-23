#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <random>
#include <string>
#include <vector>

#include "Engine/AudioHelper.hpp"
#include "Bullet/Bullet.hpp"
#include "Character.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Engine/LOG.hpp"
#include "Engine/Resources.hpp"
#include "Scene/PlayScene.hpp"
#include "Character/Warrior.hpp"
#include "Character/Rider.hpp"
#include "Character/Giant.hpp"


PlayScene* Character::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Character::Character(std::string imgPath, float x, float y, bool isAlly, float Collradius, float Atkradius, float w, float h, float speed, float hp, float attack, int money) :
	Engine::Sprite(imgPath, x, y, Collradius, Atkradius, w, h), speed(speed), hp(hp), money(money), attack(attack) {
	CollisionRadius = Collradius;
    AttackRadius = Atkradius;
    curState = Walk;
    Ally = isAlly;
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
// 		getPlayScene()->CharacterGroup->RemoveObject(objectIterator);
// 		AudioHelper::PlayAudio("explosion.wav");
// 	}
// }

void Character::LoadImages(const std::vector<std::string>& LAP, const std::vector<std::string>& RAP, const std::vector<std::string>& LMP, const std::vector<std::string>& RMP){
    for (const std::string& path : LAP) {
        leftAtkBmps.push_back(Engine::Resources::GetInstance().GetBitmap(path));
    }
    for (const std::string& path : RAP) {
        rightAtkBmps.push_back(Engine::Resources::GetInstance().GetBitmap(path));
    }
    for (const std::string& path : LMP) {
        leftMoveBmps.push_back(Engine::Resources::GetInstance().GetBitmap(path));
    }
    for (const std::string& path : RMP) {
        rightMoveBmps.push_back(Engine::Resources::GetInstance().GetBitmap(path));
    }
}
void Character::UpdatePath(const std::vector<std::vector<int>>& mapDistance, bool isAlly) {
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
		Engine::LOG(Engine::ERROR) << "Character path finding error";
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

void Character::Update(float deltaTime) {
	// Pre-calculate the velocity.
    float remainSpeed = 0;
    if (curState == Walk)
	    remainSpeed = speed * deltaTime;

    auto allies = getPlayScene()->CharacterGroup->GetObjects();
    auto enemies = getPlayScene()->EnemyGroup->GetObjects();

    bool shouldstop = false;
    if (Ally){
        for (auto& obj : allies){
            if (shouldstop) break;
            for (auto& otherObj : enemies){
                Engine::Point diff = obj->Position - otherObj->Position;
                float distance = diff.Magnitude();
                if (distance <= AttackRadius){
                    remainSpeed = 0;
                    curState = Attack;
                    shouldstop = true;
                    break;
                }
            }
        }
    }
    if (!Ally){
        for (auto& obj : enemies){
            if (shouldstop) break;
            for (auto& otherObj : allies){
                Engine::Point diff = obj->Position - otherObj->Position;
                float distance = diff.Magnitude();
                if (distance <= AttackRadius){
                    remainSpeed = 0;
                    curState = Attack;
                    shouldstop = true;
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
        } else {
            if (curTicks >= animationSpan) {
            // Loop the animation
                curTicks = fmod(curTicks, animationSpan);
            }
            int phase = floor(curTicks / animationSpan * leftAtkBmps.size());
            // Ensure phase is within the bounds of the frames vector
            phase = std::min(phase, static_cast<int>(leftAtkBmps.size()) - 1);
            bmp = leftAtkBmps[phase];
        }
        
    }
    if (!Ally){
        if (curState == Walk){
            if (curTicks >= animationSpan) {
            // Loop the animation
                curTicks = fmod(curTicks, animationSpan);
            }
            int phase = floor(curTicks / animationSpan * rightMoveBmps.size());
            // Ensure phase is within the bounds of the frames vector
            phase = std::min(phase, static_cast<int>(rightMoveBmps.size()) - 1);
            bmp = rightMoveBmps[phase];
        } else {
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
void Character::Draw() const {
	Sprite::Draw();
	if (PlayScene::DebugMode) {
		// Draw collision radius.
		al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
	}
}