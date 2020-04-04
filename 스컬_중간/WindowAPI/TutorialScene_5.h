#pragma once

#include "gameNode.h"
#include "gate.h"
#include "player.h"
#include "EnemyBase.h"
#include "Ogre.h"

class TutorialScene_5 : public gameNode
{
private:
	gate* _gate;

	bool _FadeOut;
	bool _FadeIn;

	int _Alpha;

	RECT minimapRc;
	RECT minimapPlayerRc;
	RECT minimapGateRc;

	EnemyBase* _enemyO;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void minimapUpdate(image* originalField, image* minimapField);
	void minimapRender(image* minimapField);

	TutorialScene_5() {}
	~TutorialScene_5() {}
};