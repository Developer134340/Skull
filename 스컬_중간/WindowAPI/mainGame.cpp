#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();

	//�̰����� �ʱ�ȭ�� �Ѵ�
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

	//����� ����
	SCENEMANAGER->loadScene("Loading");

	return S_OK;
}

//=============================================================
//	## ���� ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
	//�̹��� Ŭ������ ���������� ����� �� ����
	//�����Ҵ� new�� ����ߴٸ� �̰����� SAFE_DELETE() ����Ѵ�
}


//=============================================================
//	## ������Ʈ ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�
	//�����ϰ� �̰����� �ڵ��Ѵٰ� �����ϸ� �ȴ�
	
	//���Ŵ��� ������Ʈ
	SCENEMANAGER->update();
}

//=============================================================
//	## ���� ## render(HDC hdc)
//=============================================================
void mainGame::render()
{
	//��� �� ��Ʈ�� (�̰͵� ������ �׳� �α�)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================

	//���Ŵ��� ����
	SCENEMANAGER->render();

//=============================================================
	//������� ������ HDC�� �׸��� (�̰͵� ������ �׳� �α�)
	this->getBackBuffer()->render(getHDC());
}