#include "stdafx.h"
#include "StartMapScene.h"

HRESULT StartMapScene::init()
{
	_player->getPlayerClass()->setPlayerPositionX(400);
	_player->getPlayerClass()->setPlayerPositionY(WINSIZEY / 2 + 110);
	_player->getPlayerClass()->setImagePositionX(0);
	_player->getPlayerClass()->setImagePositionY(0);
	_player->getPlayerClass()->setDirectionRight();

	_player->getPlayerClass()->setPixelMap(IMAGEMANAGER->findImage("START_MAP_PIXEL"));

	SOUNDMANAGER->play("TUTORIAL_BGM");

	_gate = new gate;
	_gate->init("SKULL_GATE", PointMake(1350, 544));

	_FadeOut = false;
	_FadeIn = true;

	_Alpha = 255;

	return S_OK;
}

void StartMapScene::release()
{
	SAFE_DELETE(_gate);
}

void StartMapScene::update()
{
	if (!_FadeOut && !_FadeIn)
	{
		_player->setPlayerPositionBefore(_player->getPlayerClass()->getPlayerPosition());
		_player->update();
		_player->camMove(IMAGEMANAGER->findImage("START_MAP"));
	}

	if (_gate->update(_player->getPlayerClass()->getImagePosition(), _player->getPlayerClass()->getPlayerRc()) && KEYMANAGER->isOnceKeyDown('F'))
	{
		_FadeOut = true;
	}

	if (_FadeOut)
	{
		_Alpha += 3;
		if (_Alpha == 255)
		{
			_FadeOut = false;
			SCENEMANAGER->loadScene("Skull", _player);
		}
	}

	if (_FadeIn)
	{
		_Alpha -= 3;
		if (_Alpha == 0)
		{
			_FadeIn = false;
		}
	}
}

void StartMapScene::render()
{
	IMAGEMANAGER->findImage("START_BG_BACK")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("START_MAP")->render(getMemDC(), _player->getPlayerClass()->getImagePosition().x, 
		_player->getPlayerClass()->getImagePosition().y - (IMAGEMANAGER->findImage("START_MAP")->getHeight() - WINSIZEY));

	_gate->render();
	_player->render();

	if (_FadeOut || _FadeIn)
	{
		IMAGEMANAGER->alphaRender("BLACK", getMemDC(), _Alpha);
	}
}
