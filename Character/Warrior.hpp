#ifndef WARRIOR_HPP
#define WARRIOR_HPP
#include <vector>
#include "Character.hpp"
#include "Engine/Sprite.hpp"

class Warrior : public Character {
private:
public:
	Warrior(int x, int y, bool isAlly);
	std::vector<std::string> leftAtkPaths;
	std::vector<std::string> rightAtkPaths;
	std::vector<std::string> leftMovePaths;
	std::vector<std::string> rightMovePaths;
};
#endif // WARRIOR_HPP
