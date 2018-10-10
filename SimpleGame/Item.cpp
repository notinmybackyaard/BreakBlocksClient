#include "stdafx.h"
#include "Item.h"

Item::Item() {}

Item::~Item() {}

void Item::SetType(ObjType tType) {
	if (tType == OBJ_ITEM1) {
		Object::SetType(OBJ_ITEM1);
	}
	else if (tType == OBJ_ITEM2) {
		Object::SetType(OBJ_ITEM2);
	}
}

void Item::update(float elapsedTime) {
	float elapsedTimeInSecond = elapsedTime / 1000.f;

	xy.x += Vxy.x * elapsedTimeInSecond;
	xy.y += Vxy.y * elapsedTimeInSecond;

	if (xy.y < -WINDOWSIZEY / 2) {
		SetDead();
	}
}