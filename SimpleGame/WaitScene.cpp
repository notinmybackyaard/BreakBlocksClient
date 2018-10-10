#include "stdafx.h"
#include "WaitScene.h"
#include "SceneMgr.h"

WaitScene::WaitScene()
{
	Initialize();
}

WaitScene::~WaitScene()
{
}

HRESULT WaitScene::Initialize()
{
	return S_OK;
}

void WaitScene::Update(float elapsedTime)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); ++j)
		{
			if (!(*m_vecObj[OBJ_PLAYER1].begin())->IsDead() && !(*m_vecObj[OBJ_PLAYER2].begin())->IsDead() && !(*m_vecObj[OBJ_PLAYER3].begin())->IsDead()) {
				
				SceneMgr::GetInstance()->ChangeScene(SCENE_STAGE);
			}
		}
	}
}

void WaitScene::Render()
{

	Scene::Render();
}

void WaitScene::Release()
{

}
