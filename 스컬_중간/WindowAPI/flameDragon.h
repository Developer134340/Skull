#pragma once
#include "essenceBase.h"

struct tagDragon
{
	POINT position;
	POINT exImagePosition;
	POINT exPosition;
	RECT attackRc;
	int index[4];
	int direction;
	int alpha;
};


class flameDragon :
	public essenceBase
{
	vector<tagDragon> _vDragonAttack;


public:

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(RECT playerRc, int playerDirection, POINT imagePosition);

	flameDragon() {}
	~flameDragon() {}
};

