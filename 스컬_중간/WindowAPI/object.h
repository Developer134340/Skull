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
	POINT _position;	//������Ʈ ��ġ
	objectState _state;	//������Ʈ�� ����(�Ϲ�/���� 1��/�μ���)
	RECT _rc;			//�浹 ��Ʈ
	bool _potionDrop;	//���� ����� Ȯ��(70%)
	string _key;		//������Ʈ�� ������ Ű ��
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