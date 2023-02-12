#pragma once

#include "./Object/Object.hpp"

class Entity :public Object
{
public:
	Entity();
	virtual ~Entity() override;
	using Object::Object;

private:

};