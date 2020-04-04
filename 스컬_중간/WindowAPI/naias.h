#pragma once
#include "essenceBase.h"

struct tagAttack
{
	RECT rc;
	POINT position;
	float angle;
	float speed;
	bool on;
};

class naias :
	public essenceBase
{
	int _skillCount;
	int _count;
	vector<tagAttack> _vAttack;
	
public:

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(RECT playerRc, int playerDirection, POINT imagePosition);

	naias() {}
	~naias() {}
};

