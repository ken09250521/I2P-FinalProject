#include <allegro5/allegro.h>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include "UI/Component/Image.hpp"
#include "LOG.hpp"
#include "Engine/Point.hpp"
#include "Sprite.hpp"

namespace Engine {
	Sprite::Sprite(std::unordered_map<AnimationType, std::vector<std::string>> imgPaths, float x, float y, float frameDuration, float w, float h, float anchorX, float anchorY,
		float rotation, float vx, float vy, unsigned char r, unsigned char g, unsigned char b, unsigned char a) :
		Image(imgPaths[AnimationType::leftMove][0], x, y, w, h, anchorX, anchorY), Rotation(rotation), Velocity(Point(vx, vy)), Tint(al_map_rgba(r, g, b, a)), frameDuration(frameDuration), frameTimer(0.0f), curFrames(0), currentAnimationType(AnimationType::leftMove) {
			for (const std::pair<AnimationType, std::vector<std::string>> &anim : imgPaths){
				std::vector<std::shared_ptr<ALLEGRO_BITMAP>> frames;
				for (const std::string &path : anim.second){
					ALLEGRO_BITMAP* bmp = al_load_bitmap(path.c_str());
					if (bmp){
						frames.push_back(std::shared_ptr<ALLEGRO_BITMAP>(bmp, al_destroy_bitmap));
					} else {
						//handle error
					}
				}
				animations[anim.first] = frames;
			}
	
	}
	void Sprite::Draw() const {
		if (!animations.at(currentAnimationType).empty()) {
			ALLEGRO_BITMAP* bmp = animations.at(currentAnimationType)[curFrames].get();
            al_draw_tinted_scaled_rotated_bitmap(bmp, Tint, Anchor.x * al_get_bitmap_width(bmp), Anchor.y * al_get_bitmap_height(bmp),
            	Position.x, Position.y, Size.x / al_get_bitmap_width(bmp), Size.y / al_get_bitmap_height(bmp), Rotation, 0);
		}
		
	}
	void Sprite::Update(float deltaTime) {
		Position.x += Velocity.x * deltaTime;
		Position.y += Velocity.y * deltaTime;

		frameTimer += deltaTime;
		if (frameTimer >= frameDuration){
			curFrames = (curFrames + 1) & animations.at(currentAnimationType).size();
			frameTimer = 0.0f;
		}
	}

	void Sprite::SetAnimation(AnimationType type) {
        if (currentAnimationType != type) {
            currentAnimationType = type;
            curFrames = 0;
            frameTimer = 0.0f;
        }
    }
};
