#include "Bullet.hpp"
#include "Math/Math.hpp"
#include "EntityManager.hpp"
#include "BaseData.hpp"
#include "Render/Camera.hpp"

#include "Score.hpp"

Bullet::Bullet(Vector2 position, Vector2 radius, Vector2 velocity)
{
	this->position = position;
	this->radius = radius;
	this->velocity = velocity;
	GetSpriteBox().Init("./Resources/Texture/TestTexture/Circle.png", 32, 32, 1);
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	Move();
	auto entityList = EntityManager::GetInstance().GetEntityList();
	for (int i = 0; i < entityList.size(); i++) {

		if (BallCollision(GetPosition(), GetRadius(), entityList[i]->GetPosition(), entityList[i]->GetRadius())) {
			isAlive = false;
			entityList[i]->isAlive = false;
			Score::GetInstance().AddScore(1);
		}
	}
	auto wvpVpMatrix = MakeAffineMatrix({ 1,1 }, 0.0f, GetPosition()) * Camera::vpVpMatrix;
	Vector2 LeftTop = Vector2{ -radius.x, radius.y }  *wvpVpMatrix;

	Vector2 RightDown = Vector2{ radius.x, -radius.y }  *wvpVpMatrix;
	if (LeftTop.y < 0 || RightDown.y > ScreenSize.y || LeftTop.x > ScreenSize.x || RightDown.x < 0) {
		isAlive = false;
	}
}
