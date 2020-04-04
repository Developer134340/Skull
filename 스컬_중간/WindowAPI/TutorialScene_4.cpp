#include "stdafx.h"
#include "TutorialScene_4.h"

HRESULT TutorialScene_4::init()
{
	_player->getPlayerClass()->setPlayerPositionX(100);
	_player->getPlayerClass()->setPlayerPositionY(WINSIZEY / 2 + 110);
	_player->getPlayerClass()->setImagePositionX(0);
	_player->getPlayerClass()->setImagePositionY(0);
	_player->getPlayerClass()->setDirectionRight();

	_player->getPlayerClass()->setPixelMap(IMAGEMANAGER->findImage("TUTORIAL_4_MAP_PIXEL"));

	_gate = new gate;
	POINT temp;
	temp.x = 2300;
	temp.y = 545;
	_gate->init("NOMAL_GATE", temp);

	object* _object1;
	_object1 = new object;
	_object1->init("TENT_A", { 1200, WINSIZEY - 180 });
	_vObject.push_back(_object1);

	object* _object2;
	_object2 = new object;
	_object2->init("FENCE_B", { 1400, WINSIZEY - 180 });
	_vObject.push_back(_object2);

	object* _object3;
	_object3 = new object;
	_object3->init("FLAG_B", { 1500, WINSIZEY - 180 });
	_vObject.push_back(_object3);

	_FadeOut = false;
	_FadeIn = true;

	_Alpha = 255;

	return S_OK;
}

void TutorialScene_4::release()
{
}

void TutorialScene_4::update()
{
	if (!_FadeOut && !_FadeIn)
	{
		_player->setPlayerPositionBefore(_player->getPlayerClass()->getPlayerPosition());
		_player->update();
		_player->camMove(IMAGEMANAGER->findImage("TUTORIAL_4_MAP"));
	}

	for (int i = 0; i < _vObject.size(); i++)
	{
		_vObject[i]->update(_player->getPlayerClass()->getImagePosition());
		_vObject[i]->crashObject(_player->getPlayerClass()->getRc(), _player->getPlayerClass()->DMG(_vObject[i]->getObjectRect()), _player->getPlayerClass()->getDirection());
		makePotion(_vObject[i]);
	}
	healHp();

	POINT temp = _player->getPlayerClass()->getImagePosition();

	for (int i = 0; i < _vPotion.size(); i++)
	{
		_vPotion[i]->update(temp);
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
			SCENEMANAGER->loadScene("Tutorial_5", _player);
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
	
	minimapUpdate(IMAGEMANAGER->findImage("TUTORIAL_4_MAP"), IMAGEMANAGER->findImage("MINI_TUTORIAL_4"));
}

void TutorialScene_4::render()
{
	IMAGEMANAGER->findImage("TUTORIAL_BG_BACK")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("TUTORIAL_BG_BACK")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("TUTORIAL_BG_MIDDLE")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("TUTORIAL_BG_MIDDLE")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("TUTORIAL_BG_FRONT")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("TUTORIAL_BG_FRONT")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("TUTORIAL_4_MAP")->render(getMemDC(), _player->getPlayerClass()->getImagePosition().x, _player->getPlayerClass()->getImagePosition().y - (IMAGEMANAGER->findImage("TUTORIAL_4_MAP")->getHeight() - WINSIZEY));

	_gate->render();

	for (int i = 0; i < _vObject.size(); i++)
	{
		_vObject[i]->render();
	}
	for (int i = 0; i < _vPotion.size(); i++)
	{
		_vPotion[i]->render();
	}

	minimapRender(IMAGEMANAGER->findImage("MINI_TUTORIAL_4"));

	_player->render();

	if (_FadeOut || _FadeIn)
	{
		IMAGEMANAGER->alphaRender("BLACK", getMemDC(), _Alpha);
	}
}

void TutorialScene_4::healHp()
{
	RECT temp;
	for (int i = 0; i < _vPotion.size(); i++)
	{
		if (IntersectRect(&temp, &_player->getPlayerClass()->getPlayerRc(), &_vPotion[i]->getPotionRc()))
		{
			_player->getPlayerClass()->setPlayerHp(_player->getPlayerClass()->getPlayerHp() + (int)(_player->getPlayerClass()->getPlayerHp() * _vPotion[i]->getPotionPercent()));
			if (_player->getPlayerClass()->getPlayerHp() >= _player->getPlayerClass()->getMaxHP()) { _player->getPlayerClass()->setPlayerHp(_player->getPlayerClass()->getMaxHP()); }
			_vPotion.erase(_vPotion.begin() + i);
		}
	}
}

void TutorialScene_4::makePotion(object * _object)
{
	if (_object->getObjectState() == CRUSHED && _object->getObjectPotionDrop())
	{
		potion* pTemp = new potion;
		pTemp->init(_object->getObjectPotionSize(), PointMake(_object->getObjectRect().left + (_object->getObjectRect().right - _object->getObjectRect().left) / 2, _object->getObjectRect().bottom));
		_vPotion.push_back(pTemp);
		_object->setObjectPotionDrop(false);
	}
}

void TutorialScene_4::minimapUpdate(image* originalField, image* minimapField)
{
	minimapRc = RectMake(WINSIZEX - 246, WINSIZEY - 146, 206, 110);
	minimapPlayerRc = RectMake(-6 +
		minimapRc.left + (minimapField->getWidth()*(-(_player->getPlayerClass()->getImagePosition().x) + _player->getPlayerClass()->getPlayerPosition().x)) / originalField->getWidth(),
		((originalField->getHeight() - WINSIZEY) * ((float)minimapField->getHeight() / (float)originalField->getHeight())) +
		minimapRc.top + (minimapField->getHeight()*(-(_player->getPlayerClass()->getImagePosition().y) + _player->getPlayerClass()->getPlayerPosition().y)) / originalField->getHeight() + 4, 8, 15);

	minimapGateRc = RectMake(
		minimapRc.left + (minimapField->getWidth()*(-(_player->getPlayerClass()->getImagePosition().x) + _gate->getGateRect().left)) / originalField->getWidth(),
		((originalField->getHeight() - WINSIZEY) * ((float)minimapField->getHeight() / (float)originalField->getHeight())) +
		minimapRc.top + (minimapField->getHeight()*(-(_player->getPlayerClass()->getImagePosition().y) + _gate->getGateRect().bottom)) / originalField->getHeight() - 6, 15, 20);
}

void TutorialScene_4::minimapRender(image* minimapField)
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