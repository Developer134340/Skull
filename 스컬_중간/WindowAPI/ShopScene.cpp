#include "stdafx.h"
#include "ShopScene.h"


HRESULT ShopScene::init()
{
	_index = _count = 0;
	_angle = 0.0f;

	_player->getPlayerClass()->setPlayerPositionX(100);
	_player->getPlayerClass()->setPlayerPositionY(WINSIZEY / 2 + 110);
	_player->getPlayerClass()->setImagePositionX(0);
	_player->getPlayerClass()->setImagePositionY(0);
	_player->getPlayerClass()->setDirectionRight();

	_player->getPlayerClass()->setPixelMap(IMAGEMANAGER->findImage("SHOP_MAP_PIXEL"));

	_gate = new gate;
	_gate->init("CHAPTER_GATE", PointMake(1350,544));

	_FadeOut = false;
	_FadeIn = true;

	_Alpha = 255;

	itemBase* iTemp;
	essenceBase* eTemp;

	_eIndex = _iIndex = 0;


	for (int i = 0; i < 4; i++)
	{
		bool overlap = false;

		_sellingItem[i] = RectMake(_player->getPlayerClass()->getImagePosition().x + 300 + (168 * i), _player->getPlayerClass()->getImagePosition().y + 390, 54, 54);
		_itemRaiser[i] = RectMake(_player->getPlayerClass()->getImagePosition().x + 283 + (168 * i), _player->getPlayerClass()->getImagePosition().y + 448, 78, 87);
		_randNum[i] = RND->range(0, 7);

		for (int j = 0; j < i; j++)
		{
			if (_randNum[i] == _randNum[j])
			{
				i--;
				overlap = true;
				break;
			}
		}

		if (overlap)	continue;

		_printCost[i] = RectMake(_player->getPlayerClass()->getImagePosition().x + 280 + (168 * i), _player->getPlayerClass()->getImagePosition().y + 367, 170, 50);

		switch (_randNum[i])
		{
		case 0:
			iTemp = new kaleon;
			iTemp->init();
			_vItem.push_back(iTemp);
			break;
		case 1:
			iTemp = new hearthStone;
			iTemp->init();
			_vItem.push_back(iTemp);
			break;
		case 2:
			iTemp = new madBerserker;
			iTemp->init();
			_vItem.push_back(iTemp);
			break;
		case 3:
			iTemp = new gunpowderSword;
			iTemp->init();
			_vItem.push_back(iTemp);
			break;
		case 4:
			iTemp = new icarus;
			iTemp->init();
			_vItem.push_back(iTemp);
			break;
		case 5:
			iTemp = new zagamon;
			iTemp->init();
			_vItem.push_back(iTemp);
			break;
		case 6:
			iTemp = new sylphid;
			iTemp->init();
			_vItem.push_back(iTemp);
			break;
		case 7:
			eTemp = new naias;
			eTemp->init();
			_vEssence.push_back(eTemp);
			break;
		case 8:
			eTemp = new flameDragon;
			eTemp->init();
			_vEssence.push_back(eTemp);
			break;
		}

		//-----------------가격--------------

		switch (_randNum[i])
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:

			if (_vItem[_iIndex]->getItemGrade() == "일반")
			{
				_cost[i] = RND->range(10, 80);
			}
			else if (_vItem[_iIndex]->getItemGrade() == "레어")
			{
				_cost[i] = RND->range(80, 150);
			}
			else if (_vItem[_iIndex]->getItemGrade() == "유니크")
			{
				_cost[i] = RND->range(150, 200);
			}
			else if (_vItem[_iIndex]->getItemGrade() == "레전더리")
			{
				_cost[i] = RND->range(200, 300);
			}
			_iIndex++;
			break;
		case 7:
		case 8:
			if (_vEssence[_eIndex]->getEssenceGrade() == "일반")
			{
				_cost[i] = RND->range(10, 80);
			}
			else if (_vEssence[_eIndex]->getEssenceGrade() == "레어")
			{
				_cost[i] = RND->range(80, 150);
			}
			else if (_vEssence[_eIndex]->getEssenceGrade() == "유니크")
			{
				_cost[i] = RND->range(150, 200);
			}
			else if (_vEssence[_eIndex]->getEssenceGrade() == "레전더리")
			{
				_cost[i] = RND->range(200, 300);
			}
			_eIndex++;
			break;
		}
	}

	sprintf(_cost1, "%d", _cost[0]);
	sprintf(_cost2, "%d", _cost[1]);
	sprintf(_cost3, "%d", _cost[2]);
	sprintf(_cost4, "%d", _cost[3]);

	return S_OK;
}

