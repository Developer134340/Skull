#pragma once

#include "gameNode.h"

enum Edirection
{
	오른쪽,
	왼쪽
};

enum Estate
{
	대기,
	공격,
	점프,
	점프공격,
	떨어짐,
	대시,
	이동,
	원거리,
	피격,
	순간이동,
	스킬1,
	스킬2
};
enum Effect
{
	없음,
	대시이펙,
	점프이펙,
	공격이펙
};
enum DILL
{
	평타,
	스킬원,
	스킬투
};

class playerSkullBase : public gameNode
{
protected:

	RECT rc;		//캐릭터 렉트
	RECT Arc;		//공격범위
	int Stat;		//캐릭터 상태
	int direction;	//캐릭터 방향
	float Speed;	    //캐릭터 이동속도
	float Jump;		//점프 속도
	float dashSpeed; //대시 스피드
	int x, y;		//캐릭터 좌표
	float Gravity;	//중력값
	int What;       //??

	int dashCount;	//대시 카운트
	int jumpCount;	//점프 카운트
	int dashDistance;
	
	int MaxAttackCount; //어택 맥스넘버
	int AttackCount;	//어택 카운트
	int AttackDel;		//어택 딜레이
	
	bool AttackColl;	//충돌 가능 ??
	bool Attack;		//공격 가능
	bool Combo;			//콤보 가능 ?? 
	bool dash;			//대시 가능
	bool JumpAttack;
	bool Jumping;          
	bool JumpCountTrue; //점프 카운트 증가 여부

	int MaxHp;		//최대체력
	int NowHp;		//체력
	bool Skill2Null;	//두번째 스킬 있냐 없냐
	int ICount;		//이미지 카운터
	int IIndex;		//이미지 인덱스
	string name;	//케릭터 직업 넣기
	string EfName;	//이펙트 직업 넣기; 공용사용시 NUll
	image* img;		//케릭터 이미지
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
	void setDirectionRight() { direction = 오른쪽; }
	POINT getImagePosition() { return _imagePosition; }
	int getMaxHP() { return MaxHp; }
	int getNowHP() { return NowHp; }

	void setWeapon() { weapon = true; }

	void setPixelMap(image* img)	{ _PixelMap = img; }

	//키매니저 사용==============================================================
	void Move(int key);
	void setStat(int _Stat)
	{
		if (weapon)
		{
			if (!head && _Stat == 스킬1) {}
			if (_Stat == 스킬2 && Skill2Null) {}
			else if (Stat != 대시 && head && Stat != 공격 && Stat != 스킬1 && Stat != 스킬2) { Stat = _Stat; }
		}
	}

	void JumpStat();
	void KeyUp() { if (Stat == 이동) Stat = 대기; }

	void DashStat()
	{	
		if (dashCount > 0 && dash && Stat !=점프공격 && Stat !=스킬1 && Stat!= 스킬2 && Stat!=공격)
		{
			if (!JpDhS)
			{
				EX = x - _imagePosition.x;
				EY = y + 30 - _imagePosition.y;
				JpDhS = true;
				EFS = 대시이펙;
			}
			dashCount--;
			Stat = 대시;
			dash = false;
		}
	}

	void AttackStat();

	void FrameIRender(string name, string EffectName);
	void FrameIUpdate(int ImageSpeed, int capeSpeed);//이동이나 대기할때 사용
	//===========================================================================
	
	//키입력 후 동작 사용===========================================================
	void DashAction(int ImageSpeed, int DashCount); //대시할때 사용
	void JumpAction(int ImageSpeed);				//점프할때 사용
	
	//===========================================================================


	//테스트용=======================
	void FrameRender();
	RECT getRc() { return Arc; }
	RECT getPlayerRc() { return rc; }
	bool Colltrue() { return AttackColl; }


	void setReturn(bool Coll) { AttackColl = Coll; }
	

	virtual int DMG(RECT enemy) { return 0; }
	virtual bool DMGHead(RECT enemy) { return 0; }

	void YImageCheck() { if (direction == 오른쪽) { img->setFrameY(0); } else { img->setFrameY(1); } }
	//테스트용=======================


	bool getPlayerAttackColl() { return AttackColl; }
	RECT getPlayerArc() { return Arc; }
	void setPlayerHp(int newHp) { NowHp = newHp; }
	void setPlayerAttackColl(bool attackColl) { AttackColl = attackColl; }
	int getPlayerHp() { return NowHp; }
	string namecalling(string nameX) { return name = nameX; }

	playerSkullBase() {}
	~playerSkullBase() {}
};

