#pragma once
#include "gameNode.h"

class itemBase : public gameNode
{
protected:

	const char* _grade;			//���(�븻, ����, ����ũ, ��������)
	const char* _name;			//������ �̸�
	const char* _introduction;	//������ ����
	image* _itemImg;			//������ �̹���
	image* _itemInvenImg;		//�κ��丮�� ������ �̹���
	image* _itemProfileImg;		//�κ��丮 ������ �̹���
	image* _skulProfileImg;

	RECT _rc;
	POINT _position;
	float _gravity;
	bool _imageOn;
	bool _dropOn;
	bool _itemFon;

	//�ɷ�ġ ������ ���߿�
	//������ ���� �Լ��� ���ΰ��ӿ� 

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