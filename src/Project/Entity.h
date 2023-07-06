#pragma once

#include "Sprite.h"

class Entity
{
public:
	Entity() = delete;
	Entity(const std::string& fileName);
	Entity(Entity&&) = delete;
	Entity(const Entity&) = delete;
	virtual ~Entity();

	Entity& operator=(Entity&&) = delete;
	Entity& operator=(const Entity&) = delete;

	void SetPosition(glm::vec2 newPosition) { m_position = newPosition; }
	void AddPosition(glm::vec2 move) { m_position += move; }

	virtual void Update(float deltaTime) = 0;
	virtual void Tick() = 0;
	void Draw();

protected:
	Sprite* m_sprite = nullptr;
	glm::vec2 m_position = glm::vec2(0.0f);
};