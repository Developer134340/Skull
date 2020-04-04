#pragma once
#include "gameNode.h"
#include "player.h"
#include "itemBase.h"
#include "headDarkPaladin.h"
#include "headHunter.h"
#include "headReaper.h"
#include "flameDragon.h"
#include "naias.h"
#include "essenceBase.h"
#include "gate.h"

class SkullScene : public gameNode
{
	int _randNum;
	image* _tombImg;
	RECT _tombRc;
	int _tombIndex;
	int _count;
	int _tombCount;

	bool _fOn;
	bool _tombOn;

	gate* _gate;

	bool _FadeOut;
	bool _FadeIn;

	int _Alpha;

	vector<itemBase*> _vSkul;

	RECT minimapRc;
	RECT minimapPlayerRc;
	RECT minimapGateRc;
	
public:
	HRESULT init();
	void release();
	void update();
	void render();
	
	void openTomb();

	//¹Ì´Ï¸Ê

	void minimapUpdate(image* originalField, image* minimapField);
	void minimapRender(image* minimapField);

	SkullScene() {}
	~SkullScene() {}
};

