#pragma once

#include "playerSkullBase.h"

struct FireBall
{
	float Sx, Sy;
	float x, y;
	float Direction;
	RECT rc;
	float speed;
	bool fire;
	image* I;
	image* IEF;
	bool Irender;
	int index;
	int count;
};

struct slash
{
	float x, y;
	float Direction;
	RECT _rc;
	image* I;
	int index;
	int count;
	bool _slashon;
};


class chiefGuard : public playerSkullBase
{
private:
	FireBall _fireball;
	slash _slash;
	int dmg;
	bool _Fireballskillon;
	bool _slashskillon;
	int countslash;
	int _firecount;

public:

	HRESULT init();
	void release();
	void update();
	void render();
	void AttackAction(int ImageSpeed, int JumpAttackSpeed);
	void Skill1(int ImageSpeed);
	void Skill2(int ImageSpeed);
 

	int DMG()
	{
		if (What == 평타)dmg = RND->range(10, 15);
		else if (What == 스킬1)dmg = RND->range(5, 10);
		else if (What == 스킬2)dmg = RND->range(5, 10);

		if (RND->range(0, 8) == 0)
		{
			dmg *= 1.5;
		}

		return dmg;
	}
	
	chiefGuard() {}
	~chiefGuard() {}
};

