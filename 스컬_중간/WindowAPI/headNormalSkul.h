#pragma once
#include "itemBase.h"
class headNormalSkul :
	public itemBase
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	headNormalSkul(){}
	~headNormalSkul() {}
};

