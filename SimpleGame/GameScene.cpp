#include "stdafx.h"
#include "GameScene.h"
#include "SceneMgr.h"
#include "Player.h"
#include "Block.h"

float elapsedTimePlus = 0;
int retval;
CFromClientData ClientData;

GameScene::GameScene()
{
	Initialize();
}

GameScene::~GameScene()
{

}

HRESULT GameScene::Initialize()
{
	return S_OK;
}

void GameScene::Update(float elapsedTime)
{
	int PlayerDeadCnt = 0;
	ClientData.PlayerInfo.Type = (ObjType)(OBJ_PLAYER1 + PlayerID);
	ClientData.PlayerInfo.Pos = (*m_vecObj[OBJ_PLAYER1 + PlayerID].begin())->xy;
	ClientData.PlayerInfo.life = (*m_vecObj[OBJ_PLAYER1 + PlayerID].begin())->life;

	for (int i = 0; i < OBJ_END; ++i)
	{
		list<Object*>::iterator iter = m_vecObj[i].begin();
		list<Object*>::iterator iter_end = m_vecObj[i].end();
		
		for (iter; iter != iter_end;)
		{
			if ((*iter) != NULL)
			{
				if (!(*iter)->IsDead())
				{
					(*iter)->update(elapsedTime);
					++iter;
					
				}
				else
				{
					if (!(dynamic_cast<Player*>(*iter)))
					{
						delete(*iter);
						iter = m_vecObj[i].erase(iter);
					}
					else
					{
						++iter;
						++PlayerDeadCnt;

						if (PlayerDeadCnt > 2) {
							SendClientInfo();
							SceneMgr::GetInstance()->ChangeScene(SCENE_OVER);
						}
					}
				}
			}
		}
	}

	collider();
	if (!(*m_vecObj[OBJ_PLAYER1 + PlayerID].begin())->IsDead())
		collider_player();
	collider_item();

	elapsedTimePlus += elapsedTime;
	if (elapsedTimePlus > 1000.0 / 30.0) {
		SendClientInfo();
		elapsedTimePlus = 0;
	}
}

void GameScene::Render()
{
	Scene::Render();
}

void GameScene::Release()
{

}

void GameScene::InitStartInfo()
{
}

void GameScene::SendClientInfo()
{
	dataTypeInfo = DATA_PLAYER;
	retval = send(sock, (char *)&dataTypeInfo, sizeof(dataTypeInfo), 0);
	retval = send(sock, (char *)&ClientData, sizeof(ClientData), 0);
}

void GameScene::AddBlock() {
	Object* pObj = new Block;
	pObj->SetPosition(Vec2(0, WINDOWSIZEY));
	pObj->SetVector(Vec2(0.f, BLOCKSPEED));
	pObj->SetInfo(1, 50, Vec4(0.f, 0.f, 100.f, 200.f));
	pObj->SetType(OBJ_BLOCK1);

	m_vecObj[OBJ_BLOCK1].push_back(pObj);
}

void GameScene::collider() {
	for (int i = 0; i < 5; i++) 
	{
		list<Object*>::iterator block_iter = m_vecObj[OBJ_BLOCK1 + i].begin();
		list<Object*>::iterator block_iter_end = m_vecObj[OBJ_BLOCK1 + i].end();

		for (block_iter; block_iter != block_iter_end; ++block_iter)
		{
			for (int j = 0; j < 3; j++)
			{
				list<Object*>::iterator bullet_iter = m_vecObj[OBJ_BULLET1 + j].begin();
				list<Object*>::iterator bullet_iter_end = m_vecObj[OBJ_BULLET1 + j].end();


				for (bullet_iter; bullet_iter != bullet_iter_end; ++bullet_iter)
				{
					float minX, minY;
					float maxX, maxY;

					float minX1, minY1;
					float maxX1, maxY1;

					minX = (*block_iter)->GetPosition().x - ((*block_iter)->GetObjInfo().Size / 2);
					maxX = (*block_iter)->GetPosition().x + ((*block_iter)->GetObjInfo().Size / 2);
					minY = (*block_iter)->GetPosition().y - ((*block_iter)->GetObjInfo().Size / 2);
					maxY = (*block_iter)->GetPosition().y + ((*block_iter)->GetObjInfo().Size / 2);

					minX1 = (*bullet_iter)->GetPosition().x - ((*bullet_iter)->GetObjInfo().Size / 2);
					maxX1 = (*bullet_iter)->GetPosition().x + ((*bullet_iter)->GetObjInfo().Size / 2);
					minY1 = (*bullet_iter)->GetPosition().y - ((*bullet_iter)->GetObjInfo().Size / 2);
					maxY1 = (*bullet_iter)->GetPosition().y + ((*bullet_iter)->GetObjInfo().Size / 2);

					if (BoxBoxCollisionTest(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1))
					{
						(*block_iter)->life = (*block_iter)->life - (*bullet_iter)->life;
						if ((*block_iter)->life < (*bullet_iter)->life)
							(*block_iter)->life = 0;
						(*bullet_iter)->SetDead();
					}
				}
			}
		}
	}
}


