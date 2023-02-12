#include "Player.hpp"


#include<math.h>
#include "Math/Math.hpp"
#include "./Input/KeyBoard.hpp"
#include "./Input/Controller.hpp"

#include "Object/Entity/Bullet.hpp"

#include "Object/ObjectController.hpp"

#include "Render/Camera.hpp"

Player::Player()
{
	position = MiddleCentor;
	radius = { 32,32 };
	GetSpriteBox().color = 0xFFFF00FF;
}
Player::~Player()
{
	for (auto *element : bulletList_) {
		if (element) {
			delete element;
		}
	}
	bulletList_.clear();
}
void Player::Input() {
		acceleration = Vector2::Zero();
		velocity = Vector2::Zero();

	if (isAlive) {
		if (Keyboard::IsPress(DIK_W)) {
			acceleration.y += 1;
		}
		if (Keyboard::IsPress(DIK_S)) {
			acceleration.y -= 1;
		}
		if (Keyboard::IsPress(DIK_A)) {
			acceleration.x -= 1;
		}
		if (Keyboard::IsPress(DIK_D)) {
			acceleration.x += 1;
		}
		velocity = acceleration.Nomalize() * 5;

		if (Keyboard::IsTrigger(DIK_SPACE)) {
			Bullet *newBullet = new Bullet(position, { 16,16 }, facing * 15);

			bulletList_.push_back(newBullet);
		}
	}
}

void Player::Update()
{
	if (acceleration != Vector2::Zero()) {
		facing = acceleration.Nomalize();
	}
	if (hp_ <= 0) {
		isAlive = false;
	}

	Move();
	for (auto &element : bulletList_)
	{
		if (!element->isAlive) {
			delete element;
			bulletList_.erase(std::remove(bulletList_.begin(), bulletList_.end(), element), bulletList_.end());
		}
	}
	for (auto element : bulletList_) {
		element->Update();
	}
}

void Player::Init()
{
}

void Player::Draw() const
{
	if (isAlive) {
		Object::Draw();
	}
	for (auto element : bulletList_) {
		element->Draw();
	}
}
