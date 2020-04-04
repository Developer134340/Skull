#include "stdafx.h"
#include "Knight.h"
#include "player.h"

HRESULT Knight::init()
{
	EnemyBase::init();

	Stat = 대기;
	Direction = rand() % 2;	//방향
	Hp = 80;			// 체력
	maxhp = Hp;
	Attck = 10;		// 공격력
	name = "Knight";
	Live = true;
	Speed = 2.f;

	img = IMAGEMANAGER->findImage("KnightIdle");

	return S_OK;
}

void Knight::release()
{
}

void Knight::update()
{
	EnemyBase::update();
	if (Live)
	{
		AgroJudgment();
		AI();
		PlayerEnemyAttack();
		EnemyPlayerAttack(ATrc, Attck);
		Hpbar();
	}
	FrameMonsterI(6);

	if (Hp <= 0)
	{
		Hp = 0;
		Live = false;
	}

	//================================================================
	rc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth(), img->getFrameHeight());		// 몬스터 렉트
	ATrc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth(), img->getFrameHeight()); 		// 몬스터 공격범위
	Arc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth() + 460, img->getFrameHeight() + 460);		// 몬스터 어그로범위
	//================================================================
}

void Knight::render()
{
	EnemyBase::render();
	ImageRender();
	renderMonster(rc, Arc, ATrc);
	hpbarrender();
}

void Knight::AI()
{
	if (Agro)
	{
		float distance = getDistance(_player->getPlayerClass()->getPlayerPosition().x, _player->getPlayerClass()->getPlayerPosition().y, 
			x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y);

		{
			if (!Acion)
			{
				if (_player->getPlayerClass()->getPlayerPosition().x > x + _player->getPlayerClass()->getImagePosition().x)
				{
					Direction = 오른쪽;
				}
				else if (_player->getPlayerClass()->getPlayerPosition().x < x + _player->getPlayerClass()->getImagePosition().x) { Direction = 왼쪽; }
			}
			if (distance > 50)
			{
				if (!Acion)
				{
					Stat = 이동;				
				}
			}
			else
			{
				if (!Acion)
				{
					Stat = 공격;				
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

void Knight::Attack()
{	
	if (Stat == 공격)
	{
		img = IMAGEMANAGER->findImage(name + "Attack");
		ICount++;
		Acion = true;
		if (Direction == 오른쪽)
		{
			img->setFrameY(0);
		}
		else { img->setFrameY(1); }

		
		if (IIndex == 0)
		{
			if (ICount % 80 == 0)
			{
				IIndex++;
			}
		}
		else if (IIndex == 4)
		{
			if (ICount % 50 == 0)
			{
				IIndex++;
			}
		}
		else
		{
			if (IIndex < 4)
			{
				if (Direction == 왼쪽) { x -= 3; }
				else { x += 3; }
			}
			if (ICount % 8 == 0)
			{
				IIndex++;
				if (IIndex > img->getMaxFrameX())
				{
					IIndex = 0;
					Stat = 대기;
					enemyAttackColl = false;
				}
				img->setFrameX(IIndex);
			}
		}
		if (IIndex == 2)
		{
			enemyAttackColl = true;

		}
	}	
}