void GameScene::collider_player()
{
	Object* player = *m_vecObj[OBJ_PLAYER1 + PlayerID].begin();
	Vec2 PlayerPos = player->GetPosition();
	float PlayerSize = player->GetObjInfo().Size / 2.f;

	for (int i = OBJ_BLOCK1; i <= OBJ_BLOCK5; ++i)
	{
		auto iter = m_vecObj[i].begin();
		auto iter_end = m_vecObj[i].end();

		for (iter; iter != iter_end; ++iter)
		{
		
			Vec2 blockPos = (*iter)->GetPosition();
			float blockSize = (*iter)->GetObjInfo().Size / 2.f;

			float minX, minY;
			float maxX, maxY;

			float minX1, minY1;
			float maxX1, maxY1;

			minX = PlayerPos.x - PLAYERWIDTH;
			maxX = PlayerPos.x + PLAYERWIDTH;
			minY = PlayerPos.y - PLAYERHEIGHT;
			maxY = PlayerPos.y + PLAYERHEIGHT;

			minX1 = blockPos.x - blockSize;
			maxX1 = blockPos.x + blockSize;
			minY1 = blockPos.y - blockSize;
			maxY1 = blockPos.y + blockSize;

			if (BoxBoxCollisionTest(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1))
			{
				player->SetDead();
			}
		}
	}
}

void GameScene::collider_item()
{
	for (int i = 0; i < 3; ++i)
	{
		Object* player = *m_vecObj[OBJ_PLAYER1 + i].begin();
		if (player->IsDead())
			continue;
		Vec2 PlayerPos = player->GetPosition();
		float PlayerSize = player->GetObjInfo().Size / 2.f;

		for (int j = OBJ_ITEM1; j <= OBJ_ITEM2; ++j)
		{
			auto iter = m_vecObj[j].begin();
			auto iter_end = m_vecObj[j].end();
			ItemData.ItemIndex = 0;
			ItemData.ItemType = (ObjType)j;
			for (iter; iter != iter_end; ++iter)
			{
				ItemData.ItemIndex++;

				Vec2 blockPos = (*iter)->GetPosition();
				float blockSize = (*iter)->GetObjInfo().Size / 2.f;

				float minX, minY;
				float maxX, maxY;

				float minX1, minY1;
				float maxX1, maxY1;

				minX = PlayerPos.x - PLAYERWIDTH;
				maxX = PlayerPos.x + PLAYERWIDTH;
				minY = PlayerPos.y - PLAYERHEIGHT;
				maxY = PlayerPos.y + PLAYERHEIGHT;

				minX1 = blockPos.x - blockSize;
				maxX1 = blockPos.x + blockSize;
				minY1 = blockPos.y - blockSize;
				maxY1 = blockPos.y + blockSize;

				if (BoxBoxCollisionTest(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1))
				{
					if (i == PlayerID)
					{
						if ((*iter)->GetType() == OBJ_ITEM1)
						{
							if (myBulletData.BulletInfo.Type == OBJ_BULLET1)
								myBulletData.BulletInfo.Type = OBJ_BULLET2;
							else if (myBulletData.BulletInfo.Type == OBJ_BULLET2)
								myBulletData.BulletInfo.Type = OBJ_BULLET3;
							else if (myBulletData.BulletInfo.Type == OBJ_BULLET3)
								myBulletData.BulletInfo.Type = OBJ_BULLET3;
						}
						else if ((*iter)->GetType() == OBJ_ITEM2)
						{
							if (myBulletData.BulletInfo.Type == OBJ_BULLET1)
								myBulletData.BulletInfo.Type = OBJ_BULLET3;
							else if (myBulletData.BulletInfo.Type == OBJ_BULLET2)
								myBulletData.BulletInfo.Type = OBJ_BULLET3;
							else if (myBulletData.BulletInfo.Type == OBJ_BULLET3)
								myBulletData.BulletInfo.Type = OBJ_BULLET3;
						}
					}
					(*iter)->SetDead();
				}
			}
		}
	}
}

bool GameScene::BoxBoxCollisionTest(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1)
{
	if (minX > maxX1)
		return false;
	if (maxX < minX1)
		return false;

	if (minY > maxY1)
		return false;
	if (maxY < minY1)
		return false;

	return true;
}