#pragma once

#include "gameNode.h"
#include "player.h"
#include "gate.h"
#include "object.h"
#include "enemyBase.h"
#include "Knight.h"
#include "Archer.h"
#include "GiantTree.h"

class FieldScene_1 : public gameNode
{
private:
	gate* _gate;

	vector<object*> _vObject;

	bool _FadeOut;
	bool _FadeIn;

	int _Alpha;

	RECT minimapRc;
	RECT minimapPlayerRc;
	RECT minimapGateRc;

	vector<potion*> _vPotion;
	vector<EnemyBase*> _vEnemy;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void minimapUpdate(image* originalField, image* minimapField);
	void minimapRender(image* minimapField);

	void healHp();
	void makePotion(object * _object);

	FieldScene_1() {}
	~FieldScene_1() {}
};

