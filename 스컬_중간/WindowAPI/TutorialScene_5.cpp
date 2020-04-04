#include "stdafx.h"
#include "TutorialScene_5.h"

HRESULT TutorialScene_5::init()
{
	_player->getPlayerClass()->setWeapon();
	_player->getPlayerClass()->setPlayerPositionX(100);
	_player->getPlayerClass()->setPlayerPositionY(WINSIZEY / 2 + 110);
	_player->getPlayerClass()->setImagePositionX(0);
	_player->getPlayerClass()->setImagePositionY(0);
	_player->getPlayerClass()->setDirectionRight();

	_player->getPlayerClass()->setPixelMap(IMAGEMANAGER->findImage("TUTORIAL_5_MAP_PIXEL"));

	_gate = new gate;
	POINT temp;
	temp.x = 1800;
	temp.y = 545;
	_gate->init("NOTING_GATE", temp);

	_FadeOut = false;
	_FadeIn = true;

	_Alpha = 255;


	_enemyO = new Ogre;
	_enemyO->init();
	POINT tempO;
	tempO.x = 1000;
	tempO.y = 450;
	_enemyO->setPosition(tempO);
	_enemyO->setPlayer(_player);

	return S_OK;
}

void TutorialScene_5::release()
{
}

void TutorialScene_5::update()
{
	if (!_FadeOut && !_FadeIn)
	{
		_player->setPlayerPositionBefore(_player->getPlayerClass()->getPlayerPosition());
		_player->update();
		_player->camMove(IMAGEMANAGER->findImage("TUTORIAL_5_MAP"));
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
			SOUNDMANAGER->stop("TUTORIAL_BGM");
			SCENEMANAGER->loadScene("Field_1", _player);
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

	_enemyO->update();
	minimapUpdate(IMAGEMANAGER->findImage("TUTORIAL_5_MAP"), IMAGEMANAGER->findImage("MINI_TUTORIAL_5"));
}

void TutorialScene_5::render()
{
	IMAGEMANAGER->findImage("TUTORIAL_BG_BACK")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("TUTORIAL_BG_BACK")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("TUTORIAL_BG_MIDDLE")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("TUTORIAL_BG_MIDDLE")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("TUTORIAL_BG_FRONT")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("TUTORIAL_BG_FRONT")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("TUTORIAL_5_MAP")->render(getMemDC(), _player->getPlayerClass()->getImagePosition().x, _player->getPlayerClass()->getImagePosition().y - (IMAGEMANAGER->findImage("TUTORIAL_5_MAP")->getHeight() - WINSIZEY));

	_gate->render();

	_enemyO->render();
	_player->render();

	minimapRender(IMAGEMANAGER->findImage("MINI_TUTORIAL_5"));

	if (_FadeOut || _FadeIn)
	{
		IMAGEMANAGER->alphaRender("BLACK", getMemDC(), _Alpha);
	}
}

void TutorialScene_5::minimapUpdate(image* originalField, image* minimapField)
{
	minimapRc = RectMake(WINSIZEX - 246, WINSIZEY - 146, 206, 110);
	minimapPlayerRc = RectMake(-6 +
		minimapRc.left + (minimapField->getWidth()*(-(_player->getPlayerClass()->getImagePosition().x) + _player->getPlayerClass()->getPlayerPosition().x)) / originalField->getWidth(),
		((originalField->getHeight() - WINSIZEY) * ((float)minimapField->getHeight() / (float)originalField->getHeight())) +
		minimapRc.top + (minimapField->getHeight()*(-(_player->getPlayerClass()->getImagePosition().y) + _player->getPlayerClass()->getPlayerPosition().y)) / originalField->getHeight() - 9, 8, 15);

	minimapGateRc = RectMake(
		minimapRc.left + (minimapField->getWidth()*(-(_player->getPlayerClass()->getImagePosition().x) + _gate->getGateRect().left)) / originalField->getWidth(),
		((originalField->getHeight() - WINSIZEY) * ((float)minimapField->getHeight() / (float)originalField->getHeight())) +
		minimapRc.top + (minimapField->getHeight()*(-(_player->getPlayerClass()->getImagePosition().y) + _gate->getGateRect().bottom)) / originalField->getHeight() - 20, 15, 20);
}

void TutorialScene_5::minimapRender(image* minimapField)
{
	IMAGEMANAGER->findImage("미니맵배경")->alphaRender(getMemDC(), WINSIZEX - 250, WINSIZEY - 150, 100);
	minimapField->render(getMemDC(), minimapRc.left, minimapRc.bottom - minimapField->getHeight());

	HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
	Rectangle(getMemDC(), minimapPlayerRc);
	FillRect(getMemDC(), &minimapPlayerRc, brush);

	HBRUSH Gbrush = CreateSolidBrush(RGB(0, 255, 255));
	Rectangle(getMemDC(), minimapGateRc);
	FillRect(getMemDC(), &minimapGateRc, Gbrush);

	IMAGEMANAGER->findImage("미니맵프레임")->render(getMemDC(), WINSIZEX - 250, WINSIZEY - 150);
}