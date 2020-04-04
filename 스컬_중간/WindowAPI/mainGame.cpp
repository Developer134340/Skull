#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## 초기화 ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();

	//이곳에서 초기화를 한다
	SCENEMANAGER->addScene("Loading", new LoadingScene);
	SCENEMANAGER->addScene("Title", new TitleScene);
	SCENEMANAGER->addScene("Opening", new OpeningScene);
	SCENEMANAGER->addScene("Start", new StartMapScene);
	SCENEMANAGER->addScene("Tutorial_1", new TutorialScene_1);
	SCENEMANAGER->addScene("Tutorial_2", new TutorialScene_2);
	SCENEMANAGER->addScene("Tutorial_3", new TutorialScene_3);
	SCENEMANAGER->addScene("Tutorial_4", new TutorialScene_4);
	SCENEMANAGER->addScene("Tutorial_5", new TutorialScene_5);
	SCENEMANAGER->addScene("Field_1", new FieldScene_1);
	SCENEMANAGER->addScene("Field_2", new FieldScene_2);
	SCENEMANAGER->addScene("Shop", new ShopScene);
	SCENEMANAGER->addScene("Item", new ItemScene);
	SCENEMANAGER->addScene("Skull", new SkullScene);
	SCENEMANAGER->addScene("BossReadyScene", new BossReadyScene);
	SCENEMANAGER->addScene("BossScene", new BossScene);

	//현재씬 설정
	SCENEMANAGER->loadScene("Loading");

	return S_OK;
}

//=============================================================
//	## 해제 ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
	//이미지 클래스를 나갈때까진 사용할 일 없다
	//동적할당 new를 사용했다면 이곳에서 SAFE_DELETE() 사용한다
}


//=============================================================
//	## 업데이트 ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다
	//간단하게 이곳에서 코딩한다고 생각하면 된다
	
	//씬매니져 업데이트
	SCENEMANAGER->update();
}

//=============================================================
//	## 렌더 ## render(HDC hdc)
//=============================================================
void mainGame::render()
{
	//흰색 빈 비트맵 (이것도 렌더에 그냥 두기)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================

	//씬매니져 렌더
	SCENEMANAGER->render();

//=============================================================
	//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 두기)
	this->getBackBuffer()->render(getHDC());
}