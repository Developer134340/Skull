#pragma once
#include "gameNode.h"
#include "player.h"

enum potionSize
{
	S,
	M,
	L,
	XL
};

class potion : public gameNode
{
	int _count;
	int _index;
	RECT _rc;
	potionSize _potionSize;
	float _percent;
	POINT _position;
	image* _potionImg;
	float _gravity;

	POINT _initPosition;
	POINT _exImagePosition;
	POINT _exPosition;

	int _speed;
	bool _dropOn;

public:
	HRESULT init(potionSize ps, POINT pos);
	void release();
	void update(POINT imagePosition);
	void render();

	void potionDrop(POINT imagePosition);

	RECT getPotionRc() { return _rc; }
	float getPotionPercent() { return _percent; }

	POINT getPotionPosition() { return _position; }
	void setPotionPosition(POINT pos) { _position = pos; }

	potion() {}
	~potion() {}
};

