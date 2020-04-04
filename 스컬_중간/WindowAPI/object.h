#pragma once

#include "gameNode.h"
#include "potion.h"

struct tagSplinter
{
	RECT rc;
	RECT exRc;
	float height;
	float angle;
	float gravity;
};

enum objectState
{
	NORMAL, 
	ATTACKED,
	CRUSHED,
	ATTACKING,
	CRUSHING
};

class object : public gameNode
{
	POINT _position;	//오브젝트 위치
	objectState _state;	//오브젝트의 상태(일반/공격 1번/부서짐)
	RECT _rc;			//충돌 렉트
	bool _potionDrop;	//포션 드랍할 확률(70%)
	string _key;		//오브젝트를 구분할 키 값
	image* _objectImg;
	int _hp;
	bool _damaging;
	bool _changing;
	int _damageCount;

	POINT _exImagePosition;
	POINT _imagePosition;
	
	vector<tagSplinter> _vSplinter;

	potionSize _potionKey;

	int _index;
	int _count;
		
public:

	HRESULT init(string key, POINT position);
	void release();
	void update(POINT imagePosition);
	void render();

	void Scattering(int k);

	void setObjectState(objectState os) { _state = os; }
	objectState getObjectState() { return _state; }
	RECT getObjectRect() { return _rc; }
	
	int getObjectHp() { return _hp; }
	void setObjectHp(int hp) { _hp = hp; }

	bool getObjectDamaging() { return _damaging; }
	void setObjectDamaging(bool d) { _damaging = d; }

	void setObjectDamageCount(int count) { _damageCount = count; }

	potionSize getObjectPotionSize() { return _potionKey; }
	bool getObjectPotionDrop() { return _potionDrop; }
	void setObjectPotionDrop(bool d) { _potionDrop = d; }

	vector<tagSplinter> getSplinterVector() { return _vSplinter; }
	void splinterPushBack(tagSplinter splinter) { _vSplinter.push_back(splinter); }
	void crashObject(RECT playerRc, int playerAtk, int playerState);

	object() {}
	~object(){}
};