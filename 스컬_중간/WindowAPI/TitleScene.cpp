#include "stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init()
{
	_player = new Player;
	_player->init();

	_loopX = 0;
	_skulFrameCount = 0;
	SOUNDMANAGER->play("TITLE_BGM");

	return S_OK;
}

void TitleScene::release()
{
}

void TitleScene::update()
{
	SOUNDMANAGER->update();

	if (IMAGEMANAGER->findImage("TITLE_BACK_CASTLE")->getX() != 0)
	{
		IMAGEMANAGER->findImage("TITLE_BACK_CASTLE")->setX(IMAGEMANAGER->findImage("TITLE_BACK_CASTLE")->getX() + 4);
	}
	if (IMAGEMANAGER->findImage("TITLE_FRONT_CASTLE")->getX() != 0)
	{
		IMAGEMANAGER->findImage("TITLE_FRONT_CASTLE")->setX(IMAGEMANAGER->findImage("TITLE_FRONT_CASTLE")->getX() + 4);
	}
	if (IMAGEMANAGER->findImage("TITLE_GROUND")->getX() != 0)
	{
		IMAGEMANAGER->findImage("TITLE_GROUND")->setX(IMAGEMANAGER->findImage("TITLE_GROUND")->getX() + 2);
	}

	_loopX += 2;

	_skulFrameCount++;
	if (_skulFrameCount == 48)		_skulFrameCount = 0;
	IMAGEMANAGER->findImage("TITLE_SKUL")->setFrameX(_skulFrameCount / 8);

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SOUNDMANAGER->stop("TITLE_BGM");
		SCENEMANAGER->loadScene("Field_2", _player);
	}
}

void TitleScene::render()
{
	IMAGEMANAGER->findImage("TITLE_BG")->render(getMemDC());
	IMAGEMANAGER->findImage("TITLE_BACK_CASTLE")->render(getMemDC(), 
		IMAGEMANAGER->findImage("TITLE_BACK_CASTLE")->getX(), 
		IMAGEMANAGER->findImage("TITLE_BACK_CASTLE")->getY());
	RECT _winRc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("TITLE_CLOUD")->loopRender(getMemDC(), &_winRc, _loopX, 0);
	IMAGEMANAGER->findImage("TITLE_FRONT_CASTLE")->render(getMemDC(),
		IMAGEMANAGER->findImage("TITLE_FRONT_CASTLE")->getX(),
		IMAGEMANAGER->findImage("TITLE_FRONT_CASTLE")->getY());
	IMAGEMANAGER->findImage("TITLE_LOGO")->render(getMemDC(), (WINSIZEX / 2) - 160, 100);
	IMAGEMANAGER->findImage("TITLE_GROUND")->render(getMemDC(),
		IMAGEMANAGER->findImage("TITLE_GROUND")->getX(),
		IMAGEMANAGER->findImage("TITLE_GROUND")->getY());
	IMAGEMANAGER->findImage("TITLE_SKUL")->frameRender(getMemDC(), 
		IMAGEMANAGER->findImage("TITLE_GROUND")->getX() + (WINSIZEX / 2) - 50, WINSIZEY - 263);
}