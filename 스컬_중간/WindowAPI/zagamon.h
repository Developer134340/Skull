#pragma once
#include "itemBase.h"
class zagamon :
	public itemBase
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	zagamon() {}
	~zagamon() {}
};

