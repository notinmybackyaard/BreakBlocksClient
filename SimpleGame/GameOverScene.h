#pragma once
#include "Scene.h"

class GameOverScene
	: public Scene
{
public:
	GameOverScene();
	~GameOverScene();

public:
	virtual HRESULT Initialize();
	virtual void Update(float elapsedTime);
	virtual void Render();
	virtual void Release();

};