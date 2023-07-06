#pragma once

struct TextureCache;

class Sprite
{
public:
	Sprite(std::string_view fileName);
	~Sprite();

	void Draw(glm::vec2 position, glm::vec2 size);

private:
	std::string m_filename;
	GLuint m_id = 0;
};