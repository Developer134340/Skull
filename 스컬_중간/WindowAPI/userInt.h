#pragma once
#include "gameNode.h"
#include "itemBase.h"
#include "gunpowderSword.h"
#include "hearthStone.h"
#include "icarus.h"
#include "kaleon.h"
#include "madBerserker.h"
#include "sylphid.h"
#include "zagamon.h"
#include "essenceBase.h"
#include "flameDragon.h"
#include "naias.h"


class userInt :
	public gameNode
{
	bool _tapOn;
	bool _f1On;
	int _hp;
	int _index;

	string _currentSkul;

	char test[100];
	char str[100];

	RECT textRc[4];

	vector<itemBase*> _vSkul;
	vector<itemBase*> _vItem;
	vector<essenceBase*> _vEssence;

	//----------------------ÅÇ ´­·¶À» ¶§

	RECT tabSkul[2];
	RECT tabEssence;
	RECT tabItem[6];

public:

	HRESULT init();
	void release();
	void update(string currentSkul, int hp, int maxHp, vector<itemBase*> vSkul, vector<itemBase*> vItem, vector<essenceBase*> vEssence);
	void render();

	bool getTabOn() { return _tapOn; }

	userInt() {}
	~userInt() {}
};

