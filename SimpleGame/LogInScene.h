#pragma once
#include "Scene.h"

class LogInScene
	: public Scene
{
public:
	LogInScene();
	virtual ~LogInScene();

private:

private:
	virtual HRESULT Initialize();
	virtual void Update(float elapsedTime);
	virtual void Render();
	virtual void Release();
};