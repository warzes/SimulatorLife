#pragma once

class Vector2
{
public:
	Vector2() = default;
	Vector2(const Vector2&) = default;
	Vector2(float n) : x(n), y(n) {}
	Vector2(float nx, float ny) : x(nx), y(ny) {}

	Vector2& operator=(const Vector2&) = default;

	Vector2& operator-=(const Vector2& v) { x -= v.x; y -= v.y; return *this; }
	Vector2& operator+=(const Vector2& v) { x += v.x; y += v.y; return *this; }

	float x = 0.0f;
	float y = 0.0f;
};