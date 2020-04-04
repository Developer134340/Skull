#pragma once

#include "playerSkullBase.h"

struct _head
{
	float Sx, Sy;
	float x, y;
	float Direction;

	RECT rc;
	
	float speed;
	float angle;
	float Gravity;

	bool loop;
	bool Drop;
	bool fire;
	
	image* I;
	bool Irender;
	int index;
	int count;
};

class nomalSkull : public playerSkullBase
{
private:
	_head _Head;
	int dmg;

public:

	HRESULT init();
	void release();
	void update();
	void render();
	void AttackAction(int AttackSpeed, int JumpAttackSpeed);
	void Skill1(int ImageSpeed);


	virtual int DMG(RECT enemy)
	{
		RECT temp;
		if (IntersectRect(&temp, &enemy, &Arc) && AttackColl)
		{
			if (What == 평타)dmg = RND->range(6, 11);
			else if (What == 스킬1)dmg = RND->range(20, 30);

			if (RND->range(0, 8) == 0)
			{
				dmg *= 1.5;
			}

			return dmg;
		}

		return 0;
	}


	virtual bool DMGHead(RECT enemy)
	{
		RECT temp;
		if (IntersectRect(&temp, &enemy, &_Head.rc) && AttackColl)
		{
			if (What == 평타)dmg = RND->range(6, 11);
			else if (What == 스킬1)dmg = RND->range(20, 30);

			if (RND->range(0, 8) == 0)
			{
				dmg *= 1.5;
			}
			AttackColl = false;
			return _Head.Drop = true;
		}

		return 0;
	}

	nomalSkull() {}
	~nomalSkull() {}
};

