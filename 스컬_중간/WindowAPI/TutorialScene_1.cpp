#include "stdafx.h"
#include "TutorialScene_1.h"

HRESULT TutorialScene_1::init()
{
	_player->getPlayerClass()->setPlayerPositionX(100);
	_player->getPlayerClass()->setPlayerPositionY(WINSIZEY / 2 + 110);
	_player->getPlayerClass()->setImagePositionX(0);
	_player->getPlayerClass()->setImagePositionY(0);
	_player->getPlayerClass()->setDirectionRight();

	_player->getPlayerClass()->setPixelMap(IMAGEMANAGER->findImage("TUTORIAL_1_MAP_PIXEL"));

	_gate = new gate;
	POINT temp;
	temp.x = 2700;
	temp.y = 545;
	_gate->init("NOMAL_GATE", temp);

	_Collision = false;
	_NoWeapon = false;
	_FadeOut = false;
	_FadeIn = true;

	_FingerCount = 0;
	_WeaponSkullCount = 0;
	_WeaponGetCount = 0;

	_Alpha = 255;

	return S_OK;
}

void TutorialScene_1::release()
{
}

void TutorialScene_1::update()
{
	if (!_Collision && !_FadeOut && !_FadeIn)
	{
		_player->setPlayerPositionBefore(_player->getPlayerClass()->getPlayerPosition());
		_player->update();
		_player->camMove(IMAGEMANAGER->findImage("TUTORIAL_1_MAP"));
		_WeaponSkullRc = RectMake(2145 + _player->getPlayerClass()->getImagePosition().x, 93 + _player->getPlayerClass()->getImagePosition().y, 130, 60);
	}

	RECT temp;
	RECT rc = RectMake(_player->getPlayerClass()->getRc().left, _player->getPlayerClass()->getRc().top, 70, 70);
	if (IntersectRect(&temp, &_WeaponSkullRc, &rc) && _NoWeapon == false)
	{
		_player->getPlayerClass()->setStat(대기);
		_player->getPlayerClass()->setWeapon();
		_Collision = true;
	}

	_FingerCount++;
	if (_FingerCount == 32)		_FingerCount = 0;
	IMAGEMANAGER->findImage("FINGER_SKULL")->setFrameX(_FingerCount / 8);

	if (_Collision)
	{
		if (_WeaponSkullCount < 47)		_WeaponSkullCount++;
		else
		{
			_WeaponGetCount++;
			if (_WeaponGetCount == 80)
			{
				_WeaponGetCount = 79;
				_Collision = false;
			}
			else if (_WeaponGetCount == 40)
			{
				_NoWeapon = true;
			}
			IMAGEMANAGER->findImage("WEAPON_GET")->setFrameX(_WeaponGetCount / 8);
		}
		IMAGEMANAGER->findImage("WEAPON_SKULL")->setFrameX(_WeaponSkullCount / 8);
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
			SCENEMANAGER->loadScene("Tutorial_2", _player);
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

	minimapUpdate(IMAGEMANAGER->findImage("TUTORIAL_1_MAP"), IMAGEMANAGER->findImage("MINI_TUTORIAL_1"));
}

void TutorialScene_1::render()
{
	IMAGEMANAGER->findImage("TUTORIAL_BG_BACK")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("TUTORIAL_BG_BACK")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("TUTORIAL_BG_MIDDLE")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("TUTORIAL_BG_MIDDLE")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("TUTORIAL_BG_FRONT")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("TUTORIAL_BG_FRONT")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("TUTORIAL_1_MAP")->render(getMemDC(), _player->getPlayerClass()->getImagePosition().x, _player->getPlayerClass()->getImagePosition().y - (IMAGEMANAGER->findImage("TUTORIAL_1_MAP")->getHeight() - WINSIZEY));

	if (_Collision)
	{
		IMAGEMANAGER->findImage("WEAPON_GET")->frameRender(getMemDC(), 2094 + _player->getPlayerClass()->getImagePosition().x, 86 + _player->getPlayerClass()->getImagePosition().y);
	}
	if (_NoWeapon)
	{
		IMAGEMANAGER->findImage("NO_WEAPON_SKULL")->render(getMemDC(), _WeaponSkullRc.left - 3, _WeaponSkullRc.top);
	}
	else
	{
		IMAGEMANAGER->findImage("WEAPON_SKULL")->frameRender(getMemDC(), _WeaponSkullRc.left - 3, _WeaponSkullRc.top);
	}

	IMAGEMANAGER->findImage("FINGER_SKULL")->frameRender(getMemDC(), 3145 + _player->getPlayerClass()->getImagePosition().x, 20 + _player->getPlayerClass()->getImagePosition().y);

	_gate->render();

	minimapRender(IMAGEMANAGER->findImage("MINI_TUTORIAL_1"));

	if (!_Collision)
	{
		_player->render();
	}

	if (_FadeOut || _FadeIn)
	{
		IMAGEMANAGER->alphaRender("BLACK", getMemDC(), _Alpha);
	}
}

void TutorialScene_1::minimapUpdate(image* originalField, image* minimapField)
{
	minimapRc = RectMake(WINSIZEX - 246, WINSIZEY - 146, 206, 110);

	POINT playerPos;
	playerPos.x = _player->getPlayerClass()->getPlayerPosition().x - ((_player->getPlayerClass()->getPlayerRc().right - _player->getPlayerClass()->getPlayerRc().left) / 2);
	playerPos.y = _player->getPlayerClass()->getPlayerPosition().y + ((_player->getPlayerClass()->getPlayerRc().bottom - _player->getPlayerClass()->getPlayerRc().top) / 2);

	minimapPlayerRc = RectMake(-5 +
		minimapRc.left + (minimapField->getWidth()*(-(_player->getPlayerClass()->getImagePosition().x) + playerPos.x)) / originalField->getWidth(),
		((originalField->getHeight() - WINSIZEY) * ((float)minimapField->getHeight() / (float)originalField->getHeight())) +
		minimapRc.top + (minimapField->getHeight()*(-(_player->getPlayerClass()->getImagePosition().y) + playerPos.y)) / originalField->getHeight() + 20, 8, 15);

	minimapGateRc = RectMake(
		minimapRc.left + (minimapField->getWidth()*(-(_player->getPlayerClass()->getImagePosition().x) + _gate->getGateRect().left)) / originalField->getWidth(),
		((originalField->getHeight() - WINSIZEY) * ((float)minimapField->getHeight() / (float)originalField->getHeight())) +
		minimapRc.top + (minimapField->getHeight()*(-(_player->getPlayerClass()->getImagePosition().y) + _gate->getGateRect().bottom)) / originalField->getHeight() + 12, 15, 20);
}

void TutorialScene_1::minimapRender(image* minimapField)
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
