#pragma once

#include "gameNode.h"

class essenceBase : public gameNode
{
protected:
	const char* _grade;				//���(�븻, ����, ����ũ, ��������)
	const char* _name;				//���� �̸�
	const char* _introduction;		//���� ����
	const char* _skillIntroduction;	//���� ��ų ����
	image* _essenceImg;				//�����̹���
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

	//���Ŀ� ������ �ٲ㳢�� �Լ� �߰�

	void dropEssence(POINT pos);
	void getEssence(RECT playerRect);	//render�Լ�
	void showEssence(RECT essencePosition);
	

	essenceBase() {}
	~essenceBase() {}
};

