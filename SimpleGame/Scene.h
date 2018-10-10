#pragma once

class Object;

class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	virtual HRESULT Initialize();
	virtual void Update(float elapsedTime) = 0;
	virtual void Render();
	virtual void Release();

	void GetKey(unsigned char key,int playerid);
	void GetKeyUp(unsigned char key, int playerid);
	void KeyCheck(unsigned char key);

public:
	list<Object*>&	GetvecObj(ObjType type)
	{
		return m_vecObj[type];
	}
};
