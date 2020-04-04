#include "stdafx.h"
#include "Tree.h"
#include "player.h"

HRESULT Tree::init()
{
	EnemyBase::init();

	Stat = 대기;
	Direction = rand() % 2;	//방향
	x = WINSIZEX / 2;
	y = WINSIZEY / 2;		// 좌표
	Hp = 50;			// 체력
	maxhp = Hp;
	Attck = 15;		// 공격력
	name = "Tree";
	Live = true;
	Speed = 1.f;
	damageP = false;

	img = IMAGEMANAGER->findImage("TreeIdle");

	return S_OK;
}

void Tree::release()
{
}

void Tree::update()
{
	EnemyBase::update();
	if (Live)
	{
		RECT temp;
		AgroJudgment();
		AI();
		Hpbar();

		if (IntersectRect(&temp, &_player->getPlayerClass()->getPlayerRc(), &ATrc) && !damageP && Stat == 공격 && img->getFrameX() >= 1)
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

	FrameMonsterI(15);
	//================================================================
	rc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth(), img->getFrameHeight());		// 몬스터 렉트
	ATrc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth(), img->getFrameHeight()); 		// 몬스터 공격범위
	Arc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth() + 400, img->getFrameHeight() + 400);		// 몬
	//================================================================
}

void Tree::render()
{
	EnemyBase::render();
	renderMonster(rc, Arc, ATrc);
	ImageRender();
	hpbarrender();
}

void Tree::AI()
{
	float distance = getDistance(_player->getPlayerClass()->getPlayerPosition().x, _player->getPlayerClass()->getPlayerPosition().y,
		x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y);
	if (Agro)
	{	
		{
			if (!Acion)
			{
				if (_player->getPlayerClass()->getPlayerPosition().x > x)
				{
					Direction = 오른쪽;
				}
				else if (_player->getPlayerClass()->getPlayerPosition().x < x) { Direction = 왼쪽; }
			}
			if (distance > 60)
			{
				if (!Acion)
				{
					Stat = 이동;
				}
			}
			else
			{
				if (!Acion )
				{
					Stat = 공격;
				}
			Attack();
			}
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
	else
	{
		if (Stat == 대기)
		{
			static int redyCount = 0;
			redyCount++;
			

			if (redyCount % 70 == 0)
			{
				Direction = rand() % 2;
				Stat = 이동;
			}
			
		}
		if (Stat == 이동)
		{
			static int moveCount = 0;
			moveCount++;
			if (Direction == 오른쪽) { x += Speed; }
			else { x -= Speed; }
			
			if (moveCount % RND->range(120,170) == 0)
			{
				Stat = 대기;
			}
		}

	}

}

void Tree::Attack()
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


		if (IIndex == 0)
		{
			if (ICount % 40 == 0)
			{
				IIndex++;
			}
		}
		else
		{
			if (ICount % 20 == 0)
			{
				IIndex++;
				if (IIndex > img->getMaxFrameX())
				{
					IIndex = 0;
					Stat = 대기;
					damageP = false;
				}
				img->setFrameX(IIndex);
			}
		}
	}
}
