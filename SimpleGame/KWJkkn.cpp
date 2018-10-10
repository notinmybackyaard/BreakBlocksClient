#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Define.h"
#include "SceneMgr.h"
#include "ErrorFnc.h"
#include "Block.h"
#include "Bullet.h"

DWORD prevTime = 0;

SOCKET sock;

list<Object*> m_vecObj[OBJ_END];

DataType m_dataTypeInfo;

CFromServerData ServerData;

// 다른 클라이언트의 총알 패킷
CBulletData BulletData;

// 내 클라이언트의 보낼 총알 패킷
CBulletData myBulletData;

StartPacket startInfo;

DataType dataTypeInfo;

CBlockData BlockInfo;

CItemData ItemData;

GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변수
GLuint textures[8];

int PlayerID;
int startDataCnt = 0;

void Initialize() {
	myBulletData.BulletInfo.Type = OBJ_BULLET1;
};

void AddBlock(CBlockData bi) {
	for (int i = 0; i < 9; i++) {
		Object* pObj = new Block;
		pObj->SetPosition(Vec2(-400.f + (i * 100.f), WINDOWSIZEY));
		pObj->SetVector(Vec2(0.f, BLOCKSPEED));
		pObj->SetType(bi.Type[i]);
		dynamic_cast<Block*>(pObj)->SetItemType(bi.ItemType[i]);

		if (bi.Type[i] == OBJ_BLOCK1)
			pObj->SetInfo(1, 90, Vec4(0, 0, 0, 0));
		else if (bi.Type[i] == OBJ_BLOCK2)
			pObj->SetInfo(3, 90, Vec4(0, 0, 0, 0));
		else  if (bi.Type[i] == OBJ_BLOCK3)
			pObj->SetInfo(6, 90, Vec4(0, 0, 0, 0));
		else if (bi.Type[i] == OBJ_BLOCK4)
			pObj->SetInfo(10, 90, Vec4(0, 0, 0, 0));
		else if (bi.Type[i] == OBJ_BLOCK5)
			pObj->SetInfo(15, 90, Vec4(0, 0, 0, 0));

		m_vecObj[bi.Type[i]].push_back(pObj);
	}
}

void AddBullet(Vec2 Pos,ObjType type) {
	Object* pObj = new Bullet;
	pObj->SetPosition(Vec2(Pos.x, Pos.y));
	pObj->SetVector(Vec2(0.f, BULLETSPEED));
	if(type == OBJ_BULLET1)
		pObj->SetInfo(1, 5, Vec4(0.0f, 1.0f, 1.f, 1.f));
	else if (type == OBJ_BULLET2)
		pObj->SetInfo(2, 5, Vec4(1.0f, 0.5f, 0.5f, 1.f));
	else if (type == OBJ_BULLET3)
		pObj->SetInfo(3, 5, Vec4(1.0f, 0.2f, 1.0f, 1.f));
	pObj->SetType(type);

	SceneMgr::GetInstance()->GetvecObj(type).push_back(pObj);
}

int recvn(SOCKET s, char *buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);
}


