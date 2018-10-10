#include "stdafx.h"
#include "Scene.h"
#include "SceneMgr.h"
#include"player.h"

Scene::Scene()
{
	Initialize();
}

Scene::~Scene()
{
	Release();
}

HRESULT Scene::Initialize()
{

	return S_OK;
}

void Scene::Render()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		list<Object*>::iterator iter = m_vecObj[i].begin();
		list<Object*>::iterator iter_end = m_vecObj[i].end();

		for (iter; iter != iter_end; ++iter)
		{
			if (!(*iter)->IsDead())
			{
				if ((*iter)->GetObjInfo().objType >= OBJ_PLAYER1 && (*iter)->GetObjInfo().objType <= OBJ_PLAYER3)
				{
					glEnable(GL_TEXTURE_2D);
					glColor4d(1.0, 1.0, 1.0, 1.0);
					glBindTexture(GL_TEXTURE_2D, textures[(*iter)->GetObjInfo().objType - 1]);
					glBegin(GL_QUADS);
					glTexCoord2f(0, 1);
					glVertex2d((*iter)->GetObjInfo().Pos.x - PLAYERWIDTH, (*iter)->GetObjInfo().Pos.y - PLAYERHEIGHT);
					glTexCoord2f(1, 1);
					glVertex2d((*iter)->GetObjInfo().Pos.x + PLAYERWIDTH, (*iter)->GetObjInfo().Pos.y - PLAYERHEIGHT);
					glTexCoord2f(1, 0);
					glVertex2d((*iter)->GetObjInfo().Pos.x + PLAYERWIDTH, (*iter)->GetObjInfo().Pos.y + PLAYERHEIGHT);
					glTexCoord2f(0, 0);
					glVertex2d((*iter)->GetObjInfo().Pos.x - PLAYERWIDTH, (*iter)->GetObjInfo().Pos.y + PLAYERHEIGHT);
					glEnd();
					glDisable(GL_TEXTURE_2D);
				}
				else if ((*iter)->GetObjInfo().objType >= OBJ_BLOCK1 && (*iter)->GetObjInfo().objType <= OBJ_BLOCK5)
				{
					glEnable(GL_TEXTURE_2D);
					glColor4d(1.0, 1.0, 1.0, 1.0);
					glBindTexture(GL_TEXTURE_2D, textures[(*iter)->GetObjInfo().objType - 4]);
					glBegin(GL_QUADS);
					glTexCoord2f(0, 1);
					glVertex2d((*iter)->GetObjInfo().Pos.x - (*iter)->GetObjInfo().Size / 2, (*iter)->GetObjInfo().Pos.y - (*iter)->GetObjInfo().Size / 2);
					glTexCoord2f(1, 1);
					glVertex2d((*iter)->GetObjInfo().Pos.x + (*iter)->GetObjInfo().Size / 2, (*iter)->GetObjInfo().Pos.y - (*iter)->GetObjInfo().Size / 2);
					glTexCoord2f(1, 0);
					glVertex2d((*iter)->GetObjInfo().Pos.x + (*iter)->GetObjInfo().Size / 2, (*iter)->GetObjInfo().Pos.y + (*iter)->GetObjInfo().Size / 2);
					glTexCoord2f(0, 0);
					glVertex2d((*iter)->GetObjInfo().Pos.x - (*iter)->GetObjInfo().Size / 2, (*iter)->GetObjInfo().Pos.y + (*iter)->GetObjInfo().Size / 2);
					glEnd();
					glDisable(GL_TEXTURE_2D);
				}
				else
				{
					glColor4d((*iter)->GetObjInfo().Color.x, (*iter)->GetObjInfo().Color.y, (*iter)->GetObjInfo().Color.z, (*iter)->GetObjInfo().Color.w);
					glBegin(GL_POLYGON);
					glVertex2d((*iter)->GetObjInfo().Pos.x - (*iter)->GetObjInfo().Size / 2, (*iter)->GetObjInfo().Pos.y - (*iter)->GetObjInfo().Size / 2);
					glVertex2d((*iter)->GetObjInfo().Pos.x + (*iter)->GetObjInfo().Size / 2, (*iter)->GetObjInfo().Pos.y - (*iter)->GetObjInfo().Size / 2);
					glVertex2d((*iter)->GetObjInfo().Pos.x + (*iter)->GetObjInfo().Size / 2, (*iter)->GetObjInfo().Pos.y + (*iter)->GetObjInfo().Size / 2);
					glVertex2d((*iter)->GetObjInfo().Pos.x - (*iter)->GetObjInfo().Size / 2, (*iter)->GetObjInfo().Pos.y + (*iter)->GetObjInfo().Size / 2);
					glEnd();
				}
			}
		}
	}
}

void Scene::GetKey(unsigned char key,int playerid) {
	list<Object*>::iterator iter = m_vecObj[OBJ_PLAYER1 + playerid].begin();
	list<Object*>::iterator iter_end = m_vecObj[OBJ_PLAYER1 + playerid].end();

	for (iter; iter != iter_end; ++iter)
	{
		dynamic_cast<Player*>(*iter)->GetKey(key);
	}
}

void Scene::GetKeyUp(unsigned char key,int playerid) {
	list<Object*>::iterator iter = m_vecObj[OBJ_PLAYER1 + playerid].begin();
	list<Object*>::iterator iter_end = m_vecObj[OBJ_PLAYER1 + playerid].end();

	for (iter; iter != iter_end; ++iter)
	{
		dynamic_cast<Player*>(*iter)->GetKeyUp(key);
	}

	KeyCheck(key);
}

void Scene::KeyCheck(unsigned char key)
{

}

void Scene::Release()
{
	
}