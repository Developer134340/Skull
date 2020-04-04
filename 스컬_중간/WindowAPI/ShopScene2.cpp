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

	for (int i = 0; i < 4; i++)
	{
		_sellingItem[i] = RectMake(_player->getPlayerClass()->getImagePosition().x + 380 + (168 * i), _player->getPlayerClass()->getImagePosition().y + 380, 84, 81);
		_itemRaiser[i] = RectMake(_player->getPlayerClass()->getImagePosition().x + 283 + (168 * i), _player->getPlayerClass()->getImagePosition().y + 448, 78, 87);
		_randNum[i] = RND->range(0, 8);

		_printCost[i] = RectMake(_player->getPlayerClass()->getImagePosition().x + 280 + (168 * i), _player->getPlayerClass()->getImagePosition().y + 367, 170, 50);

		switch (_randNum[i])
		{
		case 0:
			_item[i] = new kaleon;
			_item[i]->init();
			break;
		case 1:
			_item[i] = new hearthStone;
			_item[i]->init();
			break;
		case 2:
			_item[i] = new madBerserker;
			_item[i]->init();
			break;
		case 3:
			_item[i] = new gunpowderSword;
			_item[i]->init();
			break;
		case 4:
			_item[i] = new icarus;
			_item[i]->init();
			break;
		case 5:
			_item[i] = new zagamon;
			_item[i]->init();
			break;
		case 6:
			_item[i] = new sylphid;
			_item[i]->init();
			break;
		case 7:
			_essence[i] = new naias;
			_essence[i]->init();
			break;
		case 8:
			_essence[i] = new flameDragon;
			_essence[i]->init();
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
			if (_item[i]->getItemGrade() == "일반")
			{
				_cost[i] = RND->range(10, 80);
			}
			else if (_item[i]->getItemGrade() == "레어")
			{
				_cost[i] = RND->range(80, 150);
			}
			else if (_item[i]->getItemGrade() == "유니크")
			{
				_cost[i] = RND->range(150, 200);
			}
			else if (_item[i]->getItemGrade() == "레전더리")
			{
				_cost[i] = RND->range(200, 300);
			}
			break;
		case 7:
		case 8:
			if (_essence[i]->getEssenceGrade() == "일반")
			{
				_cost[i] = RND->range(10, 80);
			}
			else if (_essence[i]->getEssenceGrade() == "레어")
			{
				_cost[i] = RND->range(80, 150);
			}
			else if (_essence[i]->getEssenceGrade() == "유니크")
			{
				_cost[i] = RND->range(150, 200);
			}
			else if (_essence[i]->getEssenceGrade() == "레전더리")
			{
				_cost[i] = RND->range(200, 300);
			}
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

	for (int i = 0; i < 4; i++)
	{
		switch (_randNum[i])
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			_item[i]->release();
			break;
		case 7:
		case 8:
			_essence[i]->release();
			break;
		}
	}
}

void ShopScene::update()
{
	_count++;

	_angle += 0.07f;

	_player->setPlayerPositionBefore(_player->getPlayerClass()->getPlayerPosition());
	_player->update();
	_player->camMove(IMAGEMANAGER->findImage("SHOP_MAP"));

	for (int i = 0; i < 4; i++)
	{
		_sellingItem[i] = RectMake(_player->getPlayerClass()->getImagePosition().x + 280 + (168 * i), _player->getPlayerClass()->getImagePosition().y + 367 + (int)(4 * sinf(_angle)), 84, 81);
		_itemRaiser[i] = RectMake(_player->getPlayerClass()->getImagePosition().x + 283 + (168 * i), _player->getPlayerClass()->getImagePosition().y + 448, 78, 87);
		_printCost[i] = RectMake(_player->getPlayerClass()->getImagePosition().x + 275 + (168 * i), _player->getPlayerClass()->getImagePosition().y + 506, 70, 25);
	}

	for (int i = 0; i < 4; i++)
	{
		switch (_randNum[i])
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			_item[i]->update();
			_item[i]->showItem(_sellingItem[i]);
			break;
		case 7:
		case 8:
			_essence[i]->update();
			_essence[i]->showEssence(_sellingItem[i]);
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

	//아이템 흔들리는거

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


	if (KEYMANAGER->isToggleKey(VK_SPACE))
	{
		for (int i = 0; i < 4; i++)
		{
			FrameRect(getMemDC(), _itemRaiser[i], RGB(255, 0, 0));
			FrameRect(getMemDC(), _sellingItem[i], RGB(255, 0, 0));
			FrameRect(getMemDC(), _printCost[i], RGB(0, 0, 255));
		}

	}

	DrawText(getMemDC(), _cost1, -1, &_printCost[0], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	DrawText(getMemDC(), _cost2, -1, &_printCost[1], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	DrawText(getMemDC(), _cost3, -1, &_printCost[2], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	DrawText(getMemDC(), _cost4, -1, &_printCost[3], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	
	for (int i = 0; i < 4; i++)
	{
		switch (_randNum[i])
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			_item[i]->getItem(_player->getPlayerClass()->getPlayerRc());
			_item[i]->render();
			break;
		case 7:
		case 8:
			_essence[i]->getEssence(_player->getPlayerClass()->getPlayerRc());
			_essence[i]->render();
			break;
		}
	}

	_player->render();
}