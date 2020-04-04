#include "stdafx.h"
#include "Gard.h"
#include "player.h"

HRESULT Gard::init()
{
	EnemyBase::init();

	Stat = 대기;
	Direction = rand() % 2;	//방향
	x = WINSIZEX / 2;
	y = WINSIZEY / 2;		// 좌표
	Hp = 150;			// 체력
	maxhp = Hp;
	Attck = 20;		// 공격력
	name = "Gard";
	Live = true;
	Speed = 2.f;
	dashDmg = 20;
	DashSpeed = 10.f;
	AttackCount = 0;
	Effect = false;
	damageP = false;

	TackleCount=0;
	TackleIndex=0;

	img = IMAGEMANAGER->findImage("GardIdle");
	TackleI = IMAGEMANAGER->findImage("TackleEffect");
	
	return S_OK;
}

void Gard::release()
{
}

void Gard::update()
{
	EnemyBase::update();
	RECT temp;
	if (Live)
	{
		AgroJudgment();
		AI();
		PlayerEnemyAttack();
		if (IntersectRect(&temp, &_player->getPlayerClass()->getPlayerRc(), &ATrc) && !damageP && img->getFrameX() > 2 && img->getFrameX() < 6 && Stat == 공격 || IntersectRect(&temp, &_player->getPlayerClass()->getPlayerRc(), &ATrc) && !damageP && Stat == 스킬1 && Effect)
		{
			_player->getPlayerClass()->setPlayerHp(_player->getPlayerClass()->getPlayerHp() - Attck);
			damageP = true;
		}

	}
	if (Hp <= 0)
	{
		Hp = 0;
		Live = false;
	}
	FrameMonsterI(20);

	//================================================================
	rc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth(), img->getFrameHeight());		// 몬스터 렉트
	ATrc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth(), img->getFrameHeight()); 		// 몬스터 공격범위
	Arc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth() + 400, img->getFrameHeight() + 400);		// 몬스터 어그로범위
	TackleRc = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());
	//================================================================
}

void Gard::render()
{
	EnemyBase::render();
	renderMonster(rc, Arc, ATrc);
	ImageRender();

	if (Effect)
	{
		TackleI->frameRender(getMemDC(), TackleRc.left, TackleRc.top);
	}
	hpbarrender();
}

void Gard::AI()
{
	if (Agro)
	{
		float distance = getDistance(_player->getPlayerClass()->getPlayerPosition().x, _player->getPlayerClass()->getPlayerPosition().y,
			x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y);
		{
			if (!Acion)
			{
				if (_player->getPlayerClass()->getPlayerPosition().x > x)
				{
					Direction = 오른쪽;
				}
				else if (_player->getPlayerClass()->getPlayerPosition().x < x) { Direction = 왼쪽; }
			}
			if (distance > 150)
			{
				if (!Acion)
				{
					if (AttackCount == 0) { Stat = 스킬1; AttackCount = 1; }
					else { Stat = 이동; }	  
				}
			}
			else
			{
				if (!Acion)
				{
					if (AttackCount == 0) { Stat = 스킬1; AttackCount = 1; }
					else { Stat = 공격; AttackCount = 0; }
				}
			}
			Attack();
		}

		if (Stat == 이동 && Direction == 오른쪽) 
		{
			x += Speed;
		}
		else if (Stat == 이동 && Direction == 왼쪽)
		{
			x -= Speed;
		}
	}
}

void Gard::Attack()
{
	if (Stat == 공격)
	{
		static int ICount = 0;
		static int IIndex = 0;
		img = IMAGEMANAGER->findImage(name + "Attack");
		ICount++;
		Acion = true;

		if (Direction == 오른쪽)
		{
			img->setFrameY(0);
		}
		else { img->setFrameY(1); }

		if (IIndex == 2 || IIndex == 5)
		{
			if (ICount % 60 == 0)
			{
				IIndex++;
			}
		}
		else
		{
			if (ICount % 10 == 0)
			{
				IIndex++;
				if (IIndex > img->getMaxFrameX())
				{
					IIndex = 0;
					ICount = 0;
					Stat = 대기;
					damageP = false;
				}
				img->setFrameX(IIndex);
			}
		}
	}
	if (Stat == 스킬1)
	{
		static int ICount = 0;
		static int IIndex = 0;
		img = IMAGEMANAGER->findImage(name + "Takle");
		ICount++;
		Acion = true;

		if (Direction == 오른쪽)
		{
			img->setFrameY(0);
		}
		else { img->setFrameY(1); }

		if (IIndex == 0)
		{
			if (ICount % 100 == 0)
			{
				IIndex++;
			}
		}
		else if (IIndex == 1)
		{

			Effect = true;
			if (Direction == 오른쪽) { x += DashSpeed; }
			else { x -= DashSpeed; }
			
			if (ICount % 70 == 0)
			{
				IIndex++;
			}
			
		}
		else
		{
			Effect = false;
			
			if (ICount % 30 == 0)
			{
				IIndex++;
				if (IIndex > img->getMaxFrameX())
				{
					IIndex = 0;
					ICount = 0;
					damageP = false;
					Stat = 대기;
				}		
			}
		}
		img->setFrameX(IIndex);
	}

	if(Effect)
	{	
		TackleCount++;
		
		if (Direction == 오른쪽) { TackleI->setFrameY(0); }
		else { TackleI->setFrameY(1); }
		if (TackleCount % 5 == 0)
		{
			TackleIndex++;
			
		}
		TackleI->setFrameX(TackleIndex);
	}
	else
	{
		TackleIndex = 0;
		TackleCount = 0;
	}
}

