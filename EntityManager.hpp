#pragma once

#include <vector>

class Entity;

class EntityManager final
{
public:
	EntityManager(const EntityManager &) = delete;
	EntityManager &operator=(const EntityManager &) = delete;

	/// @brief �C���X�^���X�̎擾
	/// @return �C���X�^���X�̎���
	inline static EntityManager &GetInstance() {
		static EntityManager instance;
		return instance;
	}

	void Init();

	void AddEntity(Entity *EntityPtr);

	void Update();

	void Draw() const;

	inline std::vector<Entity *> GetEntityList() {
		return entityList;
	}

private:
	std::vector<Entity *> entityList;

	EntityManager();
	~EntityManager();

};