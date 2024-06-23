#include "Engine/Point.hpp"
#include "IObject.hpp"

namespace Engine {
	IObject::IObject(float x, float y, float w, float h, float anchorX, float anchorY, float CollisionRadius, float AttackRadius) :
		Position(Point(x, y)), Size(Point(w, h)), Anchor(Point(anchorX, anchorY)) {
			CollisionRadius = CollisionRadius;
			AttackRadius = AttackRadius;
	}
	std::list<std::pair<bool, IObject*>>::iterator IObject::GetObjectIterator() const {
		return objectIterator;
	}
	void IObject::Draw() const {}
	void IObject::Update(float deltaTime) {}
}
