#include "stdafx.h"
#include "GameApp.h"
#include "Pawn.h"
Pawn* pawn;
//-----------------------------------------------------------------------------
GameApp::~GameApp()
{
	delete pawn;
}
//-----------------------------------------------------------------------------
void GameApp::Init()
{
	pawn = new Pawn("../textureTest.png");
	pawn->SetPosition({ 300.0f, 200.0f });
	pawn->SetTargetMove({ 50, 50 });
}
//-----------------------------------------------------------------------------
bool GameApp::Update(float deltaTime)
{
	pawn->Update(deltaTime);
	return true;
}
//-----------------------------------------------------------------------------
void GameApp::Frame()
{
	pawn->Draw();
}
//-----------------------------------------------------------------------------
void GameApp::Tick()
{
	pawn->Tick();
}
//-----------------------------------------------------------------------------