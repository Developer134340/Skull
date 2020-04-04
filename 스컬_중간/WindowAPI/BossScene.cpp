#include "stdafx.h"
#include "BossScene.h"

HRESULT BossScene::init()
{
	_player->getPlayerClass()->setPlayerPositionX(500);
	_player->getPlayerClass()->setPlayerPositionY(WINSIZEY / 2 + 180);
	_player->getPlayerClass()->setImagePositionX(0);
	_player->getPlayerClass()->setImagePositionY(0);
	_player->getPlayerClass()->setDirectionRight();

	_player->getPlayerClass()->setPixelMap(IMAGEMANAGER->findImage("BOSS_2_MAP_PIXEL"));

	_player->getPlayerClass()->setWeapon();

	_boss = new Boss;
	_boss->init();
	_boss->setPlayer(_player);

	_FadeOut = false;
	_FadeIn = true;

	_Alpha = 255;

	return S_OK;
}

void BossScene::release()
{
}

void BossScene::update()
{
	if (!_FadeOut && !_FadeIn)
	{
		_player->setPlayerPositionBefore(_player->getPlayerClass()->getPlayerPosition());
		_player->update();
		_player->camMove(IMAGEMANAGER->findImage("BOSS_2_MAP"));
		_boss->update();
	}

	if (_FadeOut)
	{
		_Alpha += 3;
		if (_Alpha == 255)
		{
			_FadeOut = false;
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

void BossScene::render()
{
	IMAGEMANAGER->findImage("BOSS_BG_BACK")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("BOSS_BG_FRONT")->render(getMemDC(), 0, 0);
	
	_boss->render();
	
	IMAGEMANAGER->findImage("BOSS_2_MAP")->render(getMemDC(), _player->getPlayerClass()->getImagePosition().x,
		_player->getPlayerClass()->getImagePosition().y - (IMAGEMANAGER->findImage("BOSS_2_MAP")->getHeight() - WINSIZEY));
	
	_player->render();

	if (_FadeOut || _FadeIn)
	{
		IMAGEMANAGER->alphaRender("BLACK", getMemDC(), _Alpha);
	}
}