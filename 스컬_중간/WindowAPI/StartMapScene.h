#pragma once

#include "gameNode.h"
#include "player.h"
#include "gate.h"

class StartMapScene : public gameNode
{
private:
	gate* _gate;

	bool _FadeOut;
	bool _FadeIn;

	int _Alpha;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	StartMapScene() {}
	~StartMapScene() {}
};