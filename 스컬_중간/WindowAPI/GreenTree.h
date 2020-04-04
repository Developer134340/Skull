#pragma once
#include "EnemyBase.h"

class GreenTree :public EnemyBase
{
private:
	RECT RangeRc;
	int TmpX;
	bool RageAttck;
	bool AimOn;
	image* Effect;
	image* Aim;
	int alp;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void AI();
	void Attack();


	GreenTree() {}
	~GreenTree() {}
};

