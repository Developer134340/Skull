#pragma once

#include "gameNode.h"
#include "player.h"

struct INVADE_ENEMY
{
	image* img;
	POINT pos;
	int frameCount;
	bool isPassed;
};

class OpeningScene : public gameNode
{
private:
	image* _backImg;
	image* _middleImg;
	image* _frontImg;

	bool _isScroll;
	bool _isInvade;
	bool _isCharacterOn;
	bool _fadeOut;
	bool _isReScroll;
	bool _fadeIn;

	int _count;

	int _backLoopX;
	int _frontLoopX;

	int _alpha;
	int _bgAlpha;

	int _ogreFrameCount;
	int _druidFrameCount;
	int _foxFrameCount;
	int _witchFrameCount;
	int _skulFrameCount;
	int _explosionFrameCount;
	int _heroFrameCount;

	vector<INVADE_ENEMY> _enemy;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	OpeningScene() {}
	~OpeningScene() {}
};