#pragma once
#include "itemBase.h"
class headHunter :
	public itemBase
{
public:

	HRESULT init();
	void release();
	void update();
	void render();

	headHunter() {}
	~headHunter() {}
};

