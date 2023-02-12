#include "Enemy.hpp"
#include <Math.h>
#include "BaseData.hpp"
#include "Object/Entity/Entity.hpp"
#include "Render/Resource.hpp"

#include "EntityManager.hpp"
#include "Render/Camera.hpp"

Enemy::Enemy()
{

	GetSpriteBox().LoadTexture("./Resources/Texture/TestTexture/Circle.png");
	GetSpriteBox().Init(32, 32, 1);
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	velocity = (PlayerManager::GetInstance().GetPlayer().GetPosition() - position).Nomalize() * 2;
	Object::Move();
	if (BallCollision(GetPosition(), GetRadius(), PlayerManager::GetInstance().GetPlayer().GetPosition(), PlayerManager::GetInstance().GetPlayer().GetRadius())) {
		isAlive = false;
		PlayerManager::GetInstance().GetPlayer().SetHP(PlayerManager::GetInstance().GetPlayer().GetHP() - 0.25f);
		Camera::Shake({ 5,5 }, 10);
	}
}

