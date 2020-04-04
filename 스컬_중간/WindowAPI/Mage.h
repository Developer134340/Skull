#pragma once
#include "EnemyBase.h"

struct fire
{
	float x, y;
	float speed;
	float angle;
	int Index;
	int Count;
	int HitCount;
	int HitIndex;
	bool Hit;
	RECT rc;
	RECT HitRc;
	bool fire;
	float distance;
	bool damageP;
};

class Mage :public EnemyBase
{
private:
	fire _fire;
	vector<fire>_vfire;
	int AttackCount;
	int fireCount;
	image* fireboll;
	image* fireHit;
	int Range;

	image* TelEin;
	image* TelEOut;
	RECT TelERc;
	bool TelIn;
	bool TelOut;
	bool TelGo;
	int TIndex;
	int TCount;

	bool coll;
	int alpa;



	

public:

	HRESULT init();
	void release();
	void update();
	void render();

	void mageRender();

	void AI();
	void Attack();
	void fireF();
	void Tel();


	Mage() {}
	~Mage() {}
};

