#pragma once

#include "gameNode.h"
#include "player.h"
#include "itemBase.h"
#include "essenceBase.h"
#include "gunpowderSword.h"
#include "hearthStone.h"
#include "icarus.h"
#include "kaleon.h"
#include "madBerserker.h"
#include "sylphid.h"
#include "zagamon.h"
#include "flameDragon.h"
#include "naias.h"

class ShopScene : public gameNode
{
	RECT _sellingItem[4];
	RECT _itemRaiser[4];
	RECT _printCost[4];

	int _randNum[4];
	int _cost[4];


	int _index;
	int _count;

	float _angle;

	itemBase* _item[4];
	essenceBase* _essence[4];

	char test[100];

	//가격 출력용 변수
	char _cost1[100];
	char _cost2[100];
	char _cost3[100];
	char _cost4[100];


public:
	HRESULT init();
	void release();
	void update();
	void render();

	ShopScene() {}
	~ShopScene() {}
};