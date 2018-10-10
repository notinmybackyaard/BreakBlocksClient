#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet() {}
Bullet::~Bullet() {}

void Bullet::SetType(ObjType tType) {
	if (tType == OBJ_BULLET1) {
		Object::SetType(OBJ_BULLET1);
	}
	else if (tType == OBJ_BULLET2) {
		Object::SetType(OBJ_BULLET2);
	}
	else if (tType == OBJ_BULLET3) {
		Object::SetType(OBJ_BULLET3);
	}
}

void Bullet::update(float elapsedTime) {
	float elapsedTimeInSecond = elapsedTime / 1000.f;

	xy.x += Vxy.x * elapsedTimeInSecond;
	xy.y += Vxy.y * elapsedTimeInSecond;

	if (xy.x > WINDOWSIZEX / 2 || xy.x < -WINDOWSIZEX / 2 || xy.y > WINDOWSIZEY / 2 || xy.y < -WINDOWSIZEY / 2) {
		SetDead();
	}
}