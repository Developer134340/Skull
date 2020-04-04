#pragma once
#include "EnemyBase.h"
class Ogre :public EnemyBase
{
private:
	image* OgreDeadE;
	bool DeadE;
	bool indexP;
	RECT DeadRc;
	int hitcount;
	int hitdel;
	

public:

	HRESULT init();
	void release();
	void update();
	void render();

	void OgreRender(int ImageSpeed);
	void AI();
	void Attack();
	void HP();



	Ogre() {}
	~Ogre() {}
};

