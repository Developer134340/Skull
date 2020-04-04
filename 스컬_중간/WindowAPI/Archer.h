#pragma once
#include "EnemyBase.h"

struct Shot
{
	float x, y;
	float speed;
	RECT arrowrc;
};

class Archer : public EnemyBase
{
private:

	vector<Shot>_vShot;
	Shot _Shot;
	image* Aim;
	image* Arrow;
	RECT AimRc;
	bool fire;
	bool AimOn;
	int alp;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	void AI();
	void Attack();

	Archer() {}
	~Archer() {}
};

