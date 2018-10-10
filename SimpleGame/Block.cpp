#include "stdafx.h"
#include "Block.h"
#include "Item.h"

Block::Block() {}

Block::~Block() 
{
	if (ItemType != OBJ_NOITEM)
	{
		Object* Obj = new Item;
		if (ItemType == OBJ_ITEM1)
			Obj->SetInfo(1, 20.f, Vec4(0.f, 1.f, 0.f, 1.f));
		else if (ItemType == OBJ_ITEM2)
			Obj->SetInfo(1, 20.f, Vec4(1.f, 1.f, 0.f, 1.f));
		Obj->SetPosition(xy);
		Obj->SetType(ItemType);
		Obj->SetVector(Vec2(0.f, ITEMSPEED));

		m_vecObj[ItemType].push_back(Obj);
	}
}

void Block::SetType(ObjType tType) {
	if (tType == OBJ_BLOCK1) {
		Object::SetType(OBJ_BLOCK1);
	}
	else if (tType == OBJ_BLOCK2) {
		Object::SetType(OBJ_BLOCK2);
	}
	else if (tType == OBJ_BLOCK3) {
		Object::SetType(OBJ_BLOCK3);
	}
	else if (tType == OBJ_BLOCK4) {
		Object::SetType(OBJ_BLOCK4);
	}
	else if (tType == OBJ_BLOCK5) {
		Object::SetType(OBJ_BLOCK5);
	}
}

void Block::SetItemType(ObjType tType) {
	ItemType = tType;
}
ObjType Block::GetItemType() {
	return ItemType;
}

void Block::update(float elapsedTime) {
	float elapsedTimeInSecond = elapsedTime / 1000.f;

	xy.x += Vxy.x * elapsedTimeInSecond;
	xy.y += Vxy.y * elapsedTimeInSecond;

	if(life > 0 && life <= 1)
		Object::SetType(OBJ_BLOCK1);
	if (life > 1 && life <= 3)
		Object::SetType(OBJ_BLOCK2);
	if (life > 3 && life <= 6)
		Object::SetType(OBJ_BLOCK3);
	if (life > 6 && life <= 10)
		Object::SetType(OBJ_BLOCK4);
	if (life > 10 && life <= 15)
		Object::SetType(OBJ_BLOCK5);

	if (xy.y < -WINDOWSIZEY / 2) {
		SetDead();
	}
}
