#pragma once

#include "MiniMath.h"

struct TextureCache;

class Sprite
{
public:
	Sprite(std::string_view fileName);
	~Sprite();

	void Draw(Vector2 position, Vector2 size);

private:
	std::string m_filename;
	GLuint m_id = 0;
};