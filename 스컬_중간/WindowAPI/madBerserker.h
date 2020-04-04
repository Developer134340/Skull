#pragma once
#include "itemBase.h"
class madBerserker :
	public itemBase
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	madBerserker() {}
	~madBerserker() {}
};

