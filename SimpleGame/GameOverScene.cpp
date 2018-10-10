#include "stdafx.h"
#include "GameOverScene.h"
#include "SceneMgr.h"
#include "ErrorFnc.h"

GameOverScene::GameOverScene()
{
	Initialize();
}

GameOverScene::~GameOverScene()
{
	Release();
}

HRESULT GameOverScene::Initialize()
{
	Scene::Initialize();

	return S_OK;
}

void GameOverScene::Update(float elapsedTime)
{
	int retval;

	dataTypeInfo = DATA_EXIT;
	retval = send(sock, (char *)&dataTypeInfo, sizeof(dataTypeInfo), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
	}

}

void GameOverScene::Render()
{
	Scene::Render();
}

void GameOverScene::Release()
{

	for (int i = 0; i < OBJ_END; ++i)
	{
		auto iter = m_vecObj[i].begin();
		auto iter_end = m_vecObj[i].end();

		for (iter; iter != iter_end; ++iter)
		{
			if ((*iter))
				delete(*iter);
		}
		m_vecObj[i].clear();
	}
}
