#include "stdafx.h"
#include "OpeningScene.h"

HRESULT OpeningScene::init()
{
	
	_backImg = IMAGEMANAGER->findImage("OPENING_CASTLE_BACK");
	_middleImg = IMAGEMANAGER->findImage("OPENING_CASTLE_MIDDLE");
	_frontImg = IMAGEMANAGER->findImage("OPENING_CASTLE_FRONT");

	SOUNDMANAGER->play("OPENING_PEACE");

	_isScroll = false;
	_isInvade = false;
	_isCharacterOn = true;
	_fadeOut = false;
	_isReScroll = false;
	_fadeIn = false;

	_count = 0;

	_backLoopX = _frontLoopX = 0;

	_alpha = 0;
	_bgAlpha = 0;

	_ogreFrameCount = 0;
	_druidFrameCount = 0;
	_foxFrameCount = 0;
	_witchFrameCount = 0;
	_skulFrameCount = 0;
	_explosionFrameCount = 0;
	_heroFrameCount = 0;

	for (int i = 0; i < 6; i++)
	{
		INVADE_ENEMY temp;
		temp.img = IMAGEMANAGER->findImage("OPENING_GAURD");
		temp.pos.x = WINSIZEX + RND->range(10, 2000);
		temp.pos.y = 415 + RND->range(-5, 5);
		temp.isPassed = false;
		temp.frameCount = RND->range(0, 63);
		_enemy.push_back(temp);
	}
	for (int i = 0; i < 20; i++)
	{
		INVADE_ENEMY temp;
		temp.img = IMAGEMANAGER->findImage("OPENING_WARRIOR");
		temp.pos.x = WINSIZEX + RND->range(10, 2000);
		temp.pos.y = 515 + RND->range(-5, 5);
		temp.isPassed = false;
		temp.frameCount = RND->range(0, 63);
		_enemy.push_back(temp);
	}

	for (int i = 0; i < 20; i++)
	{
		INVADE_ENEMY temp;
		temp.img = IMAGEMANAGER->findImage("OPENING_ARCHER");
		temp.pos.x = WINSIZEX + RND->range(10, 2000);
		temp.pos.y = 515 + RND->range(-5, 5);
		temp.isPassed = false;
		temp.frameCount = RND->range(0, 47);
		_enemy.push_back(temp);
	}

	return S_OK;
}

void OpeningScene::release()
{
	SAFE_DELETE(_backImg);
	SAFE_DELETE(_middleImg);
	SAFE_DELETE(_frontImg);

	SOUNDMANAGER->stop("OPENING_INVADE");
}

void OpeningScene::update()
{
	SOUNDMANAGER->update();

	_count++;

	if (_count >= 900 && _isInvade == true)
	{
		_explosionFrameCount++;
		if (_explosionFrameCount == 154)		_explosionFrameCount = 153;
		IMAGEMANAGER->findImage("OPENING_EXPLOSION")->setFrameX(_explosionFrameCount / 7);

		if (_explosionFrameCount >= 77)
		{
			_alpha += 10;
			if (_alpha > 255)		_alpha = 255;
		}
	}

	if (_count == 900)
	{
		SOUNDMANAGER->play("OPENING_CRASH");
	}

	if (_count == 1000)
	{
		SOUNDMANAGER->play("OPENING_INVADE");
	}

	if (_count == 300)
	{
		SOUNDMANAGER->stop("OPENING_PEACE");
		SOUNDMANAGER->play("OPENING_VIBRATION");
	}

	if (_count == 450)
	{
		_isScroll = true;
	}

	if (_isScroll)
	{
		if (3840 - WINSIZEX > _frontLoopX)
		{
			_frontLoopX += 6;
			_backLoopX += 4;
		}
		else
		{
			_isScroll = false;
			_isInvade = true;
		}
	}

	if (_isScroll == false && _isInvade == false)
	{
		_ogreFrameCount++;
		if (_ogreFrameCount == 50)		_ogreFrameCount = 0;
		IMAGEMANAGER->findImage("OPENING_OGRE")->setFrameX(_ogreFrameCount / 10);
		_druidFrameCount++;
		if (_druidFrameCount == 50)		_druidFrameCount = 0;
		IMAGEMANAGER->findImage("OPENING_DRUID")->setFrameX(_druidFrameCount / 10);
		_foxFrameCount++;
		if (_foxFrameCount == 50)		_foxFrameCount = 0;
		IMAGEMANAGER->findImage("OPENING_FOX")->setFrameX(_foxFrameCount / 10);
		_witchFrameCount++;
		if (_witchFrameCount == 60)		_witchFrameCount = 0;
		IMAGEMANAGER->findImage("OPENING_WITCH")->setFrameX(_witchFrameCount / 10);
		_skulFrameCount++;
		if (_skulFrameCount == 40)		_skulFrameCount = 0;
		IMAGEMANAGER->findImage("OPENING_SKUL")->setFrameX(_skulFrameCount / 10);
	}

	if (_isInvade && _count > 1000)
	{
		int count = 0;

		_heroFrameCount++;
		if (_heroFrameCount == 56)		_heroFrameCount = 0;
		IMAGEMANAGER->findImage("OPENING_HERO")->setFrameX(_heroFrameCount / 8);

		if (IMAGEMANAGER->findImage("OPENING_HERO")->getX() > WINSIZEX - 300)
		{
			IMAGEMANAGER->findImage("OPENING_HERO")->setX(IMAGEMANAGER->findImage("OPENING_HERO")->getX() - 4);
		}

		for (int i = 0; i < _enemy.size(); i++)
		{	
			if (_enemy[i].isPassed)
			{
				count++;
				continue;
			}
			_enemy[i].frameCount++;
			if (_enemy[i].frameCount == (_enemy[i].img->getMaxFrameX() + 1) * 8)		_enemy[i].frameCount = 0;
			_enemy[i].img->setFrameX(_enemy[i].frameCount / 8);

			_enemy[i].pos.x -= 4;
			if (_enemy[i].pos.x < -300)
			{
				_enemy[i].isPassed = true;
			}
		}

		if (count == _enemy.size())
		{
			_fadeOut = true;
		}
	}

	if (_fadeOut)
	{
		_bgAlpha += 2;
		if (_bgAlpha >= 255)
		{
			_bgAlpha = 255;

			if (_frontLoopX == 0)
			{
				SCENEMANAGER->loadScene("Start", _player);
			}
			_fadeIn = true;
			_fadeOut = false;
			_isInvade = false;
			_backImg = IMAGEMANAGER->findImage("OPENING_BROKEN_CASTLE_BACK");
			_middleImg = IMAGEMANAGER->findImage("OPENING_BROKEN_CASTLE_MIDDLE");
			_frontImg = IMAGEMANAGER->findImage("OPENING_BROKEN_CASTLE_FRONT");
		}
	}

	if (_fadeIn)
	{
		_bgAlpha -= 2;
		if (_bgAlpha <= 0)
		{
			_bgAlpha = 0;
			_fadeIn = false;
			_isReScroll = true;
			_isCharacterOn = false;
		}
	}

	if (_isReScroll)
	{
		_frontLoopX -= 6;
		_backLoopX -= 4;

		if (_frontLoopX <= 0)
		{
			_frontLoopX = 0;
			_backLoopX = 0;
			_isReScroll = false;
			_fadeOut = true;
		}
	}
}

