#include "stdafx.h"
#include "SkullScene.h"

HRESULT SkullScene::init()
{
	_player->getPlayerClass()->setPlayerPositionX(100);
	_player->getPlayerClass()->setPlayerPositionY(WINSIZEY / 2 + 110);
	_player->getPlayerClass()->setImagePositionX(0);
	_player->getPlayerClass()->setImagePositionY(0);
	_player->getPlayerClass()->setDirectionRight();

	_player->getPlayerClass()->setPixelMap(IMAGEMANAGER->findImage("SKULL_MAP_PIXEL"));

	_randNum = RND->range(10); //0,1,2
	_fOn = false;
	_tombOn = false;
	_count = _tombIndex = _tombCount = 0;
	itemBase* temp;

	_FadeOut = false;
	_FadeIn = true;

	_Alpha = 255;

	_gate = new gate;
	_gate->init("CHAPTER_GATE", PointMake(1350, 544));

	switch (_randNum)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		_tombImg = IMAGEMANAGER->findImage("레어무덤");
		_tombRc = RectMake(_player->getPlayerClass()->getImagePosition().x + 780, _player->getPlayerClass()->getImagePosition().y + 330, 130, 80);
		temp = new headHunter;
		temp->init();
		_vSkul.push_back(temp);
		break;
	case 6:
	case 7:
	case 8:
		_tombImg = IMAGEMANAGER->findImage("유니크무덤");
		_tombRc = RectMake(_player->getPlayerClass()->getImagePosition().x + 700, _player->getPlayerClass()->getImagePosition().y + 320, 252, 90);
		temp = new headDarkPaladin;
		temp->init();
		_vSkul.push_back(temp);
		break;
	case 9:
		_tombImg = IMAGEMANAGER->findImage("레전더리무덤");
		_tombRc = RectMake(_player->getPlayerClass()->getImagePosition().x + 650, _player->getPlayerClass()->getImagePosition().y + 190, 362, 222);
		temp = new headReaper;
		temp->init();
		_vSkul.push_back(temp);
		break;
	}

	_tombImg->setFrameY(0);


	return S_OK;
}

void SkullScene::release()
{	
	for (int i = 0; i < _vSkul.size(); i++)
	{
		SAFE_DELETE(_vSkul[i]);
	}

	_gate->release();
}

void SkullScene::update()
{
	_count++;

	if (!_FadeOut && !_FadeIn)
	{
		_player->setPlayerPositionBefore(_player->getPlayerClass()->getPlayerPosition());
		_player->update();
		_player->camMove(IMAGEMANAGER->findImage("SKULL_MAP"));
	}

	switch (_randNum)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		_tombRc = RectMake(_player->getPlayerClass()->getImagePosition().x + 780, _player->getPlayerClass()->getImagePosition().y + 330, 130, 80);
		break;
	case 6:
	case 7:
	case 8:
		_tombRc = RectMake(_player->getPlayerClass()->getImagePosition().x + 700, _player->getPlayerClass()->getImagePosition().y + 320, 252, 90);
		break;
	case 9:
		_tombRc = RectMake(_player->getPlayerClass()->getImagePosition().x + 650, _player->getPlayerClass()->getImagePosition().y + 190, 362, 222);
		break;
	}
	
	RECT temp;

	this->openTomb();

	for (int i = 0; i < _vSkul.size(); i++)
	{
		if (_tombOn && KEYMANAGER->isOnceKeyDown('F'))
		{
			if (IntersectRect(&temp, &_player->getPlayerClass()->getPlayerRc(), &_vSkul[i]->getItemRc()))
			{
				_player->playerSkulPush(_vSkul[i]);
				_vSkul.erase(_vSkul.begin() + i);
			}
		}
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
			SCENEMANAGER->loadScene("Tutorial_1", _player);
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

	//this->minimapUpdate(IMAGEMANAGER->findImage("SKULL_MAP"), IMAGEMANAGER->findImage("미니맵_스컬필드"));
}

