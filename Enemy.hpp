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
	/// @brief �G�l�~�[�̐����t���O�̐ݒ�B
	/// @param Alive �����̃t���O�B
	static void SetEnemyAlive(bool Alive) { enemyAlive = Alive; }

	static int GetCount() { return enemyCount; }

private:
	static bool enemyAlive; // �ÓI�����o�ϐ��̂�B
	static int enemyCount; // �ÓI�����o�ϐ��̂�B
};
