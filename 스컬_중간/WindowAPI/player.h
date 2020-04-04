#pragma once

#include "gameNode.h"
#include "playerSkullBase.h"
#include "nomalSkull.h"
#include "chiefGuard.h"
#include "hunter.h"
#include "userInt.h"
#include "headDarkPaladin.h"
#include "headHunter.h"
#include "headNormalSkul.h"
#include "headReaper.h"

class Player : public gameNode
{
	playerSkullBase* _MainSkul;

	POINT _positionBefore;
	float _vectorX;
	float _vectorY;

	vector<itemBase*> _vSkul;
	vector<itemBase*> _vItem;
	vector<essenceBase*> _vEssence;

	string _currentSkul;

	userInt* _ui;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void KeyAction();

	void camMove(image* bgImg);

	POINT getPlayerPositionBefore() { return _positionBefore; }
	void setPlayerPositionBefore(POINT positionBefore) { _positionBefore = positionBefore; }

	playerSkullBase* getPlayerClass() { return _MainSkul; }

	void changeSkul();

	void playerItemPush(itemBase* item) { _vItem.push_back(item); }
	void playerEssencePush(essenceBase* essence) { _vEssence.push_back(essence); }
	void playerSkulPush(itemBase* skul) { _vSkul.push_back(skul); }
	void playerEssenceRemove() { _vEssence.clear(); }

	vector<itemBase*> getPlayerSkulV() { return _vSkul; }
	vector<itemBase*> getPlayerItemV() { return _vItem; }
	vector<essenceBase*> getPlayerEssenceV() { return _vEssence; }

	Player() {}
	~Player() {}
};