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
	/// @brief エネミーの生存フラグの設定。
	/// @param Alive 生存のフラグ。
	static void SetEnemyAlive(bool Alive) { enemyAlive = Alive; }

	static int GetCount() { return enemyCount; }

private:
	static bool enemyAlive; // 静的メンバ変数のやつ。
	static int enemyCount; // 静的メンバ変数のやつ。
};
