#pragma once
#include "Object/Entity/Entity.hpp"

class Bullet :public Entity
{
public:
	Bullet(Vector2 position, Vector2 radius, Vector2 velocity);
	~Bullet();

	using Entity::Entity;
	
	void Update();

private:

};