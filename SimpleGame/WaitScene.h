#pragma once
#include "Scene.h"
#include "Dependencies\glew.h"
#include "Dependencies\glut.h"

class WaitScene
	: public Scene
{
public:
	WaitScene();
	virtual ~WaitScene();

private:

private:
	virtual HRESULT Initialize();
	virtual void Update(float elapsedTime);
	virtual void Render();
	virtual void Release();
};
