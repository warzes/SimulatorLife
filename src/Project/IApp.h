#pragma once

class IApp
{
public:
	virtual ~IApp() = default;

	virtual void Init() = 0;
	virtual bool Update(float deltaTime) = 0;
	virtual void Frame() = 0;
	virtual void Tick() = 0;
};