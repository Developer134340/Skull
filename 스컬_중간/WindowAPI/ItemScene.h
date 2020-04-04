#pragma once

#include "gameNode.h"
#include "player.h"
#include "itemBase.h"
#include "essenceBase.h"
#include "gunpowderSword.h"
#include "hearthStone.h"
#include "icarus.h"
#include "kaleon.h"
#include "madBerserker.h"
#include "sylphid.h"
#include "zagamon.h"
#include "flameDragon.h"
#include "naias.h"
#include "gate.h"

class ItemScene : public gameNode
{
	gate* _gate;

	int _randNum;
	image* _boxImg;
	RECT _boxRc;
	int _boxIndex;
	int _count;
	int _boxCount;

	bool _fOn;
	bool _boxOn;

	bool _FadeOut;
	bool _FadeIn;

	int _Alpha;

	vector<itemBase*> _vItem;
	vector<essenceBase*> _vEssence;

	RECT minimapRc;
	RECT minimapPlayerRc;
	RECT minimapGateRc;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	void openBox();

	void minimapUpdate(image* originalField, image* minimapField);
	void minimapRender(image* minimapField);

	ItemScene() {}
	~ItemScene() {}
};

