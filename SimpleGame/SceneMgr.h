#pragma once

class Scene;
class Object;
class Renderer;

class SceneMgr
{
	CREATE_SINGLETON(SceneMgr)
private:
	SceneMgr();
public:
	~SceneMgr();

private:
	Scene*			m_Scene;		// 씬 관리를 위한 씬
	SceneType		m_CurSceneType;
	Renderer*		m_Renderer;		// 윈도우를 그리기위한 렌더러

public:
	void Initialize();
	void Update(float elapsedTime);
	void Render();
	void Release();

public:
	void SetScene(SceneType _SceneType);
	void ChangeScene(SceneType _SceneType);
	void GetKey(unsigned char key , int playerid);
	void GetKeyUp(unsigned char key , int playerid);

public:
	list<Object*>& GetvecObj(ObjType type);
	void setRenderer(Renderer* _Renderer)
	{
		m_Renderer = _Renderer;
	}
	SceneType GetCurSceneType()
	{
		return m_CurSceneType;
	}
};