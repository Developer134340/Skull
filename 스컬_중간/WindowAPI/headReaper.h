#pragma once

#include "itemBase.h"

class headReaper : public itemBase
{
public:

	HRESULT init();
	void release();
	void update();
	void render();

	headReaper() {}
	~headReaper() {}
};

