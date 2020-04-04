#pragma once
#include "gameNode.h"

class itemBase : public gameNode
{
protected:

	const char* _grade;			//등급(노말, 레어, 유니크, 레전더리)
	const char* _name;			//아이템 이름
	const char* _introduction;	//아이템 설명
	image* _itemImg;			//아이템 이미지
	image* _itemInvenImg;		//인벤토리용 아이템 이미지
	image* _itemProfileImg;		//인벤토리 프로필 이미지
	image* _skulProfileImg;

	RECT _rc;
	POINT _position;
	float _gravity;
	bool _imageOn;
	bool _dropOn;
	bool _itemFon;

	//능력치 구현은 나중에
	//아이템 장착 함수는 메인게임에 

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	const char* getItemGrade() { return _grade; }
	const char* getItemName() { return _name; }
	const char* getItemIntroduction() { return _introduction; }
	image* getItemImage() { return _itemImg; }
	image* getItemInvenImage() { return _itemInvenImg; }
	image* getItemProfileImage() { return _itemProfileImg; }
	image* getSkulProfileImage() { return _skulProfileImg; }

	RECT getItemRc() { return _rc; }
	POINT getItemPoint() { return _position; }
	void setItemPoint(POINT pos) { _position = pos; }
	void setItemFon(bool fon) { _itemFon = fon; }

	void dropItem(POINT pos);
	bool getItemImageOn() { return _imageOn; }
	void setItemImageOn(bool imageOn) { _imageOn = imageOn; }
	void getItem(RECT playerRect);
	void showItem(RECT itemPosition);


	itemBase() {}
	~itemBase() {}

};