#pragma once
#include "Object.h"

class Player : public Object
{
public:
	Player();
	virtual ~Player();

private:
	string ID;

public:
	void SetID(string id);

	virtual void update(float elapsedTime);
	void GetKey(unsigned char key);
	void GetKeyUp(unsigned char key);

	void AddBullet();
};