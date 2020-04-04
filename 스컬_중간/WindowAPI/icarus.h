#pragma once
#include "itemBase.h"
class icarus :
	public itemBase
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	icarus() {}
	~icarus() {}
};

