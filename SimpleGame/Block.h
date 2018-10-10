#pragma once
#include "Define.h"
#include "Object.h"

class Block : public Object {
public:
	Block();
	virtual ~Block();

public:
	virtual void SetType(ObjType tType);
	virtual void update(float elapsedTime);
	void SetItemType(ObjType tType);
	ObjType Block::GetItemType();
private:
	ObjType ItemType;
};