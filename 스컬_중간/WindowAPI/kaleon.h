#pragma once
#include "itemBase.h"
class kaleon :
	public itemBase
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	kaleon() {}
	~kaleon() {}
};

