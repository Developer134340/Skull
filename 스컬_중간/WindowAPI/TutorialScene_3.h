#pragma once

#include "gameNode.h"
#include "gate.h"
#include "player.h"
#include "object.h"

class TutorialScene_3 : public gameNode
{
private:
	gate* _gate;

	bool _FadeOut;
	bool _FadeIn;

	int _Alpha;

	vector<potion*> _vPotion;
	vector<object*> _vObject;

	RECT minimapRc;
	RECT minimapPlayerRc;
	RECT minimapGateRc;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void healHp();
	void makePotion(object * _object);

	void minimapUpdate(image* originalField, image* minimapField);
	void minimapRender(image* minimapField);

	TutorialScene_3() {}
	~TutorialScene_3() {}
};