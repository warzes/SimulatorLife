#pragma once

#include "Entity.h"

class Pawn final : public Entity
{
public:
	Pawn(const std::string& fileName) : Entity(fileName) {}

	void SetTargetMove(glm::vec2 target);

	void Update(float deltaTime) final;
	void Tick() final;

private:
	void moving(float deltaTime);
	void setRandomTargetMove();

	glm::vec2 m_targetMovePosition = glm::vec2(0.0f);
	bool m_isMoving = false;
};