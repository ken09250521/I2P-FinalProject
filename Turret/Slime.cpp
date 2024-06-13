#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Bullet/LaserBullet.hpp"
#include "Slime.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

const int Slime::Price = 100;

Slime::Slime(float x, float y) :
	Turret("play/slime.png", "play/slime.png", x, y, 100, Price, 0) {
}

void Slime::Update(float deltaTime) {
	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();
	imgBase.Position = Position;
	imgBase.Tint = Tint;
	if (!Enabled)
		return;
}