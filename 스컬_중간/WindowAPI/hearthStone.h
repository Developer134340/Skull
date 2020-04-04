#pragma once
#include "itemBase.h"
class hearthStone :
	public itemBase
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	hearthStone(){}
	~hearthStone() {}
};