void SkullScene::render()
{
	IMAGEMANAGER->findImage("FIELD_BG_BACK")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("FIELD_BG_BACK")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("FIELD_BG_MIDDLE")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("FIELD_BG_MIDDLE")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("FIELD_BG_FRONT")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("FIELD_BG_FRONT")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);

	IMAGEMANAGER->findImage("SKULL_MAP")->render(getMemDC(), _player->getPlayerClass()->getImagePosition().x, _player->getPlayerClass()->getImagePosition().y - (IMAGEMANAGER->findImage("SKULL_MAP")->getHeight() - WINSIZEY));

	_tombImg->frameRender(getMemDC(), _tombRc.left, _tombRc.top);

	if (_fOn)
	{
		IMAGEMANAGER->findImage("F_KEY")->render(getMemDC(), _tombRc.left + ((_tombRc.right - _tombRc.left) / 2), _tombRc.top - 150);
	}

	if (_tombOn)
	{
		_fOn = false;

		if (_count % 5 == 0)
		{
			_tombIndex++;
			if (_tombIndex > 9)
			{
				_tombIndex = 9;
			}
			_tombImg->setFrameX(_tombIndex); 
		}

		if (_count - _tombCount >= 30)
		{
			for (int i = 0; i < _vSkul.size(); i++)
			{
				_vSkul[i]->getItem(_player->getPlayerClass()->getPlayerRc());
			}
		}
	}

	if (KEYMANAGER->isToggleKey('Y'))
	{
		Rectangle(getMemDC(), _tombRc);
	}
	_gate->render();	
	_player->render();

	//this->minimapRender(IMAGEMANAGER->findImage("미니맵_스컬필드"));

	if (_FadeOut || _FadeIn)
	{
		IMAGEMANAGER->alphaRender("BLACK", getMemDC(), _Alpha);
	}
}

void SkullScene::openTomb()
{
	RECT temp;

	if (IntersectRect(&temp, &_player->getPlayerClass()->getPlayerRc(), &_tombRc) && _tombOn == false)
	{
		_fOn = true;

		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			_tombOn = true;
			_tombCount = _count;
		}
	}
	else
	{
		_fOn = false;
	}

	if (_tombOn)
	{
		_fOn = false;

		if (_count % 5 == 0)
		{
			_tombIndex++;
			if (_tombIndex > 9)
			{
				_tombIndex = 9;
			}
			_tombImg->setFrameX(_tombIndex);
		}

		if (_count - _tombCount >= 30)
		{
			for (int i = 0; i < _vSkul.size(); i++)
			{
				_vSkul[i]->dropItem(PointMake(_tombRc.left + (_tombRc.right - _tombRc.left) / 2 - 40, _tombRc.bottom - 100));
			}
		}
	}
}

//void SkullScene::minimapUpdate(image* originalField, image* minimapField)
//{
//
//	minimapRc = RectMake(WINSIZEX - 246, WINSIZEY - 146, 206, 110);
//	minimapPlayerRc = RectMake(
//		minimapRc.left + (minimapField->getWidth()*(-(_player->getPlayerClass()->getImagePosition().x) + _player->getPlayerClass()->getPlayerPosition().x)) / originalField->getWidth(),
//		((originalField->getHeight() - WINSIZEY) * ((float)minimapField->getHeight() / (float)originalField->getHeight())) +
//			minimapRc.top + (minimapField->getHeight()*(-(_player->getPlayerClass()->getImagePosition().y) + _player->getPlayerClass()->getPlayerPosition().y)) / originalField->getHeight()-20, 10, 20);
//}
//
//
//void SkullScene::minimapRender(image* minimapField)
//{
//	IMAGEMANAGER->findImage("미니맵배경")->alphaRender(getMemDC(), WINSIZEX - 250, WINSIZEY - 150, 100);
//	minimapField->render(getMemDC(), minimapRc.left, minimapRc.top);
//
//	HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
//	Rectangle(getMemDC(), minimapPlayerRc);
//	FillRect(getMemDC(), &minimapPlayerRc, brush);
//
//	IMAGEMANAGER->findImage("미니맵프레임")->render(getMemDC(), WINSIZEX - 250, WINSIZEY - 150);
//}