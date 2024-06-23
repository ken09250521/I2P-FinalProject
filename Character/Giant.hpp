#ifndef GIANT_HPP
#define GIANT_HPP
#include <vector>
#include "Character.hpp"
#include "Engine/Sprite.hpp"

class Giant : public Character {
private:
public:
	Giant(int x, int y, bool isAlly);
	std::vector<std::string> leftAtkPaths;
	std::vector<std::string> rightAtkPaths;
	std::vector<std::string> leftMovePaths;
	std::vector<std::string> rightMovePaths;
};
#endif // GIANT_HPP
