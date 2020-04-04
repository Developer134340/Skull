#pragma once

#include "EnemyBase.h"

class Knight :public EnemyBase
{
private:

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void AI();
	void Attack();

	Knight() {};
	~Knight() {};
};

