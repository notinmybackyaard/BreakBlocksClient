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

extern GLubyte *pBytes; // 데이터를 가리킬 포인터
extern BITMAPINFO *info; // 비트맵 헤더 저장할 변수
extern GLuint textures[8];

// 내 클라이언트의 보낼 총알 패킷
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
