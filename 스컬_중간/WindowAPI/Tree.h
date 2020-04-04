#pragma once
#include "EnemyBase.h"
class Tree :public EnemyBase
{


private:
	bool damageP;
public:

	HRESULT init();
	void release();
	void update();
	void render();

	void AI();
	void Attack();

	Tree() {}
	~Tree() {}
};

