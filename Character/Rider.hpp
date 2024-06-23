#ifndef RIDER_HPP
#define RIDER_HPP
#include <vector>
#include "Character.hpp"
#include "Engine/Sprite.hpp"

class Rider : public Character {
private:
public:
	Rider(int x, int y, bool isAlly);
	std::vector<std::string> leftAtkPaths;
	std::vector<std::string> rightAtkPaths;
	std::vector<std::string> leftMovePaths;
	std::vector<std::string> rightMovePaths;
};
#endif // RIDER_HPP
