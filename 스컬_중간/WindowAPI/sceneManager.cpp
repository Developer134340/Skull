#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h" //�̳� �߰������ ��

HRESULT sceneManager::init()
{
	return S_OK;
}

void sceneManager::release()
{
	//�������� ���
	miSceneList iter = _mSceneList.begin();
	for (;iter != _mSceneList.end();)
	{
		if (iter->second != NULL)
		{
			DeleteObject(SelectObject(iter->second->getMemDC(), iter->second->_oldFont));
			if (iter->second == _currentScene) iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mSceneList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_mSceneList.clear();

	//C++ ��޹���
	//for(auto scene in _mSceneList) ������ ���Ұ�
	//for (auto scene : _mSceneList)
	//{
	//	scene.second->release();
	//	SAFE_DELETE(scene.second);
	//}

}

void sceneManager::update()
{
	//������� �����ϸ� �ش��ϴ� ������� ������Ʈ�ض�
	if (_currentScene) _currentScene->update();
}

void sceneManager::render()
{
	//������� �����ϸ� �ش��ϴ� ������� �����ض�
	if (_currentScene) _currentScene->render();
}

gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
{
	//���� ������ �׳� �� ����
	if (!scene) return NULL;

	settingFont(scene);

	//���� ������ �ʿ� ���
	_mSceneList.insert(make_pair(sceneName, scene));
	//_mSceneList.insert(pair<string, gameNode*>(sceneName, scene));
	return scene;
}

HRESULT sceneManager::loadScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	//��ã�Ҵٸ� E_FAIL
	if (find == _mSceneList.end()) return E_FAIL;

	//�ٲٷ��� ���� ������� ���ٸ� E_FAIL
	if (find->second == _currentScene) return E_FAIL;

	//������� ������ ������ ������ ���� ����ó������
	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}

	return E_FAIL;
}

HRESULT sceneManager::loadScene(string sceneName, Player * pl)
{
	miSceneList find = _mSceneList.find(sceneName);

	//��ã�Ҵٸ� E_FAIL
	if (find == _mSceneList.end()) return E_FAIL;

	//�ٲٷ��� ���� ������� ���ٸ� E_FAIL
	if (find->second == _currentScene) return E_FAIL;

	//������� ������ ������ ������ ���� ����ó������
	find->second->setPlayer(pl);
	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}

	return E_FAIL;
}

HDC sceneManager::getCurrentDC()
{
	if (!_currentScene)		return NULL;
	return _currentScene->getMemDC();
}

void sceneManager::settingFont(gameNode * Scene)
{
	AddFontResourceA("FONT/Oswald-Bold.ttf");
	memset(&Scene->_lf, 0, sizeof(Scene->_lf));
	Scene->_lf.lfHeight = 21;
	Scene->_lf.lfWeight = 1000;
	Scene->_lf.lfOutPrecision = OUT_TT_ONLY_PRECIS;
	strcpy(Scene->_lf.lfFaceName, "Oswald-Bold");

	Scene->_font = CreateFontIndirect(&Scene->_lf);

	Scene->_oldFont = (HFONT)SelectObject(Scene->getMemDC(), Scene->_font);

	SetBkMode(Scene->getMemDC(), TRANSPARENT);
	SetTextColor(Scene->getMemDC(), RGB(93, 73, 56));
}