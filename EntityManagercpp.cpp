#include "EntityManager.hpp"
#include "Object/Entity/Entity.hpp"

EntityManager::EntityManager() {


}

EntityManager::~EntityManager()
{
	for (Entity *element : entityList) {
		if (element) {
			delete element;
		}
	}
	entityList.clear();
}

void EntityManager::Init()
{
	for (Entity *element : entityList) {
		if (element) {
			delete element;
		}
	}
	entityList.clear();
}

void EntityManager::AddEntity(Entity *EntityPtr)
{
	entityList.push_back(EntityPtr);
}

void EntityManager::Update() {
	for (auto &element : entityList)
	{
		if (!element->isAlive) {
			delete element;
			entityList.erase(std::remove(entityList.begin(), entityList.end(), element), entityList.end());
		}
	}
	for (auto &element : entityList) {
		if (element->isAlive) {
			element->Update();
		}
	}



}

void EntityManager::Draw() const {
	for (auto element : entityList) {
		element->Draw();
	}
}
