#pragma once

#include "Entity.h"

enum class ObjectType
{

};

class Object final : public Entity
{
public:
	void Update(float deltaTime) final;
	void Tick() final;

private:
	ObjectType m_type;
};