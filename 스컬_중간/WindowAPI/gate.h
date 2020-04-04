#pragma once
#include "gameNode.h"
class gate :
	public gameNode
{
	int _count;
	int _index;
	POINT _position;
	RECT _rc;
	image* gateImg;

	bool _fOn;

public:

	HRESULT init(string gateKey, POINT position);
	void release();
	bool update(POINT imagePosition, RECT playerRc);
	void render();

	RECT getGateRect() { return _rc; }

	gate() {}
	~gate() {}
};

