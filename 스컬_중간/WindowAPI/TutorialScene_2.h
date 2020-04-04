#pragma once

#include "gameNode.h"
#include "player.h"
#include "gate.h"
#include "object.h"
#include "EnemyBase.h"
#include "Knight.h"
#include "Archer.h"

class TutorialScene_2 : public gameNode
{
private:
	gate* _gate;
	object* _cageBack;
	object* _cageFront;

	bool _FadeOut;
	bool _FadeIn;

	bool _Escape;
	int _WitchCount;

	int _Alpha;

	EnemyBase* _enemy;

	RECT minimapRc;
	RECT minimapPlayerRc;
	RECT minimapGateRc;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void minimapUpdate(image* originalField, image* minimapField);
	void minimapRender(image* minimapField);

	TutorialScene_2() {}
	~TutorialScene_2() {}
};