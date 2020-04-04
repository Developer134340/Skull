#pragma once

#include "EnemyBase.h"
#include "player.h"

#define boll 4

enum bossStat
{
	��������,
	�������,
	�����߻�,
	������ȭ,
};
struct hand
{
	RECT rc;
	int x, y;
	image* I;
	int ID;
	int C;

	int fx, fy;
	RECT frc;
	image* FI;
	int FID;
	int FC;
	bool EF;
	bool goEF;
};
struct body
{
	RECT rc;
	int x, y;
	image* I;
	int ID;
	int C;
};
struct Jaw
{
	RECT rc;
	int x, y;
	image* I;
	int ID;
	int C;
};
struct head
{
	RECT rc;
	int x, y;
	image* I;
	int ID;
	int C;
};
struct EF
{
	RECT rc;
	int x, y;
	image* I;
	int ID;
	int C;
};

struct energeBomb
{
	float x, y;
	float speed;
	float angle;
	RECT rc;
	bool fire;
	bool crush;
	int alpha;
	int index;
	int count;
	image* I;
};

class Boss : public EnemyBase
{
private:
	body _body;
	hand _hand[2];
	Jaw _jaw;
	head _head;
	EF _EF;
	energeBomb En;
	vector<energeBomb>_vEn;
	float G;
	char Cname[100];

	int ReadyCount;
	int dis;
	int handdis;
	int headdis;
	int firecount;

	//EFbool=============================================
	bool Spark;
	bool Groggy;
	bool Stfire;
	bool gether;
	bool dieEf;
	bool getherUp;
	bool rebound;
	bool reboundBody;
	bool bodydown;
	bool fireup;
	//�����߻� ���=============================
	bool firedown;
	bool gethergo;
	bool reboundbool;

	

	//�����================
	
	bool appLh;
	bool appbody;
	bool appdown;
	bool appdowngo;
	bool appheadgo;
	int appheadDis;
	bool appjawgo;
	int appjawDis;
	bool headSH;
	bool handPush;
	bool handPull;
	int handDis;
	bool appjawUP;
	bool appheadUP;
	


	char g[100];
	char s[100];
	char st[100];
	char one[100];
	char two[100];

	char ST[100];
	char Spa[100];
	char get[100];
	char handN[100];
	char headN[100];
	
public:

	HRESULT init();
	void release();
	void update();
	void render();


	void findImage();
	void renderBoss();
	void AppBoss();
	void HandDown();
	void AI();
	void hp();

	void PlayerBossAttack();
	void fireAction();


	Boss() {}
	~Boss() {}
};

