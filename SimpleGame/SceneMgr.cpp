#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "LogInScene.h"
#include "WaitScene.h"
#include "GameScene.h"
#include "GameOverScene.h"

INIT_SINGLETON(SceneMgr)

SceneMgr::SceneMgr()
	: m_Scene(nullptr)
{
	Initialize();
}

SceneMgr::~SceneMgr()
{
	Release();
}

void SceneMgr::Initialize()
{
	SetScene(SCENE_LOGIN);
}

void SceneMgr::Update(float elapsedTime)
{
	if (m_Scene)
		m_Scene->Update(elapsedTime);
}

void SceneMgr::Render()
{
	if (m_Scene)
		m_Scene->Render();
}

void SceneMgr::GetKey(unsigned char key,int playerid) {
	if (m_Scene)
		m_Scene->GetKey(key,playerid);
}

void SceneMgr::GetKeyUp(unsigned char key,int playerid) {
	if (m_Scene)
		m_Scene->GetKeyUp(key,playerid);
}

void SceneMgr::Release()
{
	if (m_Scene)
	{
		delete(m_Scene);
		m_Scene = NULL;
	}
}

void SceneMgr::SetScene(SceneType _SceneType)
{
	if (m_Scene)
	{
		delete m_Scene;
		m_Scene = NULL;
	}

	m_CurSceneType = _SceneType;

	switch (_SceneType)
	{
	case SCENE_LOGIN:
		m_Scene = new LogInScene();
		break;

	case SCENE_WAIT:
		m_Scene = new WaitScene();
		break;

	case SCENE_STAGE:
		m_Scene = new GameScene();
		break;

	case SCENE_OVER:
		m_Scene = new GameOverScene();
		break;
	}
}

void SceneMgr::ChangeScene(SceneType _SceneType)
{
	if (m_CurSceneType == _SceneType)
		return;
	SetScene(_SceneType);
}

list<Object*>& SceneMgr::GetvecObj(ObjType type)
{
	return m_Scene->GetvecObj(type);
}