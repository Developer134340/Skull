#include "stdafx.h"
#include "FieldScene_2.h"

HRESULT FieldScene_2::init()
{
	_player->getPlayerClass()->setPlayerPositionX(100);
	_player->getPlayerClass()->setPlayerPositionY(WINSIZEY / 2 + 45);
	_player->getPlayerClass()->setImagePositionX(0);
	_player->getPlayerClass()->setImagePositionY(0);
	_player->getPlayerClass()->setDirectionRight();

	_player->getPlayerClass()->setPixelMap(IMAGEMANAGER->findImage("FIELD_2_MAP_PIXEL"));

	_player->getPlayerClass()->setWeapon();

	object* _object1;
	_object1 = new object;
	_object1->init("CAULDRON", { 600, WINSIZEY - 240 });
	_vObject.push_back(_object1);

	object* _object2;
	_object2 = new object;
	_object2->init("TENT_C", { 1200, WINSIZEY - 100 });
	_vObject.push_back(_object2);

	object* _object3;
	_object3 = new object;
	_object3->init("TURRET", { 3000, WINSIZEY - 240 });
	_vObject.push_back(_object3);

	//==========================
	EnemyBase* _enemy1 = new Knight;
	_enemy1->init();
	_vEnemy.push_back(_enemy1);
	POINT temp;
	temp.x = 1000;
	temp.y = 420;
	_enemy1->setPosition(temp);
	_enemy1->setPlayer(_player);

	EnemyBase* _enemy2 = new Knight;
	_enemy2->init();
	_vEnemy.push_back(_enemy2);
	POINT temp1;
	temp1.x = 1500;
	temp1.y = WINSIZEY - 160;
	_enemy2->namecall("Knight1");
	_enemy2->setPosition(temp1);
	_enemy2->setPlayer(_player);

	EnemyBase* _enemy3 = new Knight;
	_enemy3->init();
	_vEnemy.push_back(_enemy3);
	POINT temp3;
	temp3.x = 2000;
	temp3.y = WINSIZEY - 150;
	_enemy2->namecall("Knight2");
	_enemy3->setPosition(temp3);
	_enemy3->setPlayer(_player);
	//
	EnemyBase* _enemy4 = new Knight;
	_enemy4->init();
	_vEnemy.push_back(_enemy4);
	POINT temp4;
	temp4.x = 2400;
	temp4.y = WINSIZEY - 140;
	_enemy4->namecall("Knight3");
	_enemy4->setPosition(temp4);
	_enemy4->setPlayer(_player);
	
	EnemyBase* _enemy5 = new GiantTree;
	_enemy5->init();
	_vEnemy.push_back(_enemy5);
	POINT temp5;
	temp5.x = 1533;
	temp5.y = WINSIZEY - 470;
	_enemy5->setPosition(temp5);
	_enemy5->setPlayer(_player);
	

	//
	POINT temp0;
	_gate = new gate;
	temp0.x = 3350;
	temp0.y = 481;
	_gate->init("ITEM_GATE", temp0);

	_FadeOut = false;
	_FadeIn = true;

	_Alpha = 255;


	return S_OK;
}

void FieldScene_2::release()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		SAFE_DELETE(_vEnemy[i]);
	}
}

void FieldScene_2::update()
{
	if (!_FadeOut && !_FadeIn)
	{
		_player->setPlayerPositionBefore(_player->getPlayerClass()->getPlayerPosition());
		_player->update();
		_player->camMove(IMAGEMANAGER->findImage("FIELD_2_MAP"));
	}

	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->update();
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
			SCENEMANAGER->loadScene("Item", _player);
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

	minimapUpdate(IMAGEMANAGER->findImage("FIELD_2_MAP"), IMAGEMANAGER->findImage("MINI_FIELD_2"));
}

void FieldScene_2::render()
{
	IMAGEMANAGER->findImage("TUTORIAL_BG_BACK")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("TUTORIAL_BG_BACK")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("TUTORIAL_BG_MIDDLE")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("TUTORIAL_BG_MIDDLE")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("TUTORIAL_BG_FRONT")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("TUTORIAL_BG_FRONT")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("FIELD_2_MAP")->render(getMemDC(), _player->getPlayerClass()->getImagePosition().x, _player->getPlayerClass()->getImagePosition().y - (IMAGEMANAGER->findImage("FIELD_2_MAP")->getHeight() - WINSIZEY));

	_gate->render();

	for (int i = 0; i < _vObject.size(); i++)
	{
		_vObject[i]->render();
	}

	for (int i = 0; i < _vPotion.size(); i++)
	{
		_vPotion[i]->render();
	}

	_player->render();

	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->render();
	}


	minimapRender(IMAGEMANAGER->findImage("MINI_FIELD_2"));

	if (_FadeOut || _FadeIn)
	{
		IMAGEMANAGER->alphaRender("BLACK", getMemDC(), _Alpha);
	}
}

void FieldScene_2::minimapUpdate(image* originalField, image* minimapField)
{
	minimapRc = RectMake(WINSIZEX - 246, WINSIZEY - 146, 206, 110);

	POINT playerPos;
	playerPos.x = _player->getPlayerClass()->getPlayerPosition().x - ((_player->getPlayerClass()->getPlayerRc().right - _player->getPlayerClass()->getPlayerRc().left) / 2);
	playerPos.y = _player->getPlayerClass()->getPlayerPosition().y + ((_player->getPlayerClass()->getPlayerRc().bottom - _player->getPlayerClass()->getPlayerRc().top) / 2);

	float miniGateWidth = (_gate->getGateRect().right - _gate->getGateRect().left)*((float)minimapField->getHeight() / (float)originalField->getHeight());

	minimapPlayerRc = RectMake(-5 +
		minimapRc.left + (minimapField->getWidth()*(-(_player->getPlayerClass()->getImagePosition().x) + playerPos.x)) / originalField->getWidth(),
		((originalField->getHeight() - WINSIZEY) * ((float)minimapField->getHeight() / (float)originalField->getHeight())) +
		minimapRc.top + (minimapField->getHeight()*(-(_player->getPlayerClass()->getImagePosition().y) + playerPos.y)) / originalField->getHeight() - 5, 8, 15);

	minimapGateRc = RectMake(
		minimapRc.left + (minimapField->getWidth()*(-(_player->getPlayerClass()->getImagePosition().x) + _gate->getGateRect().left)) / originalField->getWidth(),
		((originalField->getHeight() - WINSIZEY) * ((float)minimapField->getHeight() / (float)originalField->getHeight())) +
		minimapRc.top + (minimapField->getHeight()*(-(_player->getPlayerClass()->getImagePosition().y) + _gate->getGateRect().bottom)) / originalField->getHeight() - 12, miniGateWidth, 20);
}

void FieldScene_2::minimapRender(image* minimapField)
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

void FieldScene_2::healHp()
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

void FieldScene_2::makePotion(object * _object)
{
	if (_object->getObjectState() == CRUSHED && _object->getObjectPotionDrop())
	{
		potion* pTemp = new potion;
		pTemp->init(_object->getObjectPotionSize(), PointMake(_object->getObjectRect().left + (_object->getObjectRect().right - _object->getObjectRect().left) / 2, _object->getObjectRect().bottom));
		_vPotion.push_back(pTemp);
		_object->setObjectPotionDrop(false);
	}
}