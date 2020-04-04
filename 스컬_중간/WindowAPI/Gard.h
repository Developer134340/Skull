#pragma once
#include "EnemyBase.h"
class Gard :public EnemyBase
{
private:
	int dashDmg;
	int DashSpeed;
	int AttackCount;
	RECT TackleRc;
	image* TackleI;
	int TackleCount;
	int TackleIndex;
	bool Effect;
	bool damageP;

public:

	HRESULT init();
	void release();
	void update();
	void render();
	void AI();
	void Attack();

	Gard() {}
	~Gard() {}
};