void OpeningScene::render()
{
	RECT winRc = RectMake(0, 0, WINSIZEX, WINSIZEY);

	_backImg->loopRender(getMemDC(), &winRc, _backLoopX, 0);
	_middleImg->loopRender(getMemDC(), &winRc, _frontLoopX, 0);
	_frontImg->loopRender(getMemDC(), &winRc, _frontLoopX, 0);

	if (_isCharacterOn)
	{
		IMAGEMANAGER->frameRender("OPENING_OGRE", getMemDC(), IMAGEMANAGER->findImage("OPENING_OGRE")->getX() - _frontLoopX, IMAGEMANAGER->findImage("OPENING_OGRE")->getY());
		IMAGEMANAGER->frameRender("OPENING_DRUID", getMemDC(), IMAGEMANAGER->findImage("OPENING_DRUID")->getX() - _frontLoopX, IMAGEMANAGER->findImage("OPENING_DRUID")->getY());
		IMAGEMANAGER->frameRender("OPENING_FOX", getMemDC(), IMAGEMANAGER->findImage("OPENING_FOX")->getX() - _frontLoopX, IMAGEMANAGER->findImage("OPENING_FOX")->getY());
		IMAGEMANAGER->frameRender("OPENING_WITCH", getMemDC(), IMAGEMANAGER->findImage("OPENING_WITCH")->getX() - _frontLoopX, IMAGEMANAGER->findImage("OPENING_WITCH")->getY());
		IMAGEMANAGER->frameRender("OPENING_SKUL", getMemDC(), IMAGEMANAGER->findImage("OPENING_SKUL")->getX() - _frontLoopX, IMAGEMANAGER->findImage("OPENING_SKUL")->getY());
	}

	if (_isInvade)
	{
		if (_count >= 900)
		{
			IMAGEMANAGER->findImage("OPENING_EXPLOSION")->alphaFrameRender(getMemDC(), WINSIZEX - 520, (WINSIZEY / 2) - 250, _alpha);

			for (int i = 0; i < _enemy.size(); i++)
			{
				_enemy[i].img->frameRender(getMemDC(), _enemy[i].pos.x, _enemy[i].pos.y);
			}
			IMAGEMANAGER->frameRender("OPENING_HERO", getMemDC(), IMAGEMANAGER->findImage("OPENING_HERO")->getX(), IMAGEMANAGER->findImage("OPENING_HERO")->getY());
		}
	}

	if (_fadeOut || _fadeIn)
	{
		IMAGEMANAGER->alphaRender("BLACK", getMemDC(), _bgAlpha);
	}
}