#include "stdafx.h"
#include "ItemScene.h"

HRESULT ItemScene::init()
{
	_player->getPlayerClass()->setPlayerPositionX(100);
	_player->getPlayerClass()->setPlayerPositionY(WINSIZEY / 2 + 110);
	_player->getPlayerClass()->setImagePositionX(0);
	_player->getPlayerClass()->setImagePositionY(0);
	_player->getPlayerClass()->setDirectionRight();

	_player->getPlayerClass()->setPixelMap(IMAGEMANAGER->findImage("ITEM_MAP_PIXEL"));

	_randNum = RND->range(0, 8);
	_fOn = false;
	_boxOn = false;
	_count = _boxIndex = _boxCount = 0;
	itemBase* temp;
	essenceBase* temp2;

	_gate = new gate;
	_gate->init("CHAPTER_GATE", PointMake(1350, 544));

	_FadeOut = false;
	_FadeIn = true;

	_Alpha = 255;

	switch (_randNum)
	{
	case 0:
		_boxImg = IMAGEMANAGER->findImage("일반상자");
		_boxRc = RectMake(_player->getPlayerClass()->getImagePosition().x + 750, _player->getPlayerClass()->getImagePosition().y + 330, 100, 90);
		temp = new kaleon;
		temp->init();
		_vItem.push_back(temp);
		break;
	case 1:
		_boxImg = IMAGEMANAGER->findImage("일반상자");
		_boxRc = RectMake(_player->getPlayerClass()->getImagePosition().x + 750, _player->getPlayerClass()->getImagePosition().y + 330, 100, 90);
		temp = new hearthStone;
		temp->init();
		_vItem.push_back(temp);
		break;
	case 2:
		_boxImg = IMAGEMANAGER->findImage("레어상자");
		_boxRc = RectMake(_player->getPlayerClass()->getImagePosition().x + 750, _player->getPlayerClass()->getImagePosition().y + 330, 130, 90);
		temp = new madBerserker;
		temp->init();
		_vItem.push_back(temp);
		break;
	case 3:
		_boxImg = IMAGEMANAGER->findImage("레어상자");
		_boxRc = RectMake(_player->getPlayerClass()->getImagePosition().x + 750, _player->getPlayerClass()->getImagePosition().y + 330, 130, 90);
		temp = new gunpowderSword;
		temp->init();
		_vItem.push_back(temp);
		break;
	case 4:
		_boxImg = IMAGEMANAGER->findImage("유니크상자");
		_boxRc = RectMake(_player->getPlayerClass()->getImagePosition().x + 750, _player->getPlayerClass()->getImagePosition().y + 330, 160, 100);
		temp = new icarus;
		temp->init();
		_vItem.push_back(temp);
		break;
	case 5:
		_boxImg = IMAGEMANAGER->findImage("유니크상자");
		_boxRc = RectMake(_player->getPlayerClass()->getImagePosition().x + 750, _player->getPlayerClass()->getImagePosition().y + 330, 160, 100);
		temp = new zagamon;
		temp->init();
		_vItem.push_back(temp);
		break;
	case 6:
		_boxImg = IMAGEMANAGER->findImage("레전더리상자");
		_boxRc = RectMake(_player->getPlayerClass()->getImagePosition().x + 750, _player->getPlayerClass()->getImagePosition().y + 330, 150, 120);
		temp = new sylphid;
		temp->init();
		_vItem.push_back(temp);
		break;
	case 7:
		_boxImg = IMAGEMANAGER->findImage("일반상자");
		_boxRc = RectMake(_player->getPlayerClass()->getImagePosition().x + 750, _player->getPlayerClass()->getImagePosition().y + 330, 100, 90);
		temp2 = new naias;
		temp2->init();
		_vEssence.push_back(temp2);
		break;
	case 8:
		_boxImg = IMAGEMANAGER->findImage("유니크상자");
		_boxRc = RectMake(_player->getPlayerClass()->getImagePosition().x + 750, _player->getPlayerClass()->getImagePosition().y + 330, 160, 100);
		temp2 = new flameDragon;
		temp2->init();
		_vEssence.push_back(temp2);
		break;
	}

	_boxImg->setFrameY(0);

	return S_OK;
}

