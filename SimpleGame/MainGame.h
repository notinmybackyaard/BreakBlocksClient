#pragma once

class MainGame
{
public:
	MainGame();
	~MainGame();

private:

public:
	void Initialize();
	int Update(float elapsedTime);
	void Render();
	void Release();

	void KeyInput(unsigned char key);
};