DWORD WINAPI ProcessServer(LPVOID arg) {

	int retval = 0;
	while (1) {
		retval = recvn(sock, (char *)&m_dataTypeInfo, sizeof(m_dataTypeInfo), 0);
		if (retval == SOCKET_ERROR) {
			//err_display("recv()");
		}

		if (m_dataTypeInfo == DATA_PLAYER) {	// 데이터 타입이 플레이어인경우
			ServerPacketInfo firstData[3];
			retval = recvn(sock, (char *)&firstData, sizeof(firstData) * 3, 0);
			if (retval == SOCKET_ERROR) {
				//err_display("recv()");
				int i = 0;
			}
			else {
				for (int i = 0; i < 3; i++) {
					(*m_vecObj[OBJ_PLAYER1 + i].begin())->SetPosition(firstData[i].Pos);
					(*m_vecObj[OBJ_PLAYER1 + i].begin())->SetLife(firstData[i].life);
					(*m_vecObj[OBJ_PLAYER1 + i].begin())->SetType((ObjType)(OBJ_PLAYER1 + i));

				}
				startDataCnt++;
			}
		}

		else if (m_dataTypeInfo == DATA_START) {	// 데이터 타입이 스타트 패킷인경우
			retval = recvn(sock, (char *)&startInfo, sizeof(startInfo), 0);
			if (retval == SOCKET_ERROR) {
				//err_display("recv()");
			}
			else {
				PlayerID = startInfo.playerNum;
				startDataCnt++;
			}
		}

		if (startDataCnt >= 2) {
			break;
		}
	}

	SceneMgr::GetInstance()->ChangeScene(SCENE_WAIT);

	while (1) {
		retval = recvn(sock, (char *)&m_dataTypeInfo, sizeof(m_dataTypeInfo), 0);
		if (retval == SOCKET_ERROR) {
			//err_display("recv()");
		}
		if (m_dataTypeInfo == DATA_PLAYER) {	// 데이터 타입이 플레이어인경우

			retval = recvn(sock, (char *)&ServerData, sizeof(ServerData), 0);
			if (retval == SOCKET_ERROR) {
				//err_display("recv()");
			}
			else {
				for (int i = 0, num = 0; i < 3; i++) {
					if (i == PlayerID)
						continue;
					(*m_vecObj[OBJ_PLAYER1 + i].begin())->SetPosition(ServerData.PlayerInfo[num].Pos);
					(*m_vecObj[OBJ_PLAYER1 + i].begin())->SetLife(ServerData.PlayerInfo[num].life);
					++num;
				}
			}
		}
		else if (m_dataTypeInfo == DATA_BLOCK) {
			retval = recvn(sock, (char *)&BlockInfo, sizeof(BlockInfo), 0);
			if (retval == SOCKET_ERROR) {
				//err_display("recv()");
			}
			AddBlock(BlockInfo);
		}
		else if (m_dataTypeInfo == DATA_BULLET) {
			retval = recvn(sock, (char *)&BulletData, sizeof(BulletData), 0);
			if (retval == SOCKET_ERROR) {
				//err_display("recv()");
			}
			AddBullet(BulletData.BulletInfo.Pos,BulletData.BulletInfo.Type);
		}
		else if (m_dataTypeInfo == DATA_EXIT) {
			closesocket(sock);
			SceneMgr::GetInstance()->Destroy();
			exit(1);
		}
	}
	return 0;
}

void RenderScene(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	DWORD curTime = timeGetTime();
	DWORD elapsedTime = curTime - prevTime;
	prevTime = curTime;

	SceneMgr::GetInstance()->Update(elapsedTime);
	SceneMgr::GetInstance()->Render();

	glutSwapBuffers();
}

void Update(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	if ((*m_vecObj[OBJ_PLAYER1 + PlayerID].begin())->IsDead()) {
		RenderScene();
		return;
	}

	SceneMgr::GetInstance()->GetKey(key,PlayerID);

	RenderScene();
}

void KeyInputUp(unsigned char key, int x, int y)
{
	int retval = 0;

	if ((*m_vecObj[OBJ_PLAYER1 + PlayerID].begin())->IsDead()) {
		RenderScene();
		return;
	}


	SceneMgr::GetInstance()->GetKeyUp(key,PlayerID);

	if (key == 'k') {
		dataTypeInfo = DATA_BULLET;
		retval = send(sock, (char *)&dataTypeInfo, sizeof(dataTypeInfo), 0);
		if (retval == SOCKET_ERROR) {
			//err_display("send()");
		}

		myBulletData.BulletInfo.Pos = (*m_vecObj[OBJ_PLAYER1 + PlayerID].begin())->xy;

		retval = send(sock, (char *)&myBulletData, sizeof(myBulletData), 0);
		if (retval == SOCKET_ERROR) {
			//err_display("send()");
		}
	}

	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-(WINDOWSIZEX / 2), (WINDOWSIZEX / 2), -(WINDOWSIZEY / 2), (WINDOWSIZEY / 2));
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOWSIZEX, WINDOWSIZEY);
	glutCreateWindow("NetworkGameProgamming");
	SOCKET server_sock;
	SOCKADDR_IN serveraddr;
	HANDLE hThread;
	int addrlen;

	glewInit();

	hThread = CreateThread(NULL, 0, ProcessServer, 0, 0, NULL);

	CloseHandle(hThread);

	// Initialize Renderer
	Initialize();
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Update);
	glutKeyboardFunc(KeyInput);
	glutKeyboardUpFunc(KeyInputUp);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	glutReshapeFunc(Reshape);

	prevTime = timeGetTime();
	
	glutMainLoop();

    return 0;
}

