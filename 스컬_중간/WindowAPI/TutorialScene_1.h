#pragma once

#include "gameNode.h"
#include "player.h"
#include "gate.h"

class TutorialScene_1 : public gameNode
{
private:
	gate* _gate;
	int _FingerCount;
	int _WeaponSkullCount;
	int _WeaponGetCount;

	RECT _WeaponSkullRc;

	bool _Collision;
	bool _NoWeapon;
	bool _FadeOut;
	bool _FadeIn;

	int _Alpha;

	//¹Ì´Ï¸Ê
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

	TutorialScene_1() {}
	~TutorialScene_1() {}
};