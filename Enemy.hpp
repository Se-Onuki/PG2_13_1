#pragma once
#include "Object/Entity/Entity.hpp"
#include "PlayerManager.hpp"

class Enemy : public Entity
{
public:
	Enemy();

	virtual ~Enemy();

	void Update();

	using Entity::Entity;
};
