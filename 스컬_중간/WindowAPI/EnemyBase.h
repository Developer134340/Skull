#pragma once

#include "gameNode.h"

class Player;

struct BossHP
{
	int x, y;
	int Hpbar;
	RECT rc;
	image* Dmgbar;
	image* Frame;
	image* HPbar;
	image* HPbarBg;
	image* nameBg;
	RECT namerc;
};

class EnemyBase : public gameNode
{
protected:
	int Stat;		//상태
	int	Direction;	//방향
	float x, y;		// 좌표
	int Hp;			// 체력
	int Attck;		// 공격력
	float Speed;	// 이동속도

	bool Live;		// 몬스터 생존
	bool Agro;		// 몬스터 어그로
	bool Acion;
	int delayCount;

	int ICount;		//이미지 카운트
	int IIndex;		//이미지 인덱스
	int HitCount;	//경직 시간
	RECT rc;		// 몬스터 렉트
	RECT ATrc;		// 몬스터 공격범위
	RECT Arc;		// 몬스터 어그로범위
	int alpha;
	string name;
	image* img;

	BossHP _BHP;

	bool enemyAttackColl;
	bool enemyCantAttack;

	image* Hpframe;
	image* Hpbg;
	image* hpbar;
	int hpx, hpy;
	RECT hprc;
	int maxhp;
	int hpframe;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//프레임렉트
	void renderMonster(RECT rc,RECT Arc,RECT ATrc);
	//아이들,워크 프레임워크
	void FrameMonsterI(int ImageSpeed);
	//이미지 렌더
	void ImageRender();

	inline void setPosition(POINT pos) 
	{ 
		x = pos.x; 
		y = pos.y; 
	}
	
	//어그로 판정
	void AgroJudgment();

	void PlayerEnemyAttack();
	void EnemyPlayerAttack(RECT rc, int attack);

	void setEnemyHp(int newHp) { Hp = newHp; }
	string namecall(string nameX) { return name = nameX; }

	void Hpbar();
	void hpbarrender();

	EnemyBase() {};
	~EnemyBase() {};
};

