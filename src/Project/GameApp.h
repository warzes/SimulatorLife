#pragma once

#include "IApp.h"

class GameApp final : public IApp
{
public:
	~GameApp();

	void Init() final;
	bool Update(float deltaTime) final;
	void Frame() final;
	void Tick() final;
};