#include "stdafx.h"
#include "Pawn.h"
//-----------------------------------------------------------------------------
void Pawn::SetTargetMove(glm::vec2 target)
{
	m_isMoving = true;
	m_targetMovePosition = target;
}
//-----------------------------------------------------------------------------
void Pawn::Update(float deltaTime)
{
	moving(deltaTime);
}
//-----------------------------------------------------------------------------
void Pawn::Tick()
{
	if (!m_isMoving || rand() % 100 > 30)
		setRandomTargetMove();
}
//-----------------------------------------------------------------------------
void Pawn::moving(float deltaTime)
{
	if (m_isMoving)
	{
		glm::vec2 direction = m_targetMovePosition - m_position;
		if (direction.x >= -1.0f && direction.x <= 1.0f
			&& direction.y >= -1.0f && direction.y <= 1.0f)
		{
			m_isMoving = false;
		}
		else
		{
			direction = glm::normalize(direction);
			m_position += direction * 100.00f/*step*/ * deltaTime;
		}
	}
}
//-----------------------------------------------------------------------------
void Pawn::setRandomTargetMove()
{
	int x = rand() % 640;
	int y = rand() % 480;
	SetTargetMove({ x, y });
}
//-----------------------------------------------------------------------------