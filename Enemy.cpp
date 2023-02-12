#include "Enemy.hpp"
#include <Math.h>
#include "BaseData.hpp"
#include "Object/Entity/Entity.hpp"
#include "Render/Resource.hpp"

#include "EntityManager.hpp"
#include "Render/Camera.hpp"

bool Enemy::enemyAlive = true;
int Enemy::enemyCount = 0;

Enemy::Enemy()
{
	GetSpriteBox().Init("./Resources/Texture/TestTexture/Circle.png", 32, 32, 1);
	enemyCount++;

	isAlive = enemyAlive;
}

Enemy::~Enemy()
{
	enemyCount--;
	enemyAlive = false;
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

	if (!isAlive || !enemyAlive) {	//�@�{���A�G���e�B�e�B�S�̂�isAlive��ύX����ׂ������A�e��v���C���[�Ȃǂ̃G���e�B�e�B�Ɋ����Ă��܂����߁A�G�l�~�[�݂̂�enemyAlive�����o�ϐ������������B
		isAlive = false;
		enemyAlive = false;
	}
}

