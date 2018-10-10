#include "stdafx.h"
#include "MainGame.h"
#include "Define.h"
#include "SceneMgr.h"
#include "Player.h"

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

void MainGame::Initialize()
{
	SceneMgr::GetInstance()->Initialize();
	SceneMgr::GetInstance()->SetScene(SCENE_LOGIN);
}

int MainGame::Update(float elapsedTime)
{
	return 0;
}

void MainGame::Render()
{
	SceneMgr::GetInstance()->Render();
}

void MainGame::Release()
{
}

void MainGame::KeyInput(unsigned char key)
{
	
}
