#pragma once

#include "singletonBase.h"

//=============================================================
//	## sceneManager ## (���Ŵ���)
//=============================================================

//�̱����� ��ӹ��� ���̵��� static���� ����� ���⶧����
//�Ϲ�Ŭ������ ���ӳ�带 ����Ϸ��� �ϸ� ������

//���ӳ�� Ŭ���� ���漱��
class gameNode;
class Player;



class sceneManager : public singletonBase <sceneManager>
{
private:
	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:
	//map<string, gameNode*> _mSceneList;
	mSceneList _mSceneList;		//������ ��(ȭ��)���� ��Ƶ� ��
	gameNode* _currentScene;	//�����

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//���߰�
	gameNode* addScene(string sceneName, gameNode* scene);
	//������ (�ش�� �ε�)
	HRESULT loadScene(string sceneName);

	HRESULT loadScene(string sceneName, Player* pl);

	HDC getCurrentDC();
	//��Ʈ ����
	void settingFont(gameNode * Scene);

	sceneManager() : _currentScene(NULL) {}
	~sceneManager() {}
};

