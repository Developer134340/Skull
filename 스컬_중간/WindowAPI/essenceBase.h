#pragma once

#include "gameNode.h"

class essenceBase : public gameNode
{
protected:
	const char* _grade;				//등급(노말, 레어, 유니크, 레전더리)
	const char* _name;				//정수 이름
	const char* _introduction;		//정수 설명
	const char* _skillIntroduction;	//정수 스킬 설명
	image* _essenceImg;				//정수이미지
	image* _essenceProfileImg;

	RECT _rc;
	POINT _position;
	float _gravity;
	bool _imageOn;
	bool _fireOn;
	int _attackCount;
	int _count;
	bool _dropOn;
	bool _essenceFon;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	const char* getEssenceGrade() { return _grade; }
	const char* getEssenceName() { return _name; }
	const char* getEssenceIntroduction() { return _introduction; }
	const char* getEssenceSkillIntroduction() { return _skillIntroduction; }


	image* getEssenceProfileImage() { return _essenceProfileImg; }
	image* getEssenceImg() { return _essenceImg; }

	RECT getEssenceRc() { return _rc; }
	POINT getEssencePosition() { return _position; }
	void setEssencePosition(POINT pos) { _position = pos; }

	bool getEssenceImageOn() { return _imageOn; }
	void setEssenceImageOn(bool imageOn) { _imageOn = imageOn; }
	void setEssenceFon(bool fon) { _essenceFon = fon; }

	bool getImageOn() {	return _imageOn; }

	virtual void fire(RECT playerRc, int playerDirection, POINT imagePosition);

	//추후에 아이템 바꿔끼는 함수 추가

	void dropEssence(POINT pos);
	void getEssence(RECT playerRect);	//render함수
	void showEssence(RECT essencePosition);
	

	essenceBase() {}
	~essenceBase() {}
};