void ShopScene::release()
{
	_player->release();
	_gate->release();

	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->release();
	}
	for (int i = 0; i < _vEssence.size(); i++)
	{
		_vEssence[i]->release();
	}
}


void ShopScene::update()
{
	_count++;

	if (!_FadeOut && !_FadeIn)
	{
		_player->setPlayerPositionBefore(_player->getPlayerClass()->getPlayerPosition());
		_player->update();
		_player->camMove(IMAGEMANAGER->findImage("SHOP_MAP"));
	}

	if (_gate->update(_player->getPlayerClass()->getImagePosition(), _player->getPlayerClass()->getPlayerRc()) && KEYMANAGER->isOnceKeyDown('F'))
	{
		_FadeOut = true;
	}

	_angle += 0.07f;

	for (int i = 0; i < 4; i++)
	{
		_sellingItem[i] = RectMake(_player->getPlayerClass()->getImagePosition().x + 300 + (168 * i), _player->getPlayerClass()->getImagePosition().y + 390 +(int)(4 * sinf(_angle)), 54, 54);
		_itemRaiser[i] = RectMake(_player->getPlayerClass()->getImagePosition().x + 283 + (168 * i), _player->getPlayerClass()->getImagePosition().y + 448, 78, 87);
		_printCost[i] = RectMake(_player->getPlayerClass()->getImagePosition().x + 275 + (168 * i), _player->getPlayerClass()->getImagePosition().y + 506,70, 25);
	}

	_eIndex = _iIndex = 0;

	for (int i = 0; i < 4; i++)
	{
		RECT temp;

		switch (_randNum[i])
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			_vItem[_iIndex]->showItem(_sellingItem[i]);
			if (IntersectRect(&temp, &_player->getPlayerClass()->getPlayerRc(), &_itemRaiser[i]))
			{
				_vItem[_iIndex]->setItemFon(true);
				if (KEYMANAGER->isOnceKeyDown('F'))
				{
					if (_vItem[_iIndex]->getItemImageOn())
					{
						_player->playerItemPush(_vItem[_iIndex]);
						_vItem[_iIndex]->setItemImageOn(false);
					}
				}
			}
			else
			{
				_vItem[_iIndex]->setItemFon(false);
			}
			_iIndex++;
			break;
		case 7:
		case 8:
			_vEssence[_eIndex]->showEssence(_sellingItem[i]);
			if (IntersectRect(&temp, &_player->getPlayerClass()->getPlayerRc(), &_itemRaiser[i]))
			{
				_vEssence[_eIndex]->setEssenceFon(true);
				if (KEYMANAGER->isOnceKeyDown('F'))
				{
					if (_vEssence[_eIndex]->getEssenceImageOn())
					{
						if (_player->getPlayerEssenceV().size() != 0)
						{
							_player->playerEssenceRemove();
						}
						_player->playerEssencePush(_vEssence[_eIndex]);
						_vEssence[_eIndex]->setEssenceImageOn(false);
					}
				}
			}
			else
			{
				_vEssence[_eIndex]->setEssenceFon(false);
			}
			_eIndex++;
			break;
		}
	}


	IMAGEMANAGER->findImage("SHOP_NPC")->setFrameY(0);
	if (_count % 10 == 0)
	{
		_index++;
		if (_index > 4)
		{
			_index = 0;
		}
		IMAGEMANAGER->findImage("SHOP_NPC")->setFrameX(_index);
	}

	if (_FadeOut)
	{
		_Alpha += 3;
		if (_Alpha == 255)
		{
			_FadeOut = false;
			SCENEMANAGER->loadScene("Field_2", _player);
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

	minimapUpdate(IMAGEMANAGER->findImage("SHOP_MAP"), IMAGEMANAGER->findImage("MINI_SHOP"));
}

void ShopScene::render()
{
	IMAGEMANAGER->findImage("FIELD_BG_BACK")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("FIELD_BG_BACK")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("FIELD_BG_MIDDLE")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("FIELD_BG_MIDDLE")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("FIELD_BG_FRONT")->render(getMemDC(), 0, 0,
		0, IMAGEMANAGER->findImage("FIELD_BG_FRONT")->getHeight() - WINSIZEY, WINSIZEX, WINSIZEY);

	IMAGEMANAGER->findImage("SHOP_MAP")->render(getMemDC(), _player->getPlayerClass()->getImagePosition().x, _player->getPlayerClass()->getImagePosition().y - (IMAGEMANAGER->findImage("SHOP_MAP")->getHeight() - WINSIZEY));
	IMAGEMANAGER->findImage("SHOP_NPC")->frameRender(getMemDC(), _player->getPlayerClass()->getImagePosition().x + 940, _player->getPlayerClass()->getImagePosition().y + 350);


	if (KEYMANAGER->isToggleKey('T'))
	{
		for (int i = 0; i < 4; i++)
		{
			FrameRect(getMemDC(), _itemRaiser[i], RGB(255, 0, 0));
			FrameRect(getMemDC(), _sellingItem[i], RGB(255, 0, 0));
			FrameRect(getMemDC(), _printCost[i], RGB(0, 0, 255));
		}
	}

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);
	
	DrawText(getMemDC(), _cost1, -1, &_printCost[0], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	DrawText(getMemDC(), _cost2, -1, &_printCost[1], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	DrawText(getMemDC(), _cost3, -1, &_printCost[2], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	DrawText(getMemDC(), _cost4, -1, &_printCost[3], DT_VCENTER | DT_CENTER | DT_SINGLELINE);

	_gate->render();

	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->getItem(_player->getPlayerClass()->getPlayerRc());
	}
	for (int i = 0; i < _vEssence.size(); i++)
	{
		_vEssence[i]->getEssence(_player->getPlayerClass()->getPlayerRc());
	}

	minimapRender(IMAGEMANAGER->findImage("MINI_SHOP"));

	_player->render();

	if (_FadeOut || _FadeIn)
	{
		IMAGEMANAGER->alphaRender("BLACK", getMemDC(), _Alpha);
	}
}
void ShopScene::minimapUpdate(image* originalField, image* minimapField)
{
	minimapRc = RectMake(WINSIZEX - 246, WINSIZEY - 146, 206, 110);

	POINT playerPos;
	playerPos.x = _player->getPlayerClass()->getPlayerPosition().x - ((_player->getPlayerClass()->getPlayerRc().right - _player->getPlayerClass()->getPlayerRc().left) / 2);
	playerPos.y = _player->getPlayerClass()->getPlayerPosition().y + ((_player->getPlayerClass()->getPlayerRc().bottom - _player->getPlayerClass()->getPlayerRc().top) / 2);

	float miniGateWidth = (_gate->getGateRect().right - _gate->getGateRect().left)*((float)minimapField->getHeight() / (float)originalField->getHeight());

	minimapPlayerRc = RectMake(
		minimapRc.left + (minimapField->getWidth()*(-(_player->getPlayerClass()->getImagePosition().x) + playerPos.x)) / originalField->getWidth(),
		((originalField->getHeight() - WINSIZEY) * ((float)minimapField->getHeight() / (float)originalField->getHeight())) +
		minimapRc.top + (minimapField->getHeight()*(-(_player->getPlayerClass()->getImagePosition().y) + playerPos.y)) / originalField->getHeight() - 15, 8, 18);

	minimapGateRc = RectMake(
		minimapRc.left + (minimapField->getWidth()*(-(_player->getPlayerClass()->getImagePosition().x) + _gate->getGateRect().left)) / originalField->getWidth(),
		((originalField->getHeight() - WINSIZEY) * ((float)minimapField->getHeight() / (float)originalField->getHeight())) +
		minimapRc.top + (minimapField->getHeight()*(-(_player->getPlayerClass()->getImagePosition().y) + _gate->getGateRect().bottom)) / originalField->getHeight() - 20, miniGateWidth, 20);
}

void ShopScene::minimapRender(image* minimapField)
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
