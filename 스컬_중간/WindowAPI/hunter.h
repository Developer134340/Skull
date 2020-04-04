#pragma once
#include "playerSkullBase.h"

struct _bul
{
	float x, y;
	int Direction;
	RECT rc;
	float speed;
	image* I;
	bool fire;
};

struct Skill
{
	float x, y;
	RECT rc;
	int index;
	int count;
	int ii, ic;
	int direction;
	image* I;
	bool EF;
};

class hunter :public playerSkullBase
{
private:

	int dmg;

	Skill sk;
	_bul bu;
	vector<_bul> _vBullet;


public:
	HRESULT init();
	void release();
	void update();
	void render();

	void AttackAction(int ImageSpeed, int JumpAttackSpeed);
	void Skill1(int ImageSpeed);

	int DMG()
	{
		if (What == 평타)dmg = RND->range(10, 15);
		else if (What == 스킬1)dmg = RND->range(5, 10);
		else if (What == 스킬2)dmg = RND->range(20, 30);

		if (RND->range(0, 8) == 0)
		{
			dmg *= 1.5;
		}

		return dmg;

	}





	hunter() {}
	~hunter() {}
};

