#pragma once
#include "itemBase.h"
class sylphid :
	public itemBase
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	sylphid() {}
	~sylphid() {}
};

