#pragma once
#include "EnemyBase.h"

struct GreenBeen
{
	RECT rc;
	int x, y;
	int exX, exY;
	POINT exImagePosition;
	float speed;
	float angle;
	float distance;
};



class GiantTree :public EnemyBase
{
private:

	bool stomp;
	bool stompDam;
	int effetCount;
	int effectIndex;
	int AttackCount;
	RECT stompRc;
	RECT stompDagmeRC;
	image* stompEffet;
	image* GreenBeenI;
	int GreenBeenDmg;
	int range;

	int GreenCount;
	int GreenIndex;

	POINT exImagePosition;
	RECT exStompRc;

	vector<GreenBeen>_vBeen;
	GreenBeen Been;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	void AI();
	void AttactRender(int ImageSpeed);	
	void RangeAttack();



	

	GiantTree() {}
	~GiantTree() {}
};

