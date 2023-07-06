#include "stdafx.h"
#include "Sprite.h"
#include "stb_image.h"

struct TextureCache
{
	GLuint id = 0;
	unsigned numRef = 0;
};

std::unordered_map<std::string, TextureCache> TexturesCache;

GLuint createTexture(const std::string& fileName)
{
	GLuint id;
	int width, height, channels;
	unsigned char* imgData = stbi_load(fileName.c_str(), &width, &height, &channels, 0);
	if (!imgData) throw Exception(fileName + " not load!!!");

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(imgData);

	return id;
}


GLuint getTexture(const std::string& fileName)
{
	auto it = TexturesCache.find(fileName);
	if (it != TexturesCache.end())
	{
		if (it->second.numRef == 0)
			it->second.id = createTexture(fileName);
		
		it->second.numRef++;
		return it->second.id;
	}
	else
	{
		TextureCache tex;
		tex.numRef = 1;
		tex.id = createTexture(fileName);
		TexturesCache[fileName] = tex;
		return tex.id;
	}
}

void deleteTexture(const std::string& fileName)
{
	auto it = TexturesCache.find(fileName);
	if (it != TexturesCache.end())
	{
		assert(it->second.numRef > 0);
		if (it->second.numRef > 1)
			it->second.numRef--;

		if (it->second.numRef == 0 && it->second.id > 0)
		{
			glDeleteTextures(1, &it->second.id);
			it->second.id = 0;
		}
	}
}

Sprite::Sprite(std::string_view fileName)
{
	m_filename = fileName.data();
	m_id = getTexture(m_filename);
	assert(m_id);
}

Sprite::~Sprite()
{
	if (m_id > 0)
		deleteTexture(m_filename);
}

void Sprite::Draw(Vector2 position, Vector2 size)
{
	Vector2 halfSize = { size.x * 0.5f, size.y * 0.5f };
	position -= halfSize;

	glBindTexture(GL_TEXTURE_2D, m_id);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(position.x,          position.y);
	glTexCoord2f(1.0, 0.0); glVertex2f(position.x + size.x, position.y);
	glTexCoord2f(1.0, 1.0); glVertex2f(position.x + size.x, position.y + size.y);
	glTexCoord2f(0.0, 1.0); glVertex2f(position.x,          position.y + size.y);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}