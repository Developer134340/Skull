#include "stdafx.h"
#include "TutorialScene_2.h"

HRESULT TutorialScene_2::init()
{
	_player->getPlayerClass()->setPlayerPositionX(100);
	_player->getPlayerClass()->setPlayerPositionY(WINSIZEY / 2 + 110);
	_player->getPlayerClass()->setImagePositionX(0);
	_player->getPlayerClass()->setImagePositionY(0);
	_player->getPlayerClass()->setDirectionRight();

	_player->getPlayerClass()->setPixelMap(IMAGEMANAGER->findImage("TUTORIAL_2_MAP_PIXEL"));

	POINT temp;
	_gate = new gate;
	temp.x = 2180;
	temp.y = 545;
	_gate->init("NOMAL_GATE", temp);

	_cageBack = new object;
	_cageFront = new object;
	temp.x = 1220;
	temp.y = 540;
	_cageBack->init("CAGE_BACK", temp);
	_cageFront->init("CAGE_FRONT", temp);

	_FadeOut = false;
	_FadeIn = true;

	_WitchCount = 0;
	
	_Alpha = 255;

	_Escape = false;

	_enemy = new Archer;
	_enemy->init();
	temp.x = 1250;
	temp.y = 480;
	_enemy->setPosition(temp);
	_enemy->setPlayer(_player);
	


	return S_OK;
}

void TutorialScene_2::release()
{
	
}

void TutorialScene_2::update()
{
	if (!_FadeOut && !_FadeIn)
	{
		_player->setPlayerPositionBefore(_player->getPlayerClass()->getPlayerPosition());
		_player->update();
		_player->camMove(IMAGEMANAGER->findImage("TUTORIAL_2_MAP"));
	}
	_cageBack->update(_player->getPlayerClass()->getImagePosition());
	_cageFront->update(_player->getPlayerClass()->getImagePosition());
	_cageBack->crashObject(_player->getPlayerClass()->getRc(), _player->getPlayerClass()->DMG(_cageBack->getObjectRect()), _player->getPlayerClass()->getDirection());
	_cageFront->crashObject(_player->getPlayerClass()->getRc(), _player->getPlayerClass()->DMG(_cageFront->getObjectRect()), _player->getPlayerClass()->getDirection());

	if (_cageFront->getObjectState() == CRUSHED && _Escape == false)
	{
		_Escape = true;
	}
	
	if (_gate->update(_player->getPlayerClass()->getImagePosition(), _player->getPlayerClass()->getPlayerRc()) && KEYMANAGER->isOnceKeyDown('F') && _Escape)
	{
		_FadeOut = true;
	}

	if (_Escape)
	{
		_WitchCount++;
		if (_WitchCount == 48)		_WitchCount = 0;
		IMAGEMANAGER->findImage("CAGE_WITCH_IDLE")->setFrameX(_WitchCount / 8);
	}

	_enemy->update();

	if (_FadeOut)
	{
		_Alpha += 3;
		if (_Alpha == 255)
		{
			_FadeOut = false;
			SCENEMANAGER->loadScene("Tutorial_3", _player);
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

	minimapUpdate(IMAGEMANAGER->findImage("TUTORIAL_2_MAP"), IMAGEMANAGER->findImage("MINI_TUTORIAL_2"));
}

void TutorialScene_2::render()
{
	IMAGEMANAGER->findImage("TUTORIAL_BG_BACK")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("TUTORIAL_BG_BACK")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("TUTORIAL_BG_MIDDLE")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("TUTORIAL_BG_MIDDLE")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("TUTORIAL_BG_FRONT")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("TUTORIAL_BG_FRONT")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("TUTORIAL_2_MAP")->render(getMemDC(), _player->getPlayerClass()->getImagePosition().x, _player->getPlayerClass()->getImagePosition().y - (IMAGEMANAGER->findImage("TUTORIAL_2_MAP")->getHeight() - WINSIZEY));

	_cageBack->render();
	if (_Escape)
	{
		IMAGEMANAGER->frameRender("CAGE_WITCH_IDLE", getMemDC(), 1330 + _player->getPlayerClass()->getImagePosition().x, 328 + _player->getPlayerClass()->getImagePosition().y);
	}
	else
	{
		IMAGEMANAGER->render("CAGE_WITCH", getMemDC(), 1330 + _player->getPlayerClass()->getImagePosition().x, 388 + _player->getPlayerClass()->getImagePosition().y);
	}

	_cageFront->render();

	if (_Escape)
	{
		_gate->render();
	}
	else
	{
		IMAGEMANAGER->findImage("NOMAL_GATE_LOCK")->render(getMemDC(), 2180 + _player->getPlayerClass()->getImagePosition().x, 289 + _player->getPlayerClass()->getImagePosition().y);
	}

	_enemy->render();
	_player->render();

	minimapRender(IMAGEMANAGER->findImage("MINI_TUTORIAL_2"));

	if (_FadeOut || _FadeIn)
	{
		IMAGEMANAGER->alphaRender("BLACK", getMemDC(), _Alpha);
	}
}

void TutorialScene_2::minimapUpdate(image* originalField, image* minimapField)
{
	minimapRc = RectMake(WINSIZEX - 246, WINSIZEY - 146, 206, 110);
	minimapPlayerRc = RectMake(-6 +
		minimapRc.left + (minimapField->getWidth()*(-(_player->getPlayerClass()->getImagePosition().x) + _player->getPlayerClass()->getPlayerPosition().x)) / originalField->getWidth(),
		((originalField->getHeight() - WINSIZEY) * ((float)minimapField->getHeight() / (float)originalField->getHeight())) +
		minimapRc.top + (minimapField->getHeight()*(-(_player->getPlayerClass()->getImagePosition().y) + _player->getPlayerClass()->getPlayerPosition().y)) / originalField->getHeight() + 5, 8, 15);

	minimapGateRc = RectMake(
		minimapRc.left + (minimapField->getWidth()*(-(_player->getPlayerClass()->getImagePosition().x) + _gate->getGateRect().left)) / originalField->getWidth(),
		((originalField->getHeight() - WINSIZEY) * ((float)minimapField->getHeight() / (float)originalField->getHeight())) +
		minimapRc.top + (minimapField->getHeight()*(-(_player->getPlayerClass()->getImagePosition().y) + _gate->getGateRect().bottom)) / originalField->getHeight() - 5, 15, 20);
}

void TutorialScene_2::minimapRender(image* minimapField)
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