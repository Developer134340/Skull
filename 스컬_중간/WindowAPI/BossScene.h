#pragma once

#include "gameNode.h"
#include "player.h"
#include "Boss.h"

class BossScene : public gameNode
{
private:
	Boss* _boss;

	bool _FadeOut;
	bool _FadeIn;

	int _Alpha;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	BossScene() {}
	~BossScene() {}
};

