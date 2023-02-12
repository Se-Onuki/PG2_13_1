#pragma once
#include "./Object/Entity/Entity.hpp"

#include <vector>

class Bullet;

class Player :public Entity
{
public:
	Player();
	~Player();

	using Entity::Entity;

	void Input() override;
	void Update() override;
	void Init() override;
	void Draw() const override;

	void SetHP(float hp) { hp_ = hp; }
	float GetHP() { return hp_; }
	std::vector<Bullet *> GetBulletList() { return bulletList_; }
private:
	std::vector<Bullet *> bulletList_;
	float hp_;
};
