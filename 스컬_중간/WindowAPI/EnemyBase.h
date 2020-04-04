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
	int Stat;		//����
	int	Direction;	//����
	float x, y;		// ��ǥ
	int Hp;			// ü��
	int Attck;		// ���ݷ�
	float Speed;	// �̵��ӵ�

	bool Live;		// ���� ����
	bool Agro;		// ���� ��׷�
	bool Acion;
	int delayCount;

	int ICount;		//�̹��� ī��Ʈ
	int IIndex;		//�̹��� �ε���
	int HitCount;	//���� �ð�
	RECT rc;		// ���� ��Ʈ
	RECT ATrc;		// ���� ���ݹ���
	RECT Arc;		// ���� ��׷ι���
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

	//�����ӷ�Ʈ
	void renderMonster(RECT rc,RECT Arc,RECT ATrc);
	//���̵�,��ũ �����ӿ�ũ
	void FrameMonsterI(int ImageSpeed);
	//�̹��� ����
	void ImageRender();

	inline void setPosition(POINT pos) 
	{ 
		x = pos.x; 
		y = pos.y; 
	}
	
	//��׷� ����
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

