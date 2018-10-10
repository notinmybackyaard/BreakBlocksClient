#pragma once

#include "Enum.h"
#include "Struct.h"
#include "Macro.h"

const int PLAYERWIDTH = 26;
const int PLAYERHEIGHT = 36;

extern SOCKET sock;

class Object;
extern list<Object*> m_vecObj[OBJ_END];
extern int PlayerID;
extern DataType dataTypeInfo;

extern GLubyte *pBytes; // �����͸� ����ų ������
extern BITMAPINFO *info; // ��Ʈ�� ��� ������ ����
extern GLuint textures[8];

// �� Ŭ���̾�Ʈ�� ���� �Ѿ� ��Ŷ
extern CBulletData myBulletData;

extern CItemData ItemData;

#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000
#define MAX_OBJECTS_COUNT 200
#define WINDOWSIZEX 800
#define WINDOWSIZEY 800
#define PLAYERSPEED 200
#define BULLETSPEED 800
#define BLOCKSPEED -300
#define ITEMSPEED -100