void ItemScene::release()
{
	_gate->release();
	_player->release();
	switch (_randNum)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		for(int i = 0; i<_vItem.size(); i++)
		{
			_vItem[i]->release();
		}
		break;
	case 7:
	case 8:
		for (int i = 0; i < _vEssence.size(); i++)
		{
			_vEssence[i]->release();
		}
		break;
	}
}

void ItemScene::update()
{
	_count++;

	if (!_FadeOut && !_FadeIn)
	{
		_player->setPlayerPositionBefore(_player->getPlayerClass()->getPlayerPosition());
		_player->update();
		_player->camMove(IMAGEMANAGER->findImage("ITEM_MAP"));
	}
	_boxRc = RectMake(_player->getPlayerClass()->getImagePosition().x+750, _player->getPlayerClass()->getImagePosition().y + 330, 150, 120);

	RECT temp;

	switch (_randNum)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		for (int i = 0; i < _vItem.size(); i++)
		{
			if (_boxOn && KEYMANAGER->isOnceKeyDown('F'))
			{
				if (IntersectRect(&temp, &_player->getPlayerClass()->getPlayerRc(), &_vItem[i]->getItemRc()))
				{
					_player->playerItemPush(_vItem[i]);
					_vItem.erase(_vItem.begin() + i);
				}
			}
		}
		break;
	case 7:
	case 8:
		for (int i = 0; i < _vEssence.size(); i++)
		{
			if (_boxOn && KEYMANAGER->isOnceKeyDown('F'))
			{
				if (IntersectRect(&temp, &_player->getPlayerClass()->getPlayerRc(), &_vEssence[i]->getEssenceRc()))
				{
					if (_player->getPlayerEssenceV().size() != 0)
					{
						_player->playerEssenceRemove();
					}
					_player->playerEssencePush(_vEssence[i]);
					_vEssence.erase(_vEssence.begin() + i);
				}
			}
		}
		break;
	}

	switch (_randNum)
	{
	case 0:	//일반
	case 1:
	case 7:
		_boxRc = RectMake(_player->getPlayerClass()->getImagePosition().x + 750, _player->getPlayerClass()->getImagePosition().y + 340, 100, 90);
		break;
	case 2:	//레어
	case 3:
		_boxRc = RectMake(_player->getPlayerClass()->getImagePosition().x + 750, _player->getPlayerClass()->getImagePosition().y + 340, 130, 90);
		break;
	case 4://유니크
	case 5:
	case 8:
		_boxRc = RectMake(_player->getPlayerClass()->getImagePosition().x + 750, _player->getPlayerClass()->getImagePosition().y + 330, 160, 100);
		break;
	case 6:	//레전더리
		_boxRc = RectMake(_player->getPlayerClass()->getImagePosition().x + 750, _player->getPlayerClass()->getImagePosition().y + 300, 150, 120);
		break;
	}

	this->openBox();

	if (_FadeOut)
	{
		_Alpha += 3;
		if (_Alpha == 255)
		{
			_FadeOut = false;
			SCENEMANAGER->loadScene("BossReadyScene", _player);
			SOUNDMANAGER->stop("FIELD_BGM");
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

	if (_gate->update(_player->getPlayerClass()->getImagePosition(), _player->getPlayerClass()->getPlayerRc()) && KEYMANAGER->isStayKeyDown('F'))
	{
		_FadeOut = true;
	}

	minimapUpdate(IMAGEMANAGER->findImage("ITEM_MAP"), IMAGEMANAGER->findImage("MINI_ITEM"));
}

void ItemScene::render()
{
	IMAGEMANAGER->findImage("FIELD_BG_BACK")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("FIELD_BG_BACK")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("FIELD_BG_MIDDLE")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("FIELD_BG_MIDDLE")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("FIELD_BG_FRONT")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("FIELD_BG_FRONT")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);

	IMAGEMANAGER->findImage("ITEM_MAP")->render(getMemDC(), _player->getPlayerClass()->getImagePosition().x, _player->getPlayerClass()->getImagePosition().y - (IMAGEMANAGER->findImage("ITEM_MAP")->getHeight() - WINSIZEY));
	_boxImg->frameRender(getMemDC(), _boxRc.left, _boxRc.top);

	if (_fOn)
	{
		IMAGEMANAGER->findImage("F_KEY")->render(getMemDC(), _boxRc.left + ((_boxRc.right - _boxRc.left)/2), _boxRc.top -150);
	}

	if (_boxOn && _count - _boxCount >= 30)
	{
		switch (_randNum)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			for (int i = 0; i < _vItem.size(); i++)
			{
				_vItem[i]->getItem(_player->getPlayerClass()->getPlayerRc());

			}
			break;
		case 7:
		case 8:
			for (int i = 0; i < _vEssence.size(); i++)
			{
				_vEssence[i]->getEssence(_player->getPlayerClass()->getPlayerRc());
			}
			break;
		}
	}

	if(KEYMANAGER->isToggleKey('Y'))
	{
		FrameRect(getMemDC(), _boxRc, RGB(255, 0, 0));
	}

	_gate->render();

	_player->render();

	minimapRender(IMAGEMANAGER->findImage("MINI_ITEM"));

	if (_FadeOut || _FadeIn)
	{
		IMAGEMANAGER->alphaRender("BLACK", getMemDC(), _Alpha);
	}
}

