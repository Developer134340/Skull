#pragma once
#include "itemBase.h"
class gunpowderSword :
	public itemBase
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	gunpowderSword() { }
	~gunpowderSword() {}
};

