#pragma once

#include "gameNode.h"
#include "player.h"
class TitleScene : public gameNode
{
private:
	int _loopX;
	int _skulFrameCount;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	TitleScene() {}
	~TitleScene() {}
};