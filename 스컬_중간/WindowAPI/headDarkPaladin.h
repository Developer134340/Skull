#pragma once

#include "itemBase.h"

class headDarkPaladin : public itemBase
{
public:

	HRESULT init();
	void release();
	void update();
	void render();

	headDarkPaladin() {}
	~headDarkPaladin() {}
};