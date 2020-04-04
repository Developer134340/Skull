#include "stdafx.h"
#include "BossReadyScene.h"

HRESULT BossReadyScene::init()
{
	_player->getPlayerClass()->setPlayerPositionX(100);
	_player->getPlayerClass()->setPlayerPositionY(WINSIZEY / 2 + 110);
	_player->getPlayerClass()->setImagePositionX(0);
	_player->getPlayerClass()->setImagePositionY(0);
	_player->getPlayerClass()->setDirectionRight();

	_player->getPlayerClass()->setPixelMap(IMAGEMANAGER->findImage("BOSS_1_MAP_PIXEL"));

	_gate = new gate;
	_gate->init("LASTBOSS_GATE", PointMake(600, 544));

	_FadeOut = false;
	_FadeIn = true;

	_Alpha = 255;

	SOUNDMANAGER->play("BOSS_BGM");

	return S_OK;
}

void BossReadyScene::release()
{
}

void BossReadyScene::update()
{
	if (!_FadeOut && !_FadeIn)
	{
		_player->setPlayerPositionBefore(_player->getPlayerClass()->getPlayerPosition());
		_player->update();
		_player->camMove(IMAGEMANAGER->findImage("BOSS_1_MAP"));
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
			SCENEMANAGER->loadScene("BossScene", _player);
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

void BossReadyScene::render()
{
	IMAGEMANAGER->findImage("BOSS_BG_BACK")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("BOSS_BG_FRONT")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("BOSS_1_MAP")->render(getMemDC(), _player->getPlayerClass()->getImagePosition().x, 
		_player->getPlayerClass()->getImagePosition().y - (IMAGEMANAGER->findImage("BOSS_1_MAP")->getHeight() - WINSIZEY));

	_gate->render();

	_player->render();

	if (_FadeOut || _FadeIn)
	{
		IMAGEMANAGER->alphaRender("BLACK", getMemDC(), _Alpha);
	}
}
