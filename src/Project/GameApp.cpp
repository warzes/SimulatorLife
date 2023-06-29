#include "stdafx.h"
#include "GameApp.h"
#include "stb_image.h"
GLuint texture_id;
//-----------------------------------------------------------------------------
GameApp::~GameApp()
{
	glDeleteTextures(1, &texture_id);
}
//-----------------------------------------------------------------------------
void GameApp::Init()
{
	int width, height, channels;
	unsigned char* imgData = stbi_load("../textureTest.png", &width, &height, &channels, 0);

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(imgData);
}
//-----------------------------------------------------------------------------
bool GameApp::Update(float deltaTime)
{

	return true;
}
//-----------------------------------------------------------------------------
void GameApp::Frame()
{
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(0.0f,  0.0f);
	glTexCoord2f(1.0, 0.0); glVertex2f(64.0f, 0.0f);
	glTexCoord2f(1.0, 1.0); glVertex2f(64.0f, 64.0f);
	glTexCoord2f(0.0, 1.0); glVertex2f(0.0f,  64.0f);
	glEnd();
}
//-----------------------------------------------------------------------------
void GameApp::Tick()
{
}
//-----------------------------------------------------------------------------