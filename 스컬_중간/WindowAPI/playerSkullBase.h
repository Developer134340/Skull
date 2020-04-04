#pragma once

#include "gameNode.h"

enum Edirection
{
	������,
	����
};

enum Estate
{
	���,
	����,
	����,
	��������,
	������,
	���,
	�̵�,
	���Ÿ�,
	�ǰ�,
	�����̵�,
	��ų1,
	��ų2
};
enum Effect
{
	����,
	�������,
	��������,
	��������
};
enum DILL
{
	��Ÿ,
	��ų��,
	��ų��
};

class playerSkullBase : public gameNode
{
protected:

	RECT rc;		//ĳ���� ��Ʈ
	RECT Arc;		//���ݹ���
	int Stat;		//ĳ���� ����
	int direction;	//ĳ���� ����
	float Speed;	    //ĳ���� �̵��ӵ�
	float Jump;		//���� �ӵ�
	float dashSpeed; //��� ���ǵ�
	int x, y;		//ĳ���� ��ǥ
	float Gravity;	//�߷°�
	int What;       //??

	int dashCount;	//��� ī��Ʈ
	int jumpCount;	//���� ī��Ʈ
	int dashDistance;
	
	int MaxAttackCount; //���� �ƽ��ѹ�
	int AttackCount;	//���� ī��Ʈ
	int AttackDel;		//���� ������
	
	bool AttackColl;	//�浹 ���� ??
	bool Attack;		//���� ����
	bool Combo;			//�޺� ���� ?? 
	bool dash;			//��� ����
	bool JumpAttack;
	bool Jumping;          
	bool JumpCountTrue; //���� ī��Ʈ ���� ����

	int MaxHp;		//�ִ�ü��
	int NowHp;		//ü��
	bool Skill2Null;	//�ι�° ��ų �ֳ� ����
	int ICount;		//�̹��� ī����
	int IIndex;		//�̹��� �ε���
	string name;	//�ɸ��� ���� �ֱ�
	string EfName;	//����Ʈ ���� �ֱ�; ������� NUll
	image* img;		//�ɸ��� �̹���
	image* JuDhDust;
	image* AttackEfect;
	RECT JpDhR;
	int EFS;
	int EX, EY;
	bool JpDhS;

	POINT _imagePosition;
	image* _PixelMap;

	bool head;
	bool weapon;
	
public:
	HRESULT init();
	void release();
	void update();
	void render();

	POINT getPlayerPosition();
	void setPlayerPositionX(int setX) { x = setX; }
	void setPlayerPositionY(int setY) { y = setY; }
	void setImagePositionX(int setX) { _imagePosition.x = setX; }
	void setImagePositionY(int setY) { _imagePosition.y = setY; }
	int getDirection() { return direction; }
	void setDirectionRight() { direction = ������; }
	POINT getImagePosition() { return _imagePosition; }
	int getMaxHP() { return MaxHp; }
	int getNowHP() { return NowHp; }

	void setWeapon() { weapon = true; }

	void setPixelMap(image* img)	{ _PixelMap = img; }

	//Ű�Ŵ��� ���==============================================================
	void Move(int key);
	void setStat(int _Stat)
	{
		if (weapon)
		{
			if (!head && _Stat == ��ų1) {}
			if (_Stat == ��ų2 && Skill2Null) {}
			else if (Stat != ��� && head && Stat != ���� && Stat != ��ų1 && Stat != ��ų2) { Stat = _Stat; }
		}
	}

	void JumpStat();
	void KeyUp() { if (Stat == �̵�) Stat = ���; }

	void DashStat()
	{	
		if (dashCount > 0 && dash && Stat !=�������� && Stat !=��ų1 && Stat!= ��ų2 && Stat!=����)
		{
			if (!JpDhS)
			{
				EX = x - _imagePosition.x;
				EY = y + 30 - _imagePosition.y;
				JpDhS = true;
				EFS = �������;
			}
			dashCount--;
			Stat = ���;
			dash = false;
		}
	}

	void AttackStat();

	void FrameIRender(string name, string EffectName);
	void FrameIUpdate(int ImageSpeed, int capeSpeed);//�̵��̳� ����Ҷ� ���
	//===========================================================================
	
	//Ű�Է� �� ���� ���===========================================================
	void DashAction(int ImageSpeed, int DashCount); //����Ҷ� ���
	void JumpAction(int ImageSpeed);				//�����Ҷ� ���
	
	//===========================================================================


	//�׽�Ʈ��=======================
	void FrameRender();
	RECT getRc() { return Arc; }
	RECT getPlayerRc() { return rc; }
	bool Colltrue() { return AttackColl; }


	void setReturn(bool Coll) { AttackColl = Coll; }
	

	virtual int DMG(RECT enemy) { return 0; }
	virtual bool DMGHead(RECT enemy) { return 0; }

	void YImageCheck() { if (direction == ������) { img->setFrameY(0); } else { img->setFrameY(1); } }
	//�׽�Ʈ��=======================


	bool getPlayerAttackColl() { return AttackColl; }
	RECT getPlayerArc() { return Arc; }
	void setPlayerHp(int newHp) { NowHp = newHp; }
	void setPlayerAttackColl(bool attackColl) { AttackColl = attackColl; }
	int getPlayerHp() { return NowHp; }
	string namecalling(string nameX) { return name = nameX; }

	playerSkullBase() {}
	~playerSkullBase() {}
};