void ItemScene::openBox()
{
	RECT temp;

	if (IntersectRect(&temp, &_player->getPlayerClass()->getPlayerRc(), &_boxRc) && _boxOn == false)
	{
		_fOn = true;

		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			_boxOn = true;
			_boxCount = _count;
			_fOn = false;
		}
	}
	else
	{
		_fOn = false;
	}

	if (_boxOn)
	{
		_fOn = false;

		if (_count % 5 == 0)
		{
			_boxIndex++;
			if (_boxIndex > 8)
			{
				_boxIndex = 8;
			}
			_boxImg->setFrameX(_boxIndex);
		}
		
		if (_count - _boxCount >= 30)
		{
			switch (_randNum)
			{
			case 0:
			case 1:
			case 2:
			case 3:	
			case 4:
			case 5:
			case 6:
				for (int i = 0; i < _vItem.size(); i++)
				{
					_vItem[i]->dropItem(PointMake(_boxRc.left + (_boxRc.right - _boxRc.left) / 2 - 40, _boxRc.top));
				}
				break;
			case 7:
			case 8:
				for (int i = 0; i < _vEssence.size(); i++)
				{
					_vEssence[i]->dropEssence(PointMake(_boxRc.left + (_boxRc.right - _boxRc.left) / 2 - 40, _boxRc.top));
				}
				break;
			}
		}
	}
}

void ItemScene::minimapUpdate(image* originalField, image* minimapField)
{
	minimapRc = RectMake(WINSIZEX - 246, WINSIZEY - 146, 206, 110);

	POINT playerPos;
	playerPos.x = _player->getPlayerClass()->getPlayerPosition().x - ((_player->getPlayerClass()->getPlayerRc().right - _player->getPlayerClass()->getPlayerRc().left) / 2);
	playerPos.y = _player->getPlayerClass()->getPlayerPosition().y + ((_player->getPlayerClass()->getPlayerRc().bottom - _player->getPlayerClass()->getPlayerRc().top) / 2);

	float miniGateWidth = (_gate->getGateRect().right - _gate->getGateRect().left)*((float)minimapField->getHeight() / (float)originalField->getHeight());

	minimapPlayerRc = RectMake(-3 +
		minimapRc.left + (minimapField->getWidth()*(-(_player->getPlayerClass()->getImagePosition().x) + playerPos.x)) / originalField->getWidth(),
		((originalField->getHeight() - WINSIZEY) * ((float)minimapField->getHeight() / (float)originalField->getHeight())) +
		minimapRc.top + (minimapField->getHeight()*(-(_player->getPlayerClass()->getImagePosition().y) + playerPos.y)) / originalField->getHeight() - 12, 8, 15);

	minimapGateRc = RectMake(
		minimapRc.left + (minimapField->getWidth()*(-(_player->getPlayerClass()->getImagePosition().x) + _gate->getGateRect().left)) / originalField->getWidth(),
		((originalField->getHeight() - WINSIZEY) * ((float)minimapField->getHeight() / (float)originalField->getHeight())) +
		minimapRc.top + (minimapField->getHeight()*(-(_player->getPlayerClass()->getImagePosition().y) + _gate->getGateRect().bottom)) / originalField->getHeight() - 20, miniGateWidth, 20);

}

void ItemScene::minimapRender(image* minimapField)
